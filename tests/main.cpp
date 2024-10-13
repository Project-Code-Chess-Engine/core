#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "board.h"


// Uncomment if necessary. Tests a bitboard
/*TEST_CASE("Print bitboard", "[table][debug]"){
    uint64_t arrZeros[64] = {};
    std::fill(arrZeros, arrZeros + 64, 0);
    printbitboard(arrZeros);

    uint64_t arrOnes[64] = {};
    std::fill(arrOnes, arrOnes + 64, 1);
    printbitboard(arrOnes);
}*/

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