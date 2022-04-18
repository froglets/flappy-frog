[![Build and tests](https://github.com/froglets/flappy-frog/actions/workflows/ci.yml/badge.svg?event=push)](https://github.com/froglets/flappy-frog/actions/workflows/ci.yml)


## Setup environment

Install Conan (preferably in a virtual environment)

```sh
pip install conan
```

## Build and run locally

> Note.- See [docs/building.md](docs/building.md) for more detailed instructions

```sh
# using release as build type, it should match your default profile
mkdir cmake-build-release && cd cmake-build-release
conan install ..
```

Use your preferred IDE or tool to build, debug and develop the project, typically:

```sh
cmake .. -DCMAKE_MODULE_PATH=$(pwd) -DCMAKE_PREFIX_PATH=$(pwd) -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_INSTALL_PREFIX:PATH=$(pwd)/install
cmake --build .
cmake --install .
```

And enjoy

```sh
./install/bin/mygame
```
