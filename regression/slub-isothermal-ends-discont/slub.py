from check import *
from sys import *

for filename in argv[1:]:
    res=filename.split('.')[1]
    diff = Curve(filename,1,2) - Curve(filename+".ref",1,2)
    print res, diff.norm1(), diff.norm2(), diff.normi()
