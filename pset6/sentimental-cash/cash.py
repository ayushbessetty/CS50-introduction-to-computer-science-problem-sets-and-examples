from cs50 import get_float


while (True):
    cents = get_float("Change owed: ")
    if cents > 0:
        break

cents = cents * 100
# quarters
q = 0
while cents >= 25:
    q += 1
    cents = cents - 25

# dimes
d = 0
while cents >= 10:
    d += 1
    cents = cents - 10

# nickels
n = 0
while cents >= 5:
    n += 1
    cents = cents - 5

# pennies
p = 0
while cents >= 1:
    p += 1
    cents = cents - 1

coins = q + d + n + p
print(f"{coins}")
