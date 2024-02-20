# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 11:44:59 by iestero-          #+#    #+#              #
#    Updated: 2024/02/20 11:30:09 by iestero-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directorios
PATHS = tests/
PATHB = build/
PATHO = build/objs/
PATHR = build/results/
PATHT = build/text/

# Archivos
MINISHELL = ../libs/libMinishell.a
LIBFT = ../libft/libft.a
LIBFTINC = ../libft/inc
MINISHELLINC = ../inc

# Flags de compilación
INCLUDES = -I$(LIBFTINC) -I$(MINISHELLINC)
CC = gcc -fsanitize=address
CFLAGS = -g $(INCLUDES)
LINK = gcc -lreadline -fsanitize=address

# Fuentes y objetos
SRC_FILES 	= 	TestTrimCommand.c	\
				TestSplitCommand.c	\
				TestSplitPipes.c	\
				TestEnvVariable.c	\


SRCS = $(addprefix $(PATHS),$(SRC_FILES))
OBJS = $(patsubst $(PATHS)%.c,$(PATHO)%.o,$(SRCS))
OUTS = $(patsubst $(PATHO)%.o,$(PATHR)%.out,$(OBJS))
TXT  = $(patsubst $(PATHO)%.o,$(PATHT)%.txt,$(OBJS))

# Reglas
test: build $(TXT)

build: $(OBJS) $(OUTS) 
	@echo done

clean:
	@rm -rf $(PATHO) $(PATHR)

re: clean build

$(PATHR)%.out: $(PATHO)%.o
	@mkdir -p $(PATHR)
	$(LINK) $< $(LIBFT) $(MINISHELL) -o $@ 

$(PATHO)%.o: $(PATHS)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(PATHT)%.txt: $(PATHR)%.out
	@mkdir -p $(PATHT)
	./$< > $@



.PHONY: test build clean re

