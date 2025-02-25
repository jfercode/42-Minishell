# Static library name
NAME = build/libft.a

# Compiler and compiler flags
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g3 -I $(HEADER_DIR)

# Directories
SRC_DIR = source
OBJ_DIR = build/obj
HEADER_DIR = /include

# Source files
SRC_FILES = 	$(SRC_DIR)/ft_atoi.c		$(SRC_DIR)/ft_atol.c	$(SRC_DIR)/ft_bzero.c	\
				$(SRC_DIR)/ft_calloc.c 		$(SRC_DIR)/ft_get_next_line.c 	\
				$(SRC_DIR)/ft_get_next_line_utils.c					$(SRC_DIR)/ft_isalnum.c	\
				$(SRC_DIR)/ft_isalpha.c		$(SRC_DIR)/ft_isascii.c	$(SRC_DIR)/ft_isdigit.c	\
				$(SRC_DIR)/ft_isprint.c		$(SRC_DIR)/ft_itoa.c	$(SRC_DIR)/ft_lstadd_back.c	\
				$(SRC_DIR)/ft_lstadd_front.c	$(SRC_DIR)/ft_lstclear.c	$(SRC_DIR)/ft_lstdelone.c	\
				$(SRC_DIR)/ft_lstiter.c		$(SRC_DIR)/ft_lstlast.c	$(SRC_DIR)/ft_lstmap.c	\
				$(SRC_DIR)/ft_lstnew.c		$(SRC_DIR)/ft_lstsize.c	$(SRC_DIR)/ft_memchr.c	\
				$(SRC_DIR)/ft_memcmp.c		$(SRC_DIR)/ft_memcpy.c	$(SRC_DIR)/ft_memmove.c	\
				$(SRC_DIR)/ft_memset.c		$(SRC_DIR)/ft_printf.c	$(SRC_DIR)/ft_printf_utils.c	\
				$(SRC_DIR)/ft_putchar_fd.c	$(SRC_DIR)/ft_putendl_fd.c	$(SRC_DIR)/ft_putnbr_fd.c	\
				$(SRC_DIR)/ft_putstr_fd.c	$(SRC_DIR)/ft_split.c	$(SRC_DIR)/ft_strchr.c	\
				$(SRC_DIR)/ft_strdup.c		$(SRC_DIR)/ft_striteri.c	$(SRC_DIR)/ft_strjoin.c	\
				$(SRC_DIR)/ft_strlcat.c		$(SRC_DIR)/ft_strlcpy.c	$(SRC_DIR)/ft_strlen.c	\
				$(SRC_DIR)/ft_strmapi.c		$(SRC_DIR)/ft_strncmp.c	$(SRC_DIR)/ft_strnstr.c	\
				$(SRC_DIR)/ft_strrchr.c		$(SRC_DIR)/ft_strtrim.c	$(SRC_DIR)/ft_substr.c	\
				$(SRC_DIR)/ft_tolower.c		$(SRC_DIR)/ft_toupper.c	$(SRC_DIR)/ft_strarrlen.c	\

OBJS = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule to compile .c files into .o 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;33mCOMPILING $<...\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	@echo "\033[1;31mCLEANING OBJECT FILES AND EXECUTABLES FROM LIBFT...\033[0m" 
	rm -rf $(OBJ_DIR)
	@echo "\033[32mCLEANING LIBFT DONE\033[0m"

# Full clean (including library)
fclean: clean
	rm -f $(NAME)
	@echo "\033[32mLIBFT CLEAR\033[0m"

# Rebuild the project
re: fclean all
	@echo "\033[1;34mREBUILDING LIBFT LIBRARY...\033[0m"

.PHONY: all clean fclean re