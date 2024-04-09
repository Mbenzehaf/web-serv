/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:06:03 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/04/09 03:10:14 by mben-zeh         ###   ########.fr       */
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
    int epollFd;
    //sockaddr_in serverAdress;
    
    serverfd = -1;
    epollFd = -1;
    //(void)av;
    try
    {
        if(ac != 2)
           throw std::runtime_error("./webserv [configuration file]");
        GlobalConfig config(av[1]);
        std::map < std::string, serverConfig >::iterator servers;
        
        for(servers = config.servers.begin(); servers !=  config.servers.end() ; servers++)
        {
            show(servers->second.config.begin(),servers->second.config.end());
        }
       /* if((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1 )
           throw std::runtime_error("Failed to create socket.");
        serverAdress.sin_family = AF_INET;
        serverAdress.sin_port = htons(PORT);
        serverAdress.sin_addr.s_addr = INADDR_ANY;
        if(bind(serverfd,(sockaddr *)&serverAdress,(socklen_t)sizeof(serverAdress)) == -1)
            throw std::runtime_error("Failed to bind socket.");
        if(listen(serverfd,MAX_CLIENTS) == -1 )
            throw std::runtime_error("Failed to listen.");
        if((epollFd  = epoll_create1(0))== -1)
            throw std::runtime_error("Failed to create epoll instance");
        epoll_event serverEvents;
        serverEvents.events = EPOLLIN;
        serverEvents.data.fd = serverfd;
        if(epoll_ctl(epollFd,EPOLL_CTL_ADD,serverfd,&serverEvents) == -1)
            throw std::runtime_error("Failed to add server socket to epoll instance");
        epoll_event events[MAX_CLIENTS];
        std::vector<int> fd_clients;*/
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