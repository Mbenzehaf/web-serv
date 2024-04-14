# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/30 20:04:20 by mben-zeh          #+#    #+#              #
#    Updated: 2024/04/09 00:49:50 by mben-zeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME1 = Client
NAME = Server

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

#-fsanitize=address -g3

SRCS = server.cpp config.cpp

OBJS = ${SRCS:.cpp=.o}

all : ${NAME} 

${NAME} : ${OBJS}
	${CXX} ${OBJS} ${CXXFLAGS} -o ${NAME}

clean : 
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all