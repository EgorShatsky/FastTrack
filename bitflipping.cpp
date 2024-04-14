#include <iostream>
#include <bitset>

void BitFlipping(uint64_t* ptr, uint64_t len){
   for (uint64_t i = 0; i < len; ++i) {
        std::bitset<8>(~*(ptr + i));
    }
}

int main() {
    uint64_t x = 22;
    uint64_t* ptr = &x;
    uint64_t len = 3;
    BitFlipping(ptr, len);
}

