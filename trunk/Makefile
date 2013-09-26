CC=clang
CXX=clang++
CFLAGS=-c -Wall
LDFLAGS=-lmysqlclient
INCLUDE=-I../rpcp
BINDIR=./bin

all: backend client

backend:
	$(CXX) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend backend.cpp mysql_connection.cpp handler.cpp logger.cpp

client:
	$(CC) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*
