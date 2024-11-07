import matplotlib.pyplot as plt

file = open('modelingTime.txt', 'r')
i = 0
li = []
for line in file:
    li.append(float(line.strip()))  # Преобразуем строки в числа
li.sort()

plt.hist(li, bins=6)  # Задаем количество отрезков
plt.show()

file.close()
