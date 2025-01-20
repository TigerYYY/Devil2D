
# Метод ближайших соседей.

import numpy as np
import matplotlib.pyplot as plt
#%matplotlib inline

# Создадим функцию, которая генерирует датасет "Игрушка дьявола"
# из N точек и K классов в D-мерном пространстве.

def devil(N, D=2, K=3):
    #N = 100
    D = 2
    K = 3
    X = np.zeros((N * K, D))
    y = np.zeros(N * K, dtype='uint8')

    for j in range(K):
        ix = range(N * j,N * (j + 1))
        r = np.linspace(0.0, 1, N)
        t = np.linspace( j * 4, (j + 1) * 4, N ) + np.random.randn(N) * 0.2 # theta
        #t = np.linspace( j * 4, (j + 1) * 4, N )
        X[ix] = np.c_[r * np.sin(t), r * np.cos(t)]
        y[ix] = j
    return X, y

#X, y = devil(300)
X, y = devil(10)

print( X )
print()
print()
print( y )

# Добавим в данные шум, чтобы усложнить задачу.
X[:, 0] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
X[:, 1] += np.random.normal(loc=0, scale=0.15, size=30)  # 300
print()

print( X )

print()

print( X[:, 0] )
print( X[:, 1] )

# Отрисовочная магия
from matplotlib.colors import ListedColormap

cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA', '#AAAAFF'])

print( cmap_light )

x_min, x_max = (-1, 1)
y_min, y_max = (-1, 1)

h = 0.05

#
print( "Вот как выглядит наш датасет. Три цвета обозначают три различных класса." )

plt.figure(figsize=(12, 12))

plt.scatter(X[:, 0], X[:, 1], c=y)

plt.xlim((x_min, x_max))
plt.ylim((y_min, y_max))

plt.grid(True)

plt.show()

