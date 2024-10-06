#include "board.h"
#include <iostream>

// Resource on Magic Bitboards
// https://www.chessprogramming.org/Magic_Bitboards
// The idea is that you have some sort of magic numbter that can perfectly hash your "occupants" and give you the moves
// https://www.chessprogramming.org/Looking_for_Magics
// This page explains the way to calculate magics

uint64_t arrBishop[8][8][64] = {{{0}}};

// prints the current bitboard to console for debug purposes
void printbitboard(uint64_t bitboard[64]) {
    for (int i = 0; i < 64; i++) {
        std::cout << bitboard[i];
        if ((i+1)%8 == 0 && i != 0){
            std::cout << std::endl;
        }
        else{
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void onLoad(){
    // Iterate through each possible position for the pieces to move
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            // Get the current array index
            uint64_t* bishopBitBoard = arrBishop[i][j];
            // Loop through all four directions
            for (int left = -1; left != 3; left +=2){
                for (int down = -1; down != 3; down +=2){
                    int curRow = i + left; int curCol = j + down;
                    while (curRow >= 0 && curRow < 8 && curCol >= 0 && curCol < 8){
                        // Update the value
                        bishopBitBoard[curRow * 8 + curCol] = 1;
                        // Increment the values
                        curRow += left;
                        curCol += down;
                    }
                }
            }
            printbitboard(bishopBitBoard);
            //bishopBitBoard << 7;
        }
    }
}

void findRookMagics() {
    // Use a bitboard to go through all positions and genreate the SMagic
}

void findBishopMagics() {
    // Use a bitboard to go through all positions and genreate the SMagic
}

void useMagic(const Board& board, const SMagic& magic) {
    // Use the SMagic on the board to calculate the moves
}

void generateKnightTable() {
    // Use a bitboard to go through all of the positions and generate the places that the knight is able to move.
    // https://www.chessprogramming.org/Knight_Pattern
}

void generateKingTable() {
    // Use a bitboard to go through all of the positions and generate the places that the king is able to move.
    // https://www.chessprogramming.org/King_Pattern
}

uint64_t getPawnMoves(const Board& board, uint64_t position) {
    // Use the bitboard to get the moves that can be done by pawn
    // Tip, I would use a capture table and also the information from the enpassant square
    // The en passant square is a bitboard storing the double pawn move
    return 0;
}