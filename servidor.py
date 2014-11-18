#TCPserver.py
#!/usr/bin/python
import socket
import serial
import threading
		
s = socket.socket()
port = 11111
#?ser? = serial.Serial('/dev/ttyACM0', 9600)
ser = serial.Serial('COM10', 9600)
ser2 = serial.Serial('COM9', 9600)

s.bind(('', port))
s.listen(1)
data = 0

def leer():
	while(True):
		while(ser2.inWaiting() > 0):
			msg = ser2.readline()
			print(msg)

threads = list()
t = threading.Thread(target=leer)
threads.append(t)
t.start()

while True:
	c, addr = s.accept()
	data=c.recv(1024)
	if(str(data) == 'salir'):
		print ('Server Closed')
		#ser.write(3) #parar la shit
		c.close()
		t._Thread__stop()
		exit()
	else:
		print ('Address:',addr,'Data:',data)
		ser.write(data)
	
	#?mylist?=list(data.split(':'))
	#?intlist?=list()
	#?for? i in range(0,len(mylist)):
	# intlist.append(int(mylist[i]))
	#intlist.sort()
	#?c?.send(str(intlist))
