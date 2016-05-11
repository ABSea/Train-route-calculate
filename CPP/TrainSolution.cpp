//
//  TrainSolution.cpp
//  CPP
//
//  Created by Andy on 16/5/10.
//  Copyright © 2016年 Andy. All rights reserved.
//

#include "TrainSolution.h"

using namespace std;

void TrainSolution::init_city_count(char *pcBufPointer)
{
    //if the city exist, the map bool = true
    std::map<char, bool> mapCity;
    
    char charStartCity = '0';
    char charEndCity = '0';
    while (*pcBufPointer != '\0') {
        charStartCity = *pcBufPointer;
        charEndCity = *(pcBufPointer + 1);
        mapCity[charStartCity] = true;
        mapCity[charStartCity] = true;
        pcBufPointer = pcBufPointer + CITY_OFFSET_IN_BUFFER;
    }
    
    CITY_COUNT = mapCity.size();
}


int TrainSolution::init_input_data(char *pcInput_path)
{
    int nRet = SUCCESS;
    std::ifstream inFile;
    size_t nFileSize = 0;
    char *pcFileBuf = NULL;
    
    inFile.open(pcInput_path, ios::in);
    
    if (!inFile.is_open()) {
        //cout << "Error to open the input file." << endl;
        nRet = ERROR_OPEN_FILE;
        goto DONE;
    }
    else
    {
        //cout << "Success to open the input file" << endl;
        
        //calculate the file buffer length
        inFile.seekg(0, ios::end);
        nFileSize = (size_t)inFile.tellg();
        inFile.seekg(0, ios::beg);
        
        //new + CITY_OFFSET_IN_BUFFER reason: check *pcBufPointer != '\0'
        //or the final *pcBufPointer may be other value
        pcFileBuf = new char[nFileSize + CITY_OFFSET_IN_BUFFER];
        memset(pcFileBuf, 0, nFileSize + CITY_OFFSET_IN_BUFFER);
        if(!pcFileBuf)
        {
            //cout << "Error to alloc memory for the file buffer" << endl;
            nRet = BUFFER_ALLOC_FAILED;
            goto DONE;
        }
        else
        {
            //cout << "Read the file buffer..." << endl;
            inFile.read(pcFileBuf, nFileSize);
            
            //get the real data point "AB5, ....." pcBufPoint -> "A"
            char *pcBufPointer = pcFileBuf + CITY_DATA_OFFSET;
            
            init_city_count(pcBufPointer);
            for(int i = 0; i < CITY_COUNT; i++)
            {
                CITY_ARRAY CityArrayTmp;
                for(int j = 0; j < CITY_COUNT; j++)
                {
                    CityArrayTmp.push_back(City(ASCII_A_BASED_NUM + i + 1, ASCII_A_BASED_NUM + j + 1, MAX));
                }
                vecCityGraph.push_back(CityArrayTmp);
            }
            
            pcBufPointer = pcFileBuf + CITY_DATA_OFFSET;
            char charStartCity = '0';
            char charEndCity = '0';
            int nStartCityIndex = 0;
            int nEndCityIndex = 0;
            int nDistance = MAX;
            while (*pcBufPointer != '\0') {
                charStartCity = *pcBufPointer;
                charEndCity = *(pcBufPointer + 1);
                nDistance = *(pcBufPointer + 2) - ASCII_0_BASED_NUM;
                nStartCityIndex = charStartCity - ASCII_A_BASED_NUM - 1;
                nEndCityIndex = charEndCity - ASCII_A_BASED_NUM - 1;
                vecCityGraph[nStartCityIndex][nEndCityIndex].nDistance = nDistance;
                pcBufPointer = pcBufPointer + CITY_OFFSET_IN_BUFFER;
            }
        }
    }
    
    
DONE:
    if(inFile.is_open())
    {
        inFile.close();
    }
    if(pcFileBuf != NULL)
    {
        delete[] pcFileBuf;
        pcFileBuf = NULL;
    }
    
    return nRet;
    
}

