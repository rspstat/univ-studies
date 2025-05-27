num = int(input('1. 입력한 수식 계산    2. 두 수 사이의 합계 : '))

if num == 1:
    num2 = input('*** 수식을 입력하세요 : ')
    print("{0} 결과는 {1} 입니다." .format(num2, eval(num2)))
    exit()
    

elif num == 2:
    num3 = int(input('*** 첫 번째 숫자를 입력하세요 : '))
    num4 = int(input('*** 두 번째 숫자를 입력하세요 : '))

res = 0
for i in range (num3, num4+1):
    res+=i
    if num3 > num4:
        break

print("%d+...+%d는 %d 입니다." %(num3, num4, res))