//! @file net_packet.h
#pragma once


#include "config.h"
#include "os.h"
#include "pool_allocator.h"
#include "List.h"
#include "inet_addr.h"



//! @class Net_Packet
//! @brief 网络包封装类
class Net_Packet
{
public:
    Net_Packet();
    virtual ~Net_Packet();

    DECLARE_ALLOCATOR(Net_Packet, NET_PACKET_POOL_COUNT)

	void write_data(const char* buf, uint32_t len);

	uint32_t get_left_write_len();

	char* get_rptr();

	void read_data(uint32_t len);
public:
    //! 通道id
    uint32_t id;

    //! 对端地址
    INET_Addr remote_addr;

	//! 消息内容
	char msg[MAX_PACKET_LENGTH];

	//! 当前长度
	uint32_t cur_len;
	
	//! 消息长度
	uint32_t msg_len;

	//! 应用层消息id
	uint32_t msg_id;

public:
    enum NET_COMMAND
    {
        NET_TCP_ACCEPTOR_REGISTER,
        NET_TCP_CONNECTOR_REGISTER,
        NET_UDP_REGISTER,
        NET_DELETE
    };

    struct INTERNAL_CMD
    {
        uint32_t id;		// 网络组件Id
        NET_COMMAND cmd;	// 网络组件消息类型
        void* data;			// 回调
        int mask;			// 读写
        int timeout;		// 超时
    } m_cmd;

};
