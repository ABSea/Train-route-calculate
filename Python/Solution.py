#!/usr/bin/python
__author__ = 'Andy'


from Distance import Distance
from get_input_data import Data

MAX = 100000
NOT_VISITED = 0
HAS_VISITED = 1
CNT = 6

A = 1
B = 2
C = 3
D = 4
E = 5

CITY_DIC = {}
CITY_DIC[A] = "A"
CITY_DIC[B] = "B"
CITY_DIC[C] = "C"
CITY_DIC[D] = "D"
CITY_DIC[E] = "E"

class Solution:

    def __init__(self):
        self.city_dict = {}
        self.pre_node = []
        self.visited = []
        self.distance = []
        self.route_distance = 0
        self.city_route = []
        self.city_route_tmp = []
        self.route_max_cnt = 0
        self.route_max_distance = 0

        for city_index in range(1, CNT, 1):
            tmp_node = []
            tmp_node.append(Distance(MAX))
            tmp_node.append(Distance(MAX))
            tmp_node.append(Distance(MAX))
            tmp_node.append(Distance(MAX))
            tmp_node.append(Distance(MAX))

            self.city_dict[city_index] = tmp_node
            self.pre_node.append(0)
            self.visited.append(NOT_VISITED)

        input_data = Data("input")

        for index_i in range(1, input_data.city_city_distance.__len__() + 1, 1):
            for index_j in range(0, input_data.city_city_distance.__len__(), 1):
                if input_data.city_city_distance[index_i][index_j] != MAX:
                    self.city_dict[index_i][index_j] = Distance(int(input_data.city_city_distance[index_i][index_j]))

    # use the djikstra algorithm
    # this method can get the shortest distance between the node and all other nodes
    def get_shortest_route_btw_city(self, node, train_route):
        # step 1, init part
        self.distance = []
        for index in range(1, CNT, 1):
            self.pre_node[index - 1] = 0
            self.visited[index - 1] = 0
            self.distance.append(self.city_dict[node][index - 1].distance)
            if self.distance[index - 1] == Distance(MAX):
                self.pre_node[index - 1] = 0
            else:
                self.pre_node[index - 1] = node

        # step 2 find the shortest distance to node, and set it to be visited
        min_value = MAX + 1
        new_node = 0
        for i in range(1, CNT, 1):
            min_value = MAX + 1
            for j in range(0, CNT - 1, 1):
                if (not self.visited[j]) and self.distance[j] < min_value:
                    min_value = self.distance[j]
                    new_node = j

            self.visited[new_node] = HAS_VISITED

            # step 3 set the previous node
            for k in range(0, CNT - 1, 1):
                if (not self.visited[k]) and (self.distance[k] > (self.distance[new_node] +
                                                                      self.city_dict[new_node + 1][k].distance)):
                    self.distance[k] = self.distance[new_node] + self.city_dict[new_node + 1][k].distance
                    self.pre_node[k] = new_node + 1

    # get the distance of some route, such as A-B-C
    def get_route_distance(self, city_list):
        self.route_distance = 0
        for i in range(1, city_list.__len__(), 1):
            if self.city_dict[city_list[i-1]][city_list[i] - 1].distance == MAX:
                self.route_distance = "NO SUCH ROUTE" #not find the route, return the fail
                return
            else:
                self.route_distance += self.city_dict[city_list[i-1]][city_list[i] - 1].distance

    # get route count (< max_cnt) between start_city and end city
    def get_routecnt_within_maxcnt(self, start_city, end_city, max_cnt):
        if max_cnt == 0:
            return False
        self.city_route_tmp.append(CITY_DIC[start_city])

        for i in range(1, CNT, 1):
            if self.city_dict[start_city][i - 1].distance != MAX:
                if i == end_city:
                    tmp_list = []
                    for j in range(0, self.city_route_tmp.__len__(), 1):
                        tmp_list.append(self.city_route_tmp[j])
                    tmp_list.append(CITY_DIC[end_city])
                    self.city_route.append(tmp_list)
                    if not self.get_routecnt_within_maxcnt(i, end_city, max_cnt - 1):
                        if self.city_route_tmp.__len__() > (self.route_max_cnt - max_cnt + 1):
                            self.city_route_tmp.pop(self.city_route_tmp.__len__() - 1)
                            continue
                else:
                    if not self.get_routecnt_within_maxcnt(i, end_city, max_cnt - 1):
                        if self.city_route_tmp.__len__() > (self.route_max_cnt - max_cnt + 1):
                            self.city_route_tmp.pop(self.city_route_tmp.__len__() - 1)
                            continue

    # get route count (= max_cnt) between start_city and end city
    def get_routecnt_eq_cnt(self, start_city, end_city, max_cnt):
        if max_cnt == 0:
            return False
        self.city_route_tmp.append(CITY_DIC[start_city])

        for i in range(1, CNT, 1):
            if self.city_dict[start_city][i - 1].distance != MAX:
                if i == end_city:
                    if max_cnt == 1:# find the city
                        tmp_list = []
                        for j in range(0, self.city_route_tmp.__len__(), 1):
                            tmp_list.append(self.city_route_tmp[j])
                        tmp_list.append(CITY_DIC[end_city])
                        self.city_route.append(tmp_list)
                        continue
                    else:
                        if not self.get_routecnt_eq_cnt(i, end_city, max_cnt - 1):
                            if self.city_route_tmp.__len__() > (self.route_max_cnt - max_cnt + 1):
                                self.city_route_tmp.pop(self.city_route_tmp.__len__() - 1)
                                continue
                else:
                    if not self.get_routecnt_eq_cnt(i, end_city, max_cnt - 1):
                        if self.city_route_tmp.__len__() > (self.route_max_cnt - max_cnt + 1):
                            self.city_route_tmp.pop(self.city_route_tmp.__len__() - 1)
                            continue

    # get route count that the distance is less than distance_arg between start_city and end city
    def get_routecnt_within_distance(self, start_city, end_city, distance_arg):

        self.city_route_tmp.append(CITY_DIC[start_city])

        for i in range(1, CNT, 1):
            if self.city_dict[start_city][i - 1].distance != MAX:
                if i == end_city:# find the city
                    distance_tmp = distance_arg - self.city_dict[start_city][i - 1].distance
                    if distance_tmp <= 0:
                        continue
                    else:
                        tmp_list = []
                        for j in range(0, self.city_route_tmp.__len__(), 1):
                            tmp_list.append(self.city_route_tmp[j])
                        tmp_list.append(CITY_DIC[end_city])
                        self.city_route.append(tmp_list)
                        self.get_routecnt_within_distance(i, end_city, distance_tmp)
                else:
                    distance_tmp = distance_arg - self.city_dict[start_city][i - 1].distance
                    if distance_tmp <= 0:
                        continue
                    else:
                        self.get_routecnt_within_distance(i, end_city, distance_tmp)


        self.city_route_tmp.pop(self.city_route_tmp.__len__() - 1)

if __name__ == "__main__":
    solution = Solution()

    # 1
    city_list = []
    city_list.append(A)
    city_list.append(B)
    city_list.append(C)
    solution.get_route_distance(city_list)
    print solution.route_distance