CC=clang
CXX=clang++
CFLAGS=-Wall -O2
CXXFLAGS=$(CFLAGS) -std=c++11
LDFLAGS=-lmysqlclient -lboost_system
INCLUDE=-I/home/fads/dev/uav/rpcp/
BINDIR=./bin
SOURCES=backend.cpp mysql_connection.cpp handler.cpp logger.cpp network.cpp

all: backend client

backend:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend $(SOURCES)

client:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*

install:
	scp $(BINDIR)/backend bpla.falt.ru:
