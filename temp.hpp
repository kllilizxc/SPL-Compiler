//
// Created by 54179 on 2017/6/3.
//

#ifndef SPL_COMPILER_TEMP_HPP
#define SPL_COMPILER_TEMP_HPP

#include <string>
#include <map>

class Temp {
public:
    Temp() {
        name = std::to_string(count++);
        tempMap[name] = *this;
    };

    Temp& lookUp(std::string name) {
        return tempMap[name];
    }
private:
    std::string name;
    static int count = 100;
    static std::map<std::string, Temp&> tempMap;
};

class Label {
public:
    Label() {
        name = std::to_string(count++);
    }
private:
    std::string name;
    static int count = 0;
};

#endif //SPL_COMPILER_TEMP_HPP
