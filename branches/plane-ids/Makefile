CC=clang
CXX=clang++
CFLAGS=-Wall -O2
CXXFLAGS=$(CFLAGS) -std=c++11
CXXFLAGS_DEBUG=-Wall -ggdb -O0 -std=c++11
#statically link against boost
#LDFLAGS=/usr/lib/libmysqlcppconn.a /usr/lib/mysql/libmysqlclient.a /usr/lib/libboost_system.a /usr/lib/libz.a
LDFLAGS=-L/usr/lib/mysql -static -lpthread -lboost_system -lmysqlcppconn -lmysqlclient -lz #-static-libstdc++ -static-libgcc
INCLUDE=-I/home/fads/dev/uav/rpcp/
BINDIR=./bin
SOURCES=backend.cpp database.cpp handler.cpp logger.cpp network.cpp

all: backend client

backend:
	$(CXX) $(SOURCES) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend

debug:
	$(CXX) $(SOURCES) $(CXXFLAGS_DEBUG) $(LDFLAGS) $(INCLUDE) -o $(BINDIR)/backend.debug

client:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/client client.c

clean:
	rm $(BINDIR)/*

install:
	scp $(BINDIR)/backend bpla.falt.ru:
