# Installation Guide

Open the .sln file in Visual Studio 2022. In the top bar, select build, then batch build, and check the release box for your system, probably x64. Then click "Build."

Download the latest [MemProcFS Release](https://github.com/ufrisk/MemProcFS/releases). Install The win_x64 File. Drag and drop these files into the directory containing the exectuable we just built: dbghelp.dll, info, leechcore.dll, leechcore_driver.dll, vcruntime140.dll. This program uses a modified vmm.dll for patching CR3. Drag the vmm.dll that is found in the root folder into the directory containing the executable. 

Download the latest [FTD3XX dlls](https://ftdichip.com/wp-content/uploads/2024/01/FTD3XXLibrary_v1.3.0.9.zip). Go to the FTD3XXLibrary/x64/DLL folder and drag and drop the FTD3XX.dll file into the directory containing the exectutable.

Run the executable.