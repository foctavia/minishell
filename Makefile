# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
RESET		= "\033[m"

# Compilation flags
ifeq ($(DMEM),1)
MEM 		= -fsanitize=address
endif

ifeq ($(DTHREAD),1)
MEM 		= -fsanitize=thread
endif

# Variables
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g
CC			= cc
FLAGS		= -lreadline

OBJ_DIR		= objs/
SRC_DIR		= src/
INC_DIR		= inc/

SRC_FILES	=	minishell.c \
				init/init.c init/env.c\
				lexer/lexer.c lexer/tokenize.c lexer/copy.c lexer/quote.c lexer/utils.c lexer/checker.c \
				expanser/expanser.c expanser/var.c expanser/quote.c expanser/insert.c \
				parser/parser.c parser/utils.c parser/path.c \
				utils/display.c utils/error.c utils/utils.c utils/string.c \
				builtins/builtins.c builtins/ms_exit.c builtins/ms_env.c\
				clean/clean.c

OBJS		= $(addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o})
INC			= -I./$(INC_DIR)

# Rules
all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p ${@D}
	$(CC) $(CFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(MEM) $(INC)  $(OBJS) -o  $@ $(FLAGS)
	@echo -n "Compiling minishell"
	@echo $(GREEN)"\tOK"$(RESET)

run: re
	./minishell

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
	make all

.PHONY : all clean fclean re