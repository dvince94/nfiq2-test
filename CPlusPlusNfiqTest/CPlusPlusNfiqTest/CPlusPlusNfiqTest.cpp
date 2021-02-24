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

using namespace std;

int main()
{
    std::cout << "Hello World!\n";
    std::cout << InitNfiq2() << "\n";
    string fileName = "D:\\Downloads\\sample_image.wsq";

    //open file
    ifstream infile(fileName.c_str(), std::ios::binary | std::ios::in);

    if (infile)
    {
        // copies all data into buffer
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(infile), {});

        //get length of file
        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0);

        vector<unsigned char> mBuffer;
        mBuffer.resize(length);
        infile.read((char*)(&mBuffer[0]), length);
        cout << " size=" << mBuffer.size() << endl;


        //HBITMAP wsqImage = CreateBMPFromFile("D:\\Downloads\\sample_image.wsq");
        //BITMAP bitmap;
        //unsigned char* test = (unsigned char*)malloc(length);
        //GetObject(wsqImage, sizeof(bitmap), (LPVOID)&bitmap);
        //GetBitmapBits(wsqImage, sizeof(test), (LPVOID)&test);

        //uint8_t* val = (uint8_t*)test;
        //unsigned char val2[23717];
        //copy(mBuffer.begin(), mBuffer.end(), val2);
        //Data data = Data(val2, length);

        // Decode stream
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
        std::cout << "score: " << score << "\n";
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
