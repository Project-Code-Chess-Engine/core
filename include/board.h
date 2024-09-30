#pragma once
#include <array>
#include <cstdint>

// table to store moves for knights
static std::array<std::array<uint64_t, 8>, 8> knightTable;
// table to store the moves for kings
static std::array<std::array<uint64_t, 8>, 8> kingTable;

// generate the table for knights
void generateKnightTable();

//generate the table for Kings
void generateKingTable();