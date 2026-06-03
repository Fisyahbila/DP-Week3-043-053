#ifndef HAND_SCORE_TABLE_H
#define HAND_SCORE_TABLE_H

#include "../evaluation/PokerHandType.h"
#include <map>
#include <string>

namespace system_p {

struct HandScoreEntry {
    int baseChips;
    int baseMult;
    int level;
};

class HandScoreTable {
public:
    HandScoreTable();
    HandScoreEntry getScoreEntry(PokerHandType handType) const;
    void upgradeHand(PokerHandType handType);
    std::string getHandName(PokerHandType handType) const;

private:
    std::map<PokerHandType, HandScoreEntry> table;
};

} // namespace system_p

#endif // HAND_SCORE_TABLE_H
