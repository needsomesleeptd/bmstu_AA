import itertools as it
import numpy as np
from random import random
from constants import MIN_PHEROMONE

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

def calcQ(matrix, size):
    q = 0
    count = 0
    for i in range(size):
        for j in range(size):
            if (i != j):
                q += matrix[i][j]
                count += 1
    return q / count

def calcPheromones(size):
    min_phero = 1
    pheromones = [[min_phero for i in range(size)] for j in range(size)]
    return pheromones


def calcVisibility(matrix, size):
    visibility = [[(1.0 / matrix[i][j] if (i != j) else 0) for j in range(size)] for i in range(size)]
    return visibility


def calcVisitedPlaces(route, ants):
    visited = [list() for _ in range(ants)]
    for ant in range(ants):
        visited[ant].append(route[ant])
    return visited


def calcLength(matrix, route):
    length = 0

    for way_len in range(1, len(route)):
        length += matrix[route[way_len - 1], route[way_len]]

    return length


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


def findProbs(pheromones, visibility, visited, places, ant, alpha, beta):
    pk = [0] * places

    for place in range(places):
        if place not in visited[ant]:
            ant_place = visited[ant][-1]
            pk[place] = pow(pheromones[ant_place][place], alpha) * \
                pow(visibility[ant_place][place], beta)
        else:
            pk[place] = 0

    sum_pk = sum(pk)

    for place in range(places):
        pk[place] /= sum_pk

    return pk



def chooseNextСity(pk):
    posibility = random()
    choice = 0
    chosenPlace = 0
    while ((choice < posibility) and (chosenPlace < len(pk))):
        choice += pk[chosenPlace]
        chosenPlace += 1

    return chosenPlace



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