//
// Created by Ko-chieh Yin on 9/27/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_COMMANDPIPELINE_H
#define DISTRIBUTED_LOCK_DEMO_COMMANDPIPELINE_H
#include <memory>
#include <vector>

#include "ICommandFilter.h"

struct ICommand;



class CommandPipeline {
    std::vector<std::shared_ptr<ICommandFilter>> filters;

public:
    void addFilter(std::shared_ptr<ICommandFilter> f);

    //可写，但是不拥有所有权
    void process(ICommand& cmd) const;
};

#endif //DISTRIBUTED_LOCK_DEMO_COMMANDPIPELINE_H