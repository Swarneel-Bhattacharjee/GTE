def generateRandomFile():
    import random

    len = random.randrange(10, 30)
    delimit_len = random.randrange(5, 15)


    file = open("test.txt", "w")
    for i in range(len // delimit_len):
        s = ""

        for j in range(delimit_len) : 
            c = random.randrange(32, 127)
            s = s + chr(c)
        
        s += "\n"
        file.write(s);

    file.close()

def build():
    import sys
    import os

    filename = sys.argv[1]
    buildtype = sys.argv[2]

    print(f"Building {filename}")
    os.system(f"gcc main.c dependencies/scr.c dependencies/kb.c dependencies/mem.c dependencies/inputmode.c dependencies/normalmode.c \
    -o {filename} -lncurses -g")
    print("done")

    if buildtype == "test": 
        generateRandomFile()


if __name__ == "__main__":
    build()
