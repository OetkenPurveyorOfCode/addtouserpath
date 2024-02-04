<div id="addtopath-logo" align="center">
    <br />
    <img src="./logos/addtopath.svg" alt="AddToPath Logo" width="200"/>
    <h1>Add To Path</h1>
    <h3>Adds the first argument to USER PATH environment variable without truncating it like setx.</h3>
</div>

> [!NOTE]  
> This program only works on windows.

# Why does this exist

The default `setx` programme truncated my environment variable without my permission. It gave no prior indication that it would do that. Bad `setx`!

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
Or use your own Docker-ised Cmake remote build generator Meta-Meta-Build-System compiling to autotools with Perl-orchestrated Perforce Jamfiles cross-compiled to Meson.

# Contributing
For contributions make sure that the source compiles with no errors or warnings and use the following compiler flags: Example clang:
```
clang -D_CRT_SECURE_NO_WARNINGS -Wno-newline-eof -Wall -Wextra 
-Wshadow -Wconversion -pedantic -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wimplicit-fall
through -fsanitize=address -fsanitize=undefined main.c -o main.exe
```

# License:

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
