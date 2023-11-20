import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/deleting_from_last_time_sorted.txt")

plt.plot(data['t'], data['n'], color='b', label='Время удаления')
plt.xlabel('Время от начала удаления')
plt.ylabel('Количество оставшихся ключей')
plt.title('Удаление с последнего добаленного ключа после упорядоченного добавления')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/deleting_from_last_time_sorted.png", dpi=300)