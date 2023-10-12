from cs50 import get_int

# Getting the Height of Mario's Pyramid
height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")
        
    
# Defining the line
for a in range(height):
    for b in range(height):
        # Printing blank spaces
        if height - a > b + 1:
            print(" ", end="")
        # Printing blocks #
        else:
            print("#", end="")
    # Printing the gap
    print("  ", end="")
    # Printing the second part of Pyramid
    print("#" * (a + 1))