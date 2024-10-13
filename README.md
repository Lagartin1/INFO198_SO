# INFO198_SO
## Descripcion
Este programa es un sistema que permite a los usuarios interactuar con un menú personalizado compuesto por ocho opciones para usuarios genericos:
detección de palíndromos, conteo de vocales, conteo de letras en un texto, cálculo del promedio y sumatoria de un vector, y 
evaluación de la función f(x) = 5x^2 + 1/x, conteo de palabras sobre documentos en un directorio,conteo de palabras de documentos sobre un directorio usando threads y creacion de un indice invertido. Ademas cuenta con opciones para usuarios Admin: listar usuarios,agregar usuarios,eliminar usuarios. El usuario proporciona los datos necesarios mediante argumentos de 
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

1. Varibles de entorno:
   
   Para modificar las variables deben abrir el archivo `config.sh` precente en la raiz del repositorio, las variables son las detalladas aqui:
   | Variable | Descripcion |
    | -------- | ----------- |
    | TXT_FILE_PATH | es la ruta completa al archivo ` Users.txt` precente en el directorio  `/Data` de este programa |
    | MAPA_ARCHIVOS | es la ruta completa al archivo ` Map.txt` que puede o no existir |
    | STOP_WORDS | es la ruta completa al archivo ` stop_words.txt` que precente en el directorio `/Data` de este programa |
    | INVERTED_INDEX | es la ruta completa al archvio ` indice.INDEX` precente en el directorio `/Data` de este programa|
    |CANTIDAD_THREAD | es la cantidad de Threads que se ocuparan para el Programa de Procesar con hilos |
    
    al modificar se debe dar permisos de ejecucion y luego cargarlo al bash el programa,se debe estar el la raiz del repositorio y ejecutar:

      ```bash
      chmod +x config.sh
      source ./config.sh
      ```
      
2. Navega al directorio `bin/` donde se encuentra el archivo ejecutable `app`.

   ```bash
   cd bin/
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



