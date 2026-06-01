#ifndef JOKER_OBSERVER_H
#define JOKER_OBSERVER_H

#include "ScoreContext.h"
#include "../../system/scoring/PlayedHandResult.h"

namespace mechanic {

    // Observer interface — setiap Joker mengimplementasikan ini
    class JokerObserver {
    public:
        virtual void onNotify(ScoreContext& ctx, const system_p::PlayedHandResult& result) = 0;
        virtual ~JokerObserver() = default;
    };

} // namespace mechanic

#endif // JOKER_OBSERVER_H
