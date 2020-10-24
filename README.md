# Deber de Programacion Numero1 pa1:Syscalls

Este programa lee el archivo que recibe como parámetro y muestra su contenido en pantalla, si no recibe un parámetro lee a partir de la entrada estándar. Muy similar al comando cat de linux

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

Uso 1: muestra el contenido de un archivo, en el ejemplo mycat muestra el contenido de prueba.txt

```bash
./build/mycat prueba.txt
```

Uso 2: muestra el contenido que recibe desde la entrada estándar, en el ejemplo se utiliza junto con el pipe | para redirigir la salida del comando sort a nuestro programa mycat.

```bash
sort prueba.txt | ./build/mycat
```

Otra forma de uso es que reescribe por consola todo lo que se escriba.

```bash
./build/mycat
```


