""" import sys
import csv

file = open("phone.csv","a")

name = input("name: ")
number = input("number: ")
number2 = input("number2: ")

writer = csv.writer(file)

writer.writerow([name, number, number2])
file.close() """


import pyttsx3
import pyaudio

engine = pyttsx3.init()
name = input("name: ")
engine.say(f"Hello, {name}!")
engine.runAndWait()


""" import os
import qrcode

img = qrcode.make("https://docs.google.com/forms/d/e/1FAIpQLSe-e5jgQZUo2D49y8CmiQOPXC9Bd1Hwt0JkOFgZ2D9REcIFmQ/viewform")

img.save("qr.png","PNG")

os.system("open qr.png") """
