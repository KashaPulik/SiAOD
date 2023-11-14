import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./data/deleting_time.txt")

plt.plot(data['t'], data['n'], color='b', label='Время удаления')
plt.xlabel('Время от начала удаления')
plt.ylabel('Количество оставшихся ключей')
plt.title('ABOBA')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/graphic2.png", dpi=300)