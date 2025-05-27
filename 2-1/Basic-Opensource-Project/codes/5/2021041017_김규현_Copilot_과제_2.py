# 사용자로부터 두 개의 숫자를 입력받음
num1 = int(input("첫 번째 숫자를 입력하세요: "))
num2 = int(input("두 번째 숫자를 입력하세요: "))

# 두 숫자 사이의 모든 숫자를 합산
total = sum(range(num1, num2+1))

# 결과 출력
print("두 숫자 사이의 합계는", total, "입니다.")