CC=clang
CXX=clang++
CFLAGS=-Wall -O2
CXXFLAGS=$(CFLAGS) -std=c++11
CXXFLAGS_DEBUG=-Wall -ggdb -O0 -std=c++11
RPCP=/home/fads/dev/uav/rpcp
RPCPLIBS=$(RPCP)/dcp.o $(RPCP)/protoskel.o
LDFLAGS=-lboost_system -lmysqlcppconn 
INCLUDE=-I$(RPCP)
BINDIR=./bin
SOURCES=backend.cpp database.cpp handler.cpp logger.cpp network.cpp command.cpp

all: backend client

backend:
	$(CXX) $(RPCPLIBS) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend

debug:
	$(CXX) $(SOURCES) $(CXXFLAGS_DEBUG) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend.debug

client:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*

install:
	scp $(BINDIR)/backend bpla.falt.ru:
