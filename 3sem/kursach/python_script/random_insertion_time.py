import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/random_insertion_time.txt")

plt.plot(data['t'], data['n'], color='b', label='Время добавления')
plt.xlabel('Время от начала добавления')
plt.ylabel('Количество добавленных ключей')
plt.title('Время добавления ключей в случайном порядке')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/random_insertion_time.png", dpi=300)