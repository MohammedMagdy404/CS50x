# TODO

n = input("Height: ")
while not n.isdigit() or int(n) <= 0 or int(n) == 9:
    n = input("Height: ")

num = int(n)
for i in range(num):
        print(" " * (num-i-1) + "#" * (i+1))
        