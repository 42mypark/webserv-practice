SERVER_NAME = server.out
CLIENT_NAME = client.out

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj
SERVER_DIR = Server

SERVER_SRC =	server_main.cpp \
							Receiver.cpp \
							Sender.cpp \
							Parser.cpp \
							HttpRequestParser.cpp \
							CgiResponseParser.cpp \
							CgiToHttpTransformer.cpp \
							HttpResponseGenerator.cpp \
							ResponseGenerator.cpp \
							Log.cpp

SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC:.cpp=.o))

VPATH = $(shell ls -R)

INC_DIRS =	-I$(SRC_DIR)/$(SERVER_DIR)/Sender\
			-I$(SRC_DIR)/Log\
			-I$(SRC_DIR)/$(SERVER_DIR)/Receiver\
			-I$(SRC_DIR)/$(SERVER_DIR)/Parser\
			-I$(SRC_DIR)/$(SERVER_DIR)/ResponseGenerator\
			-I$(INC_DIR)\
			-I$(INC_DIR)/DataStructure

ifeq ($(shell uname), Linux)
LIBRARY = -L./lib -lkqueue -lpthread
INC_DIRS += -I./lib/
endif

CXXFLAGS = -fsanitize=address -g
LDFLAGS = -fsanitize=address -g $(LIBRARY)

all:  server

$(OBJ_DIR):
	mkdir $@

server:$(OBJ_DIR) $(SERVER_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	$(CXX) $(SERVER_OBJ) $(LDFLAGS) -o $@

client: $(CLIENT_NAME)

$(CLIENT_NAME): $(SRC_DIR)/Client/Client.cpp
	$(CXX) $< -o $@ $(INC_DIRS)

$(OBJ_DIR)/%.o : %.cpp 
	$(CXX) -c $< -o $@ $(INC_DIRS) $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(SERVER_NAME)

re: fclean
	$(MAKE) all