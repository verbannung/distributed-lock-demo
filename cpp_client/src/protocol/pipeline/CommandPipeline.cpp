//
// Created by Ko-chieh Yin on 9/28/25.
//


#include "CommandPipeline.h"

void CommandPipeline::addFilter(std::shared_ptr<ICommandFilter> f) {
    filters.push_back(std::move(f));
}

void CommandPipeline::process(ICommand &cmd) const {

        for (auto& f : filters) {
            f->doFilter(cmd);
        }
}
