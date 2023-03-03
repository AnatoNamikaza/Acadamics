import time
import random
import threading
  
thread = []
# open file
file_Access = open("file22.txt", "w")
threadLock = threading.Lock()

def num_1000():
    for i in range(1000):
        file_Access.write(str(random.randint(0,1000000)) + '\n')

# main program
# ------------------------

# get the start time
st = time.time()

for i in range(100):
    t_ = threading.Thread(target=num_1000, args=())
    t_.start()
    thread.append(t_)

for th in thread:
    threadLock.acquire()
    th.join()
    threadLock.release()
    
# close file
file_Access.close()

# get the end time
et = time.time()

# get the execution time
res = et - st
final_res = res * 1000
print('Execution time:', final_res, 'milliseconds')

