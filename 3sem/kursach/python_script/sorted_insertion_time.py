import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./experimental_data/sorted_insertion_time.txt")

plt.plot(data['n'], data['t'], color='b', label='Время добавления')
plt.xlabel('Количество добавленных ключей')
plt.ylabel('Время добавления')
plt.title('Время упорядоченного добавления ключей')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/sorted_insertion_time.png", dpi=300)