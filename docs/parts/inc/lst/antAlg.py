def antAlg(matrix, cities, alpha, beta, k_evaporation, days):
    q = calcQ(matrix, cities)
    bestWay = []
    minDist = float("inf")
    pheromones = calcPheromones(cities)
    visibility = calcVisibility(matrix, cities)
    ants = cities
    for day in range(days):
        route = np.arange(cities)
        visited = calcVisitedPlaces(route, ants)

        for ant in range(ants):
            while (len(visited[ant]) != ants):
                pk = findProbs(pheromones, visibility, visited, cities, ant, alpha, beta)
                chosenPlace = chooseNextСity(pk)
                visited[ant].append(chosenPlace - 1)

            curLength = calcLength(matrix, visited[ant])

            if (curLength < minDist):
                minDist = curLength
                bestWay = visited[ant]

        pheromones = updPher(matrix, cities, visited, pheromones, q, k_evaporation)

    return minDist, bestWay