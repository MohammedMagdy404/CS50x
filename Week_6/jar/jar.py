""" import sys
def ValueError():
    print ("ValueError")
    sys.exit(1) """

# __the__ command here consider as a keyword in class in python


class Jar:
    def __init__(self, capacity=12):
        if (capacity <= 0):
            raise ValueError
        self.numOfCok = 0
        self.Capacity = capacity

    def __str__(self):
        return ("🍪" * self.numOfCok)

    def deposit(self, n):
        if ((self.numOfCok + n) > self.Capacity):
            raise ValueError
        else:
            self.numOfCok += n

    def withdraw(self, n):
        if ((self.numOfCok - n) < 0):
            raise ValueError
        else:
            self.numOfCok -= n

    @property
    def capacity(self):
        return self.Capacity

    @property
    def size(self):
        return self.numOfCok


def main():
    jar = Jar()
    print(str(jar.capacity))
    print(str(jar))

    jar.deposit(5)
    print(str(jar))

    jar.withdraw(3)
    print(str(jar))


main()
