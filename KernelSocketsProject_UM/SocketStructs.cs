using System.Runtime.InteropServices;

namespace KernelSocketsProject_UM
{
    internal static class SocketStructs
    {
        internal static ulong magic_header_value = 0x427572676572733a;

        // Define the packet structures
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        internal struct PacketHeader
        {
            public ulong magic_header;
            public e_packet_type type;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        internal struct PacketPing
        {
            public int ping_magic;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        internal struct PacketResponse
        {
            public ulong data;
        }

        [StructLayout(LayoutKind.Explicit, Pack = 1)]
        internal struct DataPacket
        {
            [FieldOffset(0)]
            public PacketHeader header;

            [FieldOffset(16)]
            public PacketPing ping;

            [FieldOffset(16)]
            public PacketResponse response;
        }

        // Define the packet types
        internal enum e_packet_type
        {
            ping,
            completed
        }
    }
}
