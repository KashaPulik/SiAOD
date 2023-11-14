import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("./data/data3.txt")

plt.plot(data['n'], data['t'], color='b', label='Время поиска')
plt.xlabel('n')
plt.ylabel('t')
plt.title('ABOBA')
plt.legend()
plt.grid(True)

plt.savefig("./graphic/graphic3.png", dpi=300)