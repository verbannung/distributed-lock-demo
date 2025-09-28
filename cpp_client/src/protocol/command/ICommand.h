//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_ICOMMAND_H
#define DISTRIBUTED_LOCK_DEMO_ICOMMAND_H
#include <string>

struct ICommand {
    virtual ~ICommand() = default;
    [[nodiscard]] virtual std::string toString() const = 0;
};

#endif //DISTRIBUTED_LOCK_DEMO_ICOMMAND_H