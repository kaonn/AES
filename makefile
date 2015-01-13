CFLAGS=-c -Wall -Wextra -Werror -g -fwrapv -std=c99
LINK=-Wall -Wextra -Werror -g -fwrapv -std=c99

all: main.o aes.o finite_field.o 
	gcc main.o aes.o finite_field.o -o a.out

main.o: main.c
	gcc $(CFLAGS) main.c

aes.o: aes.c
	gcc $(CFLAGS) aes.c

finite_field.o: finite_field.c
	gcc $(CFLAGS) finite_field.c

test.o: test.c
	gcc $(CFLAGS) test.c

app.o: app.c
	gcc $(CFLAGS) app.c

debug: aes.o finite_field.o test.o 
	gcc $(LINK) aes.o finite_field.o test.o -o debug 

app: aes.o finite_field.o app.o 
	gcc $(LINK) aes.o finite_field.o app.o -o app

clean:
	rm -rf *o hello