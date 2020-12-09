all: TicketToRide

TicketToRide: main.o TicketToRideAPI.o clientAPI.o
	gcc -Wall -o TicketToRide main.o TicketToRideAPI.o clientAPI.o

main.o: main.c
	gcc -Wall -c main.c

TicketToRideAPI.o: TicketToRideAPI.c
	gcc -Wall -c TicketToRideAPI.c

clientAPI.o : clientAPI.c
	gcc -Wall -c clientAPI.c
