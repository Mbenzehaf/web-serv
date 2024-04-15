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
void close(const std::map<int,sockaddr_in> & map)
{
    std::map<int,sockaddr_in>::const_iterator it_socketFds;
    for(it_socketFds = map.begin(); it_socketFds != map.end(); it_socketFds++)
    {
        close(it_socketFds->first);
    }
}

void close(const std::map<int,epoll_event> & map)
{
    std::map<int,epoll_event>::const_iterator it;
    for(it = map.begin(); it != map.end(); it++)
    {
        close(it->first);
    }
}

void close(const std::vector<int> & arr)
{
    std::vector<int>::const_iterator it;
    for(it= arr.begin(); it != arr.end(); it++)
    {
        close(*it);
    }
}
int main(int ac,char **av)
{
    //int epollFd;
    //sockaddr_in serverAdress;
    std::map < std::string, serverConfig >::iterator it_servers;
    std::map<int,sockaddr_in> socketFds ;
    std::map<int,sockaddr_in>::iterator it_socketFds;
    std::vector<int> clientFds ;
    std::map<int,epoll_event> epollFds;
    int socketFd,clientfd,epollFd;
    epoll_event event;
    //epollFd = -1;
    //(void)av;
    try
    {
        if(ac != 2)
           throw std::runtime_error("./webserv [configuration file]");
        GlobalConfig config(av[1]);
       
        for(it_servers = config.servers.begin();it_servers !=config.servers.end() ; it_servers++ )
        {
            for(size_t i = 0 ;i < it_servers->second.config["listen"].size() ; i++)
            {
                socketFd = socket(AF_INET,SOCK_STREAM,0);
                if(socketFd == -1)
                    throw std::runtime_error("Failed to create socket.");
                memset(&socketFds[socketFd],0,sizeof(socketFds[socketFd]));
                socketFds[socketFd].sin_family = AF_INET;
                socketFds[socketFd].sin_port = htons(atoi(it_servers->second.config["listen"].at(i).c_str()));
                socketFds[socketFd].sin_addr.s_addr = inet_addr(it_servers->first.c_str());
                if(bind(socketFd,(sockaddr*)&socketFds[socketFd],sizeof(socketFds[socketFd])) == -1)
                    throw std::runtime_error("Failed to bind socket.");
                if(listen(socketFd,5) == -1)
                    throw std::runtime_error("Failed to listen.");
                epollFd = epoll_create(0);
                if(epollFd == -1)
                    throw std::runtime_error("Failed to create epoll instance.");
                epollFds[epollFd].events = EPOLLIN;
                epollFds[epollFd].data.fd = socketFd;
                if(epoll_ctl(epollFd,EPOLL_CTL_ADD,socketFd,&epollFds[epollFd]))
                {
                    throw std::runtime_error("Failed to add server socket to epoll instance.");
                }
            }
        }
        // while (1)
        // {
        //     int numEvents = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        // }
    }
    catch(const std::exception& e)
    {
        close(socketFds);
        close(clientFds);
        close(epollFds);
        std::cerr  << BOLDRED << e.what() << '\n';
        return(1);
    }
    return (0);
}