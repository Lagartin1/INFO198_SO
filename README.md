# INFO198_SO
## Descripcion
Este programa es un sistema que permite a los usuarios interactuar con un menú personalizado compuesto por cinco opciones:
detección de palíndromos, conteo de vocales, conteo de letras en un texto, cálculo del promedio y sumatoria de un vector, y 
evaluación de la función f(x) = 5x^2 + 1/x . El usuario proporciona los datos necesarios mediante argumentos de 
línea de comandos para ejecutar las opciones correspondientes, como nombre de usuario, contraseña, frase de texto,
vector de números, y un valor numérico.

## Requisitos
Para compilar este programa en C++, se necesitan los siguientes elementos:

- **Compilador C**: GCC para compliar C++.
- **Sistema Operativo**: Preferentemente Linux o cualquier sistema compatible con compiladores estándar de C.
- **Bibliotecas estándar de C**: Asegúrate de tener instaladas las bibliotecas estándar necesarias para la entrada/salida y manejo de cadenas.
- **Terminal**: Acceso a una terminal para compilar y ejecutar el programa utilizando línea de comandos.
## Instalacion / Compilacion
Para compilar el programa, sigue los siguientes pasos:

1. Navega al directorio raíz del proyecto donde se encuentra el `Makefile`.
2. Ejecuta el siguiente comando en la terminal:

   ```bash
   make
## Ejecucion

Una vez que el programa ha sido compilado correctamente, puedes ejecutarlo desde la terminal de la siguiente manera:

1. Navega al directorio `bin/` donde se encuentra el archivo ejecutable `app`.

   ```bash
   cd bin/
2. Asegure tener cargada la variable de entorno CSV_FILE_PATH que contiene los datos de ingreso.
   Debes obtener la ruta al archivo ` Users.txt` precente en el directorio  `/Data` de este programa,y cargarlo a las varibales de entorno.
    * Para Linux/MacOS (bash) debe ser de la forma:
        ```bash
        export TXT_FILE_PATH="/ruta/al/archivo/Users.txt"
        ```

3. Ejecuta el programa proporcionando los argumentos necesarios. El formato general es:
    ```bash
    ./app -u <nombre_usuario> -p <contraseña> -t <frase_de_texto> -v <vector_de_números> -n <número>
    ```
    A continuación se detallan los argumentos:
    | Argumento | Descripcion |
    | -------- | ----------- |
    | u | Especifica el usuario |
    | p | Especifica la contraseña del usuario |
    | t | Especifica el texto que quiere ser procesado en las funciones del sistema. Debe ser ingresado entre comillas |
    | v | Especifica un vector  de numeros enteros para procesar, los numeros deben estar separados por ";", ademas de ser ingresado entre comillas|
    | n | Especifica un numero entero o flotante para procesar. En caso de ser un numero flotante, el separador desimal debe ser ","|



### Ejemplos de ejecución
```bash
./app -u usuario -p micontraseña -t "Hola Mundo" -v "6;7;2;9;5" -n 30
```

