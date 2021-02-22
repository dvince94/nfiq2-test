#include "data.h"

#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

Data::Data()
{
}

Data::Data(const uint8_t* pData, uint32_t dataSize)
    : std::basic_string<uint8_t>(pData, dataSize)
{
}

Data::Data(const Data& otherData)
    : std::basic_string<uint8_t>(otherData)
{
}

Data::Data(const std::basic_string<uint8_t>& otherData)
    : std::basic_string<uint8_t>(otherData)
{
}

Data::~Data()
{
}

bool Data::readFromFile(const std::string& filename)
{
    bool success = false;
    if (!filename.empty()) {
        unsigned long len;
        unsigned char* pBuffer;
        std::ifstream f;
        f.open(filename.c_str(), std::ios::binary | std::ios::in);
        if (f.is_open()) {
            // detecting size
            f.seekg(0, std::ios::end);
            len = (unsigned long)f.tellg();
            f.seekg(0, std::ios::beg);
            if (len > 0) {
                pBuffer = new unsigned char[len];
                f.read((char*)pBuffer, len);
                this->assign(pBuffer, len);
                delete[] pBuffer;
                success = !f.fail(); // failbit is set if read
                             // was incomplete or failed
                f.close();
            }
            else {
                // must be zero since type is unsigned
                this->clear();
                // empty file is no error
                success = true;
            }
        }
    }
    return success;
}