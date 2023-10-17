import pandas as pd
import matplotlib.pyplot as plt

# Считывание данных из файла
data = pd.read_csv("./data/data.csv")

# Построение графика
plt.plot(data['n'], data['t'], color='b', label='Данные из файла')
plt.xlabel('Ось n')
plt.ylabel('Ось t')
plt.title('Зависимость времени поиска от количества элементов')
plt.legend()
plt.grid(True)

# Сохранение графика в файл
plt.savefig("./graphic/graphic.png", dpi=600)  # dpi - это разрешение изображения, можно настроить по своему усмотрению