# '#' is comment symbol in makefile
# After you have finished writing your makefile, OUTcute it by typing
# "make" at the terminal.

# The following will assign file/command to variables. 
# e.g. assign g++ command to variable CC, assign all the .o files to variable OBJS.
# When you want to use g++, use $(OUT).
CC = g++
OBJS = main.o Motorbike/Motorbike.o Member/Member.o Date/Date.o Review/Review.o Admin/Admin.o Request/Request.o System/System.o 
OUT = a

# The syntax rule format is as follows: 
# target : pre-requisites
# 	command to be used, i.e. recipe

# this is to generate the program OUT file (i.e. in this example, prog.out).
# Target is .out file, and the pre-requisite files needed are all the .o files.
# Refer to the syntax rule format above.  
ifeq ($(OS),Windows_NT)
	EXE_EXTENSION = .exe
else
	EXE_EXTENSION = .out
endif

$(OUT)$(EXE_EXTENSION): $(OBJS)
	$(CC) $(OBJS) -o $(OUT)$(EXE_EXTENSION)
	rm -f $(OBJS)

# $(OUT) : $(OBJS)
# 	$(CC) $(OBJS) -o $(OUT)
# 	rm -f $(OBJS)

# IMPORTANT: for the gap between the starting line to $(CC) in the above command, 
# use TAB key only. Do not use space key. 

# You need to set the recipe to generate each.o file. 
# Basically, one .cpp file will generate one .o file.
# For the pre-requisite files, look at your .cpp file. If you include 
# user-defined header files, then you need to put it as pre-requisite files. 
# No need to include in the pre-requisite if you are using standard header files, like iostream.
# If the file is in the folder, specify the folder as well.

Motorbike/Motorbike.o : Motorbike/Motorbike.cpp Motorbike/Motorbike.h
	$(CC) -c Motorbike/Motorbike.cpp -o Motorbike/Motorbike.o

Member/Member.o : Member/Member.cpp Member/Member.h
	$(CC) -c Member/Member.cpp -o Member/Member.o

Date/Date.o : Date/Date.cpp Date/Date.h
	$(CC) -c Date/Date.cpp -o Date/Date.o

Review/Review.o : Review/Review.cpp Review/Review.h
	$(CC) -c Review/Review.cpp -o Review/Review.o

Admin/Admin.o : Admin/Admin.cpp Admin/Admin.h
	$(CC) -c Admin/Admin.cpp -o Admin/Admin.o

Request/Request.o : Request/Request.cpp Request/Request.h
	$(CC) -c Request/Request.cpp -o Request/Request.o

System/System.o : System/System.cpp System/System.h
	$(CC) -c System/System.cpp -o System/System.o

main.o : main.cpp Motorbike/Motorbike.h Member/Member.h Date/Date.h Review/Review.h Admin/Admin.h Request/Request.h System/System.h 
	$(CC) -c main.cpp -o main.o 

# clean target is used to remove all the .o files and .out file
# To use it, type "make clean" at the terminal 
# If you are using Mac, change the command "del" to "rm".
clean :
	rm -f $(OBJS)

clean-out:
	rm -f $(OUT)$(EXE_EXTENSION)


