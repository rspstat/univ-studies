print('** 로또 추첨을 시작합니다. **')
print()

import random

lotto_numbers = []   #set(집합) 쓰면, this codes can be more simple code!!
while len(lotto_numbers) < 6:
    n = random.randrange(1, 46)
    if n not in lotto_numbers:
        lotto_numbers.append(n)

print("추첨된 로또 번호 ==>  ", end="")
print('  '.join(map(str, sorted(list(lotto_numbers)))), end="")
# 요소별 구분 공백 삽입, 리스트 요소별 함수 적용, 정렬하여 출력