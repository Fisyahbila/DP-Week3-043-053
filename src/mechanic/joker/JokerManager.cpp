#include "JokerManager.h"
#include <algorithm>
#include <iostream>

namespace mechanic {

void JokerManager::attach(JokerObserver* joker)
{
  observers.push_back(joker);
  std::cout << "[JokerManager] Joker di-attach. Total observer: " << observers.size() << std::endl;
}

void JokerManager::detach(JokerObserver* joker)
{
  auto it = std::find(observers.begin(), observers.end(), joker);
  if (it != observers.end()) {
    observers.erase(it);
    std::cout << "[JokerManager] Joker di-detach. Total observer: " << observers.size()
              << std::endl;
  }
}

void JokerManager::notify(ScoreContext& ctx, const system_p::PlayedHandResult& result)
{
  std::cout << "[JokerManager] Notifying semua joker (" << observers.size() << " joker aktif)..."
            << std::endl;
  for (JokerObserver* joker : observers) {
    joker->onNotify(ctx, result);
  }
  std::cout << "[JokerManager] Semua joker telah dijalankan." << std::endl;
}

int JokerManager::getFinalScore(const system_p::PlayedHandResult& result)
{
  // Inisialisasi ScoreContext dari base value hasil tangan
  ScoreContext ctx;
  ctx.chips = result.baseChips;
  ctx.mult = result.baseMult;

  std::cout << "[JokerManager] Base score — Chips: " << ctx.chips << ", Mult: " << ctx.mult
            << std::endl;

  // Notify semua joker agar memodifikasi ScoreContext
  notify(ctx, result);

  // Final score dihitung SETELAH semua joker run
  int finalScore = ctx.chips * ctx.mult;
  std::cout << "[JokerManager] Final score: " << ctx.chips << " chips x " << ctx.mult
            << " mult = " << finalScore << std::endl;

  return finalScore;
}

JokerManager::~JokerManager()
{
  for (JokerObserver* joker : observers) {
    delete joker;
  }
}

} // namespace mechanic