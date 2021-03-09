// CPlusPlusNfiqTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nfiq2api.h>
#include <WSQ_library64.h>
#include <wingdi.h>
#include "data.h"
extern "C" {
    #include <wsq.h>
    int biomeval_nbis_debug = 0; /* Required by libwsq */
}

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    std::cout << InitNfiq2() << "\n";
    string fileName = "D:\\Downloads\\sample_image.wsq";
    string pngFile = "D:\\Downloads\\Sample-fingerprinti.png";

    //open file
    ifstream infile(fileName.c_str(), std::ios::binary | std::ios::in);

    if (infile)
    {
        //get length of file
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0);

        vector<unsigned char> mBuffer;
        mBuffer.resize(length);
        infile.read((char*)(&mBuffer[0]), length);
        cout << " size=" << mBuffer.size() << endl;

        // Decode stream using cognaxon
        int width = 545;
        int height = 622;
        int ppi = 500;
        int* wd = &width;
        int* ht = &height;
        int* dpi = &ppi;
        int size = width * height;
        unsigned char* outBuffer = new unsigned char[size]();
        unsigned char* cmt = NULL;
        WSQ_decode_stream(mBuffer.data(), length, &outBuffer, wd, ht, dpi, &cmt);
        int score = ComputeNfiq2Score(6, outBuffer, size, width, height, 500);
        std::cout << "Cognaxon Decode score: " << score << "\n";

        //Decode stream using Nist nbis libbiomeval
        int depth = 8;
        int* dp = &depth;
        int lossyflag = 1;
        int* lf = &lossyflag;
        unsigned char* oData = new unsigned char[size]();
        const int len = length;
        int test = biomeval_nbis_wsq_decode_mem(&oData, wd, ht, dp, dpi, lf, mBuffer.data(), len);
        int score2 = ComputeNfiq2Score(6, oData, size, width, height, 500); 
        std::cout << "NBIS Decode score: " << score2 << "\n";

        unsigned char* o2Data = new unsigned char[size]();
        int test2 = DecodeWsq(&o2Data, wd, ht, dpi, mBuffer.data(), len);
        //int test2 = (&oData, wd, ht, dp, dpi, lf, mBuffer.data(), len);
        int score3 = ComputeNfiq2Score(6, o2Data, size, width, height, 500);
        std::cout << "Edited Decode score: " << score3 << "\n";

        int score4 = DecodeWsqAndComputeNfiq2Score(6, mBuffer.data(), length, width, height, 500);
        std::cout << "Combined decode and compute score: " << score4 << "\n";
        infile.close();
    }

    //open file
    ifstream pngStream(pngFile.c_str(), std::ios::binary | std::ios::in);

    if (pngStream)
    {
        //Get bytes
        //get length of file
        pngStream.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        pngStream.seekg(0);

        vector<unsigned char> mBuffer;
        mBuffer.resize(length);
        pngStream.read((char*)(&mBuffer[0]), length);
        cout << " size=" << mBuffer.size() << endl;

        //Encode byte
        int width = 361;
        int height = 344;
        int ppi = 500;
        int* wd = &width;
        int* ht = &height;
        int* dpi = &ppi;
        int depth = 8;
        int* dp = &depth;
        unsigned char* oData = new unsigned char[length]();
        int olength = 0;
        int* olen = &olength;


        pngStream.close();
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:   
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
