#include "cola.h"
#include <stdlib.h>
typedef struct nodo nodo_t;
struct nodo { 
    void* dato;
    struct nodo* siguiente;
};

struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};

/* PRIMITIVAS DE LA COLA */



cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if (cola == NULL) {
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)){
    while (cola_esta_vacia(cola) == false){
        if (destruir_dato != NULL){
            destruir_dato(cola->primero->dato);
        }
        cola_desencolar(cola);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->primero == NULL && cola->ultimo == NULL;
}

nodo_t* crear_nodo(void* valor) { 
    nodo_t* nodo = malloc(sizeof(nodo_t)); 
    if (!nodo) {
        return NULL; 
    }
    nodo->dato = valor; 
    nodo->siguiente = NULL; 
    return nodo; 
}

bool cola_encolar(cola_t *cola, void* valor){
    nodo_t* nodo = crear_nodo(valor);
    if (nodo == NULL){
        return false;
    } 
    if(cola_esta_vacia(cola) == true){
        cola->primero = nodo;
    } else{
        cola->ultimo->siguiente = nodo; 
    }
    cola->ultimo = nodo;
    return true;
}

void* cola_ver_primero(const cola_t *cola){
    if(cola_esta_vacia(cola) ==true){
        return NULL;
    }
    return (cola->primero->dato);
}

void* cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola) == true){
        return NULL;
    }
    void* dato_desencolado = cola->primero->dato;
    nodo_t* nuevo_primero = cola->primero->siguiente;
    free(cola->primero);
    if (nuevo_primero == NULL){
        cola->primero = NULL;
        cola->ultimo = NULL;    
    }else {
        cola->primero = nuevo_primero;
    }
    return dato_desencolado;
}