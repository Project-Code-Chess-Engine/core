#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "board.h"


// Uncomment if necessary. Tests a bitboard
// TEST_CASE("Print bitboard", "[table][latest]"){
//     std::cout << "All Zeros" << std::endl;
//     uint64_t arrZeros = 0ull;
//     printbitboard(arrZeros);

//     std::cout << "All Ones" << std::endl;
//     uint64_t arrOnes = ~0ull;
//     printbitboard(arrOnes);

//     std::cout << "First Two Rows" << std::endl;
//     uint64_t arrTwoRows = (0xFFFFull) << (8 * 6);
//     printbitboard(arrTwoRows);

//     std::cout << "First Two Columns" << std::endl;
//     uint64_t arrTwoCols = 0x0101010101010101 | 0x0202020202020202;
//     printbitboard(arrTwoCols);
// }

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

TEST_CASE("Bitboard blockers: zeros", "[table][debug]") {
    // Loop through all squares on the chessboard
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Get rook and bishop magic structs for the current square
            SMagic& rookBitBoard = rookMagics[i][j];
            SMagic& bishopBitBoard = bishopMagics[i][j];

            const uint64_t square = rookBitBoard.square;
            const uint64_t occupancy = EMPTY_MASK; // Empty occupancy bitboard (no blockers)

            // Calculate index for rook attacks
            uint64_t rookAttacks = getRookAttacks(rookBitBoard.square, EMPTY_MASK);  // Access attacks array

            std::cout << "Rook attacks from (" << i << ", " << j << ") on an empty board:\n";
            printbitboard(rookAttacks, rookBitBoard.square);

            // Calculate index for bishop attacks
            uint64_t bishopAttacks = getBishopAttacks(bishopBitBoard.square, EMPTY_MASK);

            std::cout << "Bishop attacks from (" << i << ", " << j << ") on an empty board:\n";
            printbitboard(bishopAttacks, bishopBitBoard.square);

        }
    }
}
