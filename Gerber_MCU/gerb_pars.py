import fileinput
import re
import sys
from subprocess import call
#example: python gerb_parser.py name add

def IsInt(s):
    try: 
        int(s)
        return True
    except ValueError:
        return False

if len(sys.argv) != 3:
	print "Argument error!"
	sys.exit(1)
filename=sys.argv[1]
insert=sys.argv[2]

call(["cp", filename, filename+"_original"])

vsebina = []
with open(filename) as f:
    for line in f:
    	for m in re.finditer('D', line):
    		a=IsInt(line[m.end():m.end()+2])

    		if(a):
    			num=int(line[m.end():m.end()+2]);
    			if num > 9:
					line = line[:m.end()+2]+insert+line[m.end()+2:]
    	vsebina.append(line)


f=open(filename,"w+")
for line in vsebina:
	f.write(line)
f.close()