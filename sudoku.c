#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
stdio.h proporciona funcionalidades de entrada y salida, como printf y scanf.
stdbool.h permite usar el tipo de dato bool, representando valores booleanos true y false.
string.h proporciona funciones para manejar strings y arrays, como memcpy y strcpy.
*/

#define DIMENSION 9
//Define una constante DIMENSION con valor 9, que se usa para especificar el tamaño de la matriz del Sudoku (9x9).

typedef struct {
    int matrizInicial[DIMENSION][DIMENSION];
    int matrizJuego[DIMENSION][DIMENSION];
    int numModificaciones;
    char ultimoMovimiento[100];
    char nombreJugador[100];
} Sudoku;

/*
Define una estructura Sudoku que contiene dos matrices 9x9 (una para el estado inicial del juego y otra para el 
estado actual del juego), un contador de modificaciones hechas por el jugador, un string para el último movimiento 
realizado, y un string para el nombre del jugador.
*/

const int matrizInicialPredeterminada[DIMENSION][DIMENSION] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};
// Define e inicializa una matriz constante que representa el estado inicial predeterminado del tablero de Sudoku.


void iniciarJuego(Sudoku* juego) {
/*
Sudoku* juego: Es el parámetro que toma la función, donde Sudoku* indica que se espera un puntero a una variable de 
tipo Sudoku. El uso de un puntero permite modificar la variable original pasada a la función, en este caso,
para inicializar el juego.
*/

    memcpy(juego->matrizInicial, matrizInicialPredeterminada, sizeof(juego->matrizInicial));
    memcpy(juego->matrizJuego, matrizInicialPredeterminada, sizeof(juego->matrizJuego));
    /*
    memcpy es una función de la biblioteca estándar de C que copia un bloque de memoria de un lugar a otro.
    
    juego->matrizInicial y juego->matrizJuego son las direcciones de destino donde se copiarán los datos. 
    El operador -> se utiliza para acceder a los miembros de una estructura a través de su puntero.

    matrizInicialPredeterminada es la matriz de origen que se copiará a las matrices de la estructura Sudoku.

    sizeof(juego->matrizInicial) determina el tamaño del bloque de memoria que se va a copiar. 
    Asegura que la cantidad de datos copiados coincida exactamente con el tamaño de las matrices en la estructura.
    */

    juego->numModificaciones = 0;
    strcpy(juego->ultimoMovimiento, "Inicio del juego");
    /*
    juego->numModificaciones = 0; inicializa el contador de modificaciones en el juego a 0.
    strcpy es una función que copia una cadena de caracteres en otra. 
    Aquí, se utiliza para establecer el mensaje inicial de ultimoMovimiento.
    */
   
    printf("Introduzca el nombre del jugador:\n");
    fgets(juego->nombreJugador, sizeof(juego->nombreJugador), stdin);
    juego->nombreJugador[strcspn(juego->nombreJugador, "\n")] = 0; // Remover el salto de línea

    /*
    printf muestra un mensaje al usuario pidiéndole que introduzca su nombre.
    fgets lee una línea de texto desde la entrada estándar (stdin), incluyendo el salto de línea, 
    y la guarda en juego->nombreJugador. sizeof(juego->nombreJugador) asegura que no se lea más 
    caracteres de los que puede almacenar el array, protegiendo contra desbordamiento de buffer.

    juego->nombreJugador[strcspn(juego->nombreJugador, "\n")] = 0; busca el índice del primer salto 
    de línea en el nombre del jugador y lo reemplaza por el carácter nulo (\0), efectivamente eliminando el salto de línea. 
    
    Esto es necesario porque fgets incluye el salto de línea en la cadena leída si hay espacio suficiente.
    */
}

