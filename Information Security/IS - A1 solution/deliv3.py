import pocket_aes as aes


def split_to_blocks(data):
    plaintext = ''.join([f'{ord(c):08b}' for c in data])
    # Pad with null byte if needed
    if len(plaintext) % 16 != 0:
        plaintext += '00000000'
    return [int(plaintext[i:i+16], 2) for i in range(0, len(plaintext), 16)]


def decode_blocks(bitstring):
    data = ''
    for i in range(0, len(bitstring), 8):
        eight_bits = bitstring[i:i+8]
        if eight_bits != '00000000':  # discard padding if any
            data += chr(int(eight_bits, 2))
    return data


def generate_secret():
    key  = 0x149c
    instring = "Gentlemen, you can't fight in here. This is the war room."
    blocks = split_to_blocks(instring)

    ciphered = []
    for block in blocks:
        ciphertext = aes.encrypt(block, key)
        ciphered.append(ciphertext)
        print(f'{ciphertext:04x}', end=' ')
    print()


def main():
    # generate_secret()
    # return

    print('Reading encrypted file secret.txt...')
    with open('secret.txt', 'r') as f:
        ciphered = f.read().split()

    ciphered = [int(block, 16) for block in ciphered]

    key = input('Enter the decryption key: ')
    key = int(key, 16)

    text = ''
    for block in ciphered:
        decrypted = aes.decrypt(block, key)
        text += f'{decrypted:016b}'

    print(f"\nDecrypted Result\n{'-'*20}\n{decode_blocks(text)}\n{'-'*20}")


if __name__ == '__main__':
    main()
