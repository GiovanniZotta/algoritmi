BOOK = "The Time Machine by H. G. Wells.txt"
WORDS = "words.txt"
SEP = ['--', ',', '.', ':', ';', '!', '?', '"', '\'']
words = set(w.strip().lower() for w in open(WORDS).readlines())

alphabet = [
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ';', ':', ',', '.', '!', '?', '"', '\'', '_', '{', '}'
]

def get_token_char(word):
    original_word = (word + '.')[:-1]
    word = list(word.lower())
    if "".join(word) not in words:
        for i in range(len(word)):
            for char in alphabet:
                original_char = original_word[i]
                word[i] = char
                if "".join(word) in words:
                    return original_char
                word[i] = original_char.lower()
    return None

TOKEN = ""
with open(BOOK) as f:
    i = 0
    for row in f:
        for sep in SEP:
            row = row.replace(sep, ' ')
        ww = row.split()
        for w in ww:
            i+=1
            char = get_token_char(w)
            if char != None:
                TOKEN += char
                print(f"{w} -> {char}")

print(TOKEN)
print(len(TOKEN))
print("Total words", i)
