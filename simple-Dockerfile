FROM ubuntu
# suppress input
ARG DEBIAN_FRONTEND=noninteractive

# essential, cmake, git, boost, GMP for Bignum library
RUN apt-get update && apt-get -y install build-essential cmake git libboost-all-dev libgmp-dev

# unittest-cpp
RUN git clone https://github.com/unittest-cpp/unittest-cpp.git
WORKDIR /unittest-cpp/builds
RUN cmake ../
RUN cmake --build ./
RUN cmake --build ./ --target install

# libalgebra_tests build
RUN mkdir libalgebra_tests
WORKDIR /libalgebra_tests
COPY . .
WORKDIR /libalgebra_tests/build
RUN cmake -DCMAKE_BUILD_TYPE=Release "$@" ..
RUN cmake --build .

# Run the tests
CMD ./test
