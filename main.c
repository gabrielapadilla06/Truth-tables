#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h" // Biblioteca de funciones personalizada.

// Definir macros para generar las matrices de verdad según el número de variables.
#define MATRIX2 (int[4][2]){ \
    {0, 0}, \
    {0, 1}, \
    {1, 0}, \
    {1, 1} \
}

#define MATRIX3 (int[8][3]){ \
    {0, 0, 0}, \
    {0, 0, 1}, \
    {0, 1, 0}, \
    {0, 1, 1}, \
    {1, 0, 0}, \
    {1, 0, 1}, \
    {1, 1, 0}, \
    {1, 1, 1} \
}

// Validación para entrada de números enteros.
int entradaNumericaValida() {
    char entrada[10];
    int esValido = 0, numero = 0;
    do {
        printf("Ingrese el numero de variables booleanas (2 o 3): ");
        fgets(entrada, sizeof(entrada), stdin);
        esValido = 1;

        // Validar que la entrada sea numérica.
        for (int i = 0; entrada[i] != '\0' && entrada[i] != '\n'; i++) {
            if (!isdigit(entrada[i])) {
                esValido = 0;
                break;
            }
        }

        // Si es válida, convertir a entero y validar rango.
        if (esValido) {
            numero = atoi(entrada);
            if (numero != 2 && numero != 3) {
                esValido = 0;
                printf("Error: las opciones válidas son 2 o 3. Intenta de nuevo.\n");
            }
        } else {
            printf("Error: por favor, ingrese un número válido (2 o 3).\n");
        }
    } while (!esValido);
    return numero;
}

int main() {
    int opcion, rows, cols;
    // ------------------------------
    // Solicitar al usuario el número de variables booleanas.
    // ------------------------------
    opcion = entradaNumericaValida();

    // ------------------------------
    // Seleccionar la matriz de verdad según el número de variables ingresado.
    // ------------------------------
    int (*matrix)[3] = NULL;

    if (opcion == 2) {
        matrix = (int(*)[3])MATRIX2; // Cast para que sea compatible con int[3].
        rows = 4;
        cols = 2;
    } else {
        matrix = MATRIX3;
        rows = 8;
        cols = 3;
    }

    // Array para guardar las salidas ingresadas por el usuario.
    int solucion[rows];

    // ------------------------------
    // Ingreso de los valores de salida para cada combinación (fila de la tabla).
    // ------------------------------
    IngresoValores(rows, cols, *matrix, solucion);

    // ------------------------------
    // Generar y mostrar la expresión en Suma de Productos (SOP).
    // ------------------------------
    ImprimirSumaDeProductos(rows, cols, *matrix, solucion);

    // ------------------------------
    // Imprimir la tabla de verdad con las entradas y sus salidas.
    // ------------------------------
    ImprimirTabla(rows, cols, *matrix, solucion);

    // ------------------------------
    // Evaluar y mostrar la tabla de verdad para una expresión SOP.
    // ------------------------------
    char *sopExpression = SumaDeProductos(rows, cols, (int *)matrix, solucion);
    TablaSop(rows, cols, *matrix, sopExpression);

    // Liberar memoria de la expresión SOP.
    free(sopExpression);

    return 0;
}
