

## Build and run locally

```
mkdir cmake-build-xxxx && cd cmake-build-xxxx
```

```
conan lock create --profile:host=../.conan/profiles/release --profile:build=default --lockfile=../lockfile.json --lockfile-out=lockfile.json --name=flappy-frog --version=0.1.0 ../conanfile.py --build --update
```

```
conan install --lockfile=lockfile.json ../conanfile.py --build=missing
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

## Update dependencies

```
conan lock create --name=flappy-frog --version=0.1.0 --base --lockfile-out lockfile.json --build --profile:host=.conan/profiles/release --profile:build=default conanfile.py
```

