INC_DIR =	-I/home/mypark/libkqueue/include\
			-I../sender\
			-I../receiver\
			-I../
LIBRARY = -L../lib -lkqueue -lpthread
CXXFLAGS = -fsanitize=address

all: server

server:
	$(CXX) main.cpp $(INC_DIR) $(LIBRARY) $(CXXFLAGS) -o $@

re:
	rm server
	$(MAKE) all