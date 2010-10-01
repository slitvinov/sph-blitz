from check import *
from sys import *

for filename in argv[1:]:
    print (Curve(filename,1,2) - Curve(filename+".ref",1,2)).norm2()
