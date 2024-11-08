import matplotlib.pyplot as plt

# Открываем файл и читаем данные
f = open("data.txt")
lines = f.read().split('\n')
lines = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines))

# Извлекаем x и y координаты
x = list(map(lambda x: x[0], lines))
y = list(map(lambda x: x[1], lines))

# Открываем файл и читаем данные
f2 = open("data2.txt")
lines2 = f2.read().split('\n')
lines2 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines2))

# Извлекаем x и y координаты
x2 = list(map(lambda x: x[0], lines2))
y2 = list(map(lambda x: x[1], lines2))

# Открываем файл и читаем данные
f3 = open("data3.txt")
lines3 = f3.read().split('\n')
lines3 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines3))

# Извлекаем x и y координаты
x3 = list(map(lambda x: x[0], lines3))
y3 = list(map(lambda x: x[1], lines3))

# Устанавливаем размер графика и диапазон оси y
plt.scatter(x, y, 2, color="green", label="Эмпирическая")

plt.scatter(x2, y2, 2, color="blue", label="Основная")

plt.scatter(x3, y3, 2, color="purple", label="Эмпирическа на эспирической")

plt.legend(loc="upper left")
plt.show()
