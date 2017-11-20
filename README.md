# Purpl.
A simple P2P instant messaging client.

# v0.1:
 - C++ socket code that allows multiple clients to connect to a single server, and exchange messages.
 - Terminal application, no GUI.
 - There is a Linux version and a Windows version, mostly becuase I started this project on Linux, but later migrated to windows. I didn't want to delete the Linux code in case I ever needed to refer to it in the future (which I did).
 - The porting process from Linux to Windows mostly involved changing certain function calls and included libraries to make the compiler happy, nothing major. Linux has system calls dedicated to setting up sockets, while sockets in Windows are implemented slightly differently; since sockets are files in Linux, and are not in Windows, there were also certain syntactic elements that can be used to work with sockets in Linux that couldn't be used in Windows (e.g. setting a socket's file descriptor equal to 0 to indicate that it is invalid works in Linux, but Windows requires it to be set to the constant "INVALID_SOCKET", since sockets are not files in Windows).
 - I'll keep the Linux version here (I don't really see a reason to get rid of it) but I probably won't be porting future versions of the application to Linux. I'm going to be focussing on developing it for Windows for the time being.
 - I'll also be trying to document my progress on here in more detail for future versions.
