import cs50

# taking text from user
text = cs50.get_string("Text: ")

# length of text
l_text = len(text)

# number of words
word = 1
for i in range(l_text):
    if text[i].isspace():
        word += 1

# average of letters per 100 words
letter = 0
for i in range(l_text):
    if text[i].isalpha():
        letter += 1
L = (letter / word) * 100

# average of sentences per 100 words
sentences = 0
for i in range(l_text):
    if text[i] in ['.', '?', '!'] or (text[i] == ' ' and text[i + 1] == ' '):
        sentences += 1
S = (sentences / word) * 100

index = 0.0588 * L - 0.296 * S - 15.8
val = round(index)

if val < 1:
    print("Before Grade 1")
elif val > 16:
    print("Grade 16+")
else:
    print(f"Grade {val}")
