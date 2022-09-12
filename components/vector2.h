#ifndef VECTOR2_H
#define VECTOR2_H

#define VECTOR2_INVALID vector2(-1, -1)

struct vector2{
    int x;
    int y;
    vector2(int x, int y){
        this->x = x;
        this->y = y;
    }

    vector2 add(vector2 v){
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    bool operator==(vector2 v){
        return this->x == v.x && this->y == v.y;
    }

    bool operator!=(vector2 v){
        return !(*this == v);
    }
};

#endif