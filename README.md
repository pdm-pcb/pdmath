### Build and Run
Running `cmake -B build -S .` from the project root will sort out the setup. In
order to build, just run `cmake --build build --parallel $(nproc)` or so.

Once it's built, you can run `./bin/tests -s` to see the various unit tests
provided via [Catch2](https://github.com/catchorg/Catch2).

Whoop!
