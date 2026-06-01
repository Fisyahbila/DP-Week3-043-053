#ifndef JOKER_MANAGER_H
#define JOKER_MANAGER_H

#include "../Joker.h"
#include "../ScoreContext.h"
#include "../../../system/scoring/PlayedHandResult.h"
#include <vector>

namespace mechanic {
    class JokerManager {
    public:
        void addJoker(Joker* joker);
        void applyAll(ScoreContext& ctx, const system_p::PlayedHandResult& result);
        ~JokerManager();

    private:
        std::vector<Joker*> jokers;
    };
}

#endif // JOKER_MANAGER_H
