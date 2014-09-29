import os
class ProgObject:
    def __init__(self, outdata="outdata_new", mu=1.0e-6,
		 polyplg = "poly.plg"):
	self.__outdata = outdata
	self.__mu = 1.0e-6
	self.__polyplg = polyplg

    def run(self):
	print os.getcwd()
	os.system("mkdir mh")
	#	os.popen("./main test-p")
	os.system(r"cp -r outdata %s" % self.__outdata)
	os.system("cp test-p.cfg polymer.cfg %s %s" % (self.__polyplg, self.__outdata))

p = ProgObject();
p.run()


    
