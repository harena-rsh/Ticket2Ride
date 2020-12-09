all: TicketToRide

TicketToRide: main.o TicketToRideAPI.o clientAPI.o Q3.o
	gcc -Wall -o TicketToRide main.o TicketToRideAPI.o clientAPI.o Q3.o

main.o: main.c
	gcc -Wall -c main.c
Q3.o:Q3.c
	gcc -Wall -c Q3.c

TicketToRideAPI.o: TicketToRideAPI.c
	gcc -Wall -c TicketToRideAPI.c

clientAPI.o : clientAPI.c
	gcc -Wall -c clientAPI.c
