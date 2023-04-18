#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    Vector<int> vector;

    for (int i = 1; i <= 5; i++) {
        vector.pushBack(i * i);
    }

    for (size_t i = 0; i < vector.size(); i++) {
        cout << vector[i] << endl;
        vector[i] += 1;
    }

    while (vector.size()) {
        cout << "Elimine el elemento: " << vector.popBack() << endl;
    }

    return 0;
}