CC = gcc
OBJ_ONE = find_one.exe
OBJ_TWO = find_two.exe
OBJ_THREE = find_three.exe

%.exe : %.o
		$(CC) -o $@ $^

%.o : %.c
		$(CC) -c -o $@ $^

all: $(OBJ_ONE) $(OBJ_TWO) $(OBJ_THREE)

clean:
		rm -f *.exe *.o