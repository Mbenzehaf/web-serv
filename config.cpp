/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:11:05 by mben-zeh          #+#    #+#             */
/*   Updated: 2024/04/09 01:51:10 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.hpp"
// bool isspace(const std::string& str)
// {
//     for(size_t i = 0 ; i < str.length();i++)
//     {
//         if(!isspace(str.at(i)))
//             return (false);
//     }
//     return (true);
// }

Keywords::Keywords()
{
    gkeywords.insert("log_level");
    gkeywords.insert("log_file");
    gkeywords.insert("error_log");
    //keywords = gkeywords;
    //key.insert("server");
    keywords.insert("server_name");
    
    keywords.insert("port");
    //keywords.insert("listen");
    
    //keywords.insert("path");
    keywords.insert("root");
    keywords.insert("alias");
    
    //keywords.insert("alias");
    keywords.insert("default_page");
    //key.insert("location");
    keywords.insert("proxy_pass");
    keywords.insert("include");
    keywords.insert("autoindex");
    keywords.insert("error_page");
    keywords.insert("access_log");
    //default_type application/octet-strem;
    //include /etc/nginx/mime.types;
    //index
    //allowed_methods
    //autoindex
    //redirect
}
bool allOf(const std::string& str ,int(*fun)(int c)=isspace)
{
    for(size_t i = 0 ; i < str.length();i++)
    {
        if(!fun(str.at(i)))
            return (false);
    }
    return (true);
}
bool iscomment(const std::string& str)
{
    std::string::const_iterator it ;
    for(it = str.begin();  it != str.end() && isspace(*it);it++)
        ;
    if(it != str.end() && *it == '#')
    {
        return (true);   
    }
    return (false);
}

// void GlobalConfig::addkeywords()
// {
//     gkeywords.insert("log_level");
//     gkeywords.insert("log_file");
//     gkeywords.insert("error_log");
//     //keywords = gkeywords;
//     //key.insert("server");
//     keywords.insert("server_name");
    
//     keywords.insert("port");
//     //keywords.insert("listen");
    
//     //keywords.insert("path");
//     keywords.insert("root");
    
//     //keywords.insert("alias");
//     keywords.insert("default_page");
//     //key.insert("location");
//     keywords.insert("proxy_pass");
//     keywords.insert("include");
//     keywords.insert("error_page");
//     keywords.insert("access_log");

//     //default_type application/octet-strem;
//     //include /etc/nginx/mime.types;
//     //index
//     //allowed_methods
//     //autoindex

// }
// std::string removeChar(const std::string &str,char c)
// {
   
    
// }

std::vector<std::string> trim(const std::string &str , char c)
{
    std::vector<std::string> arr;
    std::string value;
    size_t pos,start;

    pos = 0;
    do
    {
        start = pos;
        pos = str.find(c,start);
        if(start < pos)
        {
            if(pos == npos)
                pos = str.length();
            value = str.substr(start,pos - start);
            if(!allOf(value,isspace) && !value.empty())
               arr.push_back(value);
        }else if(pos != npos)
        {
            pos++;  
        }
    }while (pos < str.length());
    return (arr);
}

std::vector<std::string> trim(const std::vector<std::string> arr , char c)
{
    std::vector<std::string> vector,data;
    std::vector<std::string>::const_iterator it ;

    for(it = arr.begin() ; it != arr.end() ; it++)
    {
        data = trim(*it,c);
        vector.insert(vector.end(),data.begin(),data.end());
    }
    return (vector);
}
bool isValidPath(const std::string &path)
{
    std::string::const_iterator it ;
    std::string str = "/\\._-"; 
    for(it = path.begin() ; it != path.end() ; it++)
    {
        if (!isalnum(*it) && str.find(*it) == npos)
        {
            return (false);
        }
    }   
    return (true);
}
bool isDir(const std::string &path)
{
    struct stat info;
    if(stat(path.c_str(),&info) != 0)
    {
        std::cout << ">>" << info.st_mode << std::endl;
        return (false);
    }
    return (false);
}
bool isIpAdresse(const std::string &str)
{
    std::vector<std::string> arr;
    std::vector<std::string>::iterator it;
    std::stringstream ss;
    int block;
    if(std::count(str.begin() , str.end() , '.') != 3)
        return (false);
    arr = trim(str,'.');
    if(arr.size() != 4)
        return (false);
    for(it = arr.begin() ; it  != arr.end();it++)
    {
        if(!allOf(*it,isdigit))
            return false;
        ss << *it;
        ss >> block;
        if(ss.fail()|| block > 255 || block <0)
            return false;
        ss.clear();
    }
    return (true);
}
bool checkBracket(const std::string &line)
{
    size_t left, right;

    left = line.find('[',0);
    right = line.find(']',0);
    
    if(left > right ||(left > 0 && !allOf(line.substr(0,left))) 
    || (right != (line.length() - 1) && !allOf(line.substr(right+1,line.length()))))
        {
            return (false);
        }
    return (true);
}
bool GlobalConfig::checkkeywords(const std::vector<std::string>& arr)
{
    std::vector<std::string>::const_iterator it = arr.begin();
    
    if((currentServer.empty() && gkeywords.find(*it) == gkeywords.end()) 
    || (!currentServer.empty() && keywords.find(*it) == keywords.end()))
    {
        std::cout <<">>>"<<"somthing"<< "<<<<"<< std::endl;
        return (false);
    }
    else if(((*it != "index" || *it != "" ) && arr.size() > 2) 
    || (*it == "port" && !allOf(*(it + 1),isdigit)) || (*it == "root" && !isValidPath(*(it + 1))))
    {
         std::cout <<"<<<<"<< *(it+1)<< ">>>"<< std::endl;
        return (false);
    }
    return (true);
    //(currentServer.empty() && gkeywords.find(arr.at(1)) == gkeywords.end()) || keywords.find(arr.at(0)) == keywords.end()
}

GlobalConfig::GlobalConfig(const char *fileName): Keywords()
{
    size_t left,right;
    std::ifstream configFile(fileName);
    std::string line;
    std::vector<std::string> arr,data;
    
    if(!configFile.is_open())
        throw std::runtime_error("Error: Unable to open configuration file");
    while (std::getline(configFile,line))
    {
        if(line.empty() || allOf(line,isspace) || iscomment(line))
            continue;
        else if( (left = line.find('[')) != npos && (right = line.find(']')) != npos && checkBracket(line))
        {
            arr = trim(line.substr(left + 1,right-left-1),' ');
            if(arr.size() != 2)
                throw std::runtime_error(INVALIDCONFIG);
            if(arr[0] == "server" && isIpAdresse(arr[1]))
            {
                currentServer = arr.at(1);
                currentLocation.clear();
            }
            else if(arr[0] == "location" && isValidPath(arr[1]))
            {
                currentLocation = arr[1];
            }else
                throw std::runtime_error(INVALIDCONFIG);
        }else if(std::count(line.begin(),line.end(),'=') == 1)
        {
            arr = trim(trim(line , '='),' ');
            if(arr.empty() || arr.size() < 2 || !checkkeywords(arr))
                throw std::runtime_error(line);
            else if(currentServer.empty())
                config[arr[0]].assign(arr.begin()+1,arr.end());
            else if(currentLocation.empty())
                servers[currentServer].config[arr[0]].assign(arr.begin()+1,arr.end()); 
            else
                servers[currentServer].locations[currentLocation].config[arr[0]].assign(arr.begin()+1,arr.end());
        }else
            throw std::runtime_error(INVALIDCONFIG);
    }
    configFile.close();
}