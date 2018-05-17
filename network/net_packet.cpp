#include "network_pch.h"
#include "net_packet.h"
#include "hex_string.h"
#include "log.h"


#define BS_MAKE64(lo, hi) ((uint64_t)((uint64_t)(lo) | (((uint64_t)(hi)) << 32)))
#define BS_LO32(x)  ((uint32_t)((x) & 0x00000000ffffffffULL))
#define BS_HI32(x)  ((uint32_t)(((x) & 0xffffffff00000000ULL) >> 32))



Net_Packet::Net_Packet()
	:id(0),
	cur_len(0),
	msg_len(0),
	msg_id(0)
{
	memset(msg, 0, MAX_PACKET_LENGTH);
}


Net_Packet::~Net_Packet()
{
}

void Net_Packet::write_data(const char* buf, uint32_t len) {
	memcpy(msg, buf, len);
	cur_len += len;
}


uint32_t Net_Packet::get_left_write_len() {
	return msg_len - cur_len;
}

char* Net_Packet::get_rptr() {
	return msg + cur_len;
}

void Net_Packet::read_data(uint32_t len) {
	cur_len -= len;
}

IMPLEMENT_ALLOCATOR(Net_Packet)



