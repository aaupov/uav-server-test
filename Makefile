CC=clang
CXX=clang++
CFLAGS=-Wall -O2
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lmysqlclient
INCLUDE=-I../rpcp
BINDIR=./bin
SOURCES=backend.cpp mysql_connection.cpp handler.cpp logger.cpp socket.cpp

all: backend client

backend:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend $(SOURCES)

client:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*
