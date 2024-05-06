# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iestero- <iestero-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 10:56:39 by yunlovex          #+#    #+#              #
#    Updated: 2024/05/06 09:02:34 by iestero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variable

NAME				=	minishell
BONUS				=	minishell_bonus

GREEN 				= 	\033[0;32m
LIGHT_GRAY 			= 	\033[90m
BLUE 				= 	\033[0;34m
NC 					= 	\033[0m
YELLOW				=	\033[93m

MANDATORY_PART 		=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                   $(YELLOW)MANDATORY PART$(NC)                   *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"
BONUS_PART 			=	"\n ******************************************************\n				\
						*                                                    *\n					\
						*                                                    *\n					\
						*                     $(YELLOW)BONUS PART$(NC)                     *\n		\
						*                                                    *\n					\
						*                                                    *\n					\
						******************************************************\n\n"					\

SMILEY				=	😀
CHECK				=	🚀

LIBS_DIR			=	libs
LIBMINISHELL		=	$(LIBS_DIR)/libMinishell.a
LIBMINISHELL_BONUS	=	$(LIBS_DIR)/libMinishellBonus.a

LIBFT_DIR			=	./libft
LIBFT				=	$(LIBFT_DIR)/libft.a

OBJ_DIR				=	build
OBJBNS_DIR			=	buildbonus
SRC_DIR				=	src
SRCBNS_DIR			= 	srcbonus

INC_DIR				=	inc
INCBONUS_DIR		=	incbonus

MAIN_DIR			=	main
UTILS_DIR			=	utils
STRING_UTILS_DIR	=	string_utils
PARSE_DIR			=	parse
BUILTINS_DIR		=	built-ins

LDLIBS				=	$(LIBMINISHELL) $(LIBFT) -lncurses -L/Users/$(USER)/.brew/opt/readline/lib -lreadline 
LDLIBS_BONUS		=	$(LIBMINISHELL_BONUS) $(LIBFT) -lncurses -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

CC					=	gcc

CFLAGS				=	-g -Wall -Werror -Wextra $(INCLUDES) $(SANATIZE)
CFLAGS_BONUS		=	-g -Wall -Werror -Wextra $(INCLUDES_BONUS)
LDFLAGS				=   $(LDLIBS) $(SANATIZE)
LDFLAGS_BONUS		=	$(LDLIBS_BONUS)
INCLUDES			=	-I$(INC_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/) -I/Users/$(USER)/.brew/opt/readline/include
INCLUDES_BONUS		=	-I$(INCBONUS_DIR) -I$(addsuffix $(INC_DIR), $(LIBFT_DIR)/) -I/Users/$(USER)/.brew/opt/readline/include

SANITIZE			=	-fsanitize=address

MKDIR				=	mkdir -p
RM					=	rm -f
AR					= 	ar

ARFLAGS 			= 	rsc

# Source

MAIN_FILES		=	minishell.c

PARSE_FILES		=	parse_data.c			\
					parse_command.c			\
					parse_command_name.c	\
					parse_envVariable.c		\
					parse_args.c			\
					parse_redir.c			\
					parse_output.c			\
					parse_input.c			\

STRING_UTILS_FILES	=	split_command.c		\
						split_pipes.c		\
						string_utils.c		\
						string_utils2.c		\
						trim_command.c		\
				
UTILS_FILES		=	errors.c			\
					exec_command.c		\
					proc_minishell.c	\
					frees.c				\
					signal_handler.c 	\
					configurations.c	\
					misc.c				\

BUILTINS_FILES	=	built_cd.c		\
					built_echo.c	\
					built_env.c		\
					built_exit.c	\
					built_export.c	\
					built_pwd.c		\
					built_unset.c	\
									

SRCS_FILES	= 	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES)) 					\
				$(addprefix $(UTILS_DIR)/, $(UTILS_FILES)) 					\
				$(addprefix $(PARSE_DIR)/, $(PARSE_FILES)) 					\
				$(addprefix $(STRING_UTILS_DIR)/, $(STRING_UTILS_FILES)) 	\
				$(addprefix $(BUILTINS_DIR)/, $(BUILTINS_FILES)) 			\

SRCS 		=	$(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS 		=	$(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DIRS		=	$(OBJ_DIR)  $(addprefix $(OBJ_DIR)/, 			\
				$(MAIN_DIR) $(UTILS_DIR) $(PARSE_DIR)			\
				$(BUILTINS_DIR) $(STRING_UTILS_DIR)) 			\

OBJ_MAIN	=	$(addprefix $(OBJ_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES:.c=.o)))

# Source Bonus

MAIN_FILES_BONUS		=	minishell_bonus.c

PARSE_FILES_BONUS		=	parse_data_bonus.c				\
							parse_command_bonus.c			\
							parse_command_name_bonus.c		\
							parse_envVariable_bonus.c		\
							parse_args_bonus.c				\
							parse_redir_bonus.c				\
							parse_output_bonus.c			\
							parse_input_bonus.c				\
							parse_wildcard_bonus.c			\

STRING_UTILS_FILES_BONUS	=	split_command_bonus.c		\
								split_pipes_bonus.c			\
								string_utils_bonus.c		\
								string_utils2_bonus.c		\
								trim_command_bonus.c		\
				
UTILS_FILES_BONUS		=	errors_bonus.c				\
							exec_command_bonus.c		\
							proc_minishell_bonus.c		\
							frees_bonus.c				\
							signal_handler_bonus.c 		\
							configurations_bonus.c		\
							print_exit_bonus.c			\

BUILTINS_FILES_BONUS	=	built_cd_bonus.c		\
							built_echo_bonus.c		\
							built_env_bonus.c		\
							built_exit_bonus.c		\
							built_export_bonus.c	\
							built_pwd_bonus.c		\
							built_unset_bonus.c		\

SRCSBONUS_FILES		=	$(addprefix $(MAIN_DIR)/, $(MAIN_FILES_BONUS)) 						\
						$(addprefix $(UTILS_DIR)/, $(UTILS_FILES_BONUS)) 					\
						$(addprefix $(PARSE_DIR)/, $(PARSE_FILES_BONUS)) 					\
						$(addprefix $(STRING_UTILS_DIR)/, $(STRING_UTILS_FILES_BONUS)) 		\
						$(addprefix $(BUILTINS_DIR)/, $(BUILTINS_FILES_BONUS)) 				\

SRCSBONUS 			=	$(addprefix $(SRCBNS_DIR)/, $(SRCSBONUS_FILES))
OBJSBONUS 			=	$(addprefix $(OBJBNS_DIR)/, $(SRCSBONUS_FILES:.c=.o))
DIRSBONUS			=	$(OBJBNS_DIR)  $(addprefix $(OBJBNS_DIR)/, 			\
						$(MAIN_DIR) $(UTILS_DIR) $(PARSE_DIR)				\
						$(BUILTINS_DIR) $(STRING_UTILS_DIR)) 				\

OBJBONUS_MAIN		=	$(addprefix $(OBJBNS_DIR)/, $(addprefix $(MAIN_DIR)/, $(MAIN_FILES_BONUS:.c=.o)))

# Rules

all:				$(NAME)

bonus:				$(BONUS)

clean:
	@make -s fclean -C $(LIBFT_DIR)
	@$(RM) -r $(LIBS_DIR)
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJBNS_DIR)
	@echo "---- $(YELLOW)Object files deleted. $(CHECK)$(NC) ----"

fclean:				clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	@echo "---- $(YELLOW)Binary files deleted. $(CHECK)$(NC) ----"

print:
	echo $(DIRS)

re:					fclean all

# Mandatory

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c | $(DIRS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)\033[K"
	@sleep 0.5
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJ_MAIN) $(LIBMINISHELL) $(LIBFT)
	@$(CC) $(OBJ_MAIN) $(LDFLAGS) -o $@
	@sleep 1
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"	

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(LIBMINISHELL): 	$(OBJS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRS):
	@clear
	@echo $(MANDATORY_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libMinishell$(NC)"
	@$(MKDIR) $(DIRS)

$(LIBS_DIR):
	@$(MKDIR) $@


# Bonus

$(OBJBNS_DIR)/%.o:		$(SRCBNS_DIR)/%.c | $(DIRSBONUS) $(LIBS_DIR)
	@printf "\r\r\t---> $(BLUE)Compiling:\t$(LIGHT_GRAY)$<$(NC)\033[K"
	@sleep 0.5
	@$(CC) $(CFLAGS_BONUS) -c $< -o $@				

$(LIBMINISHELL_BONUS): 		$(OBJSBONUS)
	@$(AR) $(ARFLAGS) $@ $?
	@echo "\n   $(CHECK) $(GREEN)Library created.$(NC)"

$(DIRSBONUS):
	@clear
	@echo $(BONUS_PART)
	@echo "\n   ---> $(BLUE)Creating:\t$(LIGHT_GRAY)libMinishellBonus$(NC)"
	@$(MKDIR) $(DIRSBONUS)

$(BONUS):				$(OBJBONUS_MAIN) $(LIBMINISHELL_BONUS) $(LIBFT)
	@$(CC) $(OBJBONUS_MAIN) $(LDFLAGS_BONUS) -o $@
	@sleep 1
	@echo "\n$(GREEN)The program is ready.$(SMILEY) $(CHECK)$(NC)"	

.SILENT:			clean fclean
.PHONY:				all clean fclean re bonus