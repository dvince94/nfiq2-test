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
            var pngPath = "Assets\\Sample-fingerprinti.png";

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

            //Decode png 
            //Stream pngImage = new FileStream(pngPath, FileMode.Open, FileAccess.Read, FileShare.Read);
            //PngBitmapDecoder decoder = new PngBitmapDecoder(pngImage, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
            //BitmapSource bitmapSource = decoder.Frames[0];

            var ps = File.OpenRead(pngPath);
            var pngImg = new byte[ps.Length];
            ps.Read(pngImg, 0, pngImg.Length);
            int pW = 361;
            int pH = 344;
            int pD = 8;
            int pDpi = 500;
            int oSize = 0;
            IntPtr encodedWsq = IntPtr.Zero;
            var encodedByte = Nfiq2Invokes.EncodeWsqByte(ref encodedWsq, ref oSize, 2.75f, pngImg, pW, pH, pD, pDpi, string.Empty);
            Console.WriteLine("Encoded Bytes");
        }
    }
}
