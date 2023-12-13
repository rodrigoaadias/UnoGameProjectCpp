# Uno Game

Uno Game is a project developed as part of a **C++ Training** at **Kokku**.

In the following sections you will see how to setup this project in your machine and how the project is working.

# Setup Project in your machine
This project uses a Core/App project architecture template developed by [The Cherno](https://github.com/TheCherno/ProjectTemplate). There are two included projects - one called _Uno-Core_, and one called _Uno-App_. [Premake](https://github.com/premake/premake-core) is used to generate project files.

Uno-Core builds into a static library and is meant to contain common code intended for use in multiple applications. Uno-App builds into an executable and links the Core static library, as well as provides an include path to Core's code.

The `Scripts/` directory contains build scripts for Windows and Linux, and the `Vendor/` directory contains Premake binaries (currently version `5.0-beta2`).

## Getting Started
1. Clone this repository
2. The three included Premake build files are `Build.lua`, `Uno-Core/Build-Core.lua` and `Uno-App/Build-App.lua` - these files were edited to fit the Uno Game project. Please do not change these files.
3. Open the `Scripts/` directory and run the appropriate `Setup` script to generate projects files. Out of the box they are set to Visual Studio 2022 for Windows and gmake2 for Linux.

Note that no macOS setup script is currently provided; you can duplicate the Linux script and adjust accordingly.

# Guidelines
These guidelines will help you to understand how to write new code to this project and how the code is actually being managed.

## Naming Conventions
Some of the most common cases are listed below:

|            **Type**             | **Convention** |
|:-------------------------------:|:--------------:|
|      Classes/Structs names      |   PascalCase   |
|           Enums names           |  EPascalCase   |
|     Methods/Functions names     |   PascalCase   |
|         Private fields          |   PascalCase   |
|        Protected fields         |   PascalCase   |
|       Methods parameters        |   camelCase    |
|         Local variables         |   camelCase    |
|        Global variables         |   UPPER_CASE   |
| Interfaces (Abstracted classes) |  IPascalCase   |
|           Namespaces            |   PascalCase   |

Feel free to suggest a naming convention for any other case not listed above.

## Comments
Avoid comments as much as possible.
Comments, such as code, needs to be maintainable, and can be often forgotten outdated. That's the reason they should be avoided. The code must be clear an self-explained, favouring readability. Clean code practices will help reach this goal.
Acceptable comments are:

* Summaries on pubic methods that are meant to be used by other developers (such as a plugin or service)
  * Do not use extensively. If the method is self-explanatory, there’s no need for a summary
* Brief explanation of complex algorithms that are very hard to understand

## Architecture
The Uno-Core library must be used as a tool to help developers to allocate and deallocate new objects in the Heap. If any object must be allocated in the Heap, make this class always derive from `Core::Entity`.
For more information about the project architecture, please check the images files inside `Documentation` directory.

## License
- GNU GENERAL PUBLIC LICENSE for this repository (see `LICENSE.txt` for more details)
- Premake is licensed under BSD 3-Clause (see included `LICENSE.txt` file in `Vendor` directory for more details)