from utils import generateMatrix, readFileMatrix
from constants import CSV, LATEX
from time import process_time
from algorithms import CombAlg, antAlg
import matplotlib.pyplot as plt

def testTime():
    try:
        sizeStart = int(input("\n\nВведите начальный размер матрицы: "))
        sizeEnd = int(input("Введите конечный размер матрицы: "))
        if (sizeStart > sizeEnd or sizeStart < 0 or sizeEnd < 0):
            raise Exception
    except:
        print("Неправильные размеры матрицы!")
        return
    timeFullCombinations = []
    timeAntAlg = []
    sizes = [i for i in range(sizeStart, sizeEnd + 1)]
    count = 0
    print()

    for size in sizes:
        count += 1
        matrix = generateMatrix(size, 1, 2)

        start = process_time()
        CombAlg(matrix, size)
        end = process_time()
        timeFullCombinations.append(end - start)

        start = process_time()
        antAlg(matrix, size, 0.5, 0.5, 0.5, 250)
        end = process_time()

        timeAntAlg.append(end - start)

        print("Progress: %3d%s" %((count / len(sizes)) * 100, "%"))

    # Table
    print("\n %s | %s | %s" %("Размер", "Время полного перебора", "Время муравьиного алгоритма"))
    print("-" * (8 + 1 + 24 + 1 + 29))

    for i in range(len(sizes)):
        print(" %6d | %22.6f | %27.6f" %(sizes[i], timeFullCombinations[i], timeAntAlg[i]))

    # For Latex
    f_latex = open("latex_table.txt", "w")

    for i in range(len(sizes)):
        f_latex.write("%4d & %10.6f & %10.6f \\\\ \\hline\n" %(sizes[i], timeFullCombinations[i], timeAntAlg[i]))

    f_latex.close()

    # Graph
    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, timeFullCombinations, label = "Полный перебор",marker='*')
    plot.plot(sizes, timeAntAlg, label="Муравьиный алгоритм")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Размер матрицы")

    plt.show()


def parametrization(type = CSV):
    alpha_arr = [num / 10 for num in range(1, 10,2)]
    k_eva_arr = [num / 10 for num in range(1, 10,2)]
    days_arr = [1, 5, 10,30,100]
    times = 10
    size = 10

    matrix1 = readFileMatrix("real.csv")
    matrix2 = readFileMatrix("gen.csv")

    optimal1 = CombAlg(matrix1, size)
    optimal2 = CombAlg(matrix2, size)

    file1 = open("parametrization_class1.txt", "w")
    file2 = open("parametrization_class2.txt", "w")

    count = 0
    count_all = len(alpha_arr) * len(k_eva_arr)

    print()

    for alpha in alpha_arr:
        beta = 1 - alpha
        for k_eva in k_eva_arr:
            count += 1

            for days in days_arr:
                results_1 = []
                results_2 = []
                for i in range(times):
                    res1 = antAlg(matrix1, size, alpha, beta, k_eva, days)
                    res2 = antAlg(matrix2, size, alpha, beta, k_eva, days)
                    results_1.append(res1)
                    results_2.append(res2)

                if (type == LATEX):
                    sep = " & "
                    ender = " \\\\"
                elif (type == CSV):
                    sep = ", "
                    ender = ""
                else:
                    sep = " | "
                    ender = ""
                res1 = max(results_1, key=lambda x: x[0])
                res2 = max(results_2, key=lambda x: x[0])
                str1 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                    % (alpha, sep, k_eva, sep, days, sep, optimal1[0], sep, res1[0] - optimal1[0], ender)

                str2 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                    % (alpha, sep, k_eva, sep, days, sep, optimal2[0], sep, res2[0] - optimal2[0], ender)

                file1.write(str1)
                file2.write(str2)

            print("Progress: %3d%s" %((count / count_all) * 100, "%"))

    file1.close()
    file2.close()