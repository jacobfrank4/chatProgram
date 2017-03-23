##################################################
# Declare Variables
##################################################
CC=g++ -std=c++11
CFLAGS= -W -Wall -pedantic

SERVEROBJECTS = main.o server.o
EXECUTABLES = chat_server
CC_LOAD = $(CC)
CC_DONE = cleanobjects
##################################################
# Targets
##################################################
all: $(EXECUTABLES) $(CC_DONE)

chat_server: $(SERVEROBJECTS)
	$(CC_LOAD) $(CFLAGS) $(SERVEROBJECTS) -o $@

server.o:
	$(CC) -c server.cpp 
main.o:
	$(CC) -c main.cpp

##################################################
# Clean-up
##################################################
clean:
	rm -f $(EXECUTABLES)
	rm -f *.o
cleanobjects:
	rm -f *.o
