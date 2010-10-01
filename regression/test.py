import sys
import commands
import os
import os.path
sys.path.append("../doc/examples")
import gfs2tex
from datetime import *

env = "export PYTHONPATH=$PYTHONPATH:" + os.getcwd() + " &&"
system = commands.getoutput('uname -o -n -m')
path = commands.getoutput('which gerris2D')
version = commands.getoutput("""gerris2D -V 2>&1 | head -1 | cut -d' ' -f6-""")
starttime = datetime.now()

n = 0
failed = 0
for start in sys.argv[1:]:
    for root, dirs, files in os.walk(start,topdown=True):
        if not ".xvpics" in root:
            test = gfs2tex.Example(root)
            status,msg = test.run(env)
            if status != None:
                print "FAIL:",root
                if len(msg) > 0:
                    print " ".join(msg)
                print >>open(test.path + "/status",'w'), "{\color{Red}FAIL}:"
                failed += 1
            else:
                print "PASS:",root
                print >>open(test.path + "/status",'w'), "{\color{OliveGreen}PASS}:"
            n += 1

endtime = datetime.now()
e = endtime - starttime
s = e.seconds
h = int(s/3600)
s -= h*3600
m = int(s/60)
s -= m*60

summary = open('summary.tex','w')
print >>summary, r'\begin{tabular}{ll}'
print >>summary, r'{\bf Version} &', version, r'\\'
print >>summary, r'{\bf Path} &', path, r'\\'
print >>summary, r'{\bf System} &', system, r'\\'
print >>summary, r'{\bf Start} &', starttime.strftime('%a %d %b %H:%M:%S'), r'\\'
print >>summary, r'{\bf Finish} &', endtime.strftime('%a %d %b %H:%M:%S'), r'\\'
elapsed = ""
if e.days > 0:
    elapsed += '%02d:' % e.days
if h > 0:
    elapsed += '%02d:' % h
elapsed += '%02d:%02d' % (m,s)
print >>summary, r'{\bf Elapsed} &', elapsed, r'\\'
print >>summary, r'{\bf Status} &',
if failed:
    print >>summary, r'{\color{Red}FAIL (' + repr(failed) + '/' + repr(n) +')}'
else:
    print >>summary, r'{\color{OliveGreen}PASS (' + repr(n) + ')}'
print >>summary, r'\end{tabular}'

if failed:
    msg = repr(failed) + " of " + repr(n) + " tests failed"
else:
    msg = "All " + repr(n) + " tests passed"

print len(msg)*"="
print msg
print len(msg)*"="

if failed:
    sys.exit(1)
