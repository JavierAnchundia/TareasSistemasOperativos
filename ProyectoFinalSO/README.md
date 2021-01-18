# Deber de Programacion Numero2  pa2u2:Gestion de Procesos e IPC

Este programa permita simular el funcionamiento de la memoria virtual, esto conlleva llevar conocimientos teóricos a la práctica, tales como la tabla de páginas, la traducción de dirección lógicas a dirección físicas y la paginación por demanda. El usuario puede ingresar un archivo con direcciones logicas y especificar un archivo en el que quiera recibir los resultados, el sistema se encargara de escribir en el archivo de destino los resultados de la traduccion de direcciones con el siguiente formato: Virtual address: abcd Physical address: efgh Value: xyz. El programa simula la memoria secundaria con un archivo binario, del cual va a obtener datos en caso de que existen Fallos de Paginas.


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

Uso: Genera la traduccion desde un archivo origen de direcciones logicas hacia un archivo destino que contendra las traducciones con el siguiente formato: Virtual address: abcd Physical address: efgh Value: xyz.

```bash
./build/pagindemand ./addresses.txt ./data.tx
```                                                                                                                                                                                                                                                                                                                                                                                                             
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                                                                                                                                                                                                          
~                    
