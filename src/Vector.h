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

    // Pre: cantidadDatos no puede ser mayor a tamanio. NOTA: Esto se maneja internamente.
    // Post: Copia los datos del vector a uno nuevo con tamaño modificado y reasigna.
    void copiarDatos();

    // Pre: -
    // Post: Genera un nuevo vector en memoria con tamaño 1.
    void generarVector();

    // Pre: -
    // Post: Duplica el tamaño del vector.
    void ampliarVector();

    // Pre: -
    // Post: Reduce el tamaño del vector a la mitad. Si no hay ningun dato, libera la memoria.
    void reducirVector();

    // Pre: -
    // Post: Verifica y aumenta el tamaño del vector si esta lleno o lo reduce a la mitad de ser posible.
    void verificarTamanio();

public:
    // Pre: -
    // Constructor.
    Vector();

    // Pre: -
    // Post: Agrega el dato al final del vector.
    void pushBack(Dato dato);

    // Pre: -
    // Post: Elimina y devuelve el ultimo dato del vector. Si no hay ninguno, lanza excepcion.
    Dato popBack();

    // Pre: -
    // Post: Devuelve la cantidad de datos del vector.
    size_t size();

    // Pre: El indice no puede ser igual o mayor a la cantidad de datos (0-indexed).
    // Post: Devuelve una referencia al dato deseado.
    Dato& operator[](size_t indice);

    // Destructor.
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