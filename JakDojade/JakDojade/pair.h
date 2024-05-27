#pragma once
template <typename T, typename U>
class Pair {
public:
    Pair() : first(), second() {}
    Pair(const T& first, const U& second) : first(first), second(second) {}
    ~Pair() {}

    T first;
    U second;

    bool operator==(const Pair<T, U>& other) const {
        return first == other.first && second == other.second;
    }

    bool operator!=(const Pair<T, U>& other) const {
        return !(*this == other);
    }

    bool operator<(const Pair<T, U>& other) const {
        if (first < other.first) {
            return true;
        }
        else if (first == other.first) {
            return second < other.second;
        }
        else {
            return false;
        }
    }

    bool operator>(const Pair<T, U>& other) const {
        return other < *this;
    }

    bool operator<=(const Pair<T, U>& other) const {
        return !(other < *this);
    }

    bool operator>=(const Pair<T, U>& other) const {
        return !(*this < other);
    }
    friend std::ostream& operator<<(std::ostream& os, const Pair<T, U>& pair) {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
};