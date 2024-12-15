#include <iostream>
#include <switch.h>

using namespace std; 

int main() {
    // Inicjalizacja konsoli
    consoleInit(nullptr);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);
    
    
    u64 totalRam = 0;
    u64 usedRam = 0;
    s64 free_space = 0;
    u32 width, height;
    u64 uptime_ticks;
    u32 version = hosversionGet();
    // Get Hos version
    uint8_t major = HOSVER_MAJOR(version);
    uint8_t minor = HOSVER_MINOR(version);
    uint8_t micro = HOSVER_MICRO(version);
    // Get Ram info and assing to function
    svcGetInfo(&totalRam, InfoType_TotalMemorySize, CUR_PROCESS_HANDLE, 0);
    svcGetInfo(&usedRam, InfoType_UsedMemorySize, CUR_PROCESS_HANDLE, 0);
    // Set default window to get dimensions and get them
    NWindow* nw = nwindowGetDefault();
    nwindowGetDimensions(nw, &width, &height);
    // Get system uptime ticks
    uptime_ticks = svcGetSystemTick(); 
    // Get SD free space
    fsFsGetFreeSpace(fsdevGetDeviceFileSystem("sdmc"), "/", &free_space);
    double free_space_gb = (double)free_space / (1024 * 1024 * 1024);  

    // Print info (CPU and GPU are hardcoded and you can change them here)
        cout << "\033[35m" << R"(
   _  __ ____ _      __  ____      __        __ 
  / |/ // __/| | /| / / / __/___  / /_ ____ / / 
 /    /_\ \  | |/ |/ / / _/ / -_)/ __// __// _ \
/_/|_//___/  |__/|__/ /_/   \__/ \__/ \__//_//_/
                                                
)" << '\n' << "\033[0m";
    cout << "------------------------------------------------" << endl;
    cout << "HOS Version: " << (int)major << "." << (int)minor << "." << (int)micro << endl;
    if (hosversionIsAtmosphere()) {
        cout << "Atmosphere is active and loaded!" << endl;
    } else {
        cout << "Atmosphere not loaded, OFW booted." << endl;
    }
    cout << "CPU: ARM 4 Cortex-A57 @ 1,02 GHz" << endl;
    cout << "GPU: Nvidia GM20B" << endl;
    cout << "SBC: Tegra X1" << endl;    
    cout << "Total RAM: " << (totalRam / 1024 / 1024) << " MB" << endl;
    cout << "Used RAM: " << (usedRam / 1024 / 1024) << " MB" << endl;
    cout << "Screen resolution: " << width << "x" << height << endl;
    cout << "Uptime ticks: " << uptime_ticks << endl;
    cout << "SD Card free space: " << free_space_gb << " GB" << endl;
    // Exit code
    cout << "Press + to exit";
    while(appletMainLoop())
    {
        //Scan all the inputs. This should be done once for each frame

        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus) {
		break;
		}
	consoleUpdate(NULL);
    }

    // Quit 
    consoleExit(nullptr);
}
