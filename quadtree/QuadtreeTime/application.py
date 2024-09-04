from sys import argv

from node import Node
from element import Element
from quadtree import QuadTree
from query import Query
from util import EucDist, compute_level
from voxel import Voxel

import numpy as np

import time


def build_tree(filename, query):
    start_time = time.time()

    root = None
    geometric_centroid_ra = geometric_centroid_dec = None
    centroid = None
    cent_min_dist = float("inf")
    voxel = None

    with open(filename) as f:
        for line in f:
            split = line.replace("\n", "").split(",")
            if len(split) == 4:
                min_ra, max_ra, min_dec, max_dec = split
                voxel = Voxel(float(min_ra), float(max_ra), float(min_dec), float(max_dec))
                geometric_centroid_ra, geometric_centroid_dec = voxel.getVoxelCentroid()
                root = Node(voxel)
            elif line:
                border = False # if split[13].lower() == "false" else True

                star = Element(int(split[0]), float(split[1]), float(split[2]), float(split[3]), float(split[4]),
                               float(split[5]), float(split[6]), float(split[7]), float(split[8]),
                               float(split[9]), float(split[10]), float(split[11]), float(split[12]), 0, border)

                root.addElement(star)

                if star.border is False:
                    dist = EucDist(star.getRa(), geometric_centroid_ra, star.getDec(), geometric_centroid_dec)
                    if dist < cent_min_dist:
                        centroid = star
                        cent_min_dist = dist

    root.setSize(len(root.getElements()))
    root.addCentroid(centroid)

    level = compute_level(voxel.getSideSize(), voxel.getHeightSize(), query.getMaxDistance())
    tree = QuadTree(root, level)

    end_time = time.time() - start_time
    print("BT - %s - %0.25f" % (filename, end_time))
    return tree


def produce_candidates(element, distance, tree):
    root = tree.root

    start_time = time.time()
    neighbors = tree.find_neighbors(element, root, distance, [])


    #print(len(neighbors))

    return neighbors


if __name__ == '__main__':
    if len(argv) < 3:
        print("Pure Constellations Queries:\n[1]InputFile\n[2]OutputFile\n[3]Neighbor Limit")
    else:

        # Create query object instance
        query = Query.defineQuery(float(argv[3]))


        # Read Random points
        pointsList = []
        with open("/home/demori/points.csv", "r") as f:
            for line in f:
                split = line.split(",")
                element = Element(int(split[0]), float(split[1]), float(split[2]), float(split[3]), 0,
                               float(split[4]), 0, float(split[5]), 0, float(split[6]), 0,
                                  float(split[7]), 0, 0, False)
                pointsList.append(element)

        # Read Distance points
        distanceList = []
        with open("/home/demori/distances.csv", "r") as f:
            for line in f:
                distanceList.append(float(line))



        tree = build_tree(argv[1], query)
#objetos

        for element in pointsList:
            time_list = []
            for distance in distanceList:
                start_time = time.time()
                produce_candidates(element, distance, tree)
                end_time = time.time() - start_time

                time_list.append(end_time)

            array_time = np.array(time_list)
            mean = np.mean(array_time, dtype=np.float64)
            standard_deviation = np.var(array_time, dtype=np.float64)
            print("FN : Point ID = %d, Mean = %0.25f, std=%0.25f" % (element.getId(), mean, standard_deviation))
            del time_list, array_time, mean, standard_deviation

#distancias
'''
        for distance in distanceList:
            time_list = []

            for element in pointsList:

                start_time = time.time()
                produce_candidates(element, distance, tree)
                end_time = time.time() - start_time

                time_list.append(end_time)

            array_time = np.array(time_list)
            mean = np.mean(array_time, dtype=np.float64)
            standard_deviation = np.var(array_time, dtype=np.float64)
            print("FN : Point ID = %d, Mean = %0.25f, std=%0.25f" % (element.getId(), mean, standard_deviation))
            del time_list, array_time, mean, standard_deviation'''

