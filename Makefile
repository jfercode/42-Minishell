# Static library name
NAME	=	build/minishell.a

# Compiller and compiler flags
CC		=	cc
C_FLAGS	=	-Wall -Werror -Wextra 
LIBS 	=	-lreadline -lncurses -ltermcap

# Directories -> TO DO: Include Libft + Printf + Extras
SRC_DIR		=	source
OBJ_DIR		=	build/obj
HEADER_DIR	=	include
LIBFT_DIR	=	source/libft
LIBFT_LIB	=	source/libft/build/libft.a

# Source Files -> TO DO: Replace wildcard with correct directories
SRC_FILES 	=	$(wildcard $(SRC_DIR)/*.c)
TOTAL_FILES	=	$(words $(SRC_FILES))
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

$(NAME): $(LIBFT_LIB) $(OBJS)
		@mkdir -p $(OBJ_DIR)
		@echo "$(GREEN)CREATING STATIC LIBRARY $@ $(RESET)"
		ar rcs $@ $^
		@echo "$(CYAN)COMPILING AND GENERATE THE EXECUTABLE...$(RESET)"
		$(CC) $(CFLAGS) -o minishell $(OBJ_DIR)/main.o $(NAME) $(LIBFT_LIB) $(LIBS)

# Rule to compile .c files into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
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

# Phony rules
.PHONY:	all clean fclean re
