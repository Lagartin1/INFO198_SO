import matplotlib.pyplot as plt
import os

output_dir = os.getenv('GRAFICO')
# Leer los datos del archivo

data_file_path = os.getenv('DATOS')

with open(data_file_path, 'r') as file:
    data = file.readlines()

# Procesar y graficar los datos
for line in data:
    points = line.strip().split('; ')  # Elimina espacios y divide por ';'
    x = []
    y = []
    for point in points:
        # Eliminar caracteres no deseados (por ejemplo, el punto y coma al final)
        point = point.strip().rstrip(';')  # Elimina espacios y el punto y coma final
        if point:  # Asegurarse de que no esté vacío
            xi, yi = map(float, point.split(','))  # Divide por ',' y convierte a float
            x.append(xi)
            y.append(yi)
    plt.plot(x, y, marker='o', label=f'Repeticion {data.index(line) + 1}')

# Personalizar el gráfico
plt.title('Rendimiento de la aplicacion Contar Palabras con Threads')  # Cambia el título según tu preferencia
plt.xlabel('Cantidad de Threads')
plt.ylabel('Tiempo de ejcucion (segundos)') 
plt.legend()
plt.grid()

# Guardar el gráfico como imagen en la ubicación especificada
output_file = os.path.join(output_dir,"grafico.png")  # Cambia el nombre según tu preferencia
plt.savefig(output_file)  # Guarda el gráfico
plt.close()  # Cierra la figura para evitar el warning
print("Grafico generado en: ", output_file)
