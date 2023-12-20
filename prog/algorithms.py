import itertools as it
import numpy as np
from random import random
from constants import MIN_PHEROMONE

def fullCombinationAlg(matrix, size):

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


def updatePheromones(matrix, places, visited, pheromones, q, k_evaporation):
    ants = places

    for i in range(places):
        for j in range(places):
            delta = 0
            for ant in range(ants):
                length = calcLength(matrix, visited[ant])
                delta += q / length

            pheromones[i][j] *= (1 - k_evaporation)
            pheromones[i][j] += delta
            if (pheromones[i][j] < MIN_PHEROMONE):
                pheromones[i][j] = MIN_PHEROMONE

    return pheromones


def findWays(pheromones, visibility, visited, places, ant, alpha, beta):
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


# Следующий город
#  0         pk[0]  pk[1]    pk[2]       pk[2]  1
#  |----------|------|--------|---x--------|----|
def chooseNextPlaceByPosibility(pk):
    posibility = random()
    choice = 0
    chosenPlace = 0
    while ((choice < posibility) and (chosenPlace < len(pk))):
        choice += pk[chosenPlace]
        chosenPlace += 1

    return chosenPlace



def antAlgorithm(matrix, places, alpha, beta, k_evaporation, days):
    q = calcQ(matrix, places)
    bestWay = []
    minDist = float("inf")
    pheromones = calcPheromones(places)
    visibility = calcVisibility(matrix, places)
    ants = places
    for day in range(days):
        route = np.arange(places)
        visited = calcVisitedPlaces(route, ants)
        for ant in range(ants):
            while (len(visited[ant]) != ants):
                pk = findWays(pheromones, visibility, visited, places, ant, alpha, beta)
                chosenPlace = chooseNextPlaceByPosibility(pk)
                visited[ant].append(chosenPlace - 1)



            curLength = calcLength(matrix, visited[ant])

            if (curLength < minDist):
                minDist = curLength
                bestWay = visited[ant]

        pheromones = updatePheromones(matrix, places, visited, pheromones, q, k_evaporation)

    return minDist, bestWay