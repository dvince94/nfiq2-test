using System;
using System.IO;

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

            var score = Nfiq2Invokes.GetNfiq2Score(0, wsqImg, wsqImg.Length, 545, 622, 500);
            Console.WriteLine("The score for sample_image.wsq is " + score);
        }
    }
}
