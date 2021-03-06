﻿using System;
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

        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll")]
        private static extern int DecodeWsq(ref IntPtr decodedWsq, ref int width, ref int height, ref int ppi, byte[] wsq, int wsqSize);
        public static int DecodeWsqByte(ref IntPtr decodedWsq, ref int width, ref int height, ref int ppi, byte[] wsq, int wsqSize)
        {
            return DecodeWsq(ref decodedWsq, ref width, ref height, ref ppi, wsq, wsqSize);
        }

        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll")]
        private static extern int DecodeWsqAndComputeNfiq2Score(int fpos, byte[] pixels, int size, int width, int height, int ppi);
        public static int DecodeWsqAndGetNfiq2Score(int fpos, byte[] pixels, int size, int width, int height, int ppi)
        {
            return DecodeWsqAndComputeNfiq2Score(fpos, pixels, size, width, height, ppi);
        }

        [DllImport(@"..\..\..\..\..\Binaries\Nfiq2Api.dll", CharSet = CharSet.Ansi)]
        private static extern int EncodeWsq(ref IntPtr encodedWsq, ref int encodedWsqSize, float bitrate, byte[] wsq, int width, int height, int depth, int ppi, string comment_txt);
        public static int EncodeWsqByte(ref IntPtr encodedWsq, ref int encodedWsqSize, float bitrate, byte[] wsq, int width, int height, int depth, int ppi, string comment_txt)
        {
            return EncodeWsq(ref encodedWsq, ref encodedWsqSize, bitrate, wsq, width, height, depth, ppi, comment_txt);
        }
    }
}
