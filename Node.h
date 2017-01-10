//
//  Node.h
//  Graph
//
//  Created by Fırat Sezel on 30/11/2016.
//  Copyright © 2016 İsmail Fırat Sezel. All rights reserved.
//
#ifndef Point_h
#include "Point.h"
#endif

#ifndef Node_h
#define Node_h
#include <vector>

class Node
{
public:
    std::string name;
    int lineNumbers;
    std::string Link;
    std::string Link2;
    Points location;
};
#endif
