import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/last_lookup_time_sorted.txt")

plt.plot(data['n'], data['t'], color='b', label='Время поиска')
plt.xlabel('Количество ключей')
plt.ylabel('Время поиска')
plt.title('Время поиска последнего ключа из упорядоченного дерева')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/last_lookup_time_sorted.png", dpi=300)