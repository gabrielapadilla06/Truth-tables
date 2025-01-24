#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Evitamos incluir múltiples veces la cabecera
#ifndef FUNCIONES_H
#define FUNCIONES_H

#define COLUMN_WIDTH 13
#define COLUMN_WIDTH_V 4

// Array que contiene los nombres de las variables (A, B, C, ...)
// y sus formas negadas (A', B', C', ...).
const char *variableNames[] = {"A", "B", "C"};
const char *negVariableNames[] = {"A'", "B'", "C'"};

const int negA2[] = {1, 1, 0, 0};
const int negB2[] = {1, 0, 1, 0};

const int negA3[] = {1, 1, 1, 1, 0, 0, 0, 0};
const int negB3[] = {1, 1, 0, 0, 1, 1, 0, 0};
const int negC3[] = {1, 0, 1, 0, 1, 0, 1, 0};

// ---------------------------
// FUNCIÓN: IngresoValores
// ---------------------------
// Propósito: Permite al usuario ingresar los valores de salida (0 o 1) para cada fila de la matriz de verdad.
// rows     - Número de filas en la tabla de verdad.
// cols     - Número de columnas (variables booleanas).
// matrix   - Puntero a la matriz que almacena los valores de las variables en la tabla de verdad.
// solucion - Array donde cada elemento guarda el valor de la salida ingresado por el usuario (0 o 1).
void IngresoValores(int rows, int cols, int *matrix, int *solucion) {
    printf("Ingrese los valores de salida (0 o 1) para cada fila:\n");
    char entrada[10]; // Variable temporal para almacenar la entrada del usuario.
    int temp, esNumero;

    for (int i = 0; i < rows; i++) {
        printf("Fila %d: \n", i + 1);

        // Mostramos las combinaciones de valores de las variables (desde la matriz).
        for (int j = 0; j < cols; j++) {
            printf("%s: %d ", variableNames[j], *(matrix + i * cols + j));
        }

        // Solicitamos la salida al usuario y verificamos que sea un número válido (0 o 1).
        do {
            printf("Salida: ");
            fgets(entrada, sizeof(entrada), stdin); // Leemos la entrada como una cadena.

            // Verificamos si todos los caracteres de la entrada son números.
            esNumero = 1; // Asumimos que la entrada es un número.
            for (int k = 0; entrada[k] != '\0' && entrada[k] != '\n'; k++) {
                if (!isdigit(entrada[k])) {
                    esNumero = 0; // Si no es dígito, marcamos como no numérico.
                    break;
                }
            }

            // Si es un número válido, convertimos y verificamos si está en el rango permitido.
            if (esNumero) {
                temp = atoi(entrada); // Convertimos la cadena a entero.
                if (temp != 0 && temp != 1) {
                    printf("Error: La salida debe ser igual a 0 o a 1.\n");
                    esNumero = 0; // Marcamos como inválido si el número no es 0 ni 1.
                }
            } else {
                printf("Error: Por favor, ingrese un número válido (0 o 1).\n");
            }
        } while (!esNumero); // Repetimos mientras la entrada no sea válida.

        // Almacenamos el resultado ingresado por el usuario en el array de soluciones.
        solucion[i] = temp;
    }
    printf("\n");
}

// ---------------------------
// FUNCIÓN: SumaDeProductos
// ---------------------------
// Propósito: Genera la cadena de texto que representa la expresión booleana en forma de Suma de Productos.
// rows     - Número de filas en la tabla de verdad.
// cols     - Número de columnas (variables booleanas).
// matrix   - Puntero a la matriz que almacena los valores de las variables en la tabla de verdad.
// solucion - Array que contiene los valores de salida (0 o 1) para cada fila.
char *SumaDeProductos(int rows, int cols, int *matrix, int *solucion) {
    // Asignar memoria dinámica para la cadena SOP (Suma de Productos).
    char *sop = (char *)malloc(500 * sizeof(char));
    if (!sop) {
        return NULL; // Manejo de error si la asignación de memoria falla.
    }
    sop[0] = '\0'; // Inicializamos la cadena como vacía.

    int firstTerm = 1; // Variable para controlar el operador "+" entre términos.

    for (int i = 0; i < rows; i++) {
        if (solucion[i] == 1) { // Procesamos filas donde la salida sea 1.
            if (!firstTerm) {
                strcat(sop, " + "); // Agregamos "+" entre términos.
            }
            firstTerm = 0;

            char term[100] = ""; // Almacenaremos el término actual.
            for (int j = 0; j < cols; j++) {
                char temp[10];
                if (*(matrix + i * cols + j) == 1) {
                    // Si el valor es 1, añadimos la variable (A, B, C...).
                    sprintf(temp, "%c", 'A' + j);
                } else {
                    // Si el valor es 0, añadimos la negación de la variable (A', B', C').
                    sprintf(temp, "%c'", 'A' + j);
                }
                strcat(term, temp);

                if (j < cols - 1) {
                    strcat(term, " * "); // Añadimos "*" entre las variables.
                }
            }
            strcat(sop, term); // Añadimos el término completo a la expresión.
        }
    }
    return sop;
}

// ---------------------------
// FUNCIÓN: ImprimirSumaDeProductos
// ---------------------------
// Propósito: Genera y muestra en pantalla la expresión booleana en forma de Suma de Productos.
// rows     - Número de filas en la tabla de verdad.
// cols     - Número de columnas (variables booleanas).
// matrix   - Puntero a la matriz que almacena los valores de las variables en la tabla de verdad.
// solucion - Array que contiene los valores de salida (0 o 1) para cada fila.
void ImprimirSumaDeProductos(int rows, int cols, int *matrix, int *solucion) {
    printf("Expresión en Suma de Productos (SOP):\n");

    int firstTerm = 1; // Usamos para evitar el "+" al inicio.

    for (int i = 0; i < rows; i++) {
        if (solucion[i] == 1) { // Solo procesamos las filas con salida 1.
            if (!firstTerm) {
                printf(" + "); // Agregamos "+" entre términos.
            }
            firstTerm = 0;

            for (int j = 0; j < cols; j++) {
                if (*(matrix + i * cols + j) == 1) {
                    // Si el valor es 1, mostramos la variable.
                    printf("%s", variableNames[j]);
                } else {
                    // Si el valor es 0, mostramos la negación.
                    printf("%s", negVariableNames[j]);
                }

                if (j < cols - 1) {
                    printf(" * "); // Añadimos "*" entre las variables.
                }
            }
        }
    }
    printf("\n");
}

// ---------------------------
// FUNCIÓN: ImprimirTabla
// ---------------------------
// Propósito: Imprime en pantalla la tabla de verdad (valores de las variables y sus salidas).
// rows  - Número de filas en la tabla de verdad.
// cols  - Número de columnas (variables booleanas).
// matrix  - Puntero a la matriz que almacena los valores de las variables en la tabla de verdad.
// solucion - Array que contiene los valores de salida (0 o 1) para cada fila.
void ImprimirTabla(int rows, int cols, int *matrix, int *solucion) {
    printf("\nTabla de Verdad:\n");
    
    // Imprimimos los nombres de las variables en forma de encabezado de la tabla.
    for (int i = 0; i < cols; i++) {
        printf("%s\t", variableNames[i]);
    }
    printf("Salida\n"); // Encabezado para la columna de salida.

    // Iteramos sobre las filas para imprimir sus valores.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Mostramos los valores de cada variable con el color apropiado.
            if (*(matrix + i * cols + j) == 1) {
                printf("\033[0;34m%d\033[0m\t", *(matrix + i * cols + j)); // Azul para 1
            } else {
                printf("%d\t", *(matrix + i * cols + j)); // Color por defecto para 0
            }
        }

        // Mostramos el valor de la salida correspondiente a la fila en color verde.
        printf("\033[0;32m%d\033[0m\n", solucion[i]); // Verde para 1
    }
}

// ---------------------------
// FUNCIÓN: TablaSop
// ---------------------------
// Propósito: Genera una tabla de verdad para una expresión booleana en Suma de Productos (SOP).
// rows  - Número de filas en la tabla de verdad.
// cols  - Número de columnas (variables booleanas).
// matrix - Puntero a la matriz que almacena los valores de las variables.
// sop    - Cadena que representa la expresión en Suma de Productos.
void TablaSop(int rows, int cols, int *matrix, const char *sop) {
    printf("\nTabla de verdad de la expresión %s\n\n", sop);

    // Imprimimos encabezados: nombres de las variables (originales y negadas).
    for (int i = 0; i < cols; i++) {
        printf("%-*s", COLUMN_WIDTH_V, variableNames[i]);
    }
    for (int i = 0; i < cols; i++) {
        printf("%-*s", COLUMN_WIDTH_V, negVariableNames[i]);
    }

    // Extraemos los términos de la expresión SOP.
    char sopCopy[100];
    strncpy(sopCopy, sop, sizeof(sopCopy));
    sopCopy[sizeof(sopCopy) - 1] = '\0';

    char *terms[10];
    int termCount = 0;

    // Dividimos la expresión en términos separados por "+".
    char *term = strtok(sopCopy, "+");
    while (term != NULL) {
        terms[termCount++] = term;
        printf("\033[0;32m%-*s\033[0m", COLUMN_WIDTH, term);
        term = strtok(NULL, "+");
    }

    // Imprimimos encabezado para salida.
    printf("\033[0;31m%-*s\033[0m\n", COLUMN_WIDTH, "Suma (+)");

    for (int i = 0; i < rows; i++) {
        int resultado = 0; // Guardará el resultado final.

        // Imprimimos valores originales.
        for (int j = 0; j < cols; j++) {
            printf("%-*d", COLUMN_WIDTH_V, *(matrix + i * cols + j));
        }

        // Imprimimos valores de las negaciones.
        if (cols == 2) {
            for (int j = 0; j < cols; j++) {
                int negValue = (j == 0) ? negA2[i] : negB2[i];
                printf("%-*d", COLUMN_WIDTH_V, negValue);
            }
        } else {
            for (int j = 0; j < cols; j++) {
                int negValue = (j == 0) ? negA3[i] : (j == 1) ? negB3[i] : negC3[i];
                printf("%-*d", COLUMN_WIDTH_V, negValue);
            }
        }

        // Evaluamos cada término de la SOP:
        for (int t = 0; t < termCount; t++) {
            int termResult = 1; // Guardará el resultado del término actual.

            // Procesamos cada variable dentro del término.
            for (int j = 0; j < strlen(terms[t]); j++) {
                if (terms[t][j] >= 'A' && terms[t][j] <= 'C') {
                    // Determinamos el índice de la variable (0 para A, 1 para B, etc.).
                    int index = terms[t][j] - 'A';

                    // Obtenemos el valor de la variable desde la matriz.
                    int value = *(matrix + i * cols + index);

                    // Verificamos si aparece el apóstrofo (negación).
                    if (terms[t][j + 1] == '\'') {
                        value = !value; // Negamos el valor.
                        j++; // Saltamos el apóstrofo.
                    }

                    // Acumulamos el valor en el resultado del término.
                    termResult &= value;
                }
            }

            // Imprimimos el resultado parcial del término.
            printf("\033[0;32m%-*d\033[0m", COLUMN_WIDTH, termResult);

            // Acumulamos el resultado final con operación OR.
            resultado |= termResult;
        }

        // Imprimimos el resultado final de la fila.
        printf("\033[0;31m%-*d\033[0m\n", COLUMN_WIDTH, resultado);
    }
}

#endif // Fin del include guard