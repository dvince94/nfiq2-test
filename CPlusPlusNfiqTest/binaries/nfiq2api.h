#ifdef _WIN32
#include <windows.h>
#define DLLEXPORT __declspec(dllexport)
#define STDCALL __stdcall
#else
#define DLLEXPORT __attribute__((visibility("default")))
#define STDCALL
#endif

#ifdef _MSC_VER
#define __attribute__(X)
#endif

extern "C" DLLEXPORT void STDCALL GetNfiq2Version(
    int *major, int *minor, int *patch, const char **ocv);
extern "C" DLLEXPORT const char *STDCALL InitNfiq2();
extern "C" DLLEXPORT int STDCALL ComputeNfiq2Score(int fpos,
    const unsigned char *pixels, int size, int width, int height, int ppi);
extern "C" DLLEXPORT int STDCALL DecodeWsq(unsigned char **odata, int *ow, int *oh, int *oppi,
    unsigned char *idata, const int ilen);
extern "C" DLLEXPORT int STDCALL DecodeWsqAndComputeNfiq2Score(int fpos,
    unsigned char *pixels, int size, int width, int height, int ppi);
