import byte_census;

#include <iostream>

int main() {
    ByteCensus bs("Hello World!");

    std::cout << bs << '\n';

    std::cout << bs.embeds_into(ByteCensus("Hello World!Hello World!")) << '\n';

    return 0;
}