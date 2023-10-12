# Getting info and defining variables
card = input("Number: ")
size = len(card)
luhn = 0
initial = int(card[0] + card[1])
# Luhn's Algorithm
# Even size
if size % 2 == 0:
    for o in range(0, size, 2):
        odd = int(card[o])
        odd = (odd * 2)
        for i in str(odd):
            luhn += int(i) 
    for e in range(1, size, 2):
        even = int(card[e])
        luhn += even
# Odd size
else:
    for o in range(1, size, 2):
        odd = int(card[o])
        odd = (odd * 2)
        for i in str(odd):
            luhn += int(i) 
    for e in range(0, size, 2):
        even = int(card[e])
        luhn += even
# Validating the card
if luhn % 10 != 0:
    print("INVALID")
elif (initial == 34 or initial == 37) and size == 15:
    print("AMEX")
elif (51 <= initial <= 55) and size == 16:
    print("MASTERCARD")
else:
    print("VISA")
