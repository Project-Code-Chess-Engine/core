#include "board.h"
#include <bit>
#include <iostream>

// Resource on Magic Bitboards
// https://www.chessprogramming.org/Magic_Bitboards
// The idea is that you have some sort of magic number that can perfectly hash your "occupants" and give you the moves
// https://www.chessprogramming.org/Looking_for_Magics
// This page explains the way to calculate magics

// prints the current bitboard to console for debug purposes
void printbitboard(uint64_t bitboard, uint64_t origin) {
    /*for (int i = 63; i >= 0; i--) {
        std::cout << ((bitboard >> i) & 1? "X": "-");//((origin >> i) & 1? "O": "-"));
        if ((i)%8 == 0 && i != 63){
            std::cout << std::endl;
        }
        else{
            std::cout << " ";
        }
    }
    std::cout << std::endl;*/
    
    std::cout << std::endl;
    for (int row = 7; row >= 0; row--){
        for (int col = 0; col < 8; col++){
            int shift = row * 8 + col;
            std::cout << ((bitboard >> shift) & 1? "X": "-");
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// Constants and Helper Functions

uint64_t randomMagicNumber() {
    static std::mt19937_64 rng(std::random_device{}());
    return rng() & rng() & rng() & rng();  // Combine several RNG calls for higher variability
}

uint64_t getOccupancyBishop(uint64_t mask, uint64_t index) {
    uint64_t occupancy = 0;
    int bits = std::popcount(mask); // Counts number of set bits in mask
    for (int i = 0; i < bits; ++i) {
        if (index & (1ull << i)) {
            int bitPos = std::countr_zero(mask & (-mask)); // Find the lowest set bit
            occupancy |= (1ull << bitPos);
        }
        mask &= (mask - 1);  // Remove the lowest set bit
    }
    return occupancy;
}

// Function to calculate rook attacks for a given occupancy
uint64_t calculateRookAttacks(int sq, uint64_t occupancy) {
    uint64_t attacks = 0;
    int rank = sq / 8, file = sq % 8;
    for (int i = file + 1; i < 8; ++i) { // Right
        attacks |= (1ull << (rank * 8 + i));
        if (occupancy & (1ull << (rank * 8 + i))) break;
    }
    for (int i = file - 1; i >= 0; --i) { // Left
        attacks |= (1ull << (rank * 8 + i));
        if (occupancy & (1ull << (rank * 8 + i))) break;
    }
    for (int i = rank + 1; i < 8; ++i) { // Up
        attacks |= (1ull << (i * 8 + file));
        if (occupancy & (1ull << (i * 8 + file))) break;
    }
    for (int i = rank - 1; i >= 0; --i) { // Down
        attacks |= (1ull << (i * 8 + file));
        if (occupancy & (1ull << (i * 8 + file))) break;
    }
    return attacks;
}

// Function to calculate bishop attacks for a given occupancy
uint64_t calculateBishopAttacks(int sq, uint64_t occupancy) {
    uint64_t attacks = 0;
    int rank = sq / 8, file = sq % 8;

    // Top-right diagonal
    for (int r = rank + 1, f = file + 1; r < 8 && f < 8; ++r, ++f) {
        attacks |= (1ull << (r * 8 + f));
        if (occupancy & (1ull << (r * 8 + f))) break;
    }

    // Top-left diagonal
    for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; ++r, --f) {
        attacks |= (1ull << (r * 8 + f));
        if (occupancy & (1ull << (r * 8 + f))) break;
    }

    // Bottom-right diagonal
    for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; --r, ++f) {
        attacks |= (1ull << (r * 8 + f));
        if (occupancy & (1ull << (r * 8 + f))) break;
    }

    // Bottom-left diagonal
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f) {
        attacks |= (1ull << (r * 8 + f));
        if (occupancy & (1ull << (r * 8 + f))) break;
    }

    return attacks;
}

double randomnumber() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static std::default_random_engine rng;

    std::uniform_real_distribution<double> dist(0.0, 1.0); 
    return dist(rng); 
}

