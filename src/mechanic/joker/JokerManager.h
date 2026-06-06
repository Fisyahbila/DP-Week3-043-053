#ifndef JOKER_MANAGER_H
#define JOKER_MANAGER_H

#include "../../system/scoring/PlayedHandResult.h"
#include "JokerObserver.h"
#include "ScoreContext.h"
#include <vector>

namespace mechanic {

// Subject — mengelola dan memnotify semua JokerObserver
class JokerManager {
public:
  // Attach / detach observer
  void attach(JokerObserver* joker);
  void detach(JokerObserver* joker);

  // Notify semua joker dengan ScoreContext dan hasil tangan
  void notify(ScoreContext& ctx, const system_p::PlayedHandResult& result);

  // Hitung final score SETELAH semua joker di-notify
  int getFinalScore(const system_p::PlayedHandResult& result);

  ~JokerManager();

private:
  std::vector<JokerObserver*> observers;
};

} // namespace mechanic

#endif // JOKER_MANAGER_H