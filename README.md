# addtopath
Adds the first argument to USER PATH environment variable without truncating it like setx. 

This program only works on windows.

# Usage
```
> addtopath <path-to-directory>
```

# Example
```
> addtopath .\bin
Added Directory to path
```

# Building
Building with gcc:
```
gcc main.c -o addtopath.exe
```
Building with clang:
```
clang main.c -o addtopath.exe
```
Building with MSVC:
```
cl main.c /Fe:addtopath.exe
```
Building with Zig:
```
zig cc main.c -o main.exe
```
For contributions make sure that the source compiles with no errors or warnings and use the following compiler flags: Example clang:
```

```
