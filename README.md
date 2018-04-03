# bosswestfalen::string_builder
[bosswestfalen::string_builder](https://www.github.com/bosswestfalen/string_builder) offers an easy to use class to store `std::string`s and concatenate them on demand.

# Building
To build the project [CMake](https://www.cmake.org) 3.9 or later is needed.

The building is straight forward:

+ create build directory <build>
+ execute `cmake`, e.g. `cmake -H. -B<build>`
+ build from <build>: `cmake --build .`
**Note**: See [Testing] on how to disable tests.

# Testing
Tests are automaticall built.

To disable this `cmake` must be called with `-DBUILD_TEST=OFF`.

For unit testing [Catch2](https://github.com/catchorg/Catch2) is used.

# Documentation
Documentation is generated with [Doxygen](https://www.stack.nl/~dimitri/doxygen/index.html).

To generate, build target `doc`.

# Links
+ [bosswestfalen::string_builder](https://www.github.com/bosswestfalen/string_builder)
+ [Catch2](https://github.com/catchorg/Catch2)
+ [CMake](https://www.cmake.org)
+ [Doxygen](https://www.stack.nl/~dimitri/doxygen/index.html)

