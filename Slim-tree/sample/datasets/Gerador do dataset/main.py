from random import uniform

EC_param = [(15.88071, 14.94726, 14.25543, 13.81744, 13.52653),
            (15.88897, 14.96084, 14.27048, 13.83855, 13.55785),
            (15.84727, 14.95589, 14.26131, 13.8294, 13.52057),
            (15.98358, 14.94892, 14.26593, 13.8352, 13.5495)]


def saveFile(filename, mode, data):

    with open(filename, mode) as file:
        star_id = 1
        count = 0
        for row in data:
            row_str = str(star_id) + "," + ','.join(map(str,row)) + "," + ','.join(map(str,EC_param[count])) + "\n"
            file.write(row_str)

            if count == 3:
                count = 0

            count += 1
            star_id += 1


def saveDistanceFile(filename, mode, data):

    with open(filename, mode) as file:

        for row in data:
            file.write("%s\n" % row)


if __name__ == '__main__':

    raDecList = []
    distanceList = []
    for _ in range(100):
        ra = uniform(0.169676032263, 359.943168254)
        dec = uniform(-1.26875363067, -0.816707022272)

        distance = uniform(0,1)

        raDecList.append((ra,dec))
        distanceList.append(distance)

    saveFile("TestRADEC.csv", "w", raDecList)
    saveDistanceFile("TestDist.csv", "w", distanceList)