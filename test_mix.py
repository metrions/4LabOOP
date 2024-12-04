import matplotlib.pyplot as plt

f1 = open("./files/test_mix_dist1.txt")
lines1 = f1.read().split('\n')
lines1 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines1))

# Извлекаем x и y координаты
x1 = list(map(lambda x: x[0], lines1))
y1 = list(map(lambda x: x[1], lines1))

# Открываем файл и читаем данные
f2 = open("./files/test_mix_dist2.txt")
lines2 = f2.read().split('\n')
lines2 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines2))

# Извлекаем x и y координаты
x2 = list(map(lambda x: x[0], lines2))
y2 = list(map(lambda x: x[1], lines2))

# Открываем файл и читаем данные
f3 = open("./files/test_mix_mix.txt")
lines3 = f3.read().split('\n')
lines3 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines3))

# Извлекаем x и y координаты
x3 = list(map(lambda x: x[0], lines3))
y3 = list(map(lambda x: x[1], lines3))

# Открываем файл и читаем данные
f4 = open("./files/test_mix.txt")
lines4 = f4.read().split('\n')
lines4 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines4))

# Извлекаем x и y координаты
x4 = list(map(lambda x: x[0], lines4))
y4 = list(map(lambda x: x[1], lines4))

# Устанавливаем размер графика и диапазон оси y
plt.scatter(x1, y1, 2, color="blue", label="Основное 1")
plt.scatter(x2, y2, 2, color="green", label="Основное 2")
plt.scatter(x3, y3, 2, color="red", label="Смесь основного 1 + основное 2")
plt.scatter(x4, y4, 2, color="black", label="Смесь смеси 1 + основное 1")


plt.legend(loc="upper left")
plt.show()
