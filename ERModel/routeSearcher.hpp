//
//  RouteSearcher.hpp
//  EasyRouting
//
//  Created by Vladimir on 17.04.16.
//  Copyright © 2016 pvs. All rights reserved.
//

#ifndef RouteSearcher_hpp
#define RouteSearcher_hpp

#include <stdio.h>
#include "CityMap.hpp"
#include "PathList.hpp"
#include "DataAccessObject.hpp"
#include "ParamsEntity.hpp"
#include "Path.hpp"
#include "Place.hpp"

#endif /* RouteSearcher_hpp */


template <class T>
class RouteSearcher {
private:
    CityMap<T> cityMap;
    ParamsEntity params;
    PathList<T> pathList;
    DataAccessObject dao;
    
public:
    void setTime(int time);
    void setMoney(int money);
    void algorithm(Place start, Place finish);
    vector<Path<T>*> getSortedByTime();
    vector<Path<T>*> getSortedByMoney();
    CityMap<T> getCityMap();
    void load();
    void save();
};