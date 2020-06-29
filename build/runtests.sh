#! /bin/bash
set -e

FNAME=test-$(date '+%d-%m--%H-%M').txt;

DIR=/home/sam/datasig/libalgebra_tests
echo "Moving to ${DIR}/build"
cd ${DIR}/build


echo "Starting build"
cmake -DCMAKE_BUILD_TYPE=Release "$@" ..
cmake --build .
echo "Done build"

echo "Running tests"
./test 2>&1 | tee $FNAME;

echo ""
echo "Results saved into $FNAME"

echo "Cleaning up"
rm "test"



echo "Done"

