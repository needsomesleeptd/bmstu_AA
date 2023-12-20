import numpy as np
from os import system
from random import randint
from algorithms import fullCombinationAlg, antAlgorithm

def generateMatrix(size, randStart, randEnd):
    matrix = np.zeros((size, size), dtype = int)

    for i in range(size):
        for j in range(size):
            if (i == j):
                num = 0
            else:
                num = randint(randStart, randEnd)
            matrix[i][j] = num
            matrix[j][i] = num

    return matrix

def generateMatrixFile(filename, size, randStart, randEnd):
    matrix = generateMatrix(size, randStart, randEnd)
    file = open("data/" + filename, "w")

    for i in range(size):
        string = ""
        for j in range(size):
            string += str(matrix[i][j])
            string += " "
        string += "\n"

        file.write(string)

    file.close()

    return "File %s generated\n" % filename

def readFileMatrix(filename):
    file_path = "data/" + filename
    mat = np.loadtxt(open(file_path, "rb"), delimiter=",", skiprows=0)
    return mat

def listDataFiles():
    system("ls \data > files.txt") # linux works
    f_files = open("files.txt", "r")
    files = f_files.read().split()
    f_files.close()

    print("\n\nДоступные файлы: ", len(files), " штук", )
    for i in range(len(files)):
        print("%d. %s" % (i + 1, files[i]))

    return files

def updateFile():
    try:
        option = int(input("\nДобавить новый файл? (1 - да, 2 - нет): "))
        if (option == 1):
            file_name = input("\nВведите имя файла: ")
            size = int(input("\nВведите размер матрицы: "))
            rand_start = int(input("\nВведите начальное число рандома: "))
            rand_end = int(input("\nВведите конечное число рандома: "))
            print(generateMatrixFile(file_name, size, rand_start, rand_end))
        elif (option == 2):
            files = listDataFiles()
            num_file = int(input("\nВыберите файл: ")) - 1
            size = int(input("\nВведите размер матрицы: "))
            rand_start = int(input("\nВведите начальное число рандома: "))
            rand_end = int(input("\nВведите конечное число рандома: "))
            print(generateMatrixFile(files[num_file], size, rand_start, rand_end))
        else:
            print("\nОшибка: Неверно выбран пункт")
        print("\n\nУспешно обновлен список файлов\n")
    except:
        print("\nОшибка: Неверно выбран пункт")

def printMatrix():
    files = listDataFiles()
    try:
        fileIndex = int(input("\nВыберите файл: ")) - 1
    except:
        print("Неверно выбран файл\n")
        return
    matrix = readFileMatrix(files[fileIndex])
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            print("%4d" % (matrix[i][j]), end = "")
        print()

def readMatrix():
    #files = listDataFiles()
    #fileIndex = int(input("\nВыберите файл: ")) - 1
    matrix = readFileMatrix("cities.csv")
    return matrix

def parseFullCombinations():
    matrix = readMatrix()
    size = len(matrix)
    result = fullCombinationAlg(matrix, size)
    print("\n\nМинимальная сумма пути = ", result[0],
            "\nПуть: ", result[1])

def readKoeffs():
    try:
        alpha = float(input("\n\nВведите коэффициент alpha: " ))
        beta = 1 - alpha
        k_evaporation = float(input("Введите коэффициент evaporation: " ))
        days = int(input("Введите кол-во дней: " ))
    except:
        print("Неправильный ввод!")
        alpha = 0
        beta = 1
        k_evaporation = 0.5
        days = 10

    return alpha, beta, k_evaporation, days

def parseAntAlg():
    matrix = readMatrix()
    size = len(matrix)
    alpha, beta, k_evaporation, days = readKoeffs()
    result = antAlgorithm(matrix, size, alpha, beta, k_evaporation, days)
    print("\n\nМинимальная сумма пути = ", result[0],
            "\nПуть: ", result[1])

def parseAll():
    matrix = readMatrix()
    size = len(matrix)
    alpha, beta, k_evaporation, days = readKoeffs()

    result = fullCombinationAlg(matrix, size)

    print("\n\nАлгоритм полного перебора \
            \n\tМинимальная длина пути = ", result[0],
            "\n\tПуть: ", result[1])

    result = antAlgorithm(matrix, size, alpha, beta, k_evaporation, days)

    print("\n\nМуравьиный алгоритм \
            \n\tМинимальная длина пути = ", result[0],
            "\n\tПуть: ", result[1])