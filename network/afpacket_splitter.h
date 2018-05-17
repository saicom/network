//! @file afpacket_splitter.h
#pragma once


#include "packet_splitter.h"

#define START_CHECK_CODE 0x4744     ///< "DG"
#define END_CHECK_CODE 0x4641       ///< "AF"

#pragma pack(1)
/// @brief 对tcp传输数据增加消息头
struct TcpMsgHead {
	TcpMsgHead() : _cmd(0), _data_len(0) {}
	uint32_t _cmd;
	uint32_t _data_len;
};
#pragma pack()

//! @class Packet_Splitter
//! @brief tcp拆包接口
class AfPacket_Splitter : public Packet_Splitter
{
public:
    AfPacket_Splitter();

    virtual ~AfPacket_Splitter();

    //! 拆包
    //! @param buf 数据缓存
    //! @param buf_len 数据长度
    //! @param cmd 返回参数 消息id
    //! @param packet_len 返回参数 包长度
    //! @return -1:数据格式错误, 0:缓存中没有完整包, 1:得到一个包
    virtual int split(const char *buf, uint32_t buf_len, uint32_t& cmd, uint32_t& packet_len);

	//! 返回消息头的长度
	virtual int head_size() {
		return sizeof(TcpMsgHead);
	}
};

