//
//  Path.hpp
//  EasyRouting
//
//  Created by Vladimir on 17.04.16.
//  Copyright © 2016 pvs. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <stdio.h>
#include <vector>
#include "Edge.hpp"
#include "Place.hpp"
using namespace std;

#endif /* Path_hpp */


template <class T> class Path {
private:
    vector<Edge<T>*> routes;
    Place start;
    Place finish;
    
public:
    int getTotalCost();
    int getTotalTime();
};