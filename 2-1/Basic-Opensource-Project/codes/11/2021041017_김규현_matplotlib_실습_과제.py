import pandas as pd # csv 파일을 효율적으로 이용하기 위해 pandas 라이브러리 사용
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import numpy as np

plt.rc("font", family="Malgun Gothic")  # 한글 깨지는 버그 수정!
plt.rcParams['axes.unicode_minus'] = False  # '-' 기호 깨지는 버그 수정!

file_path = 'C:/Users/win11/Desktop/data/vsc/py/SURFACE_ASOS_108_DAY_2002_2002_2018.csv'
data = pd.read_csv(file_path, encoding='cp949')
data['일시'] = pd.to_datetime(data['일시'])

# x축을 0부터 350까지의 일 단위로 변환
data['일단위'] = (data['일시'] - data['일시'].min()).dt.days

fig, ax = plt.subplots(figsize=(14, 7))

line1, = ax.plot(data['일단위'], data['최고기온(°C)'], label='최고기온', color='red', linewidth=1.5)
line2, = ax.plot(data['일단위'], data['평균기온(°C)'], label='평균기온', color='yellow', linewidth=1.5)
line3, = ax.plot(data['일단위'], data['최저기온(°C)'], label='최저기온', color='blue', linewidth=1.5)

ax.set_title('서울시 2002년도 기온 변화')
ax.set_xlabel('Day')
ax.set_ylabel('Temperature')
ax.legend()

ax.grid(False)  # 격자 제거

ax.set_xticks(np.arange(0, 351, 50))

def format_coord(x, y):
    return f'(x, y) = ({x:.1f}, {y:.1f})'

ax.format_coord = format_coord

plt.show()
