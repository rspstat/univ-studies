import random
import os

dir_path = "C:/Users/rryan/Downloads/"

for i in range(10) :
    f = open(f"{dir_path}ex_{i}.txt", "w")
    f.write("다음의 문제를 풀어서 제출하세요.\n")
    f.write(("이름 :            학번 :            \n"))

    for j in range(10) :
        x = random.randint(1, 100)
        y = random.randint(1, 100)
        op = random.choice("+-*/")
        f.write(f"{x} {op} {y} = \n")
    f.close()