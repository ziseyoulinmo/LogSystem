/*
 通用功能实现：
        1.获取当前时间戳；
        2.判断文件是否存在；
        3.根据分隔符提取文件的路径；  ./aaa/bbb/c.txt   --->   ./aaa/bbb/
        4.创建目录；                  ./aaa/bbb
 */

#include<iostream>
#include<ctime>
#include<string>
#include<sys/stat.h>


namespace util{
    class Date{
        public:
        static size_t now()
        {
            return (size_t)time(nullptr);
        }
    };

    class File{
        public:
        static bool exist(const std::string &name)
        {
            struct stat st;
            return stat(name.c_str(),&st) == 0;
        }

        static std::string path(const std::string &name)
        {
            if(name.empty())
                return ".";
            size_t pos = name.find_last_of("/\\");
            if(pos == std::string::npos)
                return ".";
            return name.substr(0,pos + 1);
        }

        static void createDirectory(const std::string &path)
        {
            if(path.empty())
                return;
            if(exist(path))
                return;
            size_t pos = 0,index = 0;
            while(index < path.size())
            {
                pos = path.find_first_of("/\\",index);
                if(pos == std::string::npos)
                {
                    mkdir(path.c_str(),0755);
                    return;
                }
                if(pos == index)
                {
                    index = pos + 1;
                    continue;
                }
                std::string subdir = path.substr(0,pos);
                if(subdir == "." || subdir == "..")
                {
                    index = pos + 1;
                    continue;
                }
                if(exist(subdir))
                {
                    index = pos + 1;
                    continue;
                }
                mkdir(subdir.c_str(),0755);
                index = pos + 1;
            }
        }
    };
}
