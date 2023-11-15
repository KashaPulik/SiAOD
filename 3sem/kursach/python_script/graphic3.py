import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/lookup_time.txt")

plt.plot(data['n'], data['t'], color='b', label='Время поиска')
plt.xlabel('Количество ключей')
plt.ylabel('Время поиска случайного ключа')
plt.title('ABOBA')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/graphic3.png", dpi=300)