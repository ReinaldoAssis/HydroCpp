#ifndef VECTOR2_H
#define VECTOR2_H

#define VECTOR2_INVALID vector2(-1, -1)

#include <string>
#include <vector>

struct vector2 {
  int x;
  int y;
  vector2(int x, int y) {
    this->x = x;
    this->y = y;
  }

  vector2 add(vector2 v) {
    this->x += v.x;
    this->y += v.y;
    return *this;
  }

  bool operator==(vector2 v) { return this->x == v.x && this->y == v.y; }

  bool operator!=(vector2 v) { return !(*this == v); }

  vector2 operator+=(vector2 v) {
    this->add(v);
    return *this;
  }

  vector2 operator+(vector2 v) { return vector2(this->x + v.x, this->y + v.y); }

  vector2 operator-(vector2 v) { return vector2(this->x - v.x, this->y - v.y); }

  std::string toStr() {
    return std::string(std::to_string(this->x) + " " + std::to_string(this->y));
  }

  static bool contains(std::vector<vector2> v, vector2 vec) {
    for (int i = 0; i < v.size(); i++)
      if (vec == v[i])
        return true;

    return false;
  }
};

#endif #pragma once
