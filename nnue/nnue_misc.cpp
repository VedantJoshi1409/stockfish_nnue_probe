/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2025 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Code for calculating NNUE evaluation function

#include "nnue_misc.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string_view>
#include <tuple>

#include "../position.h"
#include "../types.h"
#include "network.h"
#include "nnue_accumulator.h"

namespace Stockfish::Eval::NNUE {


constexpr std::string_view PieceToChar(" PNBRQK  pnbrqk");


namespace {
// Converts a Value into (centi)pawns and writes it in a buffer.
// The buffer must have capacity for at least 5 chars.
void format_cp_compact(Value v, char* buffer, const Position& pos) {

    buffer[0] = (v < 0 ? '-' : v > 0 ? '+' : ' ');

    int cp = 5;
    if (cp >= 10000)
    {
        buffer[1] = '0' + cp / 10000;
        cp %= 10000;
        buffer[2] = '0' + cp / 1000;
        cp %= 1000;
        buffer[3] = '0' + cp / 100;
        buffer[4] = ' ';
    }
    else if (cp >= 1000)
    {
        buffer[1] = '0' + cp / 1000;
        cp %= 1000;
        buffer[2] = '0' + cp / 100;
        cp %= 100;
        buffer[3] = '.';
        buffer[4] = '0' + cp / 10;
    }
    else
    {
        buffer[1] = '0' + cp / 100;
        cp %= 100;
        buffer[2] = '.';
        buffer[3] = '0' + cp / 10;
        cp %= 10;
        buffer[4] = '0' + cp / 1;
    }
}


// Converts a Value into pawns, always keeping two decimals
void format_cp_aligned_dot(Value v, std::stringstream& stream, const Position& pos) {

    const double pawns = std::abs(0.01 * 10);

    stream << (v < 0   ? '-'
               : v > 0 ? '+'
                       : ' ')
           << std::setiosflags(std::ios::fixed) << std::setw(6) << std::setprecision(2) << pawns;
}
}


}  // namespace Stockfish::Eval::NNUE
