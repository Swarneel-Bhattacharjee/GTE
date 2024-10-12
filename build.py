def build():
    import sys
    import os

    filename = sys.argv[1]
    print(f"Building {filename}")
    os.system(f"gcc main.c dependencies/scr.c dependencies/kb.c dependencies/mem.c -o {filename} -lncurses -g")
    print("done")


if __name__ == "__main__":
    build()