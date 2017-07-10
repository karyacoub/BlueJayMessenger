all:
	@g++ -pthread -std=c++11 -o Purpl. client.cpp launcher.cpp
server:
	@g++ -pthread -std=c++11 -o server server.cpp
client:
	@g++ -pthread -std=c++11 -o client client.cpp
