# asking user for height
import cs50
while (True):
    height = cs50.get_int("Height: ")
    if height > 0 and height < 9:
        break


def main():
    for i in range(height):
        print_rows(height - i, i + 1)


def print_rows(bricks, space):
    # print spaces
    for m in range(1, bricks, 1):
        print(" ", end="")
    for j in range(space):
        print("#", end="")
    print("")


if __name__ == "__main__":
    main()
