# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 11:44:59 by iestero-          #+#    #+#              #
#    Updated: 2024/05/10 07:44:33 by yunlovex         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directorios
PATHS = tests/
PATHB = build/
PATHO = build/objs/
PATHR = build/results/
PATHT = build/text/

# Archivos
MINISHELL = ../libs/libMinishellBonus.a
LIBFT = ../libft/libft.a
LIBFTINC = ../libft/inc
MINISHELLINC = ../incbonus

# Flags de compilación
INCLUDES = -I$(LIBFTINC) -I$(MINISHELLINC)
CC = gcc -fsanitize=address
CFLAGS = -g $(INCLUDES)
LINK = gcc -lreadline -fsanitize=address

# Fuentes y objetos
SRC_FILES 	= 	TestSplitOperands.c


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
	$(LINK) $< $(MINISHELL) $(LIBFT) -o $@ 

$(PATHO)%.o: $(PATHS)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(PATHT)%.txt: $(PATHR)%.out
	@mkdir -p $(PATHT)
	./$< > $@



.PHONY: test build clean re

