//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_HANDLERREGISTRY_H
#define DISTRIBUTED_LOCK_DEMO_HANDLERREGISTRY_H

#include "../command/Command.h"
#include <typeindex>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <utility>

#include "ICommandHandlerErased.h"
#include "ICommandHandlerErased.h"
#include "ICommandHandlerTyped.h"
class HandlerRegistry {
private:
    std::unordered_map<std::type_index, std::unique_ptr<ICommandHandlerErased>> handlers;

public:
    template<typename T>
    void registerHandler(std::shared_ptr<ICommandHandlerTyped<T>> handler) ;

    Result dispatch(std::unique_ptr<ICommand> cmd);
};


#endif //DISTRIBUTED_LOCK_DEMO_HANDLERREGISTRY_H
