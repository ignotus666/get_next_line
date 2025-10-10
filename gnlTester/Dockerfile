FROM debian:bookworm-slim
RUN apt-get update && apt-get -y upgrade && apt-get install -y git build-essential clang valgrind \
    && mkdir -m 777 /project
RUN git config --global --add safe.directory /project/gnlTester
WORKDIR /project
