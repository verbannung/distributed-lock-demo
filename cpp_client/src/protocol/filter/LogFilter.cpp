//
// Created by Ko-chieh Yin on 9/28/25.
//

#include "LogFilter.h"

#include "../../../third_party/spdlog/include/spdlog/spdlog.h"
#include "protocol/command/ICommand.h"

void LogFilter::doFilter(ICommand &cmd) {
    spdlog::debug(cmd.toString());
}
