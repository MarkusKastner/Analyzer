#include "CrossSock.h"

namespace marscode {
  namespace network {
    CrossSock::CrossSock()
      : initialized(false), sock(INVALID_SOCKET),
      webAddress(), port()
    {
      this->initialize();
    }

    CrossSock::~CrossSock()
    {
      this->close();
    }

    bool CrossSock::IsInitialized()
    {
      return this->initialized;
    }

    void CrossSock::Connect(const std::string & address, const unsigned int & port)
    {
      this->internalConnect(address, port);
    }

    bool CrossSock::IsConnected()
    {
      if (this->sock != INVALID_SOCKET) {
        return true;
      }
      else {
        return false;
      }
    }

    std::string CrossSock::GetSide()
    {
      std::string request = "GET / HTTP/1.1\r\nHost: " + this->webAddress + "\r\nConnection: close\r\n\r\n";
      std::string response;

      int sentBytes = send(this->sock, request.c_str(), request.size(), 0);
      if (sentBytes < request.size() || sentBytes == SOCKET_ERROR){
        throw - 1;
      }

      char buffer[10000]{0};
      int dataLen;

      while ((dataLen = recv(this->sock, buffer, sizeof(buffer), 0) > 0)){
        int i = 0;
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
          response.push_back(buffer[i]);
          i += 1;
        }
      }
      return response;
    }

    #ifdef _WIN32 
    void CrossSock::initialize()
    {
      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      wVersionRequested = MAKEWORD(2, 2);

      err = WSAStartup(wVersionRequested, &wsaData);
      if (err != 0) {
        throw - 1;
      }
      if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        throw - 1;
      }
      this->initialized = true;
    }

    void CrossSock::close()
    {
      if (this->sock != INVALID_SOCKET) {
        closesocket(this->sock);
      }

      WSACleanup();
    }

    void CrossSock::internalConnect(const std::string & address, const unsigned int & port)
    {
      struct addrinfo *result = NULL, *ptr = NULL, hints;

      char recvbuf[DEFAULT_BUFLEN];

      int iResult;
      int recvbuflen = DEFAULT_BUFLEN;

      ZeroMemory(&hints, sizeof(hints));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_TCP;

      iResult = getaddrinfo(address.c_str(), std::to_string(port).c_str(), &hints, &result);
      if (iResult != 0) {
        throw - 1;
      }

      for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        this->sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->sock == INVALID_SOCKET) {
          throw - 1;
        }

        iResult = connect(this->sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
          closesocket(this->sock);
          this->sock = INVALID_SOCKET;
          continue;
        }
        break;
      }

      freeaddrinfo(result);

      if (this->sock == INVALID_SOCKET) {
        throw - 1;
      }
      this->webAddress = address;
      this->port = port;
    }

    #elif __linux__  
    void CrossSock::initialize()
    {

    }

    void CrossSock::close()
    {

    }

    void CrossSock::internalConnect(const std::string & address, const unsigned int & port)
    {

    }
    #endif
  }
}