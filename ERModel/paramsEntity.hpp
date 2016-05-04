//
//  ParamsEntity.hpp
//  EasyRouting
//
//  Created by Vladimir on 17.04.16.
//  Copyright © 2016 pvs. All rights reserved.
//

#ifndef ParamsEntity_hpp
#define ParamsEntity_hpp

#include <stdio.h>

#endif /* ParamsEntity_hpp */

class ParamsEntity {
private:
    int maxMoney;
    int maxTime;
    
public:
    void setTime(int time);
    void setMoney(int money);
    bool calculatePaths();
};