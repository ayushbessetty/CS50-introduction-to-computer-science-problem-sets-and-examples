people = {
    "yuli" : 5875869879,
    "dave" : 7689879323
}

name = input("name: ")
if name in people:
    print(f"number: {people[name]}")
else:
    print("not found")
