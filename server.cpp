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
#define MAX_CLIENTS 1024
#define MAX_EVENTS 1024
#define BUFFER_SIZE 1024

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
    std::map<int,sockaddr_in>::const_iterator it_serverSockets;
    for(it_serverSockets = map.begin(); it_serverSockets != map.end(); it_serverSockets++)
    {
        close(it_serverSockets->first);
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
    std::vector<int> serverSockets;
    std::vector<int>::iterator it;
    std::vector<int> clientFds;
    int socketFd,epollFd,clientFd;
   epoll_event events[MAX_CLIENTS];

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
                serverSockets.push_back(socketFd);
                sockaddr_in serverAddress;
                memset(&serverAddress,0,sizeof(serverAddress));
                serverAddress.sin_family = AF_INET;
                serverAddress.sin_port = htons(atoi(it_servers->second.config["listen"].at(i).c_str()));
                serverAddress.sin_addr.s_addr = inet_addr(it_servers->first.c_str());
                if(bind(socketFd,(sockaddr*)&serverAddress,sizeof(serverAddress)) == -1)
                    throw std::runtime_error("Failed to bind socket.");
                if(listen(socketFd,5) == -1)
                    throw std::runtime_error("Failed to listen.");
             }
        }
        
       epollFd = epoll_create(1);
       if(epollFd == -1)
            throw std::runtime_error("Failed to create epoll instance.");
        std::vector<epoll_event> serverEvents(serverSockets.size());
        for(size_t i = 0 ; i < serverSockets.size() ; i++)
        {
            serverEvents[i].data.fd = serverSockets.at(i);
            serverEvents[i].events = EPOLLIN;
            if(epoll_ctl(epollFd,EPOLL_CTL_ADD,serverSockets[i],&serverEvents[i]) == -1)
                throw std::runtime_error("Failed to add server socket to epoll instance.");
        }

        while (true)
        {
            int numEvents = epoll_wait(epollFd,events, MAX_EVENTS, -1);
            if(numEvents == -1)
                throw std::runtime_error("Failed to accept client connection.");
            for(int i = 0 ; i < numEvents;i++)
            {
                int fd = events[i].data.fd;
                if((it = std::find(serverSockets.begin(),serverSockets.end(),fd)) != serverSockets.end())
                {
                    sockaddr_in clientAddress;
                    socklen_t clientAddressLen = sizeof(clientAddress);
                    if((clientFd  = accept(*it,(sockaddr *)&clientAddress,&clientAddressLen)) == -1)
                    {
                        std::cerr << "Failed to accept client connection." << std::endl;
                        continue;
                    }
                    clientFds.push_back(clientFd);
                    char buf[1024];
                    memset(buf,0,1024);
                    recv(clientFd,buf,1024,0);
                    std::cout <<buf << std::endl;
                    std::string str = "<!DOCTYPE html><html><head></head><body><h1>My First Heading</h1><p>My first paragraph.</p></body></html>";
                    send(clientFd,str.c_str(),str.length(),0);
                   
                }else
                {
                    std::cout << "OKY" << std::endl;
                }
            }
        }
        
    }
    catch(const std::exception& e)
    {
        close(serverSockets);
        close(clientFds);
        close(epollFd);
        std::cerr  << BOLDRED << e.what() << '\n';
        return(1);
    }
    return (0);
}