#include "HandScoreTable.h"

namespace system_p {

HandScoreTable::HandScoreTable() {
    // Initialize default hand scores
    table[PokerHandType::ROYAL_FLUSH]     = {100, 8, 1};
    table[PokerHandType::STRAIGHT_FLUSH]  = {100, 8, 1};
    table[PokerHandType::FLUSH_FIVE]      = {160, 16, 1};
    table[PokerHandType::FIVE_OF_A_KIND]  = {120, 12, 1};
    table[PokerHandType::FOUR_OF_A_KIND]  = {60, 7, 1};
    table[PokerHandType::FLUSH_HOUSE]     = {140, 14, 1};
    table[PokerHandType::FULL_HOUSE]      = {40, 4, 1};
    table[PokerHandType::FLUSH]           = {35, 4, 1};
    table[PokerHandType::STRAIGHT]        = {30, 4, 1};
    table[PokerHandType::THREE_OF_A_KIND] = {30, 3, 1};
    table[PokerHandType::TWO_PAIR]        = {20, 2, 1};
    table[PokerHandType::PAIR]            = {10, 2, 1};
    table[PokerHandType::HIGH_CARD]       = {10, 1, 1};
    table[PokerHandType::NONE]            = {0, 0, 0};
}

HandScoreEntry HandScoreTable::getScoreEntry(PokerHandType handType) const {
    auto it = table.find(handType);
    if (it != table.end()) {
        return it->second;
    }
    return {0, 0, 0};
}

void HandScoreTable::upgradeHand(PokerHandType handType) {
    auto it = table.find(handType);
    if (it != table.end()) {
        it->second.level += 1;
        switch (handType) {
            case PokerHandType::ROYAL_FLUSH:
                it->second.baseChips += 40;
                it->second.baseMult += 4;
                break;
            case PokerHandType::STRAIGHT_FLUSH:
                it->second.baseChips += 40;
                it->second.baseMult += 4;
                break;
            case PokerHandType::FLUSH_FIVE:
                it->second.baseChips += 40;
                it->second.baseMult += 4;
                break;
            case PokerHandType::FIVE_OF_A_KIND:
                it->second.baseChips += 40;
                it->second.baseMult += 4;
                break;
            case PokerHandType::FOUR_OF_A_KIND:
                it->second.baseChips += 30;
                it->second.baseMult += 3;
                break;
            case PokerHandType::FLUSH_HOUSE:
                it->second.baseChips += 40;
                it->second.baseMult += 4;
                break;
            case PokerHandType::FULL_HOUSE:
                it->second.baseChips += 25;
                it->second.baseMult += 2;
                break;
            case PokerHandType::FLUSH:
                it->second.baseChips += 15;
                it->second.baseMult += 2;
                break;
            case PokerHandType::STRAIGHT:
                it->second.baseChips += 30;
                it->second.baseMult += 4;
                break;
            case PokerHandType::THREE_OF_A_KIND:
                it->second.baseChips += 20;
                it->second.baseMult += 2;
                break;
            case PokerHandType::TWO_PAIR:
                it->second.baseChips += 20;
                it->second.baseMult += 1;
                break;
            case PokerHandType::PAIR:
                it->second.baseChips += 15;
                it->second.baseMult += 1;
                break;
            case PokerHandType::HIGH_CARD:
                it->second.baseChips += 10;
                it->second.baseMult += 1;
                break;
            default:
                break;
        }
    }
}

std::string HandScoreTable::getHandName(PokerHandType handType) const {
    switch (handType) {
        case PokerHandType::ROYAL_FLUSH:     return "Royal Flush";
        case PokerHandType::STRAIGHT_FLUSH:  return "Straight Flush";
        case PokerHandType::FLUSH_FIVE:      return "Flush Five";
        case PokerHandType::FIVE_OF_A_KIND:  return "Five of a Kind";
        case PokerHandType::FOUR_OF_A_KIND:  return "Four of a Kind";
        case PokerHandType::FLUSH_HOUSE:     return "Flush House";
        case PokerHandType::FULL_HOUSE:      return "Full House";
        case PokerHandType::FLUSH:           return "Flush";
        case PokerHandType::STRAIGHT:        return "Straight";
        case PokerHandType::THREE_OF_A_KIND: return "Three of a Kind";
        case PokerHandType::TWO_PAIR:        return "Two Pair";
        case PokerHandType::PAIR:            return "Pair";
        case PokerHandType::HIGH_CARD:       return "High Card";
        default:                             return "None";
    }
}

} // namespace system_p
