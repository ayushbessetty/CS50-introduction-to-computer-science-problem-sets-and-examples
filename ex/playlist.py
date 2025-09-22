import csv

def main():
    min_tempo = int(input("min: "))
    max_tempo = int(input("max: "))

    playlist = []
    filename = "2018_100.csv"

    #read songs
    with open(filename) as file:
        file_reader = csv.DictReader(file) #reads the file line by line as dictionary
        for song in file_reader:
            if float(song["tempo"]) > min_tempo and float(song["tempo"]) < max_tempo:
                playlist.append(song)

    #add to play
    for song in playlist:
        print(song["name"])


main()
