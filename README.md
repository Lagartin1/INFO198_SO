# INFO198_SO
## Descripcion
Este programa es un sistema que permite a los usuarios interactuar con un menú personalizado compuesto por 10 opciones para usuarios genericos:
detección de palíndromos, conteo de vocales, conteo de letras en un texto, cálculo del promedio y sumatoria de un vector, y 
evaluación de la función f(x) = 5x^2 + 1/x, conteo de palabras sobre documentos en un directorio,conteo de palabras de documentos sobre un directorio usando threads y creacion de un indice invertido, Analizador de preformance, planificador,buscador de palabras. Ademas cuenta con opciones para usuarios Admin: listar usuarios,agregar usuarios,eliminar usuarios. El usuario proporciona los datos necesarios mediante argumentos de 
línea de comandos para ejecutar las opciones correspondientes, como nombre de usuario, contraseña, frase de texto,
vector de números, y un valor numérico.

## Requisitos
Para compilar este programa en C++, se necesitan los siguientes elementos:
- **Python 3**: Contar con Python 3.8 o superior, y ademas contar con la libreria `matplotlib`
- **Compilador C**: GCC para compliar C++.
- **Sistema Operativo**: Preferentemente Linux o cualquier sistema compatible con compiladores estándar de C.
- **Bibliotecas estándar de C**: Asegúrate de tener instaladas las bibliotecas estándar necesarias para la entrada/salida y manejo de cadenas.
- **Terminal**: Acceso a una terminal para compilar y ejecutar el programa utilizando línea de comandos.
## Instalacion / Compilacion

Para instalar la libreria de Python matplotlib: 

```bash
      pip install matplotlib
   ```
en caso de no tener pip ,instalarlo de la siguiente forma y luego instalar mathplotlib de la forma anterior:
```bash
      sudo apt update
      sudo apt install python3-pip
   ```


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
    |RESULTADOS | es la ruta completa al archivo `resultados.txt`|
    |PROCESOS | es la ruta completa al archivo `procesos.txt`|
    |SOCKET_DIR |es la ruta completa al directorio donde estaran los sockets |
    |COUNTWORDS_OUT| es la ruta al archivo ejecutable de Contar palabras en un directorio|
    |COUNTWORD_THREADS_OUT |es la ruta al archivo ejecutable de contar palabras en un direcotio con threads |
    |PLANIFICADOR_OUT | es la ruta al archivo ejecutable de planificador|
    |INVERTED_OUT| es la ruta al archvio ejectuable de Indice invertido|
    |CANTIDAD_CORES| es la cantidad de cores que se usaran para el planificador|
    |CARPETA_ENTRADA|es la ruta de la carpeta en donde estan los archivos con los que se contaran las palabras|
    |CARPTA_SALIDA|es la ruta a la carpeta que contendra los archivos de salida del programa que cuenta las palabras|
    |ARRAY_THREADS|array que contiene las cantidades de threads a utulizar para hacer los graficos de performances,las cantidades de threads deben ser separadas por coma (,)|
    |DATOS|es la ruta al archivo que contendra los resutlados del las mediciones de rendimiento|
    |GRAFICO|es la ruta a la carpeta en donde se guardara el grafico|
    |GRAP_PYTHON_PATH|es la ruta al programa python que sera ejecutado para crear el grafico|
    |REPETICIONES|es la cantidad de repeticiones por cada cantidad de threads del array de threads|
    |PERFORMANCE_OUT| es la ruta al ejecutable del programa que hace el analisis de performance|
    |COUNT_WITH_THREADS|es la ruta al ejecutable mas el parametro "-h" para poder ejecutarlo en el analisis de performance|
    |SEARCH_OUT|es la ruta al ejecutable del programa que busca palabras en los archivos|
    
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

## Formatos de la informacion contenida en los archivos

1. **Users.txt** 

   contiene informacion de los usuarios de la siguiente forma:

   < username > ; < password > ; < Admin / Usuario Generico>; 
2. **index.INDEX**
   
   contiene informacion de las diferentes palabras extraidas y ademas la cantidad existente en los archivos que se procesaron de la siguiente forma:

   < palabra > ; (id , num palabra) ;  (id , num palabra) ; ... ;
3. **map.txt**

   contiene informacion de los archivos procesados,de la siguiente forma:

   < nombre archivo > ; < id >
4. **stop_words**

   contiente las plabras que se filtran al procesar los archivos de la sigueite forma:

   < palabra1 >

   < palabra2 >
   
   .

   .

   .

   < palabraN >
5. **procesos.txt** 

   contiene los procesos que se ejecutaran al ejecutar el ejecutable planificador de la siguiente forma:

   < n > ; < operacion >; < numero 1 > ; < numero 2 >;

   las operaciones solo comprenden: suma,resta,multiplicacion y divicion.
   numero 1 y numero 2 podran ser decimales pero el separador decimal es el punto ( . )
6. **resultados.txt** 

   contiene la informacion de el resultado de el procesamiento de los procesos,de la siguiente forma:

   ( < id_core > ; < operacion >; < numero 1 >; < numero 2 > ) => < resultado >
7.**DATOS.txt**
   contiene la informacion de el analisis de performance donde sigue el siguiente formato:

   < Cantidad de Threads > , < Tiempo de ejecucion > ; < Cantidad de Threads > , < Tiempo de ejecucion > , ... asi por cada elemento del array de theads

   y cada linea hacia abajo son la cantidad de repeticiones.