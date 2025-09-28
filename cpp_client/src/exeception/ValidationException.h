//
// Created by Ko-chieh Yin on 9/28/25.
//

#ifndef DISTRIBUTED_LOCK_DEMO_VALIDATIONEXCEPTION_H
#define DISTRIBUTED_LOCK_DEMO_VALIDATIONEXCEPTION_H
#include <stdexcept>

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif //DISTRIBUTED_LOCK_DEMO_VALIDATIONEXCEPTION_H