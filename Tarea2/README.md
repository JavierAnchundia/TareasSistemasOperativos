# Deber de Programacion Numero2  pa2u2:Gestion de Procesos e IPC

Este programa permite correr cualquier comando (incluyendo parametros) que se pase como parametro al programa y calcula el tiempo en microsegundos que dicho programa se tarda en poder ejecutar.
Es un programa que tiene dos versiones, la diferencia entre ambas es que una usa shared memory para poder intercambiar mensajes entre el proceso hijo y el proceso padre, mientras 
que la otra utiliza pipe para el intercambio de mensajes.

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

Uso: Ejecuta cualquier comando (incluyendo parametros) pasado como parametro al programa y calcula el tiempo en microsegundos que se tarda en ejecutar.

Version1: Usando SharedMemory

```bash
./build/timeshmm [comando] [parametros]
```
Version2: Usando Pipe

```bash
./build/timepipe [comando] [parametros]
```
                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                    
