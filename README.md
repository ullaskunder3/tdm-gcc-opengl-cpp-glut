# C++ OpenGL (FreeGLUT) Development on Windows with VS Code and TDM-GCC

This guide will help you set up a modern, portable C++ OpenGL development environment using [FreeGLUT](http://freeglut.sourceforge.net/), [TDM-GCC](https://jmeubank.github.io/tdm-gcc/), and [Visual Studio Code](https://code.visualstudio.com/) on Windows.

## Table of Contents

- [Prerequisites](#prerequisites)
- [FreeGLUT Installation](#freeglut-installation)
- [Project Structure](#project-structure)
- [VS Code Configuration](#vs-code-configuration)
  - [c_cpp_properties.json](#c_cpp_propertiesjson)
  - [tasks.json](#tasksjson)
- [Building and Running](#building-and-running)
- [Sample Code](#sample-code)
- [Troubleshooting](#troubleshooting)
- [References](#references)

---

## 📸 Preview

| Screenshot                                                                                                       | Demo                                                                                            |
| ---------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------- |
| ![Screenshot 2025-05-18 202433](https://github.com/user-attachments/assets/766bc417-3882-49b2-bbe2-3b3a3210b152) | ![opengl-demo](https://github.com/user-attachments/assets/e256b931-8033-4df9-84ea-64b98cf27d9a) |

---

## Prerequisites

- **TDM-GCC** (or MinGW-w64) installed (64-bit recommended)
- **Visual Studio Code** installed
- **C/C++ extension** for VS Code (by Microsoft)
- **FreeGLUT MinGW package** ([Download here](https://www.transmissionzero.co.uk/software/freeglut-devel/))

## FreeGLUT Installation

1. **Download** the latest FreeGLUT MinGW package from [TransmissionZero](https://www.transmissionzero.co.uk/software/freeglut-devel/).

2. **Extract** the ZIP archive.

3. **Copy header files:**

   - From:  
     `freeglut\include\GL\*`
   - To:  
     `C:\TDM-GCC-64\include\GL\`
   - Files to copy:
     - `freeglut.h`
     - `freeglut_ext.h`
     - `freeglut_std.h`
     - `glut.h`

4. **Copy library files:**

   - From:  
     `freeglut\lib\x64\libfreeglut.a`
   - To:  
     `C:\TDM-GCC-64\lib\`

5. **Copy DLL file:**
   - From:  
     `freeglut\bin\x64\freeglut.dll`
   - To:  
     `C:\TDM-GCC-64\bin\`
   - **Do NOT** copy to `C:\Windows\System32\` unless you want it globally available (not recommended).

## Project Structure

```
your-project/
├── .vscode/
│   ├── c_cpp_properties.json
│   └── tasks.json
├── build/
├── src/
│   └── main.cpp
└── README.md
```

## VS Code Configuration

### `.vscode/c_cpp_properties.json`

```json
{
  "version": 4,
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "${workspaceFolder}/src",
        "C:/TDM-GCC-64/include",
        "C:/TDM-GCC-64/include/c++/10.3.0",
        "C:/TDM-GCC-64/include/c++/10.3.0/x86_64-w64-mingw32",
        "C:/TDM-GCC-64/x86_64-w64-mingw32/include",
        "C:/TDM-GCC-64/include/GL"
      ],
      "defines": ["_DEBUG", "UNICODE", "_UNICODE"],
      "compilerPath": "C:/TDM-GCC-64/bin/g++.exe",
      "cStandard": "c17",
      "cppStandard": "gnu++14",
      "intelliSenseMode": "windows-gcc-x64"
    }
  ]
}
```

### `.vscode/tasks.json`

This setup allows you to:

- Build the currently open C++ file (`${file}`)
- Output the executable to `build/`
- Automatically run the executable after building

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Active C++ File (FreeGLUT)",
      "type": "shell",
      "command": "g++",
      "args": [
        "${file}",
        "-IC:/TDM-GCC-64/include",
        "-LC:/TDM-GCC-64/lib",
        "-lfreeglut",
        "-lopengl32",
        "-lglu32",
        "-o",
        "${workspaceFolder}/build/${fileBasenameNoExtension}.exe"
      ],
      "group": "build",
      "problemMatcher": ["$gcc"]
    },
    {
      "label": "Run Executable",
      "type": "shell",
      "command": "${workspaceFolder}/build/${fileBasenameNoExtension}.exe",
      "dependsOn": "Build Active C++ File (FreeGLUT)",
      "group": "test",
      "presentation": {
        "echo": true,
        "reveal": "always",
        "focus": true,
        "panel": "new"
      }
    },
    {
      "label": "Build and Run",
      "dependsOn": ["Build Active C++ File (FreeGLUT)", "Run Executable"],
      "dependsOrder": "sequence",
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

## Building and Running

- **To build and run:**  
  Press `Ctrl+Shift+P` → "Tasks: Run Task" → select **Build and Run**.

- **To build only:**  
  Press `Ctrl+Shift+B` (default build task).

- The output executable will appear in the `build/` folder.

## Sample Code

Try this minimal FreeGLUT test:

```cpp
#include

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("FreeGLUT Test");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

Compile with:

```sh
g++ -o test.exe test.cpp -lfreeglut -lopengl32
```

If you see a window pop up, your setup is working!

## Troubleshooting

- **No window appears:**  
  Ensure `freeglut.dll` is in `C:\TDM-GCC-64\bin` or the same folder as your `.exe`.

- **Header not found:**  
  Check that all header files are in `C:\TDM-GCC-64\include\GL\`.

- **Linker errors:**  
  Ensure `libfreeglut.a` is in `C:\TDM-GCC-64\lib\` and you are linking with `-lfreeglut -lopengl32 -lglu32`.

- **IntelliSense not working:**  
  Check your `c_cpp_properties.json` paths.

## References

- [FreeGLUT for Windows (TransmissionZero)](https://www.transmissionzero.co.uk/software/freeglut-devel/)
- [TDM-GCC Compiler](https://jmeubank.github.io/tdm-gcc/)
- [OpenGL/GLUT Programming Guide](https://www.opengl.org/resources/libraries/glut/)
- [VS Code C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

---

**Happy Coding!**  
If you run into any issues, double-check your paths and library files, or ask for help!

- I added GLFW aslo similar way include to include, lib to lib, and dll to bin
