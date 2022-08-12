INC_DIR =	-ISender\
			-IReceiver\
			-IParser\
			-I../../inc\
			-I../../inc/DataStructure
CXXFLAGS = -fsanitize=address -g

ifeq ($(shell uname), Linux)

LIBRARY = -L../../lib -lkqueue -lpthread
INC_DIR += -I../../lib/

endif

all: server.out

server.out:
	$(CXX) main.cpp $(INC_DIR) $(LIBRARY) $(CXXFLAGS) -o $@

re:
	rm server
	$(MAKE) all