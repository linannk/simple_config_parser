# simple_config_parser
Parse configuration file like .ini file.

## Example:
```sh
[ config ]
name = config
version = test

# This is comment
[ version ]
version-code = 1.23.4
abc = enabled
bitcode = 

```

## Interfaces:
```c++
std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromIStream(std::istream& is);

std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromFile(const std::string& filename);

```

## Usage example
See test_simple_config_parser.cpp

## note
The `ParseConfigurationFrom*` functions will not merge two or more sections with the same name.

## How to build?
```sh
$ cd simple_config_parser
$ mkdir build && cd build
$ cmake .. && make
$ ./test_simple_config_parser ../1.txt
```

