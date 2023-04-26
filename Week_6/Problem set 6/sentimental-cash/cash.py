# TODO

n = input("Change owed: ")
# print('0'.isdigit())
while not n[0:n.find('.')].isdigit() or not n[n.find('.')+1:len(n)].isdigit() or float(n) < 0:
    n = input("Change owed: ")

cash = float(n)*100

counter = 0

while cash != 0:
    if cash >= 25:
        cash -= 25
        counter += 1
    elif cash >= 10 and cash < 25:
        cash -= 10
        counter += 1
    elif cash >= 5 and cash < 10:
        cash -= 5
        counter += 1
    else:
        cash -= 1
        counter += 1

print(counter)
