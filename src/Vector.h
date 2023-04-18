#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

class IndiceNoValidoException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: el indice ingresado no es valido.";
    }
};

class VectorVacioException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Error: no se puede eliminar el dato porque el vector esta vacio.";
    }
};

template<typename Dato>
class Vector {
private:
    Dato* datos;
    size_t tamanio{};
    size_t cantidadDatos{};

    void copiarDatos();

    void generarVector();

    void ampliarVector();

    void reducirVector();

    void verificarTamanio();

public:
    Vector();

    void pushBack(Dato dato);

    Dato popBack();

    size_t size();

    Dato& operator[](size_t indice);

    ~Vector();
};

template<typename Dato>
Vector<Dato>::Vector() {
    datos = nullptr;
    tamanio = 0;
    cantidadDatos = 0;
}

template<typename Dato>
void Vector<Dato>::copiarDatos() {
    Dato* nuevoVector = new Dato[tamanio];
    for (size_t i = 0; i < cantidadDatos; i++) {
        nuevoVector[i] = datos[i];
    }
    delete[] datos;
    datos = nuevoVector;
}

template<typename Dato>
void Vector<Dato>::generarVector() {
    datos = new Dato[1];
    tamanio = 1;
}

template<typename Dato>
void Vector<Dato>::ampliarVector() {
    tamanio *= 2;
    copiarDatos();
}

template<typename Dato>
void Vector<Dato>::reducirVector() {
    if (cantidadDatos == 0) {
        delete[] datos;
        datos = nullptr;
        tamanio = 0;
    } else {
        tamanio /= 2;
        copiarDatos();
    }
}

template<typename Dato>
void Vector<Dato>::verificarTamanio() {
    if (tamanio == 0) {
        generarVector();
    } else if (cantidadDatos == tamanio) {
        ampliarVector();
    } else if (cantidadDatos == tamanio / 2) {
        reducirVector();
    }
}

template<typename Dato>
void Vector<Dato>::pushBack(Dato dato) {
    verificarTamanio();
    datos[cantidadDatos] = dato;
    cantidadDatos++;
}

template<typename Dato>
Dato Vector<Dato>::popBack() {
    if (cantidadDatos == 0) {
        throw VectorVacioException();
    } else {
        Dato dato = datos[--cantidadDatos];
        verificarTamanio();
        return dato;
    }
}

template<typename Dato>
size_t Vector<Dato>::size() {
    return cantidadDatos;
}

template<typename Dato>
Dato& Vector<Dato>::operator[](size_t indice) {
    if (indice >= cantidadDatos) {
        throw IndiceNoValidoException();
    } else {
        return datos[indice];
    }
}

template<typename Dato>
Vector<Dato>::~Vector() {
    delete[] datos;
}

#endif