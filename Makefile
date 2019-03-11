FLAGS = -Wall 
DEPS = fours.h
all: main.o ops.o proc.o
	gcc ${FLAGS} -o fours $^ -lmpfr -lgmp
%.o : %.c ${DEPS}
	gcc ${FLAGS} -c $<
clean:
	rm -rf *.o
	rm fours
