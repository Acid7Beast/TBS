// (c) 2025 Acid7Beast. Use with wisdom.
#include "Registry.h"

namespace acid7beast::tbs
{
    EntityId Registry::CreateEntity(std::optional<EntityId> entityId)
    {
        // Custom entity ID.
        if (entityId.has_value() && entityId.value() > _nextEntityId) {
            // Mark all entities in between as free.
            for (EntityId id = _nextEntityId; id < entityId.value(); ++id) {
                _freeEntityIds.push_back(id);
            }

            _nextEntityId = entityId.value();
            return _nextEntityId;
        }

        // Free entity ID.
        if (!_freeEntityIds.empty()) {
            EntityId entity = _freeEntityIds.back();
            _freeEntityIds.pop_back();
            return entity;
        }
        
        return ++_nextEntityId;
    }

    void Registry::DestroyEntity(EntityId entity)
    {
        // Here we remove components from all storages
        for (auto const& [_typeId, storage] : _storages) {
            storage->RemoveComponent(entity);
        }

        _freeEntityIds.push_back(entity);
    }
} // namespace acid7beast::tbs
