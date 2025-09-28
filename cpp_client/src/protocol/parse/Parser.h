//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_PARSERCOMMAND_H
#define DISTRIBUTED_LOCK_DEMO_PARSERCOMMAND_H
#include <memory>
#include <string>

#include <memory>
#include <sstream>

#include "protocol/command/Command.h"
#include "protocol/dto/AcquireDto.h"
#include "../command/ICommand.h"


class Parser {
public:
    static std::unique_ptr<ICommand> parse(const std::string& raw);
};



#endif //DISTRIBUTED_LOCK_DEMO_PARSERCOMMAND_H
