#pragma once
#include "str.h"
#include "vec.h"
#include "point.h"
#include "queue.h"
#include "pair.h"
#include "priority_queue.h"
#include "hash_map.h"


struct Road {
    int x = 0, y = 0;
    int length = 0;
};

bool isInArray(int x, int y, int height, int width) {
    return (x >= 0 && x < height && y >= 0 && y < width);
}
bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool isName(int x, int y, int height, int width, char**& array, String& s) {
    String city_name = "";
    if (isInArray(x, y, height, width) && isAlpha(array[x][y])) {
        if (!isInArray(x, y - 1, height, width) || !isInArray(x, y + 1, height, width)) {
            while (isInArray(x, y - 1, height, width) && isAlpha(array[x][y - 1])) {
                y--;
            }
            while (isInArray(x, y, height, width) && isAlpha(array[x][y])) {
                s.append_char(array[x][y]);
                y++;
            }
            return true;
        }
        else if ((isInArray(x, y - 1, height, width) && !isAlpha(array[x][y - 1])) || (isInArray(x, y + 1, height, width) && !isAlpha(array[x][y + 1]))) {
            while (isInArray(x, y - 1, height, width) && isAlpha(array[x][y - 1])) {
                y--;
            }
            while (isInArray(x, y, height, width) && isAlpha(array[x][y])) {
                s.append_char(array[x][y]);
                y++;
            }
            return true;
        }
    }
    return false;
}
void find_city_name(int i, int j, int height, int width, char**& array, String& s) {
    int di[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dj[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int k = 0; k < 8; k++) {
        int ni = i + di[k];
        int nj = j + dj[k];
        if (isName(ni, nj, height, width, array, s)) {
            return;
        }
    }
}

bool add_road(int i, int j, int height, int width, char**& copy_array, Queue<Road>& q, int length, Road r, bool**& visited) {
    int di[] = { -1, 0, 0, 1 };
    int dj[] = { 0, -1, 1, 0 };
    int counter = 0;
    for (int k = 0; k < 4; k++) {
        int x = i + di[k];
        int y = j + dj[k];
        if (isInArray(x, y, height, width) && !visited[x][y] && (copy_array[x][y] == '#' || copy_array[x][y] == '*')) {
            counter++;
            r.x = x;
            r.y = y;
            r.length = length + 1;
            q.push(r);
            visited[x][y] = true;
        }
    }
    if (counter == 0)
        return false;
    return true;
}

void shortest_path(String source, Vector<Point>& cities, String target, int t, Hash_Map& hash_map) {
    int num_cities = cities.getSize();
    int* previous = new int[num_cities];
    int* distances = new int[num_cities];
    for (int i = 0; i < num_cities; i++) {
        previous[i] = -1;
        distances[i] = INT_MAX;
    }
    int start = hash_map.get(source);
    int dest = hash_map.get(target);
    distances[start] = 0;

    Priority_Queue<Pair<int, int>> queue;
    Pair<int, int> newPair(start, 0);
    queue.push(newPair, 0);
    
    while (!queue.empty()) {
        int current_index = queue.front().first;
        queue.pop();

        if (current_index == dest) {
            int distance = distances[dest];
            if (t == 1) {
                std::cout << distance;
                Vector<String> cities_by_the_way;
                int id = previous[dest];
                while (id != start && id != -1) {
                    cities_by_the_way.push_back(cities[id].getName());
                    id = previous[id];
                }
                for (int i = cities_by_the_way.getSize() - 1; i >= 0; i--) {
                    std::cout << " " << cities_by_the_way[i];
                }
                std::cout << std::endl;
            }
            else {
                std::cout << distance << std::endl;
            }
            delete[] previous;
            delete[] distances;
            return;
        }
        for (int i = 0; i < cities[current_index].getEdges().getSize(); i++) {
            String city_name = cities[current_index].getEdges()[i].first;
            int edge_length = cities[current_index].getEdges()[i].second;
            int new_index = hash_map.get(city_name);

            if (distances[current_index] + edge_length < distances[new_index]) {
                distances[new_index] = distances[current_index] + edge_length;
                previous[new_index] = current_index;
                Pair<int, int> newPair(new_index, distances[new_index]);
                queue.push(newPair, distances[new_index]);
            }
        }
    }
    delete[] previous;
    delete[] distances;
    return;
}





//MAIN

void reading_section(int height, int width, char**& array) {
    for (int i = 0; i < height; i++) {
        array[i] = new char[width];
        for (int j = 0; j < width; j++) {
            char c;
            while ((c = getchar()) == '\n' || c == '\r') {}
            array[i][j] = c;
        }
    }
}
void parsing_section(int height, int width, char**& array, Vector<Point>& cities, Hash_Map& hash_map) {
    bool** visited = new bool* [height];
    for (int i = 0; i < height; i++) {
        visited[i] = new bool[width];
        memset(visited[i], false, width * sizeof(bool));
    }
    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (array[i][j] == '*') {
                String city1;
                find_city_name(i, j, height, width, array, city1);
                Point p;
                p.setName(city1);
                hash_map.put(city1, counter);
                counter++;
                Queue<Road> q;
                Road r;
                bool are_there_any_neighbours = add_road(i, j, height, width, array, q, 0, r, visited);
                while (!q.empty()) {
                    int x = q.front().x;
                    int y = q.front().y;
                    int length = q.front().length;
                    q.pop();
                    if (array[x][y] == '*') {
                        String city2;
                        find_city_name(x, y, height, width, array, city2);
                        if (city1 != city2) {
                            p.addEdge(city2, length);
                        }
                    }
                    else {
                        add_road(x, y, height, width, array, q, length, r, visited);
                    }
                }
                cities.push_back(p);
                if (are_there_any_neighbours == false)
                    continue;
                visited[i][j] = true;
                for (int i = 0; i < height; i++) {
                    memset(visited[i], false, width * sizeof(bool));
                }
            }
        }
    }
    for (int i = 0; i < height; i++) {
        delete[] visited[i];
    }
    delete[] visited;
}
void air_links_section(Vector<Point>& cities, Hash_Map& hash_map) {
    int air_links;
    std::cin >> air_links;
    for (int i = 0; i < air_links; i++) {
        String s, d;
        int t;
        char c;
        c = getchar();
        while ((c = getchar()) != ' ') {
            s.append_char(c);
        }
        while ((c = getchar()) != ' ') {
            d.append_char(c);
        }
        std::cin >> t;
        cities[hash_map.get(s)].addEdge(d, t);
    }
}
void shortest_path_section(Vector<Point>& cities, Hash_Map& hash_map) {
    int question_number;
    std::cin >> question_number;
    for (int i = 0; i < question_number; i++) {
        String s, d;
        int t;
        std::cin >> s >> d >> t;
        s.remove_char('\n');
        if (s == d)
            std::cout << 0 << std::endl;
        else
            shortest_path(s, cities, d, t, hash_map);
    }
}
void free_memory(int height, char**& array) {
    for (int i = 0; i < height; i++) {
        delete[] array[i];
    }
    delete[] array;
}
