#ifndef ALGO2_GIT_VECTOR_TEMPLATE_VECTOR_H
#define ALGO2_GIT_VECTOR_TEMPLATE_VECTOR_H

template<typename generico>
class Vector {
private:
    int tamanio;
    int cantidad;
    generico* elementos;

public:
    Vector();

    void expandirVector();

    void reducirVector();

    void pushBack(generico algo);

    generico popBack();

    generico& elemento(int indice);

    ~Vector();
};

template<typename generico>
void Vector<generico>::expandirVector() {
    tamanio *= 2;
    generico* auxiliar = new generico[tamanio];
    for (int i = 0; i < cantidad; i++) {
        auxiliar[i] = elementos[i];
    }
    delete[] elementos;
    elementos = auxiliar;
}


#endif
