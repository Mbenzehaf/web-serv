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

NAME1 = Client
NAME2 = Server

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

#-fsanitize=address -g3

SRCS1 = client.cpp
SRCS2 = server.cpp config.cpp

OBJS1 = ${SRCS1:.cpp=.o}
OBJS2 = ${SRCS2:.cpp=.o}

all : ${NAME1} ${NAME2}

${NAME1} : ${OBJS1}
	${CXX} ${OBJS1} ${CXXFLAGS} -o ${NAME1}

${NAME2} : ${OBJS2}
	${CXX} ${OBJS2} ${CXXFLAGS} -o ${NAME2}

clean : 
	rm -rf ${OBJS1} ${OBJS2} 

fclean : clean
	rm -rf ${NAME1} ${NAME2}

re : fclean all