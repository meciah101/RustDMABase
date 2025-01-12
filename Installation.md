# Installation Guide

Open the .sln file in Visual Studio 2022. In the top bar, select build, then batch build, and check the release box for your system, x64 or x86. Then click "Build."

Download the latest [MemProcFS Release](https://github.com/ufrisk/MemProcFS/releases). Install The win_x64 File. Drag and drop the contents into the build directory. 

Download the latest [FTD3xx Dlls](https://ftdichip.com/wp-content/uploads/2024/01/FTD3XXLibrary_v1.3.0.9.zip) Go to the FTD3XXLibrary/x64/DLL folder and drag and drop the contents into the build directory.

Install [Python 3.8](https://www.python.org/ftp/python/3.8.0/python-3.8.0-amd64.exe). Locate your install directory (likely: AppData\Local\Programs\Python\Python38). Use Windows search to locate "Edit the system environment variables." Go to Advanced, Environment Variables, and under System variables click new. 

Variable name:
```
PythonPath
```
Variable value (assuming your install directory is the same as what I noted before):
```
C:\Users\(YOUR USER HERE)\AppData\Local\Programs\Python\Python38;C:\Users\(YOUR USER HERE)\AppData\Local\Programs\Python\Python38\Scripts
```

Click OK, and Apply.