# Deber de Programacion Numero2  pa2u2:Gestion de Procesos e IPC

Este programa permite verificar si un sudoku ya establecido en el programa es considerado como valido o invalido, para realizar esto se hizo la creacion de varios hilos para que verifiquen diferentes partes del tablero, especificamente se creo un hilo para verificar las columnas , otro hilo para verificar las filas, y 9 hilos en donde cada uno verifica que un sector sea valido. Con validez nos referimos a que ningun numero se repita tanto en filas, columnas o en los determinados cuadrantes de 3x3. Dentro del programa del codigo fuente se han puesto dos tableros, pueden entrar al codigo e intercambiar el nombre de las matrices, por ejemplo la "matriz" pasaria a llamarse "matriz2" y la "matriz 2" pasaria llamarse "matriz", de esa forma pueden comprobar los dos escenarios tanto cuando una matriz es valida y cuando una matriz es invalida

## Compilación

Para eliminar los archivos creados al hacer uso del Makefile:

```bash
make clean
```

Para crear los archivos necesarios para la ejecucion del programa:

```bash
make
```

## Uso

Uso: Determina la validez de un tablero de Sudoku, si desea probar el otro tablero debe intercambiar el nombre de las variables que contienen a las matrices.


```bash
./build/sudoku
```                                                                                                                                                                                                                                                                                                                                                                                                             
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                    
