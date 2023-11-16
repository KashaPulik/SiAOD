import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/deleting_from_first_time.txt")

plt.plot(data['t'], data['n'], color='b', label='Время удаления')
plt.xlabel('Время от начала удаления')
plt.ylabel('Количество удалённых ключей')
plt.title('Удаление с первого добаленного ключа')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/deleting_from_first_time.png", dpi=300)