import matplotlib.pyplot as plt
import numpy as np

# Leer los datos del archivo
def leer_datos(archivo_datos):
    threads = []
    tiempos = []
    
    with open(archivo_datos, 'r') as file:
        for linea in file:
            # Supone que los datos están en el formato: threads tiempo1 tiempo2 ... tiempoN
            valores = list(map(float, linea.split()))
            threads.append(int(valores[0]))
            tiempos.append(valores[1:])
    
    return threads, tiempos

# Crear gráfico
def crear_grafico(threads, tiempos, repeticiones, archivo_grafico):
    plt.figure(figsize=(10, 6))

    # Agregar líneas al gráfico
    for i in range(repeticiones):
        tiempos_por_repeticion = [tiempo[i] for tiempo in tiempos]  # Extrae el tiempo de cada repetición
        plt.plot(threads, tiempos_por_repeticion, marker='o', label=f'Repetición {i + 1}')

    # Configuraciones del gráfico
    plt.title('Tiempos de Ejecución vs Cantidad de Threads')
    plt.xlabel('Cantidad de Threads')
    plt.ylabel('Tiempo de Ejecución (segundos)')
    plt.legend(loc='best')
    plt.grid(True)
    
    # Guardar el gráfico
    plt.savefig(archivo_grafico)
    print(f"Gráfico generado: {archivo_grafico}")

# Programa principal
if __name__ == "__main__":
    # Variables de entorno
    import os
    archivo_datos = os.getenv('DATOS')
    archivo_grafico = os.getenv('GRAFICO')
    repeticiones = int(os.getenv('REPETICIONES', 2))  # Valor por defecto de 2 si no se define REPETICIONES

    # Leer datos
    threads, tiempos = leer_datos(archivo_datos)

    # Crear gráfico
    crear_grafico(threads, tiempos, repeticiones, archivo_grafico)
