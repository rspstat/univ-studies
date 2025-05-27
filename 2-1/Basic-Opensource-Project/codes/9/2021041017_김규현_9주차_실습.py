import random
import os

folder_path = 'week9_2021041017_py'    # 같은 프로젝트 폴더 내에 확인
os.makedirs(folder_path, exist_ok=True)     # 없으면 생성

def create_math_problems(files=10, problems_per_file=10):
    opers_list = ['+', '-', '*', '/']
    for i in range(files):
        filename = os.path.join(folder_path, f"ex_{i}.txt")    #파일 경로 생성
        with open(filename, 'w') as file:
            file.write("다음의 문제를 제출하세요.\n")
            file.write("이름 :        학번 : \n")

            for _ in range(problems_per_file):
                num1 = random.randint(1, 100)
                num2 = random.randint(1, 100)
                oper = random.choice(opers_list)

                if oper == '/':     #나눗셈에서 분모가 0이 되지 않도록 조정
                    num2 = random.randint(1, 100)

                problems = f"{num1} {oper} {num2} = \n"  
                file.write(problems)

create_math_problems()