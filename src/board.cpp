#include "board.h"

// Resource on Magic Bitboards
// https://www.chessprogramming.org/Magic_Bitboards
// The idea is that you have some sort of magic numbter that can perfectly hash your "occupants" and give you the moves
// https://www.chessprogramming.org/Looking_for_Magics
// This page explains the way to calculate magics

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
}