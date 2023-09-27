#include "context.h"

#include <utility>

Context::Context(const std::shared_ptr<Clock>& clock)
    : clock(clock), loop(std::make_shared<bool>(true)) {}
