//
// Created by Ko-chieh Yin on 9/27/25.
//


#include "HandlerRegistry.h"

template<typename T>
void HandlerRegistry::registerHandler(std::shared_ptr<ICommandHandlerTyped<T>> handler) {
    struct Adapter : ICommandHandlerErased {
        std::shared_ptr<ICommandHandlerTyped<T>> typedHandler;
        explicit Adapter(std::shared_ptr<ICommandHandlerTyped<T>> h) : typedHandler(std::move(h)) {}
        Result handle(std::unique_ptr<ICommand> cmd) override {
            auto* real = dynamic_cast<Command<T>*>(cmd.get());
            if (!real) throw std::runtime_error("unsupported command type");
            return typedHandler->handle(real->payload);
        }
    };
    handlers[typeid(Command<T>)] = std::make_unique<Adapter>(handler);
}


Result HandlerRegistry::dispatch(std::unique_ptr<ICommand> cmd) {
    {
        auto it = handlers.find(typeid(*cmd));
        if (it == handlers.end()) throw std::runtime_error("未发现处理器");
        return it->second->handle(std::move(cmd));
    }
}
