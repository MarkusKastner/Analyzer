#ifndef CRAOSSOCK_H
#define CRAOSSOCK_H

#include <string>

#define DEFAULT_BUFLEN 512

#ifdef _WIN32 
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#elif __linux__  

typdef int SOCKET;
#define INVALID_SOCKET -1
#endif

namespace marscode {
  namespace network {
    class CrossSock
    {
    public:
      CrossSock();
      virtual ~CrossSock();

      bool IsInitialized();

      void Connect(const std::string & address, const unsigned int & port);
      bool IsConnected();
      std::string GetSide();

    private:
      bool initialized;
      SOCKET sock;
      std::string webAddress;
      unsigned int port;

      void initialize();
      void close();
      void internalConnect(const std::string & address, const unsigned int & port);
    };
  }
}
#endif