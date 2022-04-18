[![Build and tests](https://github.com/froglets/flappy-frog/actions/workflows/ci.yml/badge.svg?event=push)](https://github.com/froglets/flappy-frog/actions/workflows/ci.yml)


## Setup environment

Install Conan (preferably in a virtual environment)
```
pip install conan
```

## Build and run locally

> Note.- See [docs/building.md](docs/building.md) for more detailed instructions

```
mkdir cmake-build-xxxx && cd cmake-build-xxxx
conan install .. <your-profile>
```

Use your preferred IDE or tool to build, debug and develop the project, typically:

```
cmake .. -DCMAKE_MODULE_PATH=$(pwd) -DCMAKE_PREFIX_PATH=$(pwd) -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_INSTALL_PREFIX:PATH=$(pwd)/install
cmake --build .
cmake --install .
```

And enjoy

```
./install/bin/mygame
```
