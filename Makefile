# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 18:09:10 by lezard            #+#    #+#              #
#    Updated: 2023/11/10 13:24:30 by jrenault         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY:     			all clear mkbuild clean fclean re

NAME					= philo

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= philosopher.h
HEADERS_WITH_PATH		= $(addprefix $(HEADER_DIR),$(HEADER_FILE))

DIR						= src/
SRC			 			= 	main.c \
							check_args_parsing.c \
							initialization.c \
							utils_lib.c \
							utils_philo.c \
							threading.c \
							fork_process.c \
							stop_condition.c \

OBJECTS			    	= ${addprefix ${BUILD_DIR},${SRC:.c=.o}}

GCC						= cc
CFLAGS					= -Wall -Wextra -Werror -g3 -pthread

RM 						= rm -rf
CLEAR					= clear


$(BUILD_DIR)%.o:		$(DIR)%.c ${HEADERS_WITH_PATH} Makefile
						mkdir -p $(@D)
						$(GCC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

all: 					mkbuild  $(HEADER_DIR)
						$(MAKE) $(NAME)

mkbuild:
						mkdir -p build

clear:
						$(CLEAR)

$(NAME): 				$(OBJECTS)
						$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME) 
				
clean:					
						${RM} $(OBJECTS)
						${RM} $(BUILD_DIR)

fclean:					clean
						${RM} ${NAME}

re:						fclean
						$(MAKE) all