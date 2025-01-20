
git commit -a -m "ReadMe.txt 1"
git push 

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

......

Введите кол-во точек (N): 10
Кол-во классов (K): 3


https://stackoverflow.com/questions/65871948/same-random-numbers-in-c-as-computed-by-python3-numpy-random-rand

https://learn.microsoft.com/ru-ru/cpp/standard-library/random?view=msvc-170

