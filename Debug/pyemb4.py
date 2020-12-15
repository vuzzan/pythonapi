import arnav
def getInteger4():
    arnav.printmsg('444444444 Python function getInteger4() called\n')
    arnav.printmsg('444444444 call foo to C++\n')
    #msg = arnav.printmsg("Neo Nghia Luong")
    #print('444444444 printmsg return ', msg)
    val = arnav.neoneo("NEONEO SEND FROM PY")
    print('444444444 call foo to return ', val)
    c = 100*50/30
    return 77

def processMsg(msg):
	#print('Process msg called\n')
	arnav.printmsg('Process msg called\n')
	#print(msg)
	arr = msg["msg"]
	#print(arr)
	#for item in arr:
	#	print(item)
	for key in arr:
		arnav.printmsg(key + " = "+str(arr[key]))
	return 0
	
#processMsg("pyemd4 started....")