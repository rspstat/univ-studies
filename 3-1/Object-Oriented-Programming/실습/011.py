import numpy as np
import matplotlib.pyplot as plt

# 지수 함수 정의
def exponential(x, a=2):
    return a ** x

# 설정
x = np.linspace(-5, 5, 400)
a = 2  # 밑

# 원본
y_original = exponential(x, a)

# 평행이동
y_vertical = exponential(x, a) + 2         # y축 위로 2
y_horizontal = exponential(x - 2, a)       # x축 오른쪽으로 2

# 대칭이동
y_x_symmetry = -exponential(x, a)          # x축 대칭
y_y_symmetry = exponential(-x, a)          # y축 대칭
y_origin_symmetry = -exponential(-x, a)    # 원점 대칭

# 그래프 출력
plt.plot(x, y_original, label='Original')
plt.plot(x, y_vertical, label='Vertical +2')
plt.plot(x, y_horizontal, label='Horizontal +2')
plt.plot(x, y_x_symmetry, label='X-axis Symmetry')
plt.plot(x, y_y_symmetry, label='Y-axis Symmetry')
plt.plot(x, y_origin_symmetry, label='Origin Symmetry')

plt.title('Parallel and Symmetric Transpositions of Exponential Function')
plt.legend()
plt.grid(True)
plt.show()