print(" #  2단  # #  3단  # #  4단  # #   5단  # #   6단  # #   7단  # #   8단  # #   9단  #")

for i in range (1, 10):
    for j in range (2, 10):
        print("     %d X %d = %2d" % (j, i, j*i), end='\t')
    print()