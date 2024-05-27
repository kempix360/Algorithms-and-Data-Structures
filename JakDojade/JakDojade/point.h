#pragma once
#include "str.h"
#include "pair.h"
#include "vec.h"

class Point {
private:
    Vector<Pair<String, int>> list;
    String name;
public:
    Point() : list(Vector<Pair<String, int>>()), name(String()) {}
    ~Point() {}
    Point(const Point& other) : list(other.list), name(other.name) {}

    Point& operator=(const Point& other) {
        if (this != &other) {
            list = other.list;
            name = other.name;
        }
        return *this;
    }
    String getName() {
        return name;
    }
    void setName(String name) {
        this->name = name;
    }
    Vector<Pair<String, int>> getEdges() {
        return list;
    }
    void setList(Vector<Pair<String, int>> list) {
        this->list = list;
    }
    void addEdge(String city, int length) {
        Pair<String, int> pair(city, length);
        list.push_back(pair);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "Name of the city: " << p.name << std::endl;
        os << p.list << std::endl;
        return os;
    }
};
