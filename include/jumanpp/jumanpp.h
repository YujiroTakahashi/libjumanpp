#pragma once

#include <string>
#include <vector>

namespace croco {

class  Jumanpp {
public:
    typedef struct _node {
        std::string surface;
        std::string reading;
        std::string baseform;
        std::string pos;
        std::string subpos;
        std::string conjType;
        std::string conjForm;
        std::string feat;
        std::string redirect;
        int32_t posId;
        int32_t subposId;
        int32_t conjTypeId;
        int32_t conjFormId;
        int32_t featflag;
    } Node;
private:
    void* _handle = nullptr;

public:
    Jumanpp(std::string modelpath);
    ~Jumanpp();
    std::vector<Node> analyze(std::string data);
    std::string wakati(std::string data);
}; // class Jumanpp

} // namespace croco

