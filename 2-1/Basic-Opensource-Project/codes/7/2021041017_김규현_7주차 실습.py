fnameList = ["childhood_size_1500.gif", "manhood_size_1500.gif", "old_age_size_1500.gif", "youth_size_1500.gif"]
num = 0

from tkinter import *
from tkinter import messagebox

def click_prev():
    global num
    num += 1
    if (num < 0):
        num = 3
    photo = PhotoImage(file = "The Voyage of Life_gif/" + fnameList[num])
    pLabel.configure(image = photo)
    pLabel.image = photo

def click_next():
    global num
    num += 1
    if (num > 3):
        num = 0
    photo = PhotoImage(file = "The Voyage of Life_gif/" + fnameList[num])
    pLabel.configure(image = photo)
    pLabel.image = photo

window = Tk()
window.title("사진 앨범 보기")
window.geometry("1500x1100")    #image size = 1500 x 1026

btn_prev = Button(window, text = "<< 이전", command = click_prev)
btn_next = Button(window, text = "다음 >>", command = click_next)

photo = PhotoImage(file = "The Voyage of Life_gif/" + fnameList[0])
pLabel = Label(window, image = photo)

btn_prev.place(x = 250, y = 10)
btn_next.place(x = 400, y = 10)
pLabel.place(x = 10, y = 40)

window.mainloop()
