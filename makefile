default:
	gcc -g -o prog main.c utils.c time.c listArrayList.c listElem.c mapElem.c mapLinkedList.c stringCode.c input.c loaders.c airline.c airport.c -lm && ./prog
clean:
	rm -f prog
run:
	./prog
debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./prog