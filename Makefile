# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 06:37:18 by codespace         #+#    #+#              #
#    Updated: 2024/03/31 07:10:52 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = server

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror

SRC = server.cpp

OBJ = ${SRC:.cpp=.o}

all : ${NAME}

${NAME}:${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -O ${NAME}

clean :
	rm -rf ${OBJ}
fclean : clean
	rm -rf ${NAME}
re:fclean all