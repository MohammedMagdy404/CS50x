from pyfiglet import Figlet
import sys


figlet = Figlet()
def main():
    global input
    if len(sys.argv)-1 == 0:
        input = input("Input: ")
        print("Output: ")
        print(figlet.renderText(input))
        sys.exit(0)
    elif len(sys.argv)-1 == 2:
        if(sys.argv[1].lower() != "-f" and sys.argv[1].lower() != "--font"):
            print("Invalid usage_1")
            sys.exit(1)
        fonts = figlet.getFonts()
        for i in fonts:
            if sys.argv[2].lower() == i.lower():
                #print(sys.argv[2])
                figlet.setFont(font=sys.argv[2])
                input = input("Input: ")
                print("Output: ")
                print(figlet.renderText(input))
                sys.exit(0)
        print("Invalid usage_1-1")
        sys.exit(1)
    else:
        print("Invalid usage_2", len(sys.argv))
        sys.exit(1)
        

main()
