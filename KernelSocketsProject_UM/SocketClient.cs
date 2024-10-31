using System.Net.Sockets;
using System.Net;
using System.Runtime.InteropServices;

namespace KernelSocketsProject_UM
{
    internal class SocketClient
    {
        Socket Socket { get; set; }

        internal SocketClient() 
        {
            Socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
        }

        internal async Task ConnectAsync(string ip, int port)
        {
            await Socket.ConnectAsync(new IPEndPoint(IPAddress.Parse(ip), port));
        }

        internal void CloseSocket()
        {
            Socket.Close();
        }

        internal async Task SendAsync<T>(T structure, SocketFlags flags)
        {
            byte[] byteArray = Utils.StructureToByteArray(structure);
            await Socket.SendAsync(byteArray, flags);
        }

        internal async Task<T> ReceiveAsync<T>(SocketFlags flags)
        {
            byte[] buffer = new byte[Marshal.SizeOf<T>()];
            await Socket.ReceiveAsync(buffer, flags);
            return Utils.ByteArrayToStructure<T>(buffer);
        }
    }
}
