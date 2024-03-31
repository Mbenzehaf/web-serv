/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 08:06:11 by codespace         #+#    #+#             */
/*   Updated: 2024/03/31 09:04:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
int main()
{
    int server = socket(AF_INET,SOCK_STREAM,0);

    if(server < 0 )
        exit(1);
    sockaddr_in addr;
    memset(&addr,'\0',sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
   int b = bind(server,(sockaddr *)&addr,(socklen_t )sizeof(addr));
   if(b == -1)
      { 
        close(server);
         exit(3);
      }
      listen(server,5);
      int client;
      if((client = accept(server,(sockaddr *)&addr,(socklen_t *)(sizeof(addr)))) == -1)
      {
        close(server);
       exit(4); 
      }
      char ptr[1024];
      recv(client,ptr,1024,0);
      std::cout <<"ol"<< ptr << std::endl;
      close(server);
      
    
}