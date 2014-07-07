CC=g++
DEBUG= -g
IFLAGS+= -I. 
LFLAGS+= -L. 
LINK+= -lboost_thread -lboost_system
CXXFLAGS= -Wall -pipe


PRO=test
OBJ=test.o

all:$(PRO)

%.o:%.cpp
	$(CC) -c -o $@ $< $(DEBUG) $(IFLAGS) $(LFLAGS) $(LINK) $(CXXFLAGS)

$(PRO):$(OBJ)
	$(CC) -o $@ $^ $(DEBUG) $(IFLAGS) $(LFLAGS) $(LINK) $(CXXFLAGS)

clean:
	rm -rf $(PRO) *.o *~

