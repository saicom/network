#pragma once

//! @file os.h
//! @brief 定义socket相关类型



#if (defined(WIN32) || defined(_WIN64))

#if defined(FD_SETSIZE)
#undef FD_SETSIZE
#define FD_SETSIZE 1024
#else
#define FD_SETSIZE 1024
#endif /* defined(FD_SETSIZE) */

#include <winsock2.h>
#include <direct.h>
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>

#pragma comment(lib,"wsock32.lib")
#define snprintf _snprintf 

typedef int socklen_t;
typedef int						socklen_t;
typedef uint32_t				in_addr_t;
typedef uint16_t				in_port_t;

//! 设置为非阻塞模式
inline int set_socket_nonblocking(SOCKET socket)
{
	int iMode = 1;
	int nret = ioctlsocket(socket, FIONBIO, (u_long FAR*)&iMode);

	return nret;
}

//! 关闭socket
inline int close(SOCKET socket)
{
	return closesocket(socket);
}

//! 错误码
inline int error_no()
{
	return WSAGetLastError();
}


#define NETWORK_EAGAIN		WSAEWOULDBLOCK		//<! 无数据可读或可写
#define NETWORK_EINPROGRESS	WSAEWOULDBLOCK			//<! 正在连接
#define NETWORK_EWOULDBLOCK	WSAEWOULDBLOCK


//! 创建文件夹
inline int mkdir(const char *dirname, int)
{
	return _mkdir(dirname);
}


#define F_OK 0
#define W_OK 2
#define R_OK 4


//! 检测文件
inline int access(const char *path, int mode)
{
	return _access(path, mode);
}


#else			// for linux

#define NETWORK_EAGAIN		EAGAIN
#define NETWORK_EINPROGRESS	EINPROGRESS
#define NETWORK_EWOULDBLOCK	EWOULDBLOCK

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>				// for snprintf
#include <stddef.h>				// for size_t
#include <unistd.h>				// for ssize_t and socklen_t
#include <netinet/in.h>			// for in_addr_t and in_port_

//! @typedef SOCKET
//! @brief socket类型
typedef int SOCKET;


//! @def INVALID_SOCKET
//! @brief 无效socket
#define INVALID_SOCKET -1

//! 睡眠，改为毫秒
inline void Sleep(unsigned long _m)
{
	struct timespec req;
	req.tv_sec = (int)_m / 1000;
	req.tv_nsec = (_m - req.tv_sec * 1000) * 1000000L;
	nanosleep(&req, NULL);
}

//! 设置为非阻塞模式
inline int set_socket_nonblocking(SOCKET socket)
{
	int val = fcntl(socket, F_GETFL, 0);
	int nret = fcntl(socket, F_SETFL, val | O_NONBLOCK);

	return nret > -1 ? 0 : nret;
}

//! 错误码
inline int error_no()
{
	return errno;
}


#endif

//设置socket接收或者发送缓冲区大小
inline int set_socket_bufsize(SOCKET sock, bool isRead, int netbufsize)
{
	int opt_name = isRead ? SO_RCVBUF : SO_SNDBUF;
	int nBufSize = netbufsize;
	return ::setsockopt(sock, SOL_SOCKET, opt_name, reinterpret_cast<char*>(&nBufSize), sizeof(nBufSize));
}

inline int get_socket_bufsize(SOCKET sock, bool isRead, int& netbufsize)
{
	int opt_name = isRead ? SO_RCVBUF : SO_SNDBUF;
	socklen_t nsize = sizeof(netbufsize);
	return ::getsockopt(sock, SOL_SOCKET, opt_name, reinterpret_cast<char*>(&netbufsize), &nsize);
}

inline std::string GetIpStr(uint32_t ip)
{
	uint32_t ip1 = ip / 0x1000000;
	ip -= ip1 * 0x1000000;
	uint32_t ip2 = ip / 0x10000;
	ip -= ip2 * 0x10000;
	uint32_t ip3 = ip / 0x100;
	ip -= ip3 * 0x100;
	uint32_t ip4 = ip;

	char ipStr[100];
	snprintf(ipStr, 100, "%d.%d.%d.%d", ip4, ip3, ip2, ip1);
	return ipStr;
}
