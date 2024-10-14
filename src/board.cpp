#include "board.h"
#include <iostream>

// Resource on Magic Bitboards
// https://www.chessprogramming.org/Magic_Bitboards
// The idea is that you have some sort of magic numbter that can perfectly hash your "occupants" and give you the moves
// https://www.chessprogramming.org/Looking_for_Magics
// This page explains the way to calculate magics

// prints the current bitboard to console for debug purposes
void printbitboard(uint64_t bitboard) {
    for (int i = 63; i >= 0; i--) {
        std::cout << ((bitboard >> i) & 1);
        if ((i)%8 == 0 && i != 63){
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
            // SMagic newStruct;
            // VARIABLE DECLARATION: Find the variables and assign them to bitboards
            SMagic& bishopBitBoard = bishopMagics[i][j];
            SMagic& arrRookBitBoard = rookMagics[i][j];
            // BISHOP CALCULATION: Loop through all four diagonal directions
            for (int left = -1; left != 3; left +=2){
                for (int down = -1; down != 3; down +=2){
                    int curRow = i + left; int curCol = j + down;
                    while (curRow >= 0 && curRow < 8 && curCol >= 0 && curCol < 8){
                        // Update the value
                        bishopBitBoard.mask += 1ull << (63 - (curRow * 8 + curCol));
                        // Increment the values
                        curRow += left;
                        curCol += down;
                    }
                }
            }
            // ROOK CALCULATION: Loop through all four directions in a straight line
            for (int x = 0; x < 8; x++){ // Calculates LEFT <-> RIGHT moves
                if (x != j){
                    arrRookBitBoard.mask += 1ull << (63 - (i * 8 + x));
                }
            }
            for (int y = 0; y < 8; y++){ // Calculates BOTTOM <-> TOP moves
                if (y != i){
                    arrRookBitBoard.mask += 1ull << (63 - (y * 8 + j));
                }
            }
            // SQUARE ASSIGNMENT: Assign the square bitboard variable
            arrRookBitBoard.square = 1ull << (63 - (i * 8 + j));
            bishopBitBoard.square = 1ull << (63 - (i * 8 + j));
            printbitboard(arrRookBitBoard.square);
        }
    }
    findRookMagics();
    findBishopMagics();
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