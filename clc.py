import time
import tkinter

state = 1
bpm = 120
trigLengh = bpm / 5000


def runClock() :
    while state == 1:
        print("1")
        time.sleep(trigLengh)
        print("0")
        time.sleep(0.25)


runClock()
