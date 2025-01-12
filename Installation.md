# Installation Guide

Open the .sln file in Visual Studio 2022. In the top bar, select build, then batch build, and check the release box for your system, x64 or x86. Then click "Build."

Download the latest [MemProcFS Release](https://github.com/ufrisk/MemProcFS/releases). Install The win_x64 File. Drag and drop these files into the directory containing the exectuable we just built: dbghelp.dll, info, leechcore.dll, leechcore_driver.dll, vcruntime140.dll, vmm.dll. 

Download the latest [FTD3xx Dlls](https://ftdichip.com/wp-content/uploads/2024/01/FTD3XXLibrary_v1.3.0.9.zip) Go to the FTD3XXLibrary/x64/DLL folder and drag and drop the FTD3XX.dll file into the directory containing the exectutable.

Run the executable.