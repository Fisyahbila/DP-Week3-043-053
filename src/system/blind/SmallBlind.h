#ifndef SMALL_BLIND_H
#define SMALL_BLIND_H

#include "BlindRule.h"

namespace system_p {

class SmallBlind : public BlindRule {
public:
    explicit SmallBlind(int ante);
    std::string getName() const override;
    int getTargetScore() const override;
    bool checkTarget(int score) override;

private:
    int targetScore;
};

} // namespace system_p

#endif // SMALL_BLIND_H
