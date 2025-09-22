import cs50

# ask user for card no.
while (True):
    card = cs50.get_string("Number: ")
    if int(card) > 1:
        break

# count number of digits
digits = len(card)

# checksum
a = 0
b = 0
# sum of all alternate digits
for i in range(len(card) - 1, -1, -2):
    a = a + int(card[i])

# sum of all remaining digits*2
for j in range(len(card) - 2, -1, -2):
    if (int(card[j]) * 2) >= 10:
        m = int(card[j]) * 2
        b = b + (m % 10) + ((m - (m % 10)) / 10)
    else:
        b = b + (int(card[j]) * 2)
checksum = (a + b) % 10

# which card
if checksum == 0:
    if int(card[0]) == 3 and int(card[1]) in [4, 7] and digits == 15:
        print("AMEX")
    elif int(card[0]) == 5 and int(card[1]) in [1, 2, 3, 4, 5] and digits == 16:
        print("MASTERCARD")
    elif int(card[0]) == 4 and digits in [13, 16]:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
