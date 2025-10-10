                                    #include "Utils/math.hpp"
                                  #include <SFML/Graphics.hpp>
                                        #include <string>   
                                        #include <cmath>
                                  #include "Utils/logging.hpp"
                                    #include "Core/World.hpp"


                           inline int coordsToMapIndex(int x, int y){
                        return globals::currentWorld->getMapSize().x*y+x;
                                                }
                       inline sf::Vector2f mapIndexToCoords(int mapIndex){
                         int x = globals::currentWorld->getMapSize().x;
                         int y = globals::currentWorld->getMapSize().y;
                      return {static_cast<float>(x),static_cast<float>(y)};
                                                }



               //! PATHFINDING ASSUMES THE COORDINATE IS IN THE CENTER OF THE TILE

                               inline void generateGraphFromMap(){
    int width =globals::currentWorld->getMapSize().x,height = globals::currentWorld->getMapSize().y;
                                 mapGraph.resize(width*height);
                               auto isCollidable = [](int index){
        return(globals::currentWorld->getMapTileInfo()[globals::currentWorld->getMap()[index]].flags&1);
                                               };
                                  auto isEmpty = [](int index){
                       return(globals::currentWorld->getMap()[index]==0);
                                               };
                                          int index=0;
                                   for(int i=0;i<height;i++){
                                    for(int j=0;j<width;j++){
                          if(!isEmpty(index) && !isCollidable(index)){
                                            index++;
                                            continue;
                                                }
                 if(j!=width-1 && !isEmpty(index+1) && !isCollidable(index+1)){
                             mapGraph[index].push_back({index+1,1});
                             mapGraph[index+1].push_back({index,1});
                                                }
             if(i!=height-1 && !isEmpty(index+width) && !isCollidable(index+width)){
                           mapGraph[index].push_back({index+width,1});
                           mapGraph[index+width].push_back({index,1});
                                                }
            if(j!=width-1 && i != height-1 && !isEmpty(index+width+1) && !isCollidable(index+index+1)){
            mapGraph[index].push_back(std::pair<int,double>(index+width+1,std::sqrt(2)));
            mapGraph[index+width+1].push_back(std::pair<int,double>(index+width+1,std::sqrt(2)));
                                                }
                                            index++;
                                                }
                                                }
                                                }

       inline void dijkstra(int s, std::vector<int> & distance, std::vector<int> & path) {
    
                                    int n = mapGraph.size();
                                 distance.assign(n, 1000000000);
                                       path.assign(n, -1);
                                 std::vector<bool> u(n, false);

                                        distance[s] = 0;
                                  for (int i = 0; i < n; i++) {
                                           int v = -1;
                                  for (int j = 0; j < n; j++) {
                      if (!u[j] && (v == -1 || distance[j] < distance[v]))
                                             v = j;
                                                }

                                 if (distance[v] == 1000000000)
                                             break;

                                          u[v] = true;
                                 for (auto edge : mapGraph[v]) {
                                      int to = edge.first;
                                     int len = edge.second;

                             if (distance[v] + len < distance[to]) {
                                distance[to] = distance[v] + len;
                                          path[to] = v;
                                                }
                                                }
                                                }
                                                }
      inline std::vector<sf::Vector2f> pathfind(sf::Vector2f startPos,sf::Vector2f endPos){
                     int startIndex=coordsToMapIndex(startPos.x,startPos.y);
                                   std::vector<int> distance;
                                     std::vector<int> path;
                               dijkstra(startIndex,distance,path);
                       int endIndex = coordsToMapIndex(endPos.x,endPos.y);
                  std::vector<sf::Vector2f> res = {mapIndexToCoords(endIndex)};
                                         int i=endIndex;
                                      sf::Vector2f coords;
                                  while (path[i]!=startIndex){
                               coords = mapIndexToCoords(path[i]);
                                         coords.x+=0.5;
                                         coords.y+=0.5;
                                    res.push_back({coords});
                                           i=path[i];
                                                }
                              std::reverse(res.begin(),res.end());
                                           return res;
                                                }

