import matplotlib.pyplot as plt

# # Открываем файл и читаем данные
# f = open("data.txt")
# lines = f.read().split('\n')
# lines = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines))

# # Извлекаем x и y координаты
# x = list(map(lambda x: x[0], lines))
# y = list(map(lambda x: x[1], lines))

# # Открываем файл и читаем данные
# f2 = open("data2.txt")
# lines2 = f2.read().split('\n')
# lines2 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines2))

# # Извлекаем x и y координаты
# x2 = list(map(lambda x: x[0], lines2))
# y2 = list(map(lambda x: x[1], lines2))

# Открываем файл и читаем данные
f4 = open("./files/out_empiric_"+"dist"+".txt")
lines4 = f4.read().split('\n')
lines4 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines4))

# Извлекаем x и y координаты
x4 = list(map(lambda x: x[0], lines4))
y4 = list(map(lambda x: x[1], lines4))

# Открываем файл и читаем данные
type = "empiric"
f3 = open("./files/out_empiric_"+type+".txt")
lines3 = f3.read().split('\n')
lines3 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines3))

# Извлекаем x и y координаты
x3 = list(map(lambda x: x[0], lines3))
y3 = list(map(lambda x: x[1], lines3))

# Открываем файл и читаем данные
f2 = open("./files/pool_"+type+".txt")
lines2 = f2.read().split('\n')
lines2 = list(map(lambda x: [float(x.split(' ')[0]), float(x.split(' ')[1])], lines2))

# Извлекаем x и y координаты
x2 = list(map(lambda x: x[0], lines2))
y2 = list(map(lambda x: x[1], lines2))

# Устанавливаем размер графика и диапазон оси y
dic = {}
dic["dist"] = "Основное"
dic["mix"] = "Смесь"
dic["empiric"] = "Эмпирическое"
plt.scatter(x2, y2, 2, color="blue", label=dic[type])
plt.scatter(x4, y4, 2, color="red", label=dic[type])

plt.scatter(x3, y3, 2, color="purple", label="Эмпирическое от " + dic[type])

plt.legend(loc="upper left")
plt.show()
