import subprocess
import os

temp_in = [6 ,5 ,1000, 5, 6, 7, 8, 1, 4, 2, 3, 4, 5, 1, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 100, 3, 4, 1, 2, 3, 4]
# create a pipe to a child process
data, temp = os.pipe()

# write to STDIN as a byte object(covert string
# to bytes with encoding utf8)
os.write(temp, bytes(' '.join(map(str,temp_in)),'utf-8'))
os.close(temp)

# store output of the program as a byte string in s
s = subprocess.check_output("../image_boarder", stdin=data, shell=True)

# decode s to a normal string
print(s.decode("utf-8"))

