#TCPclient.py
#!/usr/bin/python 
import sys
import socket
arglen=len(sys.argv)
if arglen<3:
	print('please run as python TCPclient.py <ip_address> <numbers>')
	exit()
data=str()
if sys.argv[2] == 0:
	print('no puede ingresar valores 0')
	exit()
data=data+str(sys.argv[2])
for i in range(3,arglen):
	if sys.argv[i] == 0:
		print('no puede ingresar valores 0')
		exit()
	data=data+str(sys.argv[i])
s = socket.socket()
port = 11111
s.connect((sys.argv[1], port))
s.send(data)
#?print? s.recv(1024)
s.close