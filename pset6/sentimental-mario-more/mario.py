from cs50 import get_int


def main():
    # get height
    while (True):
        height = get_int("Height: ")
        if height in range(1, 9):
            break

    for i in range(height):
        print_rows(height - i, i + 1)


def print_rows(spaces, heights):
    for m in range(1, spaces, 1):
        print(" ", end="")

    for n in range(heights):
        print("#", end="")

    print("  ", end="")

    for i in range(heights):
        print("#", end="")

    print()


if __name__ == "__main__":
    main()
