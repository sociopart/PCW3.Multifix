#include <Windows.h>
#include <process.h>
#define WIN32_LEAN_AND_MEAN 
#pragma warning(disable : 4996)
#define memcpy CRTmemcpy

extern "C" int _fltused = 0;

void * CRTmemcpy (void *dst, const void *src, size_t count)
{
   void * ret = dst;
        while (count--) {
                *(char *)dst = *(char *)src;
                dst = (char *)dst + 1;
                src = (char *)src + 1;
        }
        return(ret);
}
template <class T, class U>
void WriteMemory(U ptr, const T value, bool isProtected)
{
    if (*(T*)ptr != value) {
		if (!isProtected) memcpy((void*)ptr, &value, sizeof(T));
        else{
				DWORD		dwProtect[2];
				VirtualProtect((void*)ptr, sizeof(T), PAGE_EXECUTE_READWRITE, &dwProtect[0]);
				memcpy((void*)ptr, &value, sizeof(T));
				VirtualProtect((void*)ptr, sizeof(T), dwProtect[0], &dwProtect[1]);
			}
	}		
}
inline void MemcpyProtected(void* address, char * arrayOfBytes, size_t size)
{
    DWORD		dwProtect[2];
    VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &dwProtect[0]);
    memcpy(address, arrayOfBytes, size);
    VirtualProtect((void*)address, size, dwProtect[0], &dwProtect[1]);
}
void LoadPlugin(){

	float OrigAspectRatio = 4/3;
	float xscale = (1.0/1920.0) * (OrigAspectRatio + 3.2f + 0.2f); // 0.001557407319
	float yscale = 0.002083333442f + 0.0002f; //0.002483333461
	WriteMemory<float>(0x007339E0, 0.001557407319f, TRUE); //xscale - 0.001157407416f
	WriteMemory<float>(0x007339E4, 0.002483333461f, TRUE); //yscale - 0.002057613106
	WriteMemory<float>(0x00F56954, -2000.0f, TRUE); //galaxian_xpos mov [esi+18],c4870000; default = -930.0
	WriteMemory<float>(0x0047DF43, 200.0f, TRUE);


}
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  reasonForCall, LPVOID lpReserved)
{
	if ( reasonForCall == DLL_PROCESS_ATTACH )
	{
		LoadPlugin();
	}
    return TRUE;
}
