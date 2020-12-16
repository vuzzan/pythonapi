import secsgemdriver
codeid=4
def getInteger4():
    secsgemdriver.printmsg(str(codeid)+' Python function getInteger4() called\n')
    secsgemdriver.printmsg(str(codeid)+' call foo to C++\n')
    #msg = secsgemdriver.printmsg("Neo Nghia Luong")
    #print('444444444 printmsg return ', msg)
    val = secsgemdriver.neoneo("NEONEO SEND FROM PY")
    print(str(codeid)+' call foo to return ', val)
    c = 100*50/30
    return 77

def processMsg(msg):
	#print('Process msg called\n')
	secsgemdriver.printmsg(str(codeid)+'Process msg called\n')
	#print(msg)
	arr = msg["msg"]
	#print(arr)
	#for item in arr:
	#	print(item)
	for key in arr:
		secsgemdriver.printmsg(key + " = "+str(arr[key]))
		
	val = secsgemdriver.getdata(str(codeid)+"NEO NGHIA");
	print(str(codeid)+"Val return secsgemdriver.getdata")
	print(val)
	
	print("Test call get dict")
	dictvalue = {"NEO": "NEOVALUE","NEO1": "NEOVALUE", "NEO2": "NEOVALUE", "NEO3": "NEOVALUE", "NEO4": "NEOVALUE", "NEO5": "NEOVALUE"}
	print(dictvalue)
	print(dictvalue["NEO"])
	val = secsgemdriver.getdict( dictvalue );
	print(val);
	return 0
	
#processMsg("pyemd4 started....")