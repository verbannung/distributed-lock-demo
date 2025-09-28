//
// Created by Ko-chieh Yin on 9/28/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_PARSELOCKAQW_H
#define DISTRIBUTED_LOCK_DEMO_PARSELOCKAQW_H
#include "IParseCommand.h"
#include "protocol/command/Command.h"
#include "protocol/dto/AcquireDto.h"
class ParseLockACQ : public IParseCommand {

public:
     ~ParseLockACQ() override;

     std::unique_ptr<ICommand> parse(std::istringstream& iss)const override ;

      [[nodiscard]] std::string getCommandType()const override;
};

#endif //DISTRIBUTED_LOCK_DEMO_PARSELOCKAQW_H