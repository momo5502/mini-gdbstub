#ifndef WIN32_H
#define WIN32_H

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

#pragma comment(lib, "ws2_32.lib")

typedef int ssize_t;
//typedef SOCKET socket_t;

#define poll WSAPoll
#define close closesocket
#define read(a, b, c) recv(a,b,c,0)
#define write(a, b, c) send(a, b, c, 0)

typedef HANDLE pthread_t;

#define pthread_join(a, b) WaitForSingleObject(a, INFINITE)
#define pthread_create(a, b, c, d) *(a) = CreateThread(NULL, 0, c, d, 0, NULL)

#define __ATOMIC_RELAXED 1
#define __atomic_store_n(a, b, c) InterlockedExchange8((volatile CHAR *) (a), (b))
#define __atomic_load_n(a, b) InterlockedOr8((volatile CHAR *) (a), 0)

#define usleep(x) Sleep(x / 1000000)

#else

typedef int socket_t;
#endif

#endif