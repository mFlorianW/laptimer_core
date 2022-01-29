# LaptimerCore

## Project Structure

### src Folder
The src folder contains all sources of the LaptimerCore.
Every subfolder in src holds a component of that source code.
The include folder in the subfolder contains the public API of the component. 
Other component should only use code of the include, this behavior is checked by CMake.
Another component shouldn't have access to sources in a different as include and should get an compile error.

### doc Folder
The doc folder contains the project documentation. 
The whole documentation is written with ASCIIDoc. 
Look at the README.md in that folder to see how to generate the documentation.

### .github
That folder contains specific files for the github.

## Build
There two configure and build presets for CMake. 
Call one the in the project root directory to build the LaptimerCore.

### Debug 
#### Configure
```console
cmake --build --preset debug
```

#### Build
```console
cmake --build --preset debug
```

### Release
#### Configure
``` console
camke --preset release
```

#### Build
``` console
camke --build --preset release
```