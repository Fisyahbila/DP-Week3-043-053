#include "JokerManager.h"
#include <iostream>

namespace mechanic {

    void JokerManager::addJoker(Joker* joker) {
        jokers.push_back(joker);
        std::cout << "[JokerManager] Joker ditambahkan. Total joker: " << jokers.size() << std::endl;
    }

    void JokerManager::applyAll(ScoreContext& ctx, const system_p::PlayedHandResult& result) {
        std::cout << "[JokerManager] Menerapkan semua joker..." << std::endl;
        for (Joker* joker : jokers) {
            joker->apply(ctx, result);
        }
    }

    JokerManager::~JokerManager() {
        for (Joker* joker : jokers) {
            delete joker;
        }
    }

}
