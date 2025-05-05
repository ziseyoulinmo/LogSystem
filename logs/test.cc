#include"util.hpp"

int main()
{
    std::cout<<util::Date::now()<<std::endl;
    std::string s = "./abc/bcd/a.txt";
    util::File::createDirectory(util::File::path(s));
    return 0;
}
