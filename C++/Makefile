DEST		=	./build

GCC			=	g++
CFLAGS		+=	-Wall -Wextra -Wno-deprecated -std=c++11 
CFLAGS		+=	-I./code/inc/

SRC_PATH	=	./code/src/
INC_PATH	=	./code/inc/

LIB_SRC		=	libEthernet.cpp

TESTS_SRC	=	test.cpp

NAME		=	libEthernet.so


###
# RULES #
###
#OBJ			=	$(addprefix $(SRC_PATH), $(SRC:.c=.o))

RM			=	rm -f

all			:	$(NAME) test

$(NAME)		:	
				$(GCC) $(CFLAGS) --shared -fPIC $(SRC_PATH)$(LIB_SRC) -o $(DEST)/$(NAME)

clean		:
				$(RM) $(DEST)/$(NAME) $(DEST)/testExec 

re			:	clean all

test		:
				$(GCC) $(CFLAGS) tests/$(TESTS_SRC) -L$(DEST) -lEthernet -o $(DEST)/testExec
 

.PHONY		:	all clean re
