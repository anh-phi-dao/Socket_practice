SRC:=src/%.c #usage of wildcard
INC:=include
BUILD:=%.o
OBJECT:=main.o multiple_client_server.o socket.o 
FILE:=create_binary_file.o
CC:=gcc
TEMP_FLAG:=
CFLAG:=-c -Wall  -g $(TEMP_FLAG)
LFLAG:=-g $(TEMP_FLAG)
INC_FLAG:= -I$(INC)/


#build all target
.PHONY: all
all: main create_binary_file
	rm *.o
	@echo "You can run the program"

#build relocatable object file
$(BUILD): $(SRC) 
	$(CC) $(CFLAG) $^ -o $@ $(INC_FLAG)

#build executable file
main: $(OBJECT)
	$(CC) $(LFLAG)  $^ -o $@ 
	@echo "$@ program has been compiled sucessfully"

create_binary_file: $(FILE)
	$(CC) $(LFLAG)  $^ -o $@ 

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
	