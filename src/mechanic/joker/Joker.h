#ifndef JOKER_H
#define JOKER_H

#include "JokerObserver.h"

namespace mechanic {

// Joker adalah alias/base untuk JokerObserver
// Semua concrete joker extend class ini
using Joker = JokerObserver;

} // namespace mechanic

#endif // JOKER_H