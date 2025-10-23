SRC:=src/%.c #usage of wildcard
INC:=include
BUILD:=%.o
TCP_OBJECT:=tcp.o server.o socket.o 
UDP_OBJECT:=udp.o server_udp.o 
CC:=gcc
TEMP_FLAG:=
CFLAG:=-c -Wall  -g $(TEMP_FLAG)
LFLAG:=-g $(TEMP_FLAG)
INC_FLAG:= -I$(INC)/


#build all target
.PHONY: all
all: tcp udp
	@echo "You can run the program"

#build relocatable object file
$(BUILD): $(SRC) 
	$(CC) $(CFLAG) $^ -o $@ $(INC_FLAG)

#build executable file
tcp: $(TCP_OBJECT)
	$(CC) $(LFLAG)  $^ -o $@ 
	@echo "$@ program has been compiled sucessfully"


udp:$(UDP_OBJECT)
	$(CC) $(LFLAG)  $^ -o $@ 
	@echo "$@ program has been compiled sucessfully"

#debug command
.PHONY: debug
debug: main
	@gdb main

#execute the program
.PHONY: excecute
excecute: main
	@./main

#clean the program and unessesary file
.PHONY: clean
clean:
	- rm *i
	- rm *s 
	- rm *o 
	- rm *map
	- rm main 
	