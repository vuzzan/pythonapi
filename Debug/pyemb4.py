import arnav
print('in python: ')

val = arnav.foo()
print('in python:arnav.foo() returned ', val)

arnav.show(val*20+80)
print('444444444 Python loaded')

def getInteger4():
    print('444444444 Python function getInteger4() called\n')
    print('444444444 call foo to C++\n')
    msg = arnav.printmsg("Neo Nghia Luong")
    val = arnav.foo()
    print('444444444 call foo to return ', val)
    c = 100*50/30
    return val