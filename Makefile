NAME 		:= minishell

RM			= /bin/rm

.SUFFIXES:				# delete the default suffixes
.SUFFIXES: .c .o .h		# define our suffix list

include	minishell.mk

OBJ_FILES		= $(SRC_FILES:%.c=%.o)

LIBS			=	ft		# name of our libraries : lib[ft].a

##### DIRECTORIES

LIB_DIR			= 	libft
INC_DIR			= 	includes
SRC_DIR			= 	srcs
OBJ_DIR			= 	obj

SUB_DIRS		= 	builtins		\
					clean			\
					display			\
					environment		\
					execution		\
					init			\
					parsing			\
					parsing/lexer	\
					parsing/parser	\
					shell_level		\
					signal			\
					termcaps

SRC_SUBDIRS 	=	$(addprefix $(SRC_DIR)/, $(SUB_DIRS))

OBJ 			= 	$(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

INC_PATH		= 	$(INC_DIR) $(addsuffix /$(INC_DIR), $(LIB_DIR))

VPATH			= 	$(SRC_DIR) $(SRC_SUBDIRS)


##### COMPILING

CC				= 	gcc 

FLAGS			= 	-Wall -Wextra -Werror 
CPPFLAGS		=	$(foreach path, $(INC_PATHS), -I$(path))
LDFLAGS			= 	-L$(LIB_DIR)
LDLIBS			=	$(foreach lib, $(LIBS), -l$(lib))


##### RULES

all: libft ${NAME}

# LIBFT

libft :
	@make -C $(LIB_DIR)

# OBJECT DIRECTORY

$(OBJ_DIR):
	@mkdir -p $@

# COMPILING

$(OBJ_DIR)/%.o : %.c
	@echo "\r\033[KCompiling\t$< \c"
	@$(CC) $(CPPFLAGS) $(FLAGS) -o $@ -c $<

# LINKING

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -lncurses  -o $@
	@echo "\n\033[32mOK\t\t$@ is ready !!!\033[0m"

# CLEAN
clean: 
	@make -C $(LIB_DIR) clean
	@$(RM) -rf $(OBJ_DIR)
	@echo "Removed\t\tobject files"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@$(RM) -f $(NAME)
	@echo "Removed\t\t$(NAME)"

re: fclean all

.PHONY: all libft clean fclean re


