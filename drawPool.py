import matplotlib.pyplot as plt

file = open('pool.txt', 'r')
i = 0
li = []
x = []
i = 0
for line in file:
    li.append(float(line.strip()))  # Преобразуем строки в числа
    i += 1
    x.append(i)
li.sort()
plt.xlabel('порядок случайной величины', fontsize=16)
plt.ylabel('случайная величина', fontsize=16)
plt.plot(x, li)
plt.show()

file.close()