void findMagicNumber(SMagic& magicStruct, bool bishop) {
    // Step 1: Collect bit positions from the mask
    uint64_t bit_copy = magicStruct.mask;
    std::vector<int> placements;
    while (bit_copy) {
        int position = std::countr_zero(bit_copy);
        placements.push_back(position);
        bit_copy &= bit_copy - 1; // Clear the lowest set bit
    }

    // Step 2: Generate all blocker combinations
    std::vector<uint64_t> blocker_boards;
    int num_bits = placements.size();
    int num_combinations = 1 << num_bits;
    for (int i = 0; i < num_combinations; ++i) {
        uint64_t blocker_board = 0;
        for (int j = 0; j < num_bits; ++j) {
            if (i & (1 << j)) {
                blocker_board |= 1ULL << placements[j];
            }
        }
        blocker_boards.push_back(blocker_board);
    }

    // Step 3: Try to find a magic number
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);

    bool found = false;
    uint64_t magic = 0;

    for (int attempts = 0; attempts < 1000000 && !found; ++attempts) {
        magic = dist(rng) & dist(rng) & dist(rng); // Improve randomness
        if (__builtin_popcountll((magic * magicStruct.mask) >> 56) < 6) continue; // Heuristic check

        std::set<uint64_t> used_indices;
        bool collision = false;

        for (const auto& blockers : blocker_boards) {
            uint64_t index = (blockers * magic) >> (64 - magicStruct.bits);
            if (used_indices.count(index)) {
                collision = true;
                break;
            }
            used_indices.insert(index);
        }

        if (!collision) {
            found = true;
        }
    }

    if (!found) {
        throw std::runtime_error("Magic Number Calculation Failed for Bishop/Rook");
    }

    // Step 4: Store the magic number and prepare moves
    magicStruct.magic = magic;
    magicStruct.moves.resize(blocker_boards.size());
    for (const auto& blockers : blocker_boards) {
        uint64_t index = (blockers * magic) >> (magicStruct.bits);
        magicStruct.moves[index] = blockers;
    }
}

uint64_t getRookAttacks(uint64_t square, uint64_t occupancy) {
    const SMagic& rookMagic = rookMagics[square / 8][square % 8];

    const uint64_t index = (rookMagic.magic * occupancy) >> rookMagic.bits;

    return rookMagic.moves[index];
}

uint64_t getBishopAttacks(uint64_t square, uint64_t occupancy) {
    const SMagic& bishopMagic = bishopMagics[square / 8][square % 8];

    const uint64_t index = (bishopMagic.magic * occupancy) >> bishopMagic.bits;

    return bishopMagic.moves[index];
}


void onLoad() {
    std::cout << "Loading..." << std::endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SMagic& bishopBitBoard = bishopMagics[i][j];
            SMagic& rookBitBoard = rookMagics[i][j];

            // Calculate Bishop Mask
            for (int left = -1; left <= 1; left += 2) {
                for (int down = -1; down <= 1; down += 2) {
                    int curRow = i + left, curCol = j + down;
                    while (curRow >= 0 && curRow < 8 && curCol >= 0 && curCol < 8) {
                        bishopBitBoard.mask |= 1ull << (curRow * 8 + curCol);
                        curRow += left;
                        curCol += down;
                    }
                }
            }

            // Calculate Rook Mask
            for (int x = 0; x < 8; x++) { // Horizontal moves
                if (x != j) {
                    rookBitBoard.mask |= 1ull << (i * 8 + x);
                }
            }
            for (int y = 0; y < 8; y++) { // Vertical moves
                if (y != i) {
                    rookBitBoard.mask |= 1ull << (y * 8 + j);
                }
            }

            // Assign the square bitboard variable
            rookBitBoard.square = 1ull << (i * 8 + j);
            bishopBitBoard.square = 1ull << (i * 8 + j);

            // Calculate magic numbers for rooks and bishops
            findMagicNumber(rookBitBoard, false);
            findMagicNumber(bishopBitBoard, true);
        }
    }
    std::cout << std::endl;
}


void findRookMagics() {
    
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