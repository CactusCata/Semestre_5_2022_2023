import os

def createThreeAddressCode(arrayOfInstructions):
    file = open("a.out", "w");
    file.write("#!/user/bin/python3")

    i = 0
    for instruction in arrayOfInstructions:
        if (instruction[0] == "BOOL"):
            file.write(f"t_{i} = {instruction[2]}\n")
            i += 1
        elif (instruction[0] == "NEGAT"):
            file.write(f"t_{i} = {instruction[2]} t_{i}\n")
        else:
            file.write(f"t_{i - 2} = t_{i - 2} {instruction[2]} t_{i - 1}\n")
            i -= 1

    file.write("print(t_0)")
    file.close()

    os.chmod("a.out", 511)
