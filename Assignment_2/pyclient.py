# Import socket module
import socket

def Main():
	# local host IP '127.0.0.1'
	host = '127.0.0.1'
	# Define the port on which you want to connect
	port = int(input("Please enter Port number: "))
	s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	# connect to server on local computer
	s.connect((host,port))
	print("Welcome to the Dictionary.")
	while True:
		num = int(input("Please enter the number to indicate your choice: \n 1 Query a Word. \n 2 Add a Word \n 3 Remove a Word \n 4 Exit \n"))
		#handle num not a integer
		if num == 1:
			word = input("Please enter a single word to query in lowercase: ")
			if ' ' in word:
				print("Invalid input. Please stick to the options provided")
				continue
		#handle other invalid word cases
			word = word.lower()
			msg = 'q'+word
			s.send(msg.encode('ascii')) 
			data = s.recv(1024)
			data = data.decode('ascii')
			if data == "00":
				print("Word not in dictionary")
				continue 	
			else:
				print(word + " : " + data)

		elif num == 2:
			line = input("Please enter the word to add and its meaning(s) in space seperated format in lowercase(e.g. hurry rush run hasten): ")
			line = 'a'+line
			s.send(line.encode('ascii')) 
			data = s.recv(1024)
			data = data.decode('ascii')
			if data != "Added":
				print("Word already in Dictionary.")
				continue
			else:
				print("Word added Successfully")
				continue
		elif num == 3:
			word = input("Please enter a single word to delete in lowercase: ")
			if ' ' in word:
				print("Invalid input. Please stick to the options provided")
				continue
			#handle other invalid word cases
			word = word.lower()
			msg = 'r'+word
			s.send(msg.encode('ascii')) 
			data = s.recv(1024)
			data = data.decode('ascii')
			print(data)
			if data == "00":
				print("Word not in dictionary")
				continue 	
			else:
				print(word + " has been deleted from the Dictionary " )
		elif num == 4:
			break
		else:
			print("Invalid input. Please stick to the options provided")
			continue
	print("Goodbye")
	s.close()

if __name__ == '__main__':
	Main()
