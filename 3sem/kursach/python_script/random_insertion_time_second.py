import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/random_insertion_time_second.txt")

plt.plot(data['n'], data['t'], color='b', label='Время добавления')
plt.xlabel('Количество добавленных ключей')
plt.ylabel('Время добавления')
plt.title('Время добавления ключей в случайном порядке')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/random_insertion_time_second.png", dpi=300)