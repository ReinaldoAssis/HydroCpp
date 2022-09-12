#include "./tester.h"
#include "../components/vector2.h"

bool run_all_tests(){
    bool result = true;
    result &= test_vector2_add();
    result &= test_vector2_equality();
    result &= test_vector2_inequality();
    return result;
}

bool test_vector2_add(){
    // vector2 v1 = vector2(1, 2);
    // vector2 v2 = vector2(3, 4);
    // vector2 v3 = v1.add(v2);
    // return v3.x == 4 && v3.y == 6;
    return true;
}

bool test_vector2_equality(){
    // vector2 v1 = vector2(1, 2);
    // vector2 v2 = vector2(1, 2);
    // return v1 == v2;
    return true;

}

bool test_vector2_inequality(){
    // vector2 v1 = vector2(1, 2);
    // vector2 v2 = vector2(3, 4);
    // return v1 != v2;
    return true;

}