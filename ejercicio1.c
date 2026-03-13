/* 
 * Objetivo: Completar las primitivas de la pila para evaluación de RPN.
 */

#include <pilas.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

// =========================================================
// SECCIÓN 1: PRIMITIVAS DE LA PILA (A IMPLEMENTAR)
// =========================================================

// Funcion inicializar
void inicializar(PILA *stk) {
    TODO: 
       stk->cnt = 0;
       stk->tope = NULL;
}

// Funcion push
void push(PILA *stk, DATO x) {
    TODO: 
       ELEMENTO *nuevo = (ELEMENTO*)malloc(sizeof(ELEMENTO));
       if (nuevo == NULL) {
       printf("ERROR: DESBORDAMIENTO DE MEMORIA\n");
       exit(1);
       }
       nuevo->d = x;
       nuevo->siguiente = stk->tope;
       stk->tope = nuevo;
       stk->cnt++;
}

// Funcion pop
DATO pop(PILA *stk) {
    if (estavacia(stk)) {
        printf("ERROR: Intento de POP en pila vacia (Stack Underflow)\n");
        exit(1); 
    }
        TODO: 
        DATO valor_retorno;
        ELEMENTO *temp;
        temp = stk->tope;
        valor_retorno = temp->d;
        stk->tope = temp->siguiente;
        stk->cnt--;
        free(temp);
        return valor_retorno;
}

// Funcion estavacia
BOOLEAN estavacia(PILA *stk) {
    /* TODO: Retornar VERDADERO si el contador es 0, FALSO de lo contrario. */
    return FALSO; 
}

// Funcion estallena
BOOLEAN estallena(PILA *stk) {
    /* TODO: Retornar VERDADERO si el contador es igual a FULL. */
    return FALSO;
}

// =========================================================
// SECCIÓN 2: LÓGICA DE ALTO NIVEL (DESCRIPCIÓN INCLUIDA)
// =========================================================

// Funcion rellenar
void rellenar(PILA *stk, const char *str){
    const char *p = str; 
    char c1, c2; 
    BOOLEAN b1, b2; 
    DATO d; 
    PILA aux; 

    inicializar(stk); // Inicializamos la pila principal antes de llenarla.
    inicializar(&aux); // Inicializamos la pila auxiliar para invertir el orden.

    while (*p != '\0') {
        while(isspace(*p) || *p == '\t' || *p == ',') { 
            p++; // Saltamos espacios, tabulaciones y comas.
        }
        if (*p == '\0') break;

        b1 = (BOOLEAN) ((c1 = *p) == '+' || c1 == '-' || c1 == '*'); 
        b2 = (BOOLEAN) ((c2 = *(p + 1)) == ' ' || c2 == '\t' || c2 == ',' || c2 == '\0'); 

        if (b1 && b2) { 
            d.tipo = OPERADOR; // Establecemos el tipo del dato como OPERADOR.
            d.u.op = c1; // Asignamos el operador actual.
            p++;
        }
        else {
            d.tipo = VALOR;
            // Extraemos el valor entero de la cadena y lo almacenamos en val.
            assert(sscanf(p, "%d", &d.u.val) == 1); 
            while (*p != '\0' && !isspace(*p) && *p != '\t' && *p != ',') {
                p++; // Avanzamos p hasta el siguiente separador.
            }
        }
        
        if (!estallena(&aux)) { 
            push(&aux, d); // Empujamos a la auxiliar para procesar la cadena.
        }
    }
    
    // Ahora tomamos el dato de la pila auxiliar y lo pasamos a la principal.
    // Esto invierte el orden para que se procesen correctamente después.
    while (!estavacia(&aux)) { 
        d = pop(&aux); 
        if (!estallena(stk)) { 
            push(stk, d); 
        }
    }
}

// Funcion evaluar
int evaluar(PILA *polaca) {
    DATO d, d1, d2;
    PILA evaluacion;

    // Inicializar la pila de evaluación para almacenar los operandos.
    inicializar(&evaluacion); 

    while(!estavacia(polaca)) {
        d = pop(polaca);
        switch (d.tipo) { 
            case VALOR: 
                // Si el dato es un valor, se empuja a la pila de evaluación.
                push(&evaluacion, d); 
                break;
            case OPERADOR: 
                // Sacamos los dos argumentos de la pila de evaluación.
                // d2 es el segundo operando y d1 el primero (LIFO).
                d2 = pop(&evaluacion); 
                d1 = pop(&evaluacion);
                d.tipo = VALOR; // El resultado será un VALOR.
                switch (d.u.op) { 
                    case '+': d.u.val = d1.u.val + d2.u.val; break;
                    case '-': d.u.val = d1.u.val - d2.u.val; break;
                    case '*': d.u.val = d1.u.val * d2.u.val; break;
                }
                // Empujamos el resultado de vuelta para futuras operaciones.
                push(&evaluacion, d); 
                break;
        }
    }

    // El resultado final se encuentra en el tope de la pila de evaluación.
    d = pop(&evaluacion); 
    return d.u.val; 
}

int main(void) {
    char str[] = "3 4 5 + *"; // Representa (4 + 5) * 3 = 27
    PILA polaca;

    printf("--- INICIO DE PRÁCTICA ---\n");
    inicializar(&polaca); 
    printf("Expresion: %s\n", str);
    
    rellenar(&polaca, str);  
    printf("Resultado esperado: 27\n");
    printf("Resultado obtenido: %d\n", evaluar(&polaca)); 

    return 0;
}
