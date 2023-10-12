# Getting the text from the user
text = input("Text: ")
# Defining variables and setting values
letters = sentences = 0.0
words = text.count(" ") + 1.0
sentences = float(text.count(".") + text.count("!") + text.count("?"))
for char in text:
    if char.isalpha():
        letters += 1.0
# Calculating the index
l = letters * 100 / words
s = sentences * 100 / words
index = round(l * 0.0588 - s * 0.296 - 15.8)
# Printing the result:
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
