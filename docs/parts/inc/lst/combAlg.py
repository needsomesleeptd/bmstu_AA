def CombAlg(matrix, size):

    places = np.arange(size)
    placesCombinations = list()

    for combination in it.permutations(places):
        combArr = list(combination)
        placesCombinations.append(combArr)

    minDist = float("inf")

    for i in range(len(placesCombinations)):
        curDist = 0
        for j in range(size - 1):
            startCity = placesCombinations[i][j]
            endCity = placesCombinations[i][j + 1]
            curDist += matrix[startCity][endCity]

        if (curDist < minDist):
            minDist = curDist
            bestWay = placesCombinations[i]

    return minDist, bestWay