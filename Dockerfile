FROM ubuntu:latest

ENV TZ=Europe/Kiev
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && \
    apt-get install -y \
      git \
      libboost-all-dev \
      libgtest-dev \
      cmake \
      build-essential \
      autoconf \
      libtool \
      pkg-config \
      protobuf-compiler && \
    apt-get clean

WORKDIR /librs

RUN git clone https://github.com/google/googletest.git -b release-1.11.0 && \
	cd googletest && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make && \
	make install

ENV GRPC_RELEASE_TAG v1.43.2

WORKDIR /librs

RUN git clone -b ${GRPC_RELEASE_TAG} https://github.com/grpc/grpc && \
		cd grpc && \
    echo "--- submodule updating ---" && \
    git submodule update --init && \
    mkdir cmake/build && \
    cd cmake/build && \
    cmake ../.. && \
    echo "--- making grpc ---" && \
    make && \
    make install

WORKDIR /apps

RUN git clone https://github.com/KharchenkoMaks/SimpleTaskManager.git && \
    cd SimpleTaskManager && \
    mkdir build && \
    cd build && \
    cmake .. && \
    cmake --build . --target server --

EXPOSE 8586

WORKDIR /apps/SimpleTaskManager/build

ENTRYPOINT ["./server"]
