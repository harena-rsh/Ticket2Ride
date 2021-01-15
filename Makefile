all: TicketToRide

TicketToRide: game.o TicketToRideAPI.o clientAPI.o Q3.o Q5.o route.o
	gcc -Wall -g -o TicketToRide game.o TicketToRideAPI.o clientAPI.o Q3.o Q5.o route.o

game.o: game.c
	gcc -Wall -c -g game.c
Q3.o:Q3.c
	gcc -Wall -c -g Q3.c
Q5.o:Q5.c
	gcc -Wall -c  -g Q5.c
route.o: route.c
	gcc -Wall -c -g route.c

TicketToRideAPI.o: TicketToRideAPI.c
	gcc -Wall -c TicketToRideAPI.c

clientAPI.o : clientAPI.c
	gcc -Wall -c clientAPI.c
