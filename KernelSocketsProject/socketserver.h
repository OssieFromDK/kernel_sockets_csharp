#pragma once
#define magic_header_value 0x427572676572733a // random value
#define server_ip 0x7F000001 // https://www.browserling.com/tools/ip-to-hex

enum e_packet_type
{
	ping,
	completed
};


typedef struct _packet_header_t
{
	uint64_t magic_header;
	int type;
} packet_header_t, * lpacket_header_t;

typedef struct _packet_response_t
{
	uint64_t data;
} packet_response_t, * lpacket_response_t;

typedef struct _packet_ping_t
{
	int32_t ping_magic;
} packet_ping_t, * lpacket_ping_t;

typedef struct _data_packet_t
{
	packet_header_t header;
	union
	{
		packet_response_t response;
		packet_ping_t ping;
	} data;
} data_packet_t, * lpdata_packet_t;


SOCKET CreateSocketServer(uint16_t port);
void InitializeSocketServer(uint16_t port);
uint64_t HandlePing(data_packet_t packet);
uint64_t HandlePacket(data_packet_t packet);
bool AnswerClient(SOCKET sockfd, uint64_t result);
void ServerThread(SOCKET* sockfd);