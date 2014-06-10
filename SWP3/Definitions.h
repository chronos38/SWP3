#pragma once

#ifdef _MSC_VER

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
typedef SOCKET SocketHandle;
typedef int AddrLength;
#define CloseSocket closesocket
#define InvalidSocket INVALID_SOCKET
#define SocketError SOCKET_ERROR

#define ALIGNOF __alignof

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
typedef int SocketHandle;
typedef socklen_t AddrLength;
#define CloseSocket close
#define InetPton inet_pton
#define InetNtop inet_ntop
#define InvalidSocket -1
#define SocketError -1

#define ALIGNOF alignof
typedef unsigned char byte;

#endif

typedef addrinfo AddrInfo;
typedef sockaddr Addr;
typedef sockaddr_in AddrIn;
typedef sockaddr_in6 AddrIn6;
typedef sockaddr_storage AddrStorage;

static const int KB = 1024;
static const int MB = 1024 * 1024;

#include <cstdint>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <memory>
#include <fstream>
#include <functional>
#include <atomic>
#include <map>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <future>

typedef int8_t S8;
typedef uint8_t U8;
typedef int16_t S16;
typedef uint16_t U16;
typedef int32_t S32;
typedef uint32_t U32;
typedef int64_t S64;
typedef uint64_t U64;

typedef byte Byte;

typedef std::string String;

template <typename T>
using Vector = std::vector < T > ;

template <typename T>
using Deque = std::deque < T > ;

template <typename T>
using List = std::list < T > ;

template <typename T>
using Pointer = std::shared_ptr < T >;

template <typename T>
using WeakPointer = std::weak_ptr < T > ;

template <typename T>
using Function = std::function < T >;

template <typename T>
using Atomic = std::atomic < T > ;

template <typename Key, typename Value>
using Map = std::map < Key, Value > ;

template <typename Key, typename Value>
using Hash = std::unordered_map < Key, Value > ;

template <typename T>
using LockGuard = std::lock_guard < T > ;

template <typename T>
using Future = std::future < T > ;

typedef std::mutex Mutex;
typedef std::thread Thread;
typedef std::ifstream InputFileStream;
typedef std::ofstream OutputFileStream;
