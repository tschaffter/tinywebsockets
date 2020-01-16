# build
# rm -rf build
# rm -rf bin
# cmake -G "MinGW Makefiles" -H. -Bbuild
cmake -H. -Bbuild \
    -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl
cmake --build build -- -j1

./demo_echo_client