SERVER_NAME = server.out

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj
SERVER_DIR = server

SERVER_SRC = server_main.cpp Receiver.cpp Sender.cpp
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:.cpp=.o))

VPATH = $(shell ls -R)

INC_DIRS =	-I$(SRC_DIR)/$(SERVER_DIR)/Sender\
			-I$(SRC_DIR)/$(SERVER_DIR)/Receiver\
			-I$(SRC_DIR)/$(SERVER_DIR)/Parser\
			-I$(INC_DIR)\
			-I$(INC_DIR)/DataStructure

ifeq ($(shell uname), Linux)
LIBRARY = -L./lib -lkqueue -lpthread
INC_DIRS += -I./lib/
endif

CXXFLAGS = -fsanitize=address -g
LDFLAGS = -fsanitize=address -g $(LIBRARY)

all: $(OBJ_DIR) server

$(OBJ_DIR):
	mkdir $@

server: $(SERVER_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	$(CXX) $(SERVER_OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o : %.cpp 
	$(CXX) -c $< -o $@ $(INC_DIRS) $(CXXFLAGS)

re:
	rm $(SERVER_NAME)
	$(MAKE) all