#include "GameManager.h"
#include "RunSessionService.h"

namespace system_p {

GameManager::GameManager() {}

void GameManager::runSession() {
    RunSessionService service;
    service.runSession();
}

} // namespace system_p