#colors
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
CYAN=\033[1;36m
RESET=\033[0m

CC			= clang++
FLAGS		= -Wall -Wextra -Werror -std=c++98
INCL		= iterator.hpp list.hpp map_iterator.hpp map.hpp map_tree.hpp node.hpp queue.hpp stack.hpp vector_iterator.hpp vector.hpp is_integer.hpp
INCLUDE		= -I ./includes

NAME		= containers

SRC_DIR		= ./sources/
OBJ_DIR		= ./objects/
INCL_DIR 	= ./includes/

SRCS		= main.cpp test_list.cpp test_vector.cpp test_stack.cpp test_queue.cpp test_map.cpp

SRC			= $(addprefix $(SRC_DIR), $(SRCS))
INCLUDES	= $(addprefix $(INCL_DIR), $(INCL))
OBJ			= $(patsubst %.cpp,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME) $(INCLUDES)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(FLAGS) $(INCLUDE)
	@echo "[$(GREEN)OK$(RESET)]$(YELLOW) Compiling $<$(RESET)"

$(NAME): $(OBJ) $(OBJ_C) $(INCLUDES)
	@$(CC) -o $(NAME) $(OBJ) $(OBJ_C) $(FLAGS) $(INCLUDE)
	@echo "[$(GREEN)OK$(RESET)]$(GREEN) Compiled $(NAME) $(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[$(RED)Deleting$(RESET)]$(RED) .o files deleted$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "[$(RED)Deleting$(RESET)]$(RED) File $(NAME) deleted$(RESET)"

re: fclean all