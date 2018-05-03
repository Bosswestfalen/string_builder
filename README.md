# bosswestfalen::string_builder
[bosswestfalen::string_builder](https://www.github.com/bosswestfalen/string_builder) offers an easy to use class to convert (almost) any type to `std::string` and concatenate them on demand.

# Building
To build the project [CMake](https://www.cmake.org) 3.9 or later is needed.

The building is straight forward:

+ create build directory <build>
+ execute `cmake`, e.g. `cmake -H. -B<build>`
+ build from <build>: `cmake --build .`

**Note**: See [Testing](#testing) on how to disable tests.

# Testing
Tests will be build by default.

To disable this `cmake` must be called with `-DBUILD_TEST=OFF`.

For unit testing [Catch2](https://github.com/catchorg/Catch2) is used.


Code coverage is available by default.
Use `-DSB_TEST_COVERAGE=OFF" to disable.

To generate the coverage report run target `lcov_html`.
The report is written to `<build>/test/html`.

**Note**: Code coverage is only available if building with GCC.
Also it is assumed that `gcov`, `lcov`, and `genhtml` are available.

# Documentation
Documentation is generated with [Doxygen](https://www.stack.nl/~dimitri/doxygen/index.html).

To generate, build target `doc`.

# Links
+ [bosswestfalen::string_builder](https://www.github.com/bosswestfalen/string_builder)
+ [Catch2](https://github.com/catchorg/Catch2)
+ [CMake](https://www.cmake.org)
+ [Doxygen](https://www.stack.nl/~dimitri/doxygen/index.html)

