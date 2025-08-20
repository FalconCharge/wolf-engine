Setting up and Running with vcpkg

This guide will help you set up vcpkg for dependency management in your project using manifest mode.
1. Clone the vcpkg Repository

Clone the official vcpkg repository anywhere on your machine:

git clone https://github.com/microsoft/vcpkg.git

2. Bootstrap vcpkg

Navigate into the cloned directory and run the bootstrap script to build the vcpkg executable:

    On Windows (PowerShell):

.\bootstrap-vcpkg.bat

3. Find the Commit ID (builtin-baseline)

To enable manifest mode, you need the commit ID (a long string of letters and numbers) that corresponds to your current vcpkg version.

Run this command inside the vcpkg directory to get the latest commit hash:

git rev-parse HEAD

Copy the output string — this is your builtin-baseline.
4. Update your vcpkg.json Manifest

In your project’s vcpkg.json file, add or update the "builtin-baseline" field with the commit ID you copied:

{
  "name": "your-project-name",
  "version": "0.1.0",
  "dependencies": [
    "glm",
    "glfw3",
    "assimp",
    "glew",
    "imgui",
    "yaml-cpp"
  ],
  "builtin-baseline": "your-commit-id-here"
}

5. Configure VSCode to Use Manifest Mode

Create a CMakePresets.json file in your project root to tell VSCode and CMake to use the vcpkg toolchain with manifest mode:

{
  "version": 3,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 21,
    "patch": 1
  },
  "configurePresets": [
    {
      "name": "vcpkg-manifest",
      "displayName": "Configure with vcpkg manifest mode",
      "generator": "Ninja",
      "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": "<path-to-your-vcpkg-root>/scripts/buildsystems/vcpkg.cmake"
      }
    }
  ]
}

    Note: Replace <path-to-your-vcpkg-root> with the absolute or relative path to where you cloned the vcpkg repo.

6. Build Your Project in VSCode

    Open the Command Palette (Ctrl+Shift+P)

    Select CMake: Select Configure Preset

    Choose Configure with vcpkg manifest mode

    Run CMake: Configure and then CMake: Build

Now your project will automatically use the dependencies listed in vcpkg.json via manifest mode.
Summary

    Clone and bootstrap vcpkg

    Get the commit hash for manifest baseline

    Set "builtin-baseline" in vcpkg.json

    Create CMakePresets.json pointing to vcpkg toolchain

    Use VSCode CMake presets to configure and build

Everything should now build smoothly with vcpkg managing your dependencies!

Troubleshooting

If things aren’t working properly:

    In your CMakeLists.txt, try adding a debug line to check if the variable CMAKE_TOOLCHAIN_FILE is set:

    message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")

    If this variable is empty, likely the CMake preset is not being used correctly.

    How to fix:
    Go to VSCode settings (gear icon bottom left), search for "Use CMake Presets", and set it to Always.
    This ensures you select a preset each time you configure your project.

    Yes, this adds an extra step in the build process, but it guarantees the preset (and thus vcpkg manifest mode) is always used.

If you encounter other issues, unfortunately, that’s all the troubleshooting I have so far.