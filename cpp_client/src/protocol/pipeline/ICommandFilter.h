//
// Created by Ko-chieh Yin on 9/28/25.
//


# ifndef  DISTRIBUTED_LOCK_DEMO_ICOMMANDFILTER_H
#define DISTRIBUTED_LOCK_DEMO_ICOMMANDFILTER_H
struct ICommand;

class ICommandFilter {
public:
    virtual ~ICommandFilter() = default;

    virtual void doFilter(ICommand &cmd) {
    }
};
#endif //DISTRIBUTED_LOCK_DEMO_ICOMMANDFILTER_H