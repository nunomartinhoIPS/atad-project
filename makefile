default:
	gcc -g -o prog main.c utils.c time.c listArrayList.c listElem.c mapElem.c mapArrayList.c stringCode.c input.c loaders.c airline.c -lm && ./prog
clean:
	rm -f prog
run:
	./prog