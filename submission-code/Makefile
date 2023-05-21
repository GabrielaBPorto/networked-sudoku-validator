CFLAGS = -Wall -g
LDFLAGS = -lm

objs = server.o client.o
bins = server client

# Regra default

all: $(objs) $(bins)

# Regras de ligação

server: server.o slibrary.c 
	gcc server.c slibrary.c -o server $(CFLAGS) $(LDFLAGS)


client: client.o clibrary.c
	gcc client.c clibrary.c -o client $(CFLAGS) $(LDFLAGS)

# Regras de compilação

server.o: server.c slibrary.h geral_library.h
	gcc -c server.c $(CFLAGS)

client.o: client.c clibrary.h geral_library.h
	gcc -c client.c $(CFLAGS)


clean : 
	-rm $(objs)

purge:
	-rm $(bins) $(objs)