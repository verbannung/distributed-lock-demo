//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERTYPED_H
#define DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERTYPED_H
#include "protocol/dto/Result.h"

template <typename T>
class ICommandHandlerTyped {
    public:
    virtual ~ICommandHandlerTyped()=default;
    virtual Result handle(const T& cmd)=0;
};
#endif //DISTRIBUTED_LOCK_DEMO_ICOMMANDHANDLERTYPED_H