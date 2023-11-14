import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./data/data1.txt")

plt.plot(data['t'], data['n'], color='b', label='Время добавления')
plt.xlabel('t')
plt.ylabel('n')
plt.title('ABOBA')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/graphic1.png", dpi=300)