void TrainSolution::GetMinDistance(int nIssueIndex, char charStartCity, char charEndCity)
{
    int nStartCityIndex = charStartCity - ASCII_A_BASED_NUM - 1;
    //init
    vector<bool> vecVisted;
    vector<char> vecPreCity;
    vector<int> vecDistance;
    vecVisted.assign(CITY_COUNT, false);
    vecPreCity.assign(CITY_COUNT, '\0'); //unknow city
    vecDistance.assign(CITY_COUNT, MAX);
    
    //i --> endcity
    for(int nEndCityIndex =0; nEndCityIndex < CITY_COUNT; nEndCityIndex++)
    {
        vecDistance[nEndCityIndex] = vecCityGraph[nStartCityIndex][nEndCityIndex].nDistance;
        if(vecDistance[nEndCityIndex] == MAX)
            vecPreCity[nEndCityIndex] = '\0';
        else
            vecPreCity[nEndCityIndex] = charStartCity;
    }
    
    
    //step 2
    int nMinValue = MAX + 1;
    int nNewFindedCityIndex = 0;
    for (int i = 0; i < CITY_COUNT; i++)
    {
        
        nMinValue = MAX + 1;
        for(int j = 0; j < CITY_COUNT; j++)
        {
            if((vecVisted[j] == false) && (vecDistance[j] < nMinValue))
            {
                nMinValue = vecDistance[j];
                nNewFindedCityIndex = j;
            }
        }
        
        
        vecVisted[nNewFindedCityIndex] = true;
        
        int nDistanceTmp = 0;
        for (int j =0; j < CITY_COUNT; j++)
        {
            nDistanceTmp = vecDistance[nNewFindedCityIndex] + vecCityGraph[nNewFindedCityIndex][j].nDistance;
            if (vecVisted[j] == false && vecDistance[j] > nDistanceTmp)
            {
                vecDistance[j] = nDistanceTmp;
                vecPreCity[j] = nNewFindedCityIndex + ASCII_A_BASED_NUM + 1;
            }
        }
    }
    
    cout << "Output #"<< nIssueIndex << ": ";
    cout << vecDistance[charEndCity - ASCII_A_BASED_NUM - 1] << endl;
}

int TrainSolution::GetRouteInCityList(int nIssueIndex, vector<char> vCityList)
{
    int ndistance = 0;
    int nStartCityIndex = 0;
    int nEndCityIndex = 0;
    
    for(int i = 0; i < vCityList.size() - 1; i++)
    {
        nStartCityIndex = vCityList[i] - ASCII_A_BASED_NUM - 1;
        nEndCityIndex = vCityList[i + 1] - ASCII_A_BASED_NUM - 1;
        if(vecCityGraph[nStartCityIndex][nEndCityIndex].nDistance == MAX)
        {
            ndistance = FAIL;
            goto DONE;
        }
        else
        {
            ndistance = ndistance + vecCityGraph[nStartCityIndex][nEndCityIndex].nDistance;
        }
    }
    
DONE:
    
    cout << "Output #"<< nIssueIndex << ": ";
    if(ndistance == FAIL)
    {
        cout << "NO SUCH ROUTE" << endl;
    }
    else
    {
        cout << ndistance << endl;
    }
    
    return ndistance;
};


int TrainSolution::GetRouteCntWithInStops(char charStartCity, char charEndCity, unsigned int maxCnt)
{
    int nStartCityIndex = charStartCity - ASCII_A_BASED_NUM - 1;
    int nEndCityIndex = charEndCity - ASCII_A_BASED_NUM - 1;
    if (maxCnt == 0)
    {
        return false;
    }
    
    vecCityRouteTmp.push_back(charStartCity);
    
    char charStartCityTmp = '\0';
    for (int nCityIndex = 0; nCityIndex < CITY_COUNT; nCityIndex++)
    {
        if(vecCityGraph[nStartCityIndex][nCityIndex].nDistance != MAX)
        {
            if(nCityIndex == nEndCityIndex)//find the city
            {
                vector<char> vecRouteTmp;
                for(unsigned int i = 0; i < vecCityRouteTmp.size(); i++)
                {
                    vecRouteTmp.push_back(vecCityRouteTmp[i]);
                }
                vecRouteTmp.push_back(charEndCity);
                vecCityRoute.push_back(vecRouteTmp);
                
                charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                if(!(GetRouteCntWithInStops(charStartCityTmp, charEndCity, maxCnt - 1)))
                {
                    if(vecCityRouteTmp.size() > (nMinStops - maxCnt + 1))
                    {
                        vecCityRouteTmp.pop_back();
                        continue;
                    }
                }
            }
            else
            {
                charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                if(!(GetRouteCntWithInStops(charStartCityTmp, charEndCity, maxCnt - 1)))
                {
                    if(vecCityRouteTmp.size() > (nMinStops - maxCnt + 1))
                    {
                        vecCityRouteTmp.pop_back();
                        continue;
                    }
                }
            }
        }
    }
    
    return SUCCESS;
};

int TrainSolution::GetRouteCntEqStops(char charStartCity, char charEndCity, unsigned int maxCnt)
{
    int nStartCityIndex = charStartCity - ASCII_A_BASED_NUM - 1;
    int nEndCityIndex = charEndCity - ASCII_A_BASED_NUM - 1;
    if (maxCnt == 0)
    {
        return false;
    }
    
    vecCityRouteTmp.push_back(charStartCity);
    
    char charStartCityTmp = '\0';
    for (int nCityIndex = 0; nCityIndex < CITY_COUNT; nCityIndex++)
    {
        if(vecCityGraph[nStartCityIndex][nCityIndex].nDistance != MAX)
        {
            if(nCityIndex == nEndCityIndex)
            {
                if(maxCnt == 1) //find the city
                {
                    vector<char> vecRouteTmp;
                    for(unsigned int i = 0; i < vecCityRouteTmp.size(); i++)
                    {
                        vecRouteTmp.push_back(vecCityRouteTmp[i]);
                    }
                    vecRouteTmp.push_back(charEndCity);
                    vecCityRoute.push_back(vecRouteTmp);
                    continue;
                }
                else
                {
                    charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                    if(!(GetRouteCntEqStops(charStartCityTmp, charEndCity, maxCnt - 1)))
                    {
                        if(vecCityRouteTmp.size() > (nMinStops - maxCnt + 1))
                        {
                            vecCityRouteTmp.pop_back();
                            continue;
                        }
                    }
                }
            }
            else
            {
                charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                if(!(GetRouteCntEqStops(charStartCityTmp, charEndCity, maxCnt - 1)))
                {
                    if(vecCityRouteTmp.size() > (nMinStops - maxCnt + 1))
                    {
                        vecCityRouteTmp.pop_back();
                        continue;
                    }
                }
            }
        }
    }
    
    return SUCCESS;
};


