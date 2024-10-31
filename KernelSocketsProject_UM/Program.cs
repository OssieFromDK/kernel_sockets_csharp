using System.Net.Sockets;

namespace KernelSocketsProject_UM
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            SocketClient socketClient = new SocketClient();
            await socketClient.ConnectAsync("127.0.0.1", 9095); // Connect to the server

            Console.WriteLine("Connected to the server. Sending ping packet...");

            // Construct a packet
            var pingPacket = new SocketStructs.DataPacket
            {
                header = new SocketStructs.PacketHeader
                {
                    magic_header = SocketStructs.magic_header_value,
                    type = SocketStructs.e_packet_type.ping
                },
                ping = new SocketStructs.PacketPing
                {
                    ping_magic = 12345
                }
            };

            await socketClient.SendAsync(pingPacket, SocketFlags.None);

            // Receive the response
            var responsePacket = await socketClient.ReceiveAsync<SocketStructs.DataPacket>(SocketFlags.None);

            if (responsePacket.header.magic_header != SocketStructs.magic_header_value)
            {
                Console.WriteLine("Invalid magic header value received.");
                return;
            }

            switch (responsePacket.header.type)
            {
                case SocketStructs.e_packet_type.ping:
                    Console.WriteLine($"Received ping response: {responsePacket.ping.ping_magic}");
                    break;
                case SocketStructs.e_packet_type.completed:
                    Console.WriteLine($"Received completed response: {responsePacket.response.data}");
                    break;
                default:
                    Console.WriteLine("Unknown packet type received.");
                    break;
            }

            Console.ReadLine();
        }
    }
}
