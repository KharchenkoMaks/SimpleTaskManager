# SimpleTaskManager
## Description
Client-server application for easy orginizing tasks that need to be completed. Application was created using [Protobuf](https://github.com/protocolbuffers/protobuf) and [GRPC](https://grpc.io) libraries.
### Features
- Tasks priority
- Subtasks
- Multiple client support
## Installation
### Linux and MacOS using CMake
1. Install `CMake`, minimum version: **3.16**
2. Install libraries:
   - [Protobuf](https://github.com/protocolbuffers/protobuf)
   - [GRPC](https://github.com/grpc/grpc)
   - [Boost](https://www.boost.org)
   - [GoogleTest](https://github.com/google/googletest) (google mock as well)
3. Build from source:
```
git clone https://github.com/KharchenkoMaks/SimpleTaskManager.git
cd SimpleTaskManager
mkdir build
cd build
cmake ..
cmake --build .
```
4. Launch `server`:
   - `./server`
5. Launch `client`:
   - `./client`
### Server deployment in Docker
Repository contains `Dockerfile` to compile `Docker image` for server deployment.
