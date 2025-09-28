//
// Created by Ko-chieh Yin on 9/28/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_IPARSECOMMAND_H
#define DISTRIBUTED_LOCK_DEMO_IPARSECOMMAND_H
#include <memory>

struct ICommand;

class IParseCommand {
    virtual ~IParseCommand() = default;

    virtual std::unique_ptr<ICommand> parse(std::istringstream& iss) const = 0;

    [[nodiscard]] virtual  std::string getCommandType() const = 0;
};

#endif //DISTRIBUTED_LOCK_DEMO_IPARSECOMMAND_H
