#include "probe.h"
#include "bitboard.h"
#include "position.h"
#include "evaluate.h"
#include "misc.h"
#include "types.h"
#include "nnue/nnue_architecture.h"

namespace Stockfish {

    namespace Probe {

        void init(const char *workingDirectory, const char *bigNetFile, const char *smallNetFile) {
            Bitboards::init();
            Position::init();

            std::unordered_map<Eval::NNUE::NetSize, Eval::EvalFile> evalFiles = {
                    {Eval::NNUE::Big,   {"EvalFile",      bigNetFile,   "None", ""}},
                    {Eval::NNUE::Small, {"EvalFileSmall", smallNetFile, "None", ""}}
            };

            evalFiles = Eval::NNUE::load_networks(workingDirectory, evalFiles);

            for (auto &[netSize, evalFile]: evalFiles) {
                std::cout << "Option: " << evalFile.optionName << std::endl; // Print other members similarly
                std::cout << "Name: " << evalFile.defaultName << std::endl;
                std::cout << std::endl;
            }
        }

        int eval(const char *fen) {
            Position pos;
            StateListPtr states(new std::deque<StateInfo>(1));

            pos.set(fen, false, &states->back());

            int eval = Eval::evaluate(pos);

            return eval;
        }
    }
}