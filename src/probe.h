#ifndef STOCKFISH_PROBE_H
#define STOCKFISH_PROBE_H

namespace Stockfish {
    namespace Probe {
        void init(const char*, const char*, const char*);

        int eval(const char *fen);
    }
}

#endif //STOCKFISH_PROBE_H
