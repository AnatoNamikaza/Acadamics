import pocket_aes as aes


def main():
    text = input('Enter a text block: ')
    text = int(text, 16)

    nibbles = aes.split_nibbles(text)

    sub_result = aes.merge_nibbles(aes.sub_nibbles(nibbles, aes.sBox))
    print(f'SubNibbles({text:04x}) = {sub_result:04x}')

    shift_result = aes.merge_nibbles(aes.shift_row(nibbles))
    print(f'ShiftRow({text:04x}) = {shift_result:04x}')

    mix_result = aes.merge_nibbles(aes.mix_columns(nibbles, aes.mix_matrix))
    print(f'MixColumns({text:04x}) = {mix_result:04x}')

    key = input('\nEnter a key: ')
    key = int(key, 16)

    [k1, k2] = aes.key_schedule(key)
    [k1, k2] = [aes.merge_nibbles(k1), aes.merge_nibbles(k2)]
    print(f'GenerateRoundKeys({key:04x}) = ({k1:04x}, {k2:04x})')


if __name__ == '__main__':
    main()
