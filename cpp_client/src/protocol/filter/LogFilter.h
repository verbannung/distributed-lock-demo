//
// Created by Ko-chieh Yin on 9/28/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_LOGFILTER_H
#define DISTRIBUTED_LOCK_DEMO_LOGFILTER_H
#include "protocol/pipeline/ICommandFilter.h"


class LogFilter : public ICommandFilter{
     void doFilter(ICommand &cmd) override;
};


#endif //DISTRIBUTED_LOCK_DEMO_LOGFILTER_H