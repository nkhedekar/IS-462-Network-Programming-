# Import socket module
import socket

def Main():
	# local host IP '127.0.0.1'
	host = '127.0.0.1'
	# Define the port on which you want to connect
	while True:
		try:
			port = int(input("Please enter Port number: "))
			s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
			# connect to server on local computer	
			s.connect((host,port))
			break
		except ValueError:
			print("The port Number must be an integer.")
		except:
			print("Please enter the correct port number of the server")
		
	print("*******************************Welcome to the Dictionary.**********************************************")
	while True:
		while True:
			try:
				num = int(input("Please enter the number to indicate your choice: \n 1 Query a Word. \n 2 Add a Word \n 3 Remove a Word \n 4 Exit \nYour Choice: "))
				break
			except ValueError:
				print("Please enter a number between 1 to 4 to indicate your choice")
		
		if num == 1:
			while True:
				word = input("Please enter a single word to query in lowercase: ")
				if len(word)==1:
					print("The number of characters in a word must be >= 1")
					continue
				if word.isalpha():
					break
				else:
					print("Invalid word entered.")
			word = word.lower()
			msg = 'q'+word
			try:
				s.send(msg.encode('ascii')) 
				data = s.recv(1024)
				data = data.decode('ascii')
				if data == "00":
					print("Word not in dictionary")
					continue 	
				else:
					print(word + " : " + data)
			except:
				print("Error: Connection to server lost")
				return
			
		elif num == 2:
			while True:
				line = input("Please enter the word to add and its meaning(s) in space seperated format in lowercase(e.g. hurry rush run hasten): ")
				if ' ' not in line:
					print("Please add meanings of the word also")
					continue
				if line.replace(" ", "").isalpha():
					break
				else:
					print("The information entered is in the wrong format. Please stick to the format specified")
			line = 'a'+line
			try:
				s.send(line.encode('ascii')) 
				data = s.recv(1024)
				data = data.decode('ascii')
				if data != "Added":
					print("Word already in Dictionary.")
					continue
				else:
					print("Word added Successfully")
					continue
			except:
				print("Error: Connection to server lost")
				return
			
		elif num == 3:
			while True:
				word = input("Please enter a single word to delete in lowercase: ")
				if word.isalpha():
					break
				else:
					print("Invalid word entered.")
			
			word = word.lower()
			msg = 'r'+word
			try:
				s.send(msg.encode('ascii')) 
				data = s.recv(1024)
				data = data.decode('ascii')
				if data == "00":
					print("Word not in dictionary")
					continue 	
				else:
					print(word + " has been deleted from the Dictionary " )
			except:
				print("Error: Connection to server lost")
				return
			
		elif num == 4:
			break
		else:
			print("Invalid input. Please stick to the options provided")
			continue
	print("Goodbye")
	s.close()

if __name__ == '__main__':
	Main()
