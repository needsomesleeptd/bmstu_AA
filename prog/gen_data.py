from geopy.distance import geodesic
import numpy as np
cities = {
    'Абуджа':	(9.06, 7.5),
   ' Аддис-Абеба':	(9.02, 38.75),
   ' Аккра':	(5.56, -0.2),
    'Алжир':	(36.73, 3.09),
    'Антананариву':	(-18.91, 47.54),
    'Асмэра':	(15.34, 38.93),
    'Бамако':	(12.65, -8),
    'Банги':	(4.36, 18.56),
    'Банжул':	(13.45, -16.58),
    'Бисау':	(11.86, -15.6),
}


adjacency_matrix = []
for city1, coord1 in cities.items():
    row = []
    for city2, coord2 in cities.items():
        distance = geodesic(coord1, coord2).kilometers
        row.append(distance)
    adjacency_matrix.append(row)

np_mat = np.array(adjacency_matrix)
np.savetxt('data/data_cities.csv',np_mat, delimiter=",")
print(np_mat)