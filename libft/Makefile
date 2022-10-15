NAME := libft.a

RM = /bin/rm

.SUFFIXES:
.SUFFIXES: .c .o .h

include libft.mk

OBJ_FILES	=	$(SRC_FILES:%.c=%.o)

# ****************************** DIRS AND PATHS ****************************** #

INC_DIR		=	includes
SRC_DIR		=	srcs
OBJ_DIR		=	obj

INC			=	$(addprefix $(INC_DIR)/, $(INC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

VPATH		=	$(SRC_DIR)

# *************************** COMPILING AND FLAGS **************************** #

CC = gcc
AR = ar

ARFLAGS = -rcs
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I$(INC_DIR)

# ********************************** RULES *********************************** #

all: $(NAME)

# OBJ DIR #

$(OBJ_DIR):
	@mkdir -p $@

# COMPILING #

$(OBJ_DIR)/%.o : %.c $(INC)
	@echo "\r\033[KCompiling\t$< \c"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

# ARCHIVING AND INDEXING #

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	@$(AR) $(ARFLAGS) $@ $(OBJ)
	@echo "\n\033[32mOK\t\t$@ is ready\033[0m"


# CLEAN #

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "Removed\t\tobject files"

fclean: clean
	@$(RM) -f $(NAME)
	@echo "Removed\t\t$(NAME)"

re: fclean all

.PHONY: all clean fclean re
