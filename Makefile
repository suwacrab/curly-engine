# --	compiler
CC = gcc

#	--	include paths
INC = -I./ -I./include

# --	objects
OBJS = src/main.o

#	--	libraries
LIBS = -lm -lSDL -lSDL_image

#	--	objs, names
OBJS = src/main.o src/mokou.o src/keine.o src/kosuzu.o
NAME = mokou

#	--	main event
%.o: %.c
	$(CC) -c -o $@ $< $(INC) -Wall -Wextra

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(INC) $(LIBS)

clean:
	rm $(OBJS)

