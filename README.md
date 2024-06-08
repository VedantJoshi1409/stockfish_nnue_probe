# stockfish_nnue_probe

## What is it?

A library for probing Stockfish's NNUEs. The code for reading parameters and the forward propagation is taken from Stockfish with modifications to allow for easy access. Currently supports C++ and Java!

## C++ Usage Guide
At engine start up, run ```init(const char *bigNetName, const char *smallNetName)```\
For evaluation, run ```eval(const int pieceBoard[], bool side, int rule50)```

## Java Usage Guide
At engine start up, run ```init(String bigNetName, String smallNetName)```\
For evaluation, run ```evalArray(int[] pieceBoard, int side, int rule50)```

## Function Parameter Explanation 

**pieceBoard** is an array of size 64, where index 0 is mapped to A1, index 1 is mapped to B1, and index 63 is mapped to H8. The value in each index is 
- 0 for no piece
- 1 for white pawn
- 2 for white knight
- 3 for white bishop
- 4 for white rook
- 5 for white queen
- 6 for white king
- 9 for black pawn
- 10 for black knight
- 11 for black bishop
- 12 for black rook
- 13 for black queen
- 14 for black king

**side** is 0 for white and 1 for black\
**rule50** is the value of the halfmove clock, should be between 0 and 100\

Examples of function usage is in main.cpp
## NNUE Installation Guide

Install the nets from the [Stockfish Testing Framework](https://tests.stockfishchess.org/nns) and put them inside your source directory.

Latest supported big network is **nn-b1a57edbea57.nnue** \
Latest supported small network is **nn-baff1ede1f90.nnue**\
Both are needed!

## C++ Installation Guide

Download everything except for the NNUEBridge files and probe.dll. Put them in your source directory. The probing functions are in probe.cpp. 

## Java Installation Guide

Download probe.dll and NNUEBridge.java, and put them both in your source directory. The probing functions are in NNUEBridge.java.

## Shared Library Compilation Guide

Install all files and run ```make -j build ARCH=x86-64-avx2 ```\
Then run ```g++ -lpthread -shared -o probe.dll bitboard.o evaluate.o evaluate_nnue.o half_ka_v2_hm.o misc.o NNUEBridge.o position.o probe.o -I${JAVA_HOME}/include -I${JAVA_HOME}/include/win32```
