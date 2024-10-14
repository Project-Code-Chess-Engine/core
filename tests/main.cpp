#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "board.h"


// Uncomment if necessary. Tests a bitboard
TEST_CASE("Print bitboard", "[table][debug]"){
    std::cout << "All Zeros" << std::endl;
    uint64_t arrZeros = 0ull;
    printbitboard(arrZeros);

    std::cout << "All Ones" << std::endl;
    uint64_t arrOnes = ~0ull;
    printbitboard(arrOnes);

    std::cout << "First Two Rows" << std::endl;
    uint64_t arrTwoRows = (0xFFFFull) << (8 * 6);
    printbitboard(arrTwoRows);
}

/*TEST_CASE("Start Up", "[table][debug]"){
    onLoad(); 
}*/

/*TEST_CASE("Start Up", "[table][debug]"){
    onLoad();
}*/

TEST_CASE("Load", "[table][latest]"){
    onLoad();
}

TEST_CASE("Knight Table", "[table][knight]") {

}

TEST_CASE("King Table", "[table][king]") {

}