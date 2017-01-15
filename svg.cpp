#include "svg.h"

svg::Dimensions dimensions(20000, 20000);
std::vector<Node> nodes;//holds all rectangels

svg::Document doc("/home/firat/Desktop/my_svg.svg", svg::Layout(dimensions, svg::Layout::TopLeft));
std::map<std::string,int> mymap;
std::map<std::string,int>::iterator it;
std::map<uint64_t, Block>::iterator blockite;
std::vector<Node>::iterator n;

Node cachenode;
Node nod, linkNod, link2Nod;
Points current;

void svg_create(std::map<uint64_t, Block> block_table){
    printf("Enter the Function.");
    Block block;
    svg::Polygon border(svg::Stroke(1, svg::Color::Red));

    current.x = 50;/*location of current point*/
    current.y = 50;
    int countforFunctions = 0;

    std::string node = "";
    int countfory = 10;


    for (blockite = block_table.begin(); blockite!=block_table.end(); ++blockite){
        block = blockite->second;
        nod.name = std::to_string(block.start_address);//adresi string yap

        Points locCur = Location(nod.name, nodes);
        //int num = returnNumberofMap(node, mymap);
        if(locCur.x == -1 && locCur.y == -1){
            //mymap.insert ( std::pair<std::string,int>(Names[k],k));
            countforFunctions++;
            nod.location = current;
            nod.Link = std::to_string(block.jump1);
            nod.Link2 = std::to_string(block.jump2);
            nodes.push_back(nod);

            doc << svg::Rectangle(svg::Point(nod.location.x, nod.location.y), 80, 80, svg::Color::Yellow);
            doc << svg::Text(svg::Point(nod.location.x, nod.location.y), nod.name, svg::Color::Red, svg::Font(15, "Verdana"));

            countfory -= 1;
            current.x += 100;

            if(countfory == 0){
                current.y += 90;
                current.x = 50;
                countfory = 10;
            }
        }else{
            countforFunctions++;
            nod.location.x = locCur.x;
            nod.location.y = locCur.y;
            nod.Link = std::to_string(block.jump1);
            nod.Link2 = std::to_string(block.jump2);
        }

        std::string link1 = std::to_string(block.jump1);
        std::string link2 = std::to_string(block.jump2);

        if(1){//link varsa
            svg::Polyline polyline1(svg::Stroke(.5, svg::Color::Green));
            if(nod.name.compare(nod.Link) == 0){
                //recursive
                doc << svg::Circle(svg::Point(nod.location.x + 40, nod.location.y + 40), 60, svg::Fill(svg::Color(100, 200, 120)),
                              svg::Stroke(1, svg::Color(200, 250, 150)));
            }else{
                //drew already?
                Points locCur = Location(nod.Link, nodes);
                if(locCur.x == -1 && locCur.y == -1){
                    //new, create link node
                    linkNod.name = nod.Link;
                    linkNod.location = current;
                    nodes.push_back(linkNod);

                    doc << svg::Rectangle(svg::Point(linkNod.location.x, linkNod.location.y), 80, 80, svg::Color::Yellow);
                    doc << svg::Text(svg::Point(linkNod.location.x, linkNod.location.y), linkNod.name, svg::Color::Red, svg::Font(15, "Verdana"));

                    polyline1 << svg::Point(current.x, current.y + 20) << svg::Point(nod.location.x  , nod.location.y + 20);
                    doc << polyline1;

                    countfory -= 1;
                    current.x += 100;

                    if(countfory == 0){
                        current.y += 90;
                        current.x = 50;
                        countfory = 3;
                    }
                }else{
                    //used before
                    polyline1 << svg::Point(nod.location.x + 80, nod.location.y + 20) << svg::Point(locCur.x , locCur.y + 20);
                    doc << polyline1;
                }
            }
        }
        if(1){//link2 if link2 is not empty
            svg::Polyline polyline1(svg::Stroke(.5, svg::Color::Red));
            if(nod.name.compare(nod.Link2) == 0){
                //recursive
                doc << svg::Circle(svg::Point(nod.location.x + 40, nod.location.y + 40), 60, svg::Fill(svg::Color(100, 200, 120)),
                              svg::Stroke(1, svg::Color(200, 250, 150)));
            }else{
                //drew already
                Points locCur = Location(nod.Link2, nodes);
                if(locCur.x == -1 && locCur.y == -1){
                    //new, create link node
                    link2Nod.name = link2;
                    link2Nod.location = current;
                    nodes.push_back(link2Nod);

                    doc << svg::Rectangle(svg::Point(link2Nod.location.x, link2Nod.location.y), 80, 80, svg::Color::Yellow);
                    doc << svg::Text(svg::Point(link2Nod.location.x, link2Nod.location.y), link2Nod.name, svg::Color::Red, svg::Font(15, "Verdana"));

                    polyline1 << svg::Point(current.x, current.y + 60) << svg::Point(nod.location.x , nod.location.y + 60);
                    doc << polyline1;

                    countfory -= 1;
                    current.x += 100;

                    if(countfory == 0){
                        current.y += 90;
                        current.x = 50;
                        countfory = 3;
                    }
                }
                else{
                    //DEMEKKİ DAHA ÖNCEDEN KULLANILMIŞ
                    polyline1 << svg::Point(nod.location.x + 80, nod.location.y + 60) << svg::Point(locCur.x , locCur.y + 60);
                    doc << polyline1;
                }
            }
        }

        /*if (nod.name.compare(cachenode.name) != 0){
         doc << Rectangle(Point(nod.location.x, nod.location.y), 80, 80, Color::Yellow);
         doc << Text(Point(nod.location.x, nod.location.y), nod.name, Color::Red, Font(15, "Verdana"));

         Polyline polyline1(Stroke(.5, Color::Red));
         if(cachenode.name.compare("") != 0){
         polyline1 << Point(current.x, current.y + 40) << Point(cachenode.location.x + 80, cachenode.location.y + 40);
         doc << polyline1;
         }
         cachenode = nod;
         countfory -= 1;
         current.x += 100;
         }*/

        /*if(locCur.x == cachenode.location.x && locCur.y == cachenode.location.y){//recursive alert
         doc << Circle(Point(nod.location.x + 40, nod.location.y + 40), 60, Fill(Color(100, 200, 120)), Stroke(1, Color(200, 250, 150)));
         }else{
         cachenode = nod;
         int xyer = (num % 3) + 1;
         int yyer = (num / 3) + 1;

         xyer = xyer * 50;
         yyer = yyer * 90;
         Polyline polyline1(Stroke(.5, Color::Red));

         polyline1 << Point(current.x, current.y + 40) << Point(xyer - 20, yyer + 40);
         doc << polyline1;
         }*/




        if(countfory == 0){
            current.y += 90;
            current.x = 50;
            countfory = 3;
        }

    }
    //doc << Circle(Point(80, 80), 20, Fill(Color(100, 200, 120)), Stroke(1, Color(200, 250, 150)));


    //doc << (Polygon(Color(200, 160, 220), Stroke(.5, Color(150, 160, 200))) << Point(20, 70)
    //        << Point(25, 72) << Point(33, 70) << Point(35, 60) << Point(25, 55) << Point(18, 63));
    doc.save();
}

int returnNumberofMap(std::string name, std::map<std::string, int> mymap){
    for (it=mymap.begin(); it!=mymap.end(); ++it){
        if(it->first.compare(name) == 0)
            return it->second;
    }
    return -1;
}

Points Location(std::string name,  std::vector<Node> nodes){
    Points p;
    p.x = -1;
    p.y = -1;
    for (n=nodes.begin(); n!=nodes.end(); ++n){
        if(n->name.compare(name) == 0)
            return n->location;
    }
    return p;
}

