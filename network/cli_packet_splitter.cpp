#include "network_pch.h"
#include "cli_packet_splitter.h"
#include "os.h"
#include "config.h"


// class Packet_Splitter
Cli_Packet_Splitter::Cli_Packet_Splitter()
{

}

Cli_Packet_Splitter::~Cli_Packet_Splitter()
{

}

int Cli_Packet_Splitter::split(const char *buf, uint32_t buf_len, uint32_t& cmd, uint32_t& packet_len)
{
	uint32_t head_len = sizeof(TcpMsgHead);
    // 检查是否已经包含头部的长度
    if (buf_len < head_len)
    {
        return 0;
    }

	TcpMsgHead* msg_head = (TcpMsgHead*)buf;
	cmd = ntohl(msg_head->_cmd);
	packet_len = ntohl(msg_head->_data_len);

	if (packet_len < head_len) {
		return -1;
	}

	//超过消息包最大长度
	if (packet_len > MAX_PACKET_LENGTH) {
		return -1;
	}

    if (buf_len < packet_len) { 
        return 0; 
    }

    return 1;
}
