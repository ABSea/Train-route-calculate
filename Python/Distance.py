#!/usr/bin/python
__author__ = 'Andy'


class Distance:

    def __init__(self, distance):
        self.distance = distance

    # def __eq__(self, other):
    #     return self.distance == other


if __name__ == "__main__":
    distance = Distance('10')
    print distance.distance