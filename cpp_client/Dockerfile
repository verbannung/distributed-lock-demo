FROM ubuntu:22.04

# 设置时区和避免 tzdata 卡住
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Shanghai


RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    gdb \
    netcat \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app


COPY CMakeLists.txt ./
COPY src ./src
COPY tests ./tests
COPY third_party ./third_party





EXPOSE 8081


RUN cmake -S . -B cmake-build-debug \
 && cmake --build cmake-build-debug -j$(nproc)

CMD ["./cmake-build-debug/distributed_lock_demo"]