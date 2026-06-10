#ifndef ROUND_STATE_H
#define ROUND_STATE_H

namespace system_p {

class RoundState {
public:
    RoundState(int maxHands, int maxDiscards);
    
    int getHandsRemaining() const;
    int getDiscardsRemaining() const;
    int getCurrentScore() const;
    
    void addScore(int score);
    bool useHand();
    bool useDiscard();
    void reset();
    void addHandsRemaining(int amount);

private:
    const int maxHands;
    const int maxDiscards;
    int handsRemaining;
    int discardsRemaining;
    int currentScore;
};

} // namespace system_p

#endif // ROUND_STATE_H
