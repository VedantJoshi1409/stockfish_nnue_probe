#include <memory>

#include "probe.h"
#include "bitboard.h"
#include "position.h"
#include "evaluate.h"
#include "nnue/network.h"

namespace Stockfish {

    namespace Probe {  

        std::unique_ptr<Eval::NNUE::Networks> networks;

        void init( const char *bigNetFile, const char *smallNetFile) {
            Bitboards::init();
            Position::init();
            Eval::NNUE::Features::init_threat_offsets();

            networks = std::make_unique<Eval::NNUE::Networks>(
            std::make_unique<Eval::NNUE::NetworkBig>(
                Eval::NNUE::EvalFile{bigNetFile, "None", ""},
                Eval::NNUE::EmbeddedNNUEType::BIG
            ),
            std::make_unique<Eval::NNUE::NetworkSmall>(
                Eval::NNUE::EvalFile{smallNetFile, "None", ""},
                Eval::NNUE::EmbeddedNNUEType::SMALL
            ));
            networks->big.load("", bigNetFile);
            networks->small.load("", smallNetFile);

            std::cout << "NNUE networks loaded from files: "
                      << bigNetFile << " and " << smallNetFile << std::endl;
        }

        int eval(const char *fen) {
            Position pos;
            StateListPtr states(new std::deque<StateInfo>(1));

            pos.set(fen, &states->back());
            auto accumulators = std::make_unique<Eval::NNUE::AccumulatorStack>();
            auto caches       = std::make_unique<Eval::NNUE::AccumulatorCaches>(*networks);
            int eval = Eval::evaluate(*networks, pos, *accumulators, *caches, VALUE_ZERO);
            return eval;
        }

        int eval(const int pieceBoard[], bool side, int rule50) {
            Position pos;
            StateListPtr states(new std::deque<StateInfo>(1));

            pos.set(pieceBoard, side, rule50, &states->back());
            auto accumulators = std::make_unique<Eval::NNUE::AccumulatorStack>();
            auto caches       = std::make_unique<Eval::NNUE::AccumulatorCaches>(*networks);
            int eval = Eval::evaluate(*networks, pos, *accumulators, *caches, VALUE_ZERO);

            return eval;
        }

        int eval(const int pieces[], const int squares[], int pieceAmount, bool side, int rule50) {
            Position pos;
            StateListPtr states(new std::deque<StateInfo>(1));

            pos.set(pieces, squares, pieceAmount, side, rule50, &states->back());
            auto accumulators = std::make_unique<Eval::NNUE::AccumulatorStack>();
            auto caches       = std::make_unique<Eval::NNUE::AccumulatorCaches>(*networks);
            int eval = Eval::evaluate(*networks, pos, *accumulators, *caches, VALUE_ZERO);

            return eval;
        }
    }
}