#include "Utils/math.hpp"
#include <SFML/Graphics.hpp>
#include <string>   
#include <cmath>
#include "Utils/logging.hpp"
#include "Core/World.hpp"
#include <queue>
bool isWithinRange(float x,float y, float range){
    return abs(x-y) <= range;
}

int coordsToMapIndex(int x, int y){
    return globals::currentWorld->getMapSize().x*y+x;
}
sf::Vector2f mapIndexToCoords(int mapIndex){
    int width = globals::currentWorld->getMapSize().x;
    int height = globals::currentWorld->getMapSize().y;
    int y = mapIndex/width;
    return {static_cast<float>(mapIndex-y*width),static_cast<float>(y)};
}



//! PATHFINDING ASSUMES THE COORDINATE IS IN THE CENTER OF THE TILE

void generateGraphFromMap(){
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
            if(isEmpty(index) || isCollidable(index)){
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
            if(j!=width-1 && i != height-1 && !isEmpty(index+width+1) && !isCollidable(index+width+1)){
            mapGraph[index].push_back(std::pair<int,double>(index+width+1,std::sqrt(2)));
            mapGraph[index+width+1].push_back(std::pair<int,double>(index+width+1,std::sqrt(2)));
            }
            index++;
        }
    }
}

void dijkstra(int startIndex, std::vector<int> & distance, std::vector<int> & path) {
    int n = mapGraph.size();
    distance.assign(n, 1000000000);
    path.assign(n, -1);

    distance[startIndex] = 0;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> queue;
    queue.push({0, startIndex});
    while (!queue.empty()) {
        int vertex = queue.top().second;
        int distanceToVertex = queue.top().first;
        queue.pop();
        if (distanceToVertex != distance[vertex])
            continue;

        for (auto edge : mapGraph[vertex]) {
            int to = edge.first;
            int length = edge.second;

            if (distance[vertex] + length < distance[to]) {
                distance[to] = distance[vertex] + length;
                path[to] = vertex;
                queue.push({distance[to], to});
            }
        }
    }
}
sf::Vector2f pathfind(sf::Vector2f startPos,sf::Vector2f endPos, sf::FloatRect colliderRect){

    bool lineOfSight = true;
    std::pair<sf::Vector2f, sf::Vector2f> lines[4];
    constexpr float lineSafetyPadding = 0.01f;

    // Define the 4 corners of the AABB being raytraced
    lines[0] = {startPos+sf::Vector2f(-lineSafetyPadding,-lineSafetyPadding), endPos+sf::Vector2f(-lineSafetyPadding,-lineSafetyPadding)};
    lines[1] = {startPos + sf::Vector2f(colliderRect.size.x, 0)+sf::Vector2f(lineSafetyPadding,-lineSafetyPadding), endPos + sf::Vector2f(colliderRect.size.x, 0)+sf::Vector2f(lineSafetyPadding,+lineSafetyPadding)};
    lines[2] = {startPos + sf::Vector2f(0, colliderRect.size.y)+sf::Vector2f(-lineSafetyPadding,lineSafetyPadding), endPos + sf::Vector2f(0, colliderRect.size.y)+sf::Vector2f(-lineSafetyPadding,lineSafetyPadding)};
    lines[3] = {startPos + sf::Vector2f(colliderRect.size.x, colliderRect.size.y)+sf::Vector2f(lineSafetyPadding,lineSafetyPadding), endPos + sf::Vector2f(colliderRect.size.x, colliderRect.size.y)+sf::Vector2f(lineSafetyPadding,lineSafetyPadding)};

    for (auto& line : lines) {
        // Convert float positions to int tile coords
        int x0 = static_cast<int>(line.first.x);
        int y0 = static_cast<int>(line.first.y);
        int x1 = static_cast<int>(line.second.x);
        int y1 = static_cast<int>(line.second.y);

        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;
        while (true) {
            // Check for collision at current tile
            int index = coordsToMapIndex(x0, y0);
            if (globals::currentWorld->getMapTileInfo()[globals::currentWorld->getMap()[index]].flags & 1) {
                lineOfSight = false;
                break;
            }
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }

        if (!lineOfSight)
            break;
    }

    if (lineOfSight)
        return endPos+sf::Vector2f({colliderRect.size.x/2, colliderRect.size.y/2});

    if(endPos.x ==-1 && endPos.y ==-1)
        return startPos;
    sf::Vector2f standardOffset({0.2001F,0.2001F}); //TODO make this not hard coded
    startPos+=standardOffset; 
    endPos+=standardOffset;
    int startIndex=coordsToMapIndex(startPos.x,startPos.y);
    std::vector<int> distance;
    std::vector<int> path;
    dijkstra(startIndex,distance,path);
    int endIndex = coordsToMapIndex(endPos.x,endPos.y);
    int i=endIndex;
    if(startIndex==endIndex)
        return startPos;
    while (path[i]!=startIndex){
        i=path[i];
        if(i ==-1){
            logging::ERROR("Pathfinding-path not found");
            return startPos-standardOffset; 
        }
    }
    sf::Vector2f coords;
    coords = mapIndexToCoords(i);
    coords.x+=0.5;
    coords.y+=0.5;
    return coords;
}