int TrainSolution::GetRouteCntWithInDistance(char charStartCity, char charEndCity, int nMinDistance)
{
    int nStartCityIndex = charStartCity - ASCII_A_BASED_NUM - 1;
    int nEndCityIndex = charEndCity - ASCII_A_BASED_NUM - 1;
    vecCityRouteTmp.push_back(charStartCity);
    
    char charStartCityTmp = '\0';
    int nDistanceTmp = 0;
    for (int nCityIndex = 0; nCityIndex < CITY_COUNT; nCityIndex++)
    {
        if(vecCityGraph[nStartCityIndex][nCityIndex].nDistance != MAX)
        {
            if(nCityIndex == nEndCityIndex)//find the city
            {
                nDistanceTmp = nMinDistance - vecCityGraph[nStartCityIndex][nCityIndex].nDistance;
                if(nDistanceTmp <= 0)
                {
                    continue;
                }
                else
                {
                    vector<char> vecRouteTmp;
                    for(unsigned int i = 0; i < vecCityRouteTmp.size(); i++)
                    {
                        vecRouteTmp.push_back(vecCityRouteTmp[i]);
                    }
                    vecRouteTmp.push_back(charEndCity);
                    vecCityRoute.push_back(vecRouteTmp);
                    charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                    GetRouteCntWithInDistance(charStartCityTmp, charEndCity, nDistanceTmp);
                }
                
            }
            else
            {
                nDistanceTmp = nMinDistance - vecCityGraph[nStartCityIndex][nCityIndex].nDistance;
                if(nDistanceTmp <= 0)
                {
                    continue;
                }
                else
                {
                    charStartCityTmp = nCityIndex + ASCII_A_BASED_NUM + 1;
                    GetRouteCntWithInDistance(charStartCityTmp, charEndCity, nDistanceTmp);
                }
            }
        }
    }
    
    vecCityRouteTmp.pop_back();
    
    return SUCCESS;
};



int main(int argc, const char * argv[]) {
    
    char input_path[] = "input.txt";
    //init input data
    TrainSolution *solution = NULL;
    solution = new TrainSolution();
    solution->init_input_data(input_path);
    
    
    //# 1
    vector<char> vCityList;
    vCityList.push_back('A');
    vCityList.push_back('B');
    vCityList.push_back('C');
    solution->GetRouteInCityList(1, vCityList);
    
    //# 2
    vCityList.clear();
    vCityList.push_back('A');
    vCityList.push_back('D');
    solution->GetRouteInCityList(2, vCityList);
    
    //# 3
    vCityList.clear();
    vCityList.push_back('A');
    vCityList.push_back('D');
    vCityList.push_back('C');
    solution->GetRouteInCityList(3, vCityList);
    
    //# 4
    vCityList.clear();
    vCityList.push_back('A');
    vCityList.push_back('E');
    vCityList.push_back('B');
    vCityList.push_back('C');
    vCityList.push_back('D');
    solution->GetRouteInCityList(4, vCityList);
    
    //# 5
    vCityList.clear();
    vCityList.push_back('A');
    vCityList.push_back('E');
    vCityList.push_back('D');
    solution->GetRouteInCityList(5, vCityList);
    
    //# 6
    solution->vecCityRoute.clear();
    solution->nMinStops = 3;
    solution->GetRouteCntWithInStops('C', 'C', solution->nMinStops);
    cout << "Output #"<< 6 << ": ";
    cout << solution->vecCityRoute.size() << endl;
    
    //# 7
    solution->vecCityRoute.clear();
    solution->nMinStops = 4;
    solution->GetRouteCntEqStops('A', 'C', solution->nMinStops);
    cout << "Output #"<< 7 << ": ";
    cout << solution->vecCityRoute.size() << endl;
    
    solution->GetMinDistance(8, 'A', 'C');
    
    solution->GetMinDistance(9, 'B', 'B');
    
    //# 10
    solution->vecCityRoute.clear();
    solution->nMinDistance = 30;
    solution->GetRouteCntWithInDistance('C', 'C', solution->nMinDistance);
    cout << "Output #"<< 10 << ": ";
    cout << solution->vecCityRoute.size() << endl;
    
    
    //delete the memory newed in the front
    if(solution != NULL)
    {
        delete solution;
        solution = NULL;
    }
    
    return 0;
}
