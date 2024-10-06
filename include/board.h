#pragma once
#include <array>
#include <cstdint>
#include <memory>

// extern "C" is used here to allow non-c++ programs to use these sturcts and functions
extern "C" {
    // sets up all of the tables
    void initialize();

    // an enum to represent the different boards
    enum Piece {
        WHITE, BLACK, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING, ENPASSANT
    };

    // the struct that stores the boards
    typedef struct {
        // the bitboards
        // https://www.chessprogramming.org/Bitboards
        uint64_t boards[9];
    } Board;
};

// a magic square
struct SMagic {
    // the moves that can be made
    std::unique_ptr<uint64_t[]> moves;
    // the occupancy mask
    uint64_t mask;
    // the mask representing the square
    uint64_t square;
    // the number of significant bits
    uint8_t bits;
    // the magic number (hard part is finding it)
    uint8_t magic;
};

// table to store the rookMagics
static std::array<std::array<SMagic, 8>, 8> rookMagics;
// table to store the bishopMagics
static std::array<std::array<SMagic, 8>, 8> bishopMagics;

// generate the SMagics for rooks
void findRookMagics();

// generate the SMagics for bishops
void findBishopMagics();

// use the SMagic to get moves
void useMagic(const Board& board, const SMagic& magic);

// table to store moves for knights
static std::array<std::array<uint64_t, 8>, 8> knightTable;
// table to store the moves for kings
static std::array<std::array<uint64_t, 8>, 8> kingTable;

// generate the table for knights
void generateKnightTable();

// generate the table for Kings
void generateKingTable();

// gets the moves that can be done by a pawn
uint64_t getPawnMoves(const Board& board, uint64_t position);

// creates the magic bitboards to storage
void onLoad();

// prints out the bitboard to the console
void printbitboard();