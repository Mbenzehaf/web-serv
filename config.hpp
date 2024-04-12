/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:08:45 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/04/10 07:01:57 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <netdb.h>
#include <sstream>
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#define npos std::string::npos
#define INVALIDCONFIG "Error: invalid configuration file"

class Keywords
{
    protected:
    std::map<std::string,std::vector<std::string> > keywords,gkeywords;
    std::set<std::string> keyspath;
    public:
    Keywords();
};

class locationConfig {
    public :
        std::map < std::string, std::vector<std::string> > config;
        void setlocation(const std::vector<std::string> &);
        void getconfig();
        //std::map<std::string ,  std::vector<std::string> >& getlocations();
};

class serverConfig {
    public :
        std::map < std::string, std::vector<std::string> > config;
        std::map < std::string, locationConfig > locations;
        void getconfig();
        void setconfig(const std::vector<std::string> &arr);
};

class GlobalConfig:protected Keywords{
    private :
        std::map <std::string,  std::vector<std::string> > config;
        std::map < int, std::string > serverNames;
        std::string currentLocation;
        std::string currentServer;
        
    protected :
        bool checkkeywords(const std::vector<std::string>& );
    public :
        std::map < std::string, serverConfig > servers;
        void setconfig(const std::vector<std::string> &);
        void setServers(const std::vector<std::string>&);
        void getconfig();
        GlobalConfig(const char *);
};

#endif