void imprimirEstadoActual(const Sudoku* juego) {
/*
const Sudoku* juego: Es el parámetro que toma la función. La palabra clave const indica que el puntero juego apunta a un objeto 
de tipo Sudoku que no debe ser modificado por esta función. Esto es útil para asegurar la integridad de los datos del juego 
mientras se accede a ellos solo para lectura. Sudoku* sugiere que se espera un puntero a una estructura de tipo Sudoku, 
permitiendo a la función acceder a sus miembros.
*/

    for (int i = 0; i < DIMENSION; i++) {       
                                        /*
                                        Este bucle for recorre las filas de la matriz matrizJuego dentro de la estructura Sudoku 
                                        apuntada por juego. La variable de iteración i representa el índice de la fila actual, 
                                        comenzando en 0 y terminando en DIMENSION - 1 (donde DIMENSION es una constante predefinida que, 
                                        en el contexto del Sudoku, típicamente tiene un valor de 9, representando el número de filas y 
                                        columnas en un tablero de Sudoku estándar).
                                        */

        for (int j = 0; j < DIMENSION; j++) {
                                        /*
                                        Dentro del bucle de filas, este bucle for itera sobre las columnas de la matriz. 
                                        La variable de iteración j representa el índice de la columna actual. 
                                        Este bucle permite acceder a cada elemento individual juego->matrizJuego[i][j] en la fila i.
                                        */
            printf("%2d ", juego->matrizJuego[i][j]);
                                        /*
                                        printf se utiliza para imprimir el valor de la celda actual de la matriz de juego. 
                                        %2d es el especificador de formato que indica que se debe imprimir un entero (d) con 
                                        un ancho de campo mínimo de dos caracteres (2), asegurando que los números se alineen 
                                        correctamente y el tablero se vea ordenado. Los valores se imprimen con un espacio 
                                        después para separarlos visualmente entre sí.
                                        */
        }
        printf("\n");
    }
}


bool esValido(Sudoku* juego, int fila, int columna, int valor) {
                /*
                Sudoku* juego: Un puntero a una estructura Sudoku que contiene el estado actual del juego.
                int fila: El índice de la fila (basado en cero) donde el jugador desea colocar el valor.
                int columna: El índice de la columna (basado en cero) donde el jugador desea colocar el valor.
                int valor: El valor que el jugador desea colocar en la posición especificada por fila y columna.
                */

    // Verificar fila y columna
    for (int i = 0; i < DIMENSION; i++) {
        if (juego->matrizJuego[fila][i] == valor || juego->matrizJuego[i][columna] == valor) {
            return false;
        }
    }
                /*
                La función itera a través de cada celda en la fila y la columna especificadas usando un bucle for.
                Dentro del bucle, se verifica si el valor ya existe en la misma fila o columna. 
                Esto se hace comparando el valor con cada elemento en la fila especificada (juego->matrizJuego[fila][i]) y 
                en la columna especificada (juego->matrizJuego[i][columna]).

                Si el valor ya está presente en la misma fila o columna, la función retorna false, indicando que el movimiento no es válido.
                */

    // Verificar el subcuadrante de 3x3
    int inicioFila = fila - fila % 3, inicioColumna = columna - columna % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (juego->matrizJuego[i + inicioFila][j + inicioColumna] == valor) {
                return false;
            }
        }
    }
                /*
                Antes de verificar el subcuadrante de 3x3, se calcula el índice de inicio (inicioFila y inicioColumna) para el 
                subcuadrante que contiene la celda especificada por fila y columna. Esto se logra restando el módulo de 3 de fila 
                y columna de sus respectivos valores. Esto asegura que inicioFila y inicioColumna apunten a la esquina superior 
                izquierda del subcuadrante de 3x3 relevante.

                Luego, se itera a través de cada celda dentro de este subcuadrante de 3x3 usando dos bucles for anidados, 
                verificando si el valor ya existe dentro de este subcuadrante.

                Si se encuentra el valor dentro del subcuadrante, la función retorna false, indicando que colocar el valor en la 
                posición dada violaría las reglas del Sudoku.
                */
    return true;
}
                /*
                Si el valor no se encuentra en la misma fila, columna, o subcuadrante de 3x3, la función finalmente retorna true, 
                indicando que el movimiento es válido según las reglas del Sudoku.
                */

bool esSudokuResuelto(Sudoku* juego) {
    for (int fila = 0; fila < DIMENSION; fila++) {
        for (int columna = 0; columna < DIMENSION; columna++) {
            // Verifica si hay casillas vacías
            if (juego->matrizJuego[fila][columna] == 0) {
                return false;
            }
            // Verifica si el número cumple con las reglas del Sudoku
            int valor = juego->matrizJuego[fila][columna];
            juego->matrizJuego[fila][columna] = 0; // Temporalmente elimina el valor para la validación
            bool valido = esValido(juego, fila, columna, valor);
            juego->matrizJuego[fila][columna] = valor; // Restaura el valor
            if (!valido) {
                return false;
            }
        }
    }
    return true;
}


