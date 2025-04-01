# Static library name
NAME	=	build/minishell.a

# Compiller and compiler flags
CC		=	clang
C_FLAGS	=	-Wall -Werror -Wextra -g
LIBS 	=	-lreadline -lncurses -ltermcap

# Directories
SRC_DIR		=	source
OBJ_DIR		=	build/obj
HEADER_DIR	=	include
LIBFT_DIR	=	source/libft
LIBFT_LIB	=	source/libft/build/libft.a

BUILTINS		=	cd echo env exit export pwd unset
EXECUTION		=	ast_execution error_handling heredoc_handling node_execution node_redirection pipe_execution
PARSING			=	matrix_handling meta_handling syntax_validation matrix_utils
SIGNALS			=	signals_utils
TOKENIZATION	=	ast_utils tokenization tokenization_utils

# Source Files
SRC_FILES 	=	$(addsuffix .c, $(addprefix source/builtin/, $(BUILTINS))) \
	  			$(addsuffix .c, $(addprefix source/execution/, $(EXECUTION))) \
	  			$(addsuffix .c, $(addprefix source/parsing/, $(PARSING))) \
	  			$(addsuffix .c, $(addprefix source/signals/, $(SIGNALS))) \
	  			$(addsuffix .c, $(addprefix source/tokenization/, $(TOKENIZATION))) \
				source/main.c

OBJS 		=	$(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Color macros
RESET		= \033[0m
GREEN		= \033[1;32m
CYAN		= \033[1;36m
YELLOW		= \033[1;33m
RED			= \033[1;31m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
WHITE		= \033[1;97m
GRAY		= \033[0;37m
BRIGHT_RED	= \033[1;91m

# Default rule
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_LIB) $(OBJS)
		@mkdir -p $(OBJ_DIR)
		@echo "$(GREEN)CREATING STATIC LIBRARY $@ $(RESET)"
		ar rcs $@ $^
		@echo "$(CYAN)COMPILING AND GENERATE THE EXECUTABLE...$(RESET)"
		$(CC) $(CFLAGS) -o minishell $(OBJ_DIR)/main.o $(NAME) $(LIBFT_LIB) $(LIBS)

# Rule to compile .c files into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		@echo "$(CYAN)COMPILING $<...$(RESET)"
		$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile the libft library
$(LIBFT_LIB):
		@echo "$(MAGENTA)COMPILING LIBFT LIBRARY...$(RESET)"
		$(MAKE) -C $(LIBFT_DIR)

# Rule to clean object files and executables
clean:
		@echo "$(BRIGHT_RED)CLEANING OBJECT FILES AND EXECUTABLES...$(RESET)" 
		rm -rf build
		rm -f ./minishell
		$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)CLEANING DONE.$(RESET)"

# Rule for full clean
fclean:	clean
		@echo "$(RED)DELETING FILES $(NAME)...$(RESET)"
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean		
		@echo "$(GREEN)ALL CLEANED UP.$(RESET)" 

# Rule to rebuild the project
re:		fclean all
		@echo "$(BLUE)PROJECT REBUILD.$(RESET)"

# Norminette rule
norm:
	norminette $(SRC_FILES) $(HEADER_DIR)/*.h

# Phony rules
.PHONY:	all clean fclean re norm
