#ifndef SVG_H
#define SVG_H

#include "Node.h"
#include "Point.h"
#include "Display.h"
#include <iostream>
#include <string>
#include <map>
#include "block.h"

void CreateRect(int width, int height, int x, int y, svg::Document doc);
void svg_create(std::map<uint64_t, Block> block_table);
int returnNumberofMap(std::string name, std::map<std::string, int> mymap);
Points Location(std::string name,  std::vector<Node> nodes);



#endif // SVG_H
