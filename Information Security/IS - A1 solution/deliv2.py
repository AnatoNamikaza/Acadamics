import pocket_aes as aes


def main():
    ciphertext = input('Enter the ciphertext block: ')
    ciphertext = int(ciphertext, 16)

    key = input('Enter the key: ')
    key = int(key, 16)

    plaintext = aes.decrypt(ciphertext, key)

    print(f'Decrypted block: {plaintext:0x}')


if __name__ == '__main__':
    main()
