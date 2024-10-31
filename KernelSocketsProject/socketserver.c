#include "includes.h"

SOCKET CreateSocketServer(uint16_t port)
{
	SOCKADDR_IN address;

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(server_ip);
	address.sin_port = htons(port);

	SOCKET sockfd = socket_listen(AF_INET, SOCK_STREAM, 0);
	if (sockfd == INVALID_SOCKET)
	{
		DebugLog("Couldn't create a valid server socket.");

		return INVALID_SOCKET;
	}

	if (bind(sockfd, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		DebugLog("Couldn't bind to the server socket.");
		DebugLog("Have bound to the socket in another instance?");

		closesocket(sockfd);
		return INVALID_SOCKET;
	}

	if (listen(sockfd, 10) == SOCKET_ERROR)
	{
		DebugLog("Couldn't start listening in on the server socket.");

		closesocket(sockfd);
		return INVALID_SOCKET;
	}

	return sockfd;
}

void InitializeSocketServer(uint16_t port)
{
	NTSTATUS status = KsInitialize();

	if (!NT_SUCCESS(status))
	{
		DebugLog("Couldn't to initialize KSOCKET.");

		return;
	}

	SOCKET server_socket = CreateSocketServer(port);

	if (server_socket == INVALID_SOCKET)
	{
		DebugLog("Couldn't to initialize the server socket.");

		KsDestroy();
		return;
	}

	DebugLog("Listening on PORT: %d", port);

	while (TRUE)
	{
		struct sockaddr socket_addr;
		socklen_t socket_length;

		SOCKET client_connection = accept(server_socket, &socket_addr, &socket_length);

		if (client_connection == INVALID_SOCKET)
		{
			DebugLog("Couldn't accept client connection (%d)", port);
		}
		else
		{
			HANDLE thread_handle;
			PsCreateSystemThread(&thread_handle, THREAD_ALL_ACCESS, 0, 0, 0, ServerThread, &client_connection);
		}
	}

	closesocket(server_socket);
}

uint64_t HandlePing(data_packet_t packet)
{
	DebugLog("Received ping packet! %d", packet.data.ping.ping_magic);

	return packet.data.ping.ping_magic + 1;
}

uint64_t HandlePacket(data_packet_t packet)
{
	uint64_t result = 0ull;

	switch (packet.header.type)
	{
	case ping:
		result = HandlePing(packet);
		break;

	default:
		DebugLog("Unknown Packet");
		break;
	}

	return result;
}

bool AnswerClient(SOCKET sockfd, uint64_t result)
{
	data_packet_t packet;
	packet.header.magic_header = magic_header_value;
	packet.header.type = completed;
	packet.data.response.data = result;

	return send(sockfd, &packet, sizeof(packet), 0) != SOCKET_ERROR;
}

void ServerThread(SOCKET* sockfd)
{
	DebugLog("Connection received, server thread spawned.");

	SOCKET connection = *sockfd;

	data_packet_t packet;

	while (TRUE)
	{
		int result = recv(connection, (void*)&packet, sizeof(packet), 0);

		if (result > 0 && result >= sizeof(packet.header) && packet.header.magic_header == magic_header_value)
		{
			uint64_t packet_result = HandlePacket(packet);

			if (!AnswerClient(connection, packet_result))
			{
				break;
			}
		}
	}

	DebugLog("A server thread has terminated...");
}