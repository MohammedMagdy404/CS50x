inp = input("Greeting: ")

inp = inp.strip()

# sublist => inp[0:5] = hello
print(inp[0:5])
if inp[0]+inp[1]+inp[2]+inp[3]+inp[4] == "hello":
    print("0")
elif inp.lower()[0] == 'h':
    print("20")
else:
    print("100")
