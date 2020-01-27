#include <fstream>
#include <iostream>

#include <jumanpp/jumanpp.h>

int main(int argc, const char** argv)
{
    croco::Jumanpp jpp("/usr/local/libexec/jumanpp/jumandic.jppmdl");

    std::string input("このアボガドには魅力がたっぷりと詰まっている。");
    std::vector<croco::Jumanpp::Node> retval = jpp.analyze(input);

    for (auto &val : retval) {
        std::cout << val.surface
                  << "::" << val.reading
                  << " " << val.baseform
                  << " " << val.pos << " " << val.posId
                  << " " << val.subpos << " " << val.subposId
                  << " " << val.conjType << " " << val.conjTypeId
                  << " " << val.conjForm << " " << val.conjFormId
                  << " " << val.feat << " " << val.featflag << "\t" << val.redirect << "\n";
    }
    std::cout << std::endl;

    std::cout << jpp.wakati("魅力がたっぷりと詰まっている。") << std::endl;

    return 0;
}
