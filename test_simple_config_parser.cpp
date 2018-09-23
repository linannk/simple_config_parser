#include "simple_config_parser.h"

#include <fstream>
#include <istream>
#include <iostream>


static void dump_file(const std::string& filename);

int main(int argc, char** argv)
{
    if (argc >= 2) {
        dump_file(argv[1]);
    }

    return 0;
}

static void dump_file(const std::string& filename)
{
    auto config = ParseConfigurationFromFile(filename);
    for (auto s : config)
    {
        std::cout << "[" << s.first << "]" << std::endl;
        for (auto kv : s.second) {
            std::cout << kv.first << "  ->  " << kv.second << std::endl;
        }
        std::cout << "###### END ######" << std::endl;
    }

    SerializeConfigurationToFile(config, "tmp.txt");
}

