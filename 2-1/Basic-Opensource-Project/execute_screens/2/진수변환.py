num = input("입력 진수 결정(16/10/8/2) : ")
num2 = input("값 입력 : ")

if num == "2":
    res = int(num2, 2)
elif num == "8":
    res = int(num2, 8)
elif num == "10":
    res = int(num2)
elif num == "16":
    res = int(num2, 16)

print("16진수 ==> ", hex(res))
print("10진수 ==> ", res)
print(" 8진수 ==> ", oct(res))
print(" 2진수 ==> ", bin(res))

#bin 2진수 oct 8진수 dec 10진수 hex 16진수