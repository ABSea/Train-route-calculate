//
//  TrainSolution.h
//  CPP
//
//  Created by Andy on 16/5/10.
//  Copyright © 2016年 Andy. All rights reserved.
//

#ifndef TrainSolution_h
#define TrainSolution_h

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#endif /* TrainSolution_h */


using namespace std;

enum ERROR_CODE
{
    FAIL = -1,
    SUCCESS,
    ERROR_OPEN_FILE,
    BUFFER_ALLOC_FAILED,
}_ERROR_CODE;

//static value
static const int CITY_DATA_OFFSET = 7; //start at the A of "AB5"
static const int MAX = 100000;
static size_t    CITY_COUNT = 0;
static const int ASCII_A_BASED_NUM = 64; //'A'
static const int ASCII_0_BASED_NUM = 48; //'\0'
static const int CITY_OFFSET_IN_BUFFER = 5; //'\0'

class City
{
public:
    City(char startCity, char endCity, int distance)
    {
        nStartCity = startCity;
        nEndCity = endCity;
        nDistance = distance;
    };
    ~City(){};
    
public:
    char nStartCity;
    char nEndCity;
    int nDistance;
    
};

typedef vector<City> CITY_ARRAY;
typedef vector<char> CITY_ROUTE;


class TrainSolution
{
public:
    TrainSolution()
    {
        nMinStops = 0;
        nMinDistance = 0;
    };
    ~TrainSolution(){};
    
    void init_city_count(char *pcBufPointer);
    int  init_input_data(char *pcInput_path);
    void GetMinDistance(int nIssueIndex, char charStartCity, char charEndCity);
    int  GetRouteInCityList(int nIssueIndex, vector<char> vCityList);
    int  GetRouteCntWithInStops(char charStartCity, char charEndCity, unsigned int maxCnt);
    int  GetRouteCntEqStops(char charStartCity, char charEndCity, unsigned int maxCnt);
    int  GetRouteCntWithInDistance(char charStartCity, char charEndCity, int nMinDistance);
    
    
public:
    vector<CITY_ARRAY> vecCityGraph;
    CITY_ROUTE vecCityRouteTmp;
    vector<CITY_ROUTE> vecCityRoute;
    int nMinStops;
    int nMinDistance;
};