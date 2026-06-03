#ifndef BLIND_RULE_H
#define BLIND_RULE_H

#include <string>

namespace system_p {

class BlindRule {
public:
    virtual ~BlindRule() = default;
    virtual std::string getName() const = 0;
    virtual int getTargetScore() const = 0;
    virtual bool checkTarget(int score) = 0;
};

} // namespace system_p

#endif // BLIND_RULE_H