#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Definición de tipos básicos
typedef char DATA;
typedef struct elemento {
    DATA d;
    struct elemento *siguiente;
} ELEMENTO;

typedef struct {
    int cnt;
    ELEMENTO *tope;
} PILA;

// Funciones de Pila
void inicializar(PILA *s) {
    s->cnt = 0;
    s->tope = NULL;
}

void push(PILA *s, DATA x) {
    ELEMENTO *nuevo = (ELEMENTO *)malloc(sizeof(ELEMENTO));
    nuevo->d = x;
    nuevo->siguiente = s->tope;
    s->tope = nuevo;
    s->cnt++;
}

DATA pop(PILA *s) {
    if (s->cnt == 0) {
        printf("Error: Pila vacía\n");
        exit(1);
    }
    ELEMENTO *temp = s->tope;
    DATA dato = temp->d;
    s->tope = temp->siguiente;
    free(temp);
    s->cnt--;
    return dato;
}

int estavacia(PILA *s) {
    return s->cnt == 0;
}

// Función para saber si es palíndromo
int esPalindromo(char cadena[]) {
    PILA original, invertida;
    inicializar(&original);
    inicializar(&invertida);
    int i, longitud = strlen(cadena);

    for (i = 0; i < longitud; i++) {
        if (isalpha(cadena[i])) {
            char letra = tolower(cadena[i]);
            push(&original, letra);
        }
    }

    while (!estavacia(&original)) {
        push(&invertida, pop(&original));
    }

    // Compara las pilas
    inicializar(&original); // Reinicializar para volver a llenar
    for (i = 0; i < longitud; i++) {
        if (isalpha(cadena[i])) {
            char letra = tolower(cadena[i]);
            push(&original, letra);
        }
    }

    while (!estavacia(&original)) {
        if (pop(&original) != pop(&invertida)) {
            return 0; // No es palíndromo
        }
    }

    return 1; // Es palíndromo
}

int main() {
    char prueba1[] = "Anita lava la tina";
    char prueba2[] = "Estructuras de Datos";
    printf("--- TEST DE PALINDROMOS ---\n");
    printf("Prueba 1: '%s' -> %s\n", prueba1, esPalindromo(prueba1) ? "ES PALINDROMO" : "NO ES PALINDROMO");
    printf("Prueba 2: '%s' -> %s\n", prueba2, esPalindromo(prueba2) ? "ES PALINDROMO" : "NO ES PALINDROMO");
    return 0;
}
