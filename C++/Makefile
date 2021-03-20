DEST		=	./build

GCC			=	g++
CFLAGS		+=	-Wall -Wextra -Wno-deprecated -std=c++11 
CFLAGS		+=	-I./code/inc/

SRC_PATH	=	./code/src/
INC_PATH	=	./code/inc/

LIB_SRC		=	libEthernet.cpp

NAME		=	libEthernet.so


###
# RULES #
###
#OBJ			=	$(addprefix $(SRC_PATH), $(SRC:.c=.o))

RM			=	rm -f

all			:	$(NAME)

$(NAME)		:	
				$(GCC) $(CFLAGS) --shared -fPIC $(SRC_PATH)$(LIB_SRC) -o $(DEST)/$(NAME)

server		:	$(NAME)
				$(GCC) $(CFLAGS) tests/server.cpp -L$(DEST) -lEthernet -o $(DEST)/testServer

client		:	$(NAME)
				$(GCC) $(CFLAGS) tests/client.cpp -L$(DEST) -lEthernet -o $(DEST)/testClient
 
tests		:	$(NAME) server client

clean		:
				$(RM) $(DEST)/$(NAME) $(DEST)/testClient $(DEST)/testServer

re			:	clean all

.PHONY		:	all clean re
