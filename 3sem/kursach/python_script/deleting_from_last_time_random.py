import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/deleting_from_last_time_random.txt")

plt.plot(data['n'], data['t'], color='b', label='Время удаления')
plt.xlabel('Количество ключей')
plt.ylabel('Время удаления всех ключей')
plt.title('Удаление из неупорядоченного дерева')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/deleting_from_last_time_random.png", dpi=300)