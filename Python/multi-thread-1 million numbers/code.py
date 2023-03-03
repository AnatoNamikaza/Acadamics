import time
import random
  
# main program
# ------------------------

# get the start time
st = time.time()

f = open("file2.txt", "w")
for i in range(100000):
    f.write(str(random.randint(0,1000000)) + '\n')
f.close()

# get the end time
et = time.time()

# get the execution time
res = et - st
final_res = res * 1000
print('Execution time:', final_res, 'milliseconds')

