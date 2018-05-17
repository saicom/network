#include "network_pch.h"
#include "net_manager.h"
#include <stdint.h>
#include "log.h"


int main() {
	Net_Manager::CreateInstance();
	Net_Manager::Instance()->create_tcp_server("0.0.0.0", 8888, 0, false);
	while (true) {
		Net_Event* event = nullptr;

		// 处理网络事件
		while ((event = Net_Manager::Instance()->get_event()) != nullptr) {
			if (event->net_event_type == TYPE_ACCEPT) {
				printf("hello world\n");
			}
			else if (event->net_event_type == TYPE_EXCEPTION) {
				printf("hello qq\n");
			}
			else if (event->net_event_type == TYPE_DATA) {
				printf("hello data,%d,%d,%s\n", event->packet.msg_id, event->packet.msg_len, event->packet.msg + 8);
			}
			else if (event->net_event_type == TYPE_CLOSE) {
				printf("hello msn\n");
			}
		}
	}
	return 0;
}
