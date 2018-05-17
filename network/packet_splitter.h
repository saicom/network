//! @file packet_splitter.h
#pragma once



//! @class Packet_Splitter
//! @brief tcp拆包接口
class Packet_Splitter
{
public:
    Packet_Splitter();
	virtual ~Packet_Splitter();

	//! 拆包
	//! @param buf 数据缓存
	//! @param buf_len 数据长度
	//! @param cmd 返回参数 消息id
	//! @param packet_len 返回参数 包长度
	//! @return -1:数据格式错误, 0:缓存中没有完整包, 1:得到一个包
	virtual int split(const char *buf, uint32_t buf_len, uint32_t& cmd, uint32_t& packet_len) = 0;

	//! 返回消息头的长度
	virtual int head_size() = 0;
};

