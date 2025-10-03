#include "Utils/math.hpp"
#include <SFML/Graphics.hpp>
#include <string>   
#include "Utils/logging.hpp"

//! PATHFINDING ASSUMES THE COORDINATE IS IN THE CENTER OF THE TILE

inline void generateGraphFromMap(){
    
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

