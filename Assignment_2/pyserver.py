# import socket programming library
import socket

# import thread module
from _thread import *
import threading

wordslist = {}
unavailable = '00'
success = '1'

def queryWord(word):
	if word in wordslist.keys():
		return " ".join(wordslist[word])
	else:
		return None
	
def addWord(line):
	l = line.split()
	m = queryWord(l[0])
	if m==None:
		wordslist[l[0]] = l[1:]
	else:
		return False
	return True

def removeWord(word):
	if word in wordslist.keys():
		del wordslist[word]
		return True
	else:
		return False

# thread fuction
def threaded(c):
	while True: 
		# data received from client
		print("In threaded")
		data = c.recv(1024)
		if not data:
			print('Bye') 
			break
		data = data.decode('ascii')
		print("recieved "+ data)
		if data[0] == 'q':
			print("querying...")
			msg = queryWord(data[1:])
			if msg != None:
				print("Found : " + msg)
				msg = msg.encode('ascii')
			else:
				msg = unavailable.encode('ascii')
				print("Word not in Dictionary")
			c.send(msg)	
		elif data[0] == 'a':
			res = addWord(data[1:])
			if res:
				msg = "Added"
			else:
				msg = "Duplicate"
			c.send(msg.encode('ascii'))
		elif data[0] == 'r':
			if removeWord(data[1:]):
				msg = success.encode('ascii')
			else:
				msg = unavailable.encode('ascii')
			c.send(msg)
			# connection closed
	c.close()


def Main():
	host = ""
	port = int(input("Please enter port number: "))
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind((host, port))
	print("socket bound to port", port)
	# put the socket into listening mode
	s.listen(10)
	print("socket is listening")
	# a forever loop until client wants to exit
	while True:
	# establish connection with client
		c, addr = s.accept()
		print('Connected to :', addr[0], ':', addr[1])
		# Start a new thread and return its identifier
		start_new_thread(threaded, (c,))
	s.close()


if __name__ == '__main__':
	Main()
