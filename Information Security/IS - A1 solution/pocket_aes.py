import sys

# S-Boxes, based on DES sbox-2 first row
sBox  = [0xa, 0x0, 0x9, 0xe, 0x6, 0x3, 0xf, 0x5,
         0x1, 0xd, 0xc, 0x7, 0xb, 0x4, 0x2, 0x8]
sBoxI = [0x1, 0x8, 0xe, 0x5, 0xd, 0x7, 0x4, 0xb,
         0xf, 0x2, 0x0, 0xc, 0xa, 0x9, 0x3, 0x6]

mix_matrix     = [1, 4, 4, 1]
inv_mix_matrix = [9, 2, 2, 9]

round_const = [0b1110, 0b1010]


def key_schedule(key):
    """Generate round keys from the master key"""
    w = [None] * 12

    w[0:4] = [key >> 12, (key >> 8) & 0xf, (key >> 4) & 0xf, key & 0xf]

    w[4] = w[0] ^ sBox[w[3]] ^ round_const[0]
    w[5] = w[1] ^ w[4]
    w[6] = w[2] ^ w[5]
    w[7] = w[3] ^ w[6]

    w[8] = w[4] ^ sBox[w[7]] ^ round_const[1]
    w[9] = w[5] ^ w[8]
    w[10] = w[6] ^ w[9]
    w[11] = w[7] ^ w[10]

    return [w[4:8], w[8:]]


def split_nibbles(n):
    return [n >> 12, (n >> 8) & 0xf, (n >> 4) & 0xf, n & 0xf]


def merge_nibbles(nibbles):
    return (nibbles[0] << 12) + (nibbles[1] << 8) + (nibbles[2] << 4) + nibbles[3]


def sub_nibbles(nibbles, sbox):
    return [sbox[e] for e in nibbles]


def shift_row(state):
    return [state[2], state[1], state[0], state[3]]


def mix_columns(state, matrix):
    def gmult(p1, p2):
        """multiply two polynomials in GF(2^4)/x^4 + x + 1"""
        p = 0
        while p2:
            if p2 & 0b1:
                p ^= p1
            p1 <<= 1
            if p1 & 0b10000:
                p1 ^= 0b10011  # x^4 + x + 1
            p2 >>= 1
        return p

    s = state
    m = matrix
    return [gmult(m[0], s[0]) ^ gmult(m[2], s[1]), gmult(m[1], s[0]) ^ gmult(m[3], s[1]),
            gmult(m[0], s[2]) ^ gmult(m[2], s[3]), gmult(m[1], s[2]) ^ gmult(m[3], s[3])]


def add_key(state, round_key):
    return [i ^ j for i, j in zip(state, round_key)]


def encrypt(ptext, key):
    """Encrypt a single block of plaintext"""
    state = split_nibbles(ptext)
    [k1, k2] = key_schedule(key)

    # Round 1
    state = sub_nibbles(state, sBox)
    state = add_key(state, k1)
    state = mix_columns(state, mix_matrix)
    state = shift_row(state)

    # Round 2
    state = sub_nibbles(state, sBox)
    state = add_key(state, k2)
    state = shift_row(state)

    return merge_nibbles(state)


def decrypt(ctext, key):
    """Decrypt a single block of ciphertext"""
    state = split_nibbles(ctext)
    [k1, k2] = key_schedule(key)

    # Round 2 inverse
    state = shift_row(state)
    state = add_key(state, k2)
    state = sub_nibbles(state, sBoxI)

    # Round 1 inverse
    state = shift_row(state)
    state = mix_columns(state, inv_mix_matrix)
    state = add_key(state, k1)
    state = sub_nibbles(state, sBoxI)

    return merge_nibbles(state)


def main():
    plain = 0x6f20
    key= 0x2a09
    ciphered = encrypt(plain, key)
    original = decrypt(ciphered, key)
    try:
        assert original == plain
        print('Pass')
    except:
        print('Fail')


if __name__ == '__main__':
    main()
