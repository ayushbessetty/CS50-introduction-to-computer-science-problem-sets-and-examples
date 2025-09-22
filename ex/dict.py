people = [
    {"name" : "yuli", "number" : "468461161"},
    {"name" : "dave", "number" : "648413133"}
]

name = input("name: ")
for person in people:
    if person["name"] == name:
        number = person["number"]
        print(f"number: {number}")
        break
else:
    print("not found")
