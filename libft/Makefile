# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 11:00:43 by iestero-          #+#    #+#              #
#    Updated: 2023/09/06 09:46:09 by iestero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variable

NAME		=	libft.a

GREEN 				= 	\033[0;32m
LIGHT_GRAY 			= 	\033[90m
BLUE 				= 	\033[0;34m
NC 					= 	\033[0m
YELLOW				=	\033[93m

SMILEY				=	\xF0\x9F\x98\x81
CHECK				=	\xE2\x9C\x85

SRC_DIR		=	src
OBJ_DIR		=	build

INC_DIR		=	./inc

IS_TO_DIR	=	ft_is_to
LST_DIR		=	ft_lst
MEM_DIR		=	ft_mem
NUM_DIR		=	ft_num
PUT_DIR		=	ft_put
STR_DIR		=	ft_str
TREE_DIR	=	ft_tree
PRINT_DIR	=	ft_print
GNL_DIR		=	ft_gnl

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror $(INCLUDE)
INCLUDE		= 	-I$(INC_DIR)

MKDIR		=	mkdir -p
RM			=	rm -rf

AR			=	ar
ARFLAGS		=	rsc

#Sources

FT_IS_TO_FILES	=	ft_isalpha.c				\
					ft_isdigit.c				\
					ft_isalnum.c				\
					ft_isascii.c				\
					ft_isprint.c				\
					ft_toupper.c				\
					ft_tolower.c				\

FT_LST_FILES	= 	ft_lstadd_front_bonus.c		\
					ft_lstlast_bonus.c			\
					ft_lstnew_bonus.c			\
					ft_lstsize_bonus.c			\
					ft_lstadd_back_bonus.c		\
					ft_lstdelone_bonus.c		\
					ft_lstclear_bonus.c			\
					ft_lstmap_bonus.c			\
					ft_lstiter_bonus.c			\

FT_MEM_FILES	= 	ft_memmove.c				\
					ft_memcmp.c					\
					ft_memset.c					\
					ft_memchr.c					\
					ft_memcpy.c					\

FT_NUM_FILES	= 	ft_bzero.c					\
					ft_atoi.c					\
					ft_calloc.c					\
					ft_itoa.c					\

FT_PUT_FILES	= 	ft_putchar_fd.c				\
					ft_putstr_fd.c				\
					ft_putendl_fd.c				\
					ft_putnbr_fd.c				\

FT_STR_FILES	= 	ft_strmapi.c				\
					ft_split.c					\
					ft_striteri.c				\
					ft_strjoin.c				\
					ft_strchr.c					\
					ft_strrchr.c				\
					ft_strncmp.c				\
					ft_strnstr.c				\
					ft_strlcpy.c				\
					ft_strlcat.c				\
					ft_strlen.c					\
					ft_substr.c					\
					ft_strtrim.c				\
					ft_strdup.c					\

FT_TREE_FILES	= 	ft_find_tree.c				\
					ft_insert_node.c			\
					ft_new_node.c				\
					ft_clear_tree.c				\

FT_PRINTF_FILES	= 	check_flags_bonus.c			\
					check_format.c				\
					format_chars.c				\
					format_hex.c				\
					format_int.c				\
					format_ptr.c				\
					ft_printf_bonus.c			\
					hashflag_bonus.c			\
					minusflag_bonus.c			\
					plusflag_bonus.c			\
					precision_bonus.c			\
					spaceflag_bonus.c			\
					store_format_bonus.c		\
					utils_bonus.c				\
					width_bonus.c				\
					zeroflag_bonus.c			\

FT_GNL_FILES	= 	get_next_line.c				\

SRCS_FILES		= 	$(addprefix $(IS_TO_DIR)/, $(FT_IS_TO_FILES))		\
					$(addprefix $(LST_DIR)/, $(FT_LST_FILES))			\
					$(addprefix $(MEM_DIR)/, $(FT_MEM_FILES))			\
					$(addprefix $(NUM_DIR)/, $(FT_NUM_FILES))			\
					$(addprefix $(PUT_DIR)/, $(FT_PUT_FILES))			\
					$(addprefix $(STR_DIR)/, $(FT_STR_FILES))			\
					$(addprefix $(TREE_DIR)/, $(FT_TREE_FILES))			\
					$(addprefix $(PRINT_DIR)/, $(FT_PRINTF_FILES))		\
					$(addprefix $(GNL_DIR)/, $(FT_GNL_FILES))			\

SRCS 			= 	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 			= 	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS			=	$(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(IS_TO_DIR) $(LST_DIR) $(MEM_DIR) $(NUM_DIR) $(PUT_DIR) $(STR_DIR) $(TREE_DIR) $(PRINT_DIR) $(GNL_DIR))

#Rules
	
all:	 			$(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(DIRS)
	@printf "\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$< $(NC)\033[K"
	@sleep 0.15
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): 			$(OBJS)
	@$(AR) $(ARFLAGS) $@ $(OBJS)
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRS):
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libft$(NC)"
	@$(MKDIR) $(DIRS)
		
clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT: fclean clean
.PHONY: all clean fclean re

