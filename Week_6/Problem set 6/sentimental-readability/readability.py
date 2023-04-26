# TODO


def main():
    text = input("Text: ")
    words = count_words(text)
    letters = count_letters(text)
    sentences = count_sentences(text)

    index = ((0.0588 * ((letters / float(words)) * 100)) -
             (0.296 * ((sentences / float(words)) * 100)) - 15.8) + 0.5

    if (index > 16):
        print("Grade 16+\n")
    elif (index < 0):
        print("Before Grade 1\n")
    else:
        print("Grade %d\n", index)


def count_words(text):
    count = 1

    for i in range(len(text)):
        if (text[i] == ' '):
            count += 1

    return count


def count_letters(text):
    count = 0

    for i in range(len(text)):
        if text[i].isalpha():
            count += 1

    return count


def count_sentences(text):
    count = 0

    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            count += 1
        if ((i+1) < len(text) and text[i + 1] == ' '):
            i += 1

    return count


main()
