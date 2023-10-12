# Implement a program that identifies a person based on their DNA

# Importing librarys
from re import finditer
import csv
from sys import argv, exit

# Ensure correct usage
if len(argv) != 3:
    exit("Usage: python dna.py data.csv sequence.txt")
    
# Defining variables     
db = argv[1]
seq = argv[2]
strs = []
data = []

# Opening database.csv as list and dict
with open(db, "r") as database:
    tmp = csv.reader(database)
    for i in tmp:
        strs.append(i)
        
with open(db, "r") as database:
    reader = csv.DictReader(database)
    for row in reader:
        data.append(row)
        
# Getting the necessaries STRS
tmp = strs[0]
strs = []

for index in range(1, len(tmp)):
    strs.append(tmp[index]) 

# Opening the sequences.txt file
with open(seq, "r") as sequence:
    sequence = sequence.read()

# Defining the profile of the misterious person
person = {}
person["name"] = "Uknown"

for i in strs:
    person[i] = 1
    
b = -1

# Discovering the sequences of STR from the misterious DNA
for i in strs:
    counter = 0
    for match in finditer(i, sequence):
        a = match.start()
        if a == b:
            counter += 1
            if counter > person[i]:
                person[i] = (counter)
        else:
            counter = 1
        b = match.end()

# Matching the DNA with the database
total = 0
       
for p in data:
    for i in strs:
        if person[i] == int(p[i]):
            total += 1
    if total == len(strs):
        print(f'{p["name"]}.')
        exit(0)
    else:
        total = 0
print("No match.")
