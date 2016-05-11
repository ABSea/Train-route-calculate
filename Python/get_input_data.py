#!/usr/bin/python
__author__ = 'Andy'

A = 1
B = 2
C = 3
D = 4
E = 5


BASE_A_NUM = 64
MAX = 100000
CITY_CNT = 5

class Data:

    def __init__(self, input_path):
        self.input_path = input_path
        self.city_city_distance = {}

        distance_tmp = []
        for index in range(1, CITY_CNT + 1, 1):
            distance_tmp.append(MAX)

        for index in range(1, CITY_CNT + 1, 1):
            distance_tmp = []
            for cnt in range(1, CITY_CNT + 1, 1):
                distance_tmp.append(MAX)
            self.city_city_distance[index] = distance_tmp
        self.get_data()

    def get_data(self):
        fo = open(self.input_path, 'r')
        try:
            str = fo.read()
        except:
            fo.close()
        str_list = str.split(" ")


        for index in range(1, str_list.__len__() - 1, 1):
            letter_cap_1 = str_list[index][0]
            letter_ascii_1 = ord(letter_cap_1)
            letter_index_1 = letter_ascii_1 - BASE_A_NUM

            letter_cap_2 = str_list[index][1]
            letter_ascii_2 = ord(letter_cap_2)
            letter_index_2 = letter_ascii_2 - BASE_A_NUM - 1

            str_num_tmp = str_list[index][2:str_list[index].__len__() - 1]
            self.city_city_distance[letter_index_1][letter_index_2] = str_num_tmp

        # for the last data, such as AE7, AE7 don't have the "," after the data
        index = index + 1
        letter_cap_1 = str_list[index][0]
        letter_ascii_1 = ord(letter_cap_1)
        letter_index_1 = letter_ascii_1 - BASE_A_NUM

        letter_cap_2 = str_list[index][1]
        letter_ascii_2 = ord(letter_cap_2)
        letter_index_2 = letter_ascii_2 - BASE_A_NUM - 1

        str_num_tmp = str_list[index][2:str_list[index].__len__()]
        self.city_city_distance[letter_index_1][letter_index_2] = str_num_tmp

        fo.close()

if __name__ == "__main__":
    data = Data("input")
    data.get_data()
    print "hello"