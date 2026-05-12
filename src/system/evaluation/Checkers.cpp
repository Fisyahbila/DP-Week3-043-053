#include "Checkers.h"
#include <iostream>

namespace system_p {

    PokerHandType FlushFiveChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush Five..." << std::endl;
        // Logic will be implemented by System Programmer
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH_FIVE;
    }

    PokerHandType FlushHouseChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush House..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH_HOUSE;
    }

    PokerHandType FiveOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Five of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FIVE_OF_A_KIND;
    }

    PokerHandType RoyalFlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Royal Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::ROYAL_FLUSH;
    }

    PokerHandType StraightFlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Straight Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::STRAIGHT_FLUSH;
    }

    PokerHandType FourOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Four of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FOUR_OF_A_KIND;
    }

    PokerHandType FullHouseChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Full House..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FULL_HOUSE;
    }

    PokerHandType FlushChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Flush..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::FLUSH;
    }

    PokerHandType StraightChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Straight..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::STRAIGHT;
    }

    PokerHandType ThreeOfAKindChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Three of a Kind..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::THREE_OF_A_KIND;
    }

    PokerHandType TwoPairChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Two Pair..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::TWO_PAIR;
    }

    PokerHandType PairChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: Pair..." << std::endl;
        if (nextChecker != nullptr) {
            return nextChecker->check(hand);
        }
        return PokerHandType::PAIR;
    }

    PokerHandType HighCardChecker::check(const Hand& hand) {
        std::cout << "[Checker] Mengecek: High Card..." << std::endl;
        return PokerHandType::HIGH_CARD;
    }

} // namespace system_p
