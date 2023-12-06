import random


# Test 1: complete-100
f1 = open("complete-100.txt", "w")
f1.write("100\n")
for i in range(100):
    for j in range(i + 1, 100):
        f1.write(str(i) + " " + str(j) + "\n")
f1.close()

# Test 2: complete-1500
f1 = open("complete-1500.txt", "w")
f1.write("1500\n")
for i in range(1500):
    for j in range(i + 1, 1500):
        f1.write(str(i) + " " + str(j) + "\n")
f1.close()

# Test 3: random-100
f1 = open("random-100.txt", "w")
f1.write("100\n")
pairs_count = 0
while pairs_count < 300:
    first = random.randrange(0, 100)
    second = random.randrange(0, 100)
    if first != second:
        f1.write(str(first) + " " + str(second) + "\n")
        pairs_count += 1
f1.close()