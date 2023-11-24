# Level Zero Lookup
Use Level-Zero to retrieve information about Intel Devices.

## Requirements
- Level-Zero library must be installed.
- CMake 3.17
- The user must have the necessary permissions to access Level-Zero information.

## Install
To install `lz_lookup` run the following commands:
- `cd lz_info`
- `mkdir build`
- `cd build`
- `cmake -DCMAKE_CXX_COMPILER=/path/to/compiler ..`

## Execute
Once you have built the project, you will have two binary executables:
- `lz_lookup`: which will diplay the software informations about your Level-Zero-compatible devices;
- `lzhw_lookup`: which will display the hardware informations about your Leve-Zero-compatible devices;