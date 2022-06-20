default:
<<<<<<< HEAD
	gcc -g -o prog main.c utils.c time.c listArrayList.c listElem.c mapElem.c mapLinkedList.c stringCode.c input.c loaders.c airline.c airport.c flight.c operations.c tsp.c -lm && ./prog
=======
	gcc -g -o prog main.c utils.c time.c listArrayList.c listElem.c mapElem.c mapLinkedList.c stringCode.c input.c loaders.c airline.c airport.c flight.c operations.c -lm -Wno-pointer-compare && ./prog
>>>>>>> 5e1d84457ca84a357e7cd7a0763233f9383d8b8b
clean:
	rm -f prog
run:
	./prog
debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes ./prog