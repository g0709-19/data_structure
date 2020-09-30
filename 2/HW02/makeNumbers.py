import random

numbers = []
how = int(input('얼마나 뽑으실건가요?')) + 1
for i in range(1, how):
    numbers.append(str(i))

random.shuffle(numbers)
s = ' '.join(numbers)

with open('data.txt', mode='w') as file:
    file.write(s)