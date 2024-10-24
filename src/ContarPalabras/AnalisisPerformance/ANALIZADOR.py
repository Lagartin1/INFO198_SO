import matplotlib.pyplot as plt
import os

# Ruta donde se guardará el gráfico
home_dir = os.path.expanduser('~')  # Esto obtiene el directorio home del usuario actual

output_dir = os.path.join(home_dir, 'INFO198_SO', 'Data')
# Leer los datos del archivo

data_file_path = os.path.join(home_dir, 'INFO198_SO', 'src', 'ContarPalabras', 'AnalisisPerformance', 'variablesEntorno', 'DATOS.txt')

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
    plt.plot(x, y, marker='o', label=f'Line {data.index(line) + 1}')

# Personalizar el gráfico
plt.title('Gráficos de Línea')
plt.xlabel('Eje X')
plt.ylabel('Eje Y')
plt.legend()
plt.grid()

# Guardar el gráfico como imagen en la ubicación especificada
output_file = os.path.join(output_dir, 'grafico_lineas.png')  # Cambia el nombre según tu preferencia
plt.savefig(output_file)  # Guarda el gráfico
plt.close()  # Cierra la figura para evitar el warning
