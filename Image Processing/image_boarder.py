import struct
import subprocess
from cStringIO import StringIO

stdin_buf = StringIO()
array = [6 ,5 ,1000, 5, 6, 7, 8, 1, 4, 2, 3, 4, 5, 1, 2, 8, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 100, 3, 4, 1, 2, 3, 4]
for item in array:
    stdin_buf.write(struct.pack('<i', item))

proc = subprocess.Popen(['./image_boarder'], stdin=subprocess.PIPE, stdout = subprocess.PIPE)
out, err = proc.communicate(stdin_buf.getvalue())

# assuming the result comes back the same way it went in...
item_len = struct.calcsize('<f')
stdout_buf = StringIO(out)
stdout_buf.seek(0)
for i in range(len(out)/item_len):
    val = struct.unpack('<f', stdout_buf.read(4))
    print(val)