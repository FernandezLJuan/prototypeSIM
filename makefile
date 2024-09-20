links := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
opts := -Wall -Wexrta -Wpedantic
compiler := clang

game: main.c

	${compiler} $^ -o $@.o ${opts} ${links}