//
//  Node.h
//  Graph
//
//  Created by Fırat Sezel on 30/11/2016.
//  Copyright © 2016 İsmail Fırat Sezel. All rights reserved.
//


#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include <vector>
#include <string>

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
