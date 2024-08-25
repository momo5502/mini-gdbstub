#ifndef WINSOCK_H
#define WINSOCK_H

#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NO_POSIX_ERROR_CODES
#define _CRT_NONSTDC_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <afunix.h>
#define poll WSAPoll
#define close closesocket
#define read(a, b, c) recv(a,b,c,0)
#define write(a, b, c) send(a, b, c, 0)

typedef int ssize_t;
typedef INT_PTR socket_t;
#else

typedef int socket_t;
#endif

#endif