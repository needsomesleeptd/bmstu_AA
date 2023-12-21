def updPher(matrix, cities, visited, pheromones, q, k_evaporation):
    ants = cities

    for i in range(cities):
        for j in range(cities):
            delta = 0
            for ant in range(ants):
                cur_dist = calcLength(matrix, visited[ant])
                delta += q / cur_dist

            pheromones[i][j] *= (1 - k_evaporation)
            pheromones[i][j] += delta
            if (pheromones[i][j] < MIN_PHEROMONE):
                pheromones[i][j] = MIN_PHEROMONE

    return pheromones