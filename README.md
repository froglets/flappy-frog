[![Build and tests](https://github.com/jgsogo/flappy-frog/actions/workflows/ci.yml/badge.svg?event=push)](https://github.com/jgsogo/flappy-frog/actions/workflows/ci.yml)


## Setup environment

Install Conan (preferably in a virtual environment)
```
pip install conan
```

## Build and run locally

```
mkdir cmake-build-xxxx && cd cmake-build-xxxx
```

```
conan lock create --profile:host=../.conan/profiles/release --profile:build=default --lockfile=../lockfile.json --lockfile-out=lockfile.json --name=flappy-frog --version=0.1.0 ../conanfile.txt --build --update
```

```
conan install --lockfile=lockfile.json ../conanfile.txt --build=missing
```

Use your preferred IDE or tool to build, debug and develop the project, typically:

```

```

## Update dependencies

```
conan lock create --name=flappy-frog --version=0.1.0 --base --lockfile-out lockfile.json --build --profile:host=.conan/profiles/release --profile:build=default conanfile.txt
```
