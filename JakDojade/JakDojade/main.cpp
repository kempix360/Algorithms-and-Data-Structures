#include <iostream>
#include "vec.h"
#include "point.h"
#include "hash_map.h"
#include "main_functions.h"
using namespace std;

int main() {
    int height;
    int width;
    cin >> width;
    cin >> height;
    char** array = new char* [height];
    Vector<Point> cities;
    Hash_Map hash_map;

    reading_section(height, width, array);
    parsing_section(height, width, array, cities, hash_map);
    air_links_section(cities, hash_map);
    shortest_path_section(cities, hash_map);
    free_memory(height, array);

    return 0;
}