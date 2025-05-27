cost, num_500, num_100, num_50, num_10 = 0,0,0,0,0
cost = int(input("교환할 돈은 얼마 ? "))

num_500 = cost // 500
cost %= 500
num_100 = cost // 100
cost %= 100
num_50 = cost // 50
cost %= 50
num_10 = cost // 10

print(" 500원짜리 ==> %d개" %(num_500))
print(" 100원짜리   ==> %d개" %(num_100))
print(" 50원짜리 ==> %d개" %(num_50))
print(" 10원짜리    ==> %d개" %(num_10))
print(" 바꾸지 못한 잔돈 ==> %d원" %(cost % 10))

# 2021041017 김규현 2주차-3 동전 변환