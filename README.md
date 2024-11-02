# Kernel Sockets with C#

## Description
This project demonstrates communication with a manually mapped Kernel Driver using WinSock to make a socket server, and a C# User Mode program talking with it using the standard .NET `System.Net.Sockets` namespace. The aim is to perform various tasks through this interaction.

Whats the point to make the UM in C# compared to C++?
This was for a school project to see if it was possible to make it work.
[I have earlier worked with C++ UM <-> C KM using IOCTL as communication](https://github.com/mbn-code/The-Kernel-Driver-Guide-External), but wanted to explore other means of communication.

## Features
- Communicate with a kernel driver using sockets with a UM in C#
- Perform various tasks through kernel-level operations
- Written in C and C#

## Requirements
- Windows 
- Visual Studio 2022
- Some way to manual map the driver, I use [kdmapper](https://github.com/TheCruZ/kdmapper)

## Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/OssieFromDK/kernel_sockets_csharp.git
   ```
2. Open the solution file with VS22
3. Build the projects to compile the driver and the C# UM

## Usage
1. Map the driver using something like [kdmapper](https://github.com/TheCruZ/kdmapper)
2. Open the C# UM App

## Contributing
Feel free to open issues and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License.

## External Resources
Big thanks to [wbenny](https://github.com/wbenny) for his [KSOCKET](https://github.com/wbenny/ksocket) examples and code, as this was used in this project to make the Socket Server in KM
