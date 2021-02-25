using System;
using System.IO;
using System.Runtime.InteropServices;

namespace TestNfiqApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            var path = "Assets\\sample_image.wsq";

            //Adds a random pause and press enter
            //Console.WriteLine("Enter anything:");
            //string userName = Console.ReadLine();

            //var wsqImg = File.ReadAllBytes(path);
            var fs = File.OpenRead(path);
            var wsqImg = new byte[fs.Length];
            fs.Read(wsqImg, 0, wsqImg.Length);

            Console.WriteLine("Is initialized: " + Nfiq2Invokes.InitializeNfiq2());
            Console.WriteLine(Nfiq2Invokes.Nfiq2Version());
            int wd = 545;
            int ht = 622;
            int ppi = 500;
            IntPtr decodedWsq = IntPtr.Zero;
            var decodedByte = Nfiq2Invokes.DecodeWsqByte(ref decodedWsq, ref wd, ref ht, ref ppi, wsqImg, wsqImg.Length);
            var rawSize = wd * ht;
            byte[] b = new byte[rawSize];
            Marshal.Copy(decodedWsq, b, 0, rawSize);

            var score = Nfiq2Invokes.GetNfiq2Score(6, b, b.Length, 545, 622, 500);
            Console.WriteLine("The score for sample_image.wsq is " + score);

            var score2 = Nfiq2Invokes.DecodeWsqAndGetNfiq2Score(6, wsqImg, wsqImg.Length, 545, 622, 500);
            Console.WriteLine("The score for sample_image.wsq using DecodeWsqAndGetNfiq2Score is " + score2);
        }
    }
}
