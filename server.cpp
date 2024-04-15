/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:06:03 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/04/09 20:56:30 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#define PORT 8080
#define MAX_CLIENTS 5
#define MAX_EVENTS 5


// void affacher(std::map < std::string, std::vector<std::string> >::iterator first,std::map < std::string, std::vector<std::string> >::iterator last)
// {
//     for(;first != last;first++)
//     {
//         std::cout << first->first << " | " << first->second[0] << std::endl; 
//     }
// }
void show(std::map < std::string, std::vector<std::string> >::iterator first,std::map < std::string, std::vector<std::string> >::iterator last)
{
    for(;first != last;first++)
    {
        std::cout << first->first << " | " << first->second[0] << std::endl; 
    }
}
int main(int ac,char **av)
{
    int serverfd;
    //int epollFd;
    //sockaddr_in serverAdress;
    //std::map < std::string, serverConfig >::iterator ;
    serverfd = -1;
    //epollFd = -1;
    //(void)av;
    try
    {
        if(ac != 2)
           throw std::runtime_error("./webserv [configuration file]");
        GlobalConfig config(av[1]);
        
    }
    catch(const std::exception& e)
    {
        if(serverfd != -1)
            close(serverfd);
        std::cerr  << BOLDRED << e.what() << '\n';
        return(1);
    }
    return (0);
}