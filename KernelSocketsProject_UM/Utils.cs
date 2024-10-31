using System.Runtime.InteropServices;

namespace KernelSocketsProject_UM
{
    internal static class Utils
    {
        internal static byte[] StructureToByteArray<T>(T structure)
        {
            int size = Marshal.SizeOf(structure);
            byte[] byteArray = new byte[size];
            IntPtr ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(structure, ptr, true);
            Marshal.Copy(ptr, byteArray, 0, size);
            Marshal.FreeHGlobal(ptr);
            return byteArray;
        }

        internal static T ByteArrayToStructure<T>(byte[] byteArray)
        {
            IntPtr ptr = Marshal.AllocHGlobal(byteArray.Length);
            Marshal.Copy(byteArray, 0, ptr, byteArray.Length);
            T structure = Marshal.PtrToStructure<T>(ptr);
            Marshal.FreeHGlobal(ptr);
            return structure;
        }
    }
}
