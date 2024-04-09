/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:08:04 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/04/06 16:30:08 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main()
{
    /*int socket_client;
    try{
        socket_client = socket(AF_INET,SOCK_STREAM,0);
        if(socket_client < 0)
            throw std::runtime_error("creating socket");
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8080);
        if(inet_pton(AF_INET , "127.0.0.1",&addr.sin_addr))
        {
            
        }
        if (connect( socket_client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            
        }
    }catch(const std::exception &e)
    {
        close(socket_client);
        std::cerr <<"Error : " << e.what() << std::endl;
    }*/

    addrinfo *result;
    int error = getaddrinfo("localhost", NULL, NULL, &result);
    
    if (error != 0) {
        // Retrieve the error message for the given error code
std::cerr << "Error resolving host: " << gai_strerror(error) << std::endl;
    }
    return (0);
}