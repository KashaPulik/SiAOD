import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/random_lookup_time_sorted.txt")

plt.plot(data['n'], data['t'], color='b', label='Время поиска')
plt.xlabel('Количество ключей')
plt.ylabel('Время поиска')
plt.title('Среднее время поиска ключа из упорядоченного дерева')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/random_lookup_time_sorted.png", dpi=300)