CC = g++
NAME = pomerance

main: main.cpp
	$(CC) $< -o $(NAME)

debug: main.cpp
	$(CC) $< -DDEBUG -o $(NAME)

clean:
	rm ./$(NAME)