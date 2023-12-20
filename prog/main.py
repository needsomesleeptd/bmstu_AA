from utils import *

menu = '''Меню:
1. Полный перебор 
2. Муравьиный алгоритм 
3. Загрузить матрицу расстояний
4. Параметризация 
5. Замерить время 
6. Распечатать матрицу 
0. Выход 
Выбор: '''

if __name__ == '__main__':
    option = -1
    while (option != 0):
        option = 0
        try:
            option = int(input(menu))
        except:
            option = -1
        if (option == 1):
            parseFullCombinations()
        elif (option == 2):
            parseAntAlg()
        elif (option == 3):
            parseAll()
        elif (option == 4):
            parametrization(type = CSV)
        elif (option == 5):
            testTime()
        elif (option == 6):
            printMatrix()
        elif (option == -1):
            print("Спасибо, что пользовались этой программой!")
        else:
            print("Повторите ввод")