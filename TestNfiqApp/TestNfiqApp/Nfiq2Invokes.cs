using System;
using System.Runtime.InteropServices;

namespace TestNfiqApp
{
    public class Nfiq2Invokes
    {
        //Imports
        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll", CharSet=CharSet.Ansi)]
        private static extern void GetNfiq2Version(ref int major, ref int minor, ref int patch, ref IntPtr ovcPtr);
        public static string Nfiq2Version()
        {
            int major = 0, minor = 0, patch = 0;
            IntPtr ovcPtr = IntPtr.Zero;
            string ocv = "";
            GetNfiq2Version(ref major, ref minor, ref patch, ref ovcPtr);

            if (ovcPtr != IntPtr.Zero)
                ocv = Marshal.PtrToStringAnsi(ovcPtr);
            return string.Format("Major: {0}, Minor: {1}, Patch: {2}, OpenCV: {3}", major, minor, patch, ocv);
        }

        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll")]
        private static extern IntPtr InitNfiq2(); //Returns a hash value, but don't really need to know it
        public static bool InitializeNfiq2()
        {
            var intPtr = InitNfiq2();
            return intPtr != IntPtr.Zero;
        }

        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll")]
        private static extern int ComputeNfiq2Score(int fpos, byte[] pixels, int size, int width, int height, int ppi);
        public static int GetNfiq2Score(int fpos, byte[] pixels, int size, int width, int height, int ppi)
        {
            return ComputeNfiq2Score(fpos, pixels, size, width, height, ppi);
        }
    }
}
