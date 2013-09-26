CC=clang
CXX=clang++
CFLAGS=-c -Wall
LDFLAGS=-lmysqlclient
INCLUDE=-I../rpcp
BINDIR=./bin
SOURCES=backend.cpp mysql_connection.cpp handler.cpp logger.cpp socket.cpp

all: backend client

backend:
	$(CXX) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend $(SOURCES)

client:
	$(CC) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*
