//
// Created by Ko-chieh Yin on 9/27/25.
//

#include "Parser.h"



std::unique_ptr<ICommand> Parser::parse(const std::string &raw) {
    std::istringstream iss(raw);
    std::string op;
    iss >> op;

    if (op == "@LOCK") {
        std::string cmdType;
        iss >> cmdType;

        if (cmdType == "ACQ") {

        }
    }

    throw std::runtime_error("未知命令");
}
