links := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
opts := -Wall -Wexra -Wpedantic
compiler := clang

game: main.c

	${compiler} $^ -o $@.o ${opts} ${links}