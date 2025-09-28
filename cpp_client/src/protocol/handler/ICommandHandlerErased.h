//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERERASED_H
#define DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERERASED_H
#include <memory>

#include "protocol/dto/Result.h"


struct ICommand;

class ICommandHandlerErased {
public:
    virtual ~ICommandHandlerErased()=default;

    [[nodiscard]] virtual Result handle(std::unique_ptr<ICommand> cmd)  = 0;
};
#endif //DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERERASED_H