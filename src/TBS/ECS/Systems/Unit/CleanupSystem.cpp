// (c) 2025 Acid7Beast. Use with wisdom.
#include "CleanupSystem.h"

#include <TBS/ECS/Registry/Registry.h>
#include <TBS/ECS/Events/EventBus.h>
#include <TBS/ECS/Events/Unit/DeathEvent.h>
#include <TBS/System/WorldContext.h>
#include <algorithm>

namespace acid7beast::tbs
{
    void CleanupSystem::Update(Registry& registry, WorldContext& worldContext)
    {
        auto& events = worldContext.eventBus.GetEvents<DeathEvent>();
        for (auto& entity : events) {
            auto& order = worldContext.turnOrder;
            auto it = std::remove(order.begin(), order.end(), entity.entityId);
            if (it != order.end()) {
                order.erase(it, order.end());
            }
            registry.DestroyEntity(entity.entityId);
        }

        worldContext.eventBus.ClearEvents<DeathEvent>();
    }
} // namespace acid7beast::tbs
