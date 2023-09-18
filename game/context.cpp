#include "context.h"

#include <utility>

Context::Context(const std::shared_ptr<Graphics>& graphics,
                 const std::shared_ptr<Inputs>& inputs,
                 const std::shared_ptr<Clock>& clock)
    : graphics(graphics),
      inputs(inputs),
      clock(clock),
      loop(std::make_shared<bool>(true)) {}

Context::Context(const std::shared_ptr<Graphics>& graphics)
    : Context(graphics, std::make_shared<Inputs>(),
              std::make_shared<Clock>()) {}
