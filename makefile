links := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lconfig
opts := -Wall -Wextra -Wpedantic
compiler := clang

game: main.c

	${compiler} $^ -o $@.o ${opts} ${links}