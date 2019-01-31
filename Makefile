TARGET	= avm
CXX 	= g++
FLAGS 	= -Wall -Wextra -Werror -std=c++11
RM 		= /bin/rm -f

INC_DIR = ./inc/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

SRCS	= main.cpp Factory.cpp Lexer.cpp Parser.cpp 
OBJS 	= $(addprefix $(OBJ_DIR), $(SRCS:.cpp=.o))
HDRS	= -I $(INC_DIR)
MKDIR 	= mkdir -p

LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
RESET = '\033[0m'

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(FLAGS) $(HDRS) -o $@ $^
	@echo $(LGREEN) "AbstractVM is compiled!" $(RESET)

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CXX) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo $(YELLOW) "Object files are removed!" $(RESET)

fclean: clean
	@$(RM) $(TARGET)
	@echo $(LRED) "Executable is removed!" $(RESET)


re: fclean all