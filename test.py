#!/usr/bin/python
__author__ = 'Andy'


from Solution import Solution

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

class Case:

    def __init__(self):
        self.solution = Solution()
        return

    def case_1(self):
        city_list = []
        city_list.append(A)
        city_list.append(B)
        city_list.append(C)
        self.solution.get_route_distance(city_list)
        return self.solution.route_distance

    def case_2(self):
        city_list = []
        city_list.append(A)
        city_list.append(D)
        self.solution.get_route_distance(city_list)
        return self.solution.route_distance

    def case_3(self):
        city_list = []
        city_list.append(A)
        city_list.append(D)
        city_list.append(C)
        self.solution.get_route_distance(city_list)
        return self.solution.route_distance

    def case_4(self):
        city_list = []
        city_list.append(A)
        city_list.append(E)
        city_list.append(B)
        city_list.append(C)
        city_list.append(D)
        self.solution.get_route_distance(city_list)
        return self.solution.route_distance

    def case_5(self):
        city_list = []
        city_list.append(A)
        city_list.append(E)
        city_list.append(D)
        self.solution.get_route_distance(city_list)
        return self.solution.route_distance

    def case_6(self):
        self.solution.city_route = []
        self.solution.city_route_tmp = []
        self.solution.route_max_cnt = 3
        self.solution.get_routecnt_within_maxcnt(C, C, 3)
        return self.solution.city_route.__len__()

    def case_7(self):
        self.solution.city_route = []
        self.solution.city_route_tmp = []
        self.solution.route_max_cnt = 4
        self.solution.get_routecnt_eq_cnt(A, C, 4)
        return self.solution.city_route.__len__()

    def case_8(self):
        self.solution.get_shortest_route_btw_city(A, self.solution.city_dict)
        return self.solution.distance[C - 1]
        #get the shortest path
        # city_route_tmp = []
        # city_route_tmp.append(CITY_DIC[C])
        # pre = self.solution.pre_node[C - 1]
        # while (not pre == 0) and (not pre == A):
        #     city_route_tmp.append(CITY_DIC[pre])
        #     pre = self.solution.pre_node[pre - 1]
        # city_route_tmp.append(CITY_DIC[A])
        # # reversed the city_route_tmp to get the route
        # city_route_tmp.reverse()
        # str_route = ''
        # for i in range(0, city_route_tmp.__len__(), 1):
        #     str_route += city_route_tmp[i]
        # # print str_route

    def case_9(self):
        self.solution.get_shortest_route_btw_city(B, self.solution.city_dict)
        return self.solution.distance[B - 1]
        #get the shortest path
        # city_route_tmp = []
        # city_route_tmp.append(CITY_DIC[B])
        # pre = self.solution.pre_node[B - 1]
        # while (not pre == 0) and (not pre == B):
        #     city_route_tmp.append(CITY_DIC[pre])
        #     pre = self.solution.pre_node[pre - 1]
        # city_route_tmp.append(CITY_DIC[B])
        # # reversed the city_route_tmp to get the route
        # city_route_tmp.reverse()
        # str_route = ''
        # for i in range(0, city_route_tmp.__len__(), 1):
        #     str_route += city_route_tmp[i]
        # # print str_route

    def case_10(self):
        # init
        self.solution.city_route = []
        self.solution.city_route_tmp = []
        self.solution.route_max_distance = 30
        self.solution.get_routecnt_within_distance(C, C, 30)
        return self.solution.city_route.__len__()



if __name__ == "__main__":
    test = Case()
    print "Output #1:", test.case_1()
    print "Output #2:", test.case_2()
    print "Output #3:", test.case_3()
    print "Output #4:", test.case_4()
    print "Output #5:", test.case_5()
    print "Output #6:", test.case_6()
    print "Output #7:", test.case_7()
    print "Output #8:", test.case_8()
    print "Output #9:", test.case_9()
    print "Output #10:", test.case_10()