bool ingresarValor(Sudoku* juego, int fila, int columna, int valor) {
   if (juego->matrizInicial[fila][columna] != 0) {
        printf("casilla ocupada\n");
        printf("El valor que hay en la casilla es: %d\n",juego->matrizInicial[fila][columna]);
    }
    else;

    if (valor < 1 && valor > 9) {
        printf("Valor fuera de rango.\n");
        return false;
    }

    if (!esValido(juego, fila, columna, valor)) {
        printf("Movimiento no valido. El numero ya existe en la fila, columna o subcuadrante.\n");
        return false;
    }

    juego->matrizJuego[fila][columna] = valor;
    juego->numModificaciones++;
    snprintf(juego->ultimoMovimiento, 100, "Ingresado %d en (%d,%d)", valor, fila + 1, columna + 1);
    return true;
}


bool resolverSudoku(Sudoku* juego) {
    int fila = -1, columna = -1;
    bool espacioLibre = false;

    // Buscar un espacio libre en la matriz
    for (int i = 0; i < DIMENSION && !espacioLibre; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if (juego->matrizJuego[i][j] == 0) {
                fila = i;
                columna = j;
                espacioLibre = true;
                break;
            }
        }
    }

    // Si no hay espacios libres, el Sudoku está resuelto
    if (!espacioLibre) {
        return true;
    }

    // Intentar llenar el espacio libre con un número válido
    for (int num = 1; num <= DIMENSION; num++) {
        if (esValido(juego, fila, columna, num)) {
            juego->matrizJuego[fila][columna] = num;

            if (resolverSudoku(juego)) {
                return true; // Si la solución es válida, retorna true
            }

            juego->matrizJuego[fila][columna] = 0; // Si no es válida, retrocede
        }
    }

    // Si no se encuentra una solución, retorna falso
    return false;
}


void rotarMatriz90Grados(Sudoku* juego) {
    int temp[DIMENSION][DIMENSION];

    //Función para rotar la matriz
    for (int fila = 0; fila < DIMENSION; fila++) {
        for (int columna = 0; columna < DIMENSION; columna++) {
            temp[fila][columna] = juego->matrizJuego[columna][fila];
        }
    }

    //Función para  invertir cada fila para obtener la rotación de 90 grados
    for (int fila = 0; fila < DIMENSION; fila++) {
        for (int columna = 0; columna < DIMENSION; columna++) {
            juego->matrizJuego[fila][columna] = temp[fila][DIMENSION - 1 - columna];
        }
    }
}



int main() {
    Sudoku juego;
    iniciarJuego(&juego);
    
    int opcion;
    int fila, columna, valor;

    do {
        printf("\nJugador: %s\n", juego.nombreJugador);
        printf("1. Imprimir estado actual del juego\n");
        printf("2. Ingresar un valor\n");
        printf("3. Salir\n");
        printf("4. Resolver Sudoku automaticamente\n");
        printf("5. Rotar matriz 90°\n");

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        imprimirEstadoActual(&juego);

        switch(opcion) {
            case 1:
                imprimirEstadoActual(&juego);
                break;
            case 2:
       printf("Ingrese fila, columna y valor separados por comas (ej. 3,2,5): ");
       scanf("%d,%d,%d", &fila, &columna, &valor);
            if (ingresarValor(&juego, fila - 1, columna - 1, valor)) {
        printf("Valor ingresado correctamente.\n");
        // Llamada a la función para verificar si el Sudoku está resuelto
        if (esSudokuResuelto(&juego)) {
            printf("¡Felicidades, %s! Has completado el Sudoku correctamente.\n", juego.nombreJugador);
            opcion = 3; // Establece la opción a salir para terminar el bucle
        }
    } else {
        printf("No se pudo ingresar el valor.\n");
    }
    break;
            case 3:
                printf("Gracias por jugar, %s. Saliendo...\n", juego.nombreJugador);
                break;
            default:
                printf("Opción no valida.\n");
                break;

            case 4:
            if (resolverSudoku(&juego)) {
                printf("Sudoku resuelto automaticamente:\n");
                imprimirEstadoActual(&juego);
            } else {
                printf("No se encontro una solucion.\n");
            }
            break;

            case 5:
    rotarMatriz90Grados(&juego); // Llamada a la función para rotar la matriz
    printf("Matriz rotada 90 grados:\n");
    imprimirEstadoActual(&juego); // Imprimir el estado actual para ver los cambios
    break;


        }
    } while (opcion != 3);

    return 0;
}