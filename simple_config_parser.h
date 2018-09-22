#ifndef _LN_SIMPLE_CONFIG_PARSER_H_
#define _LN_SIMPLE_CONFIG_PARSER_H_

#include <map>
#include <vector>
#include <string>
#include <utility>

#include <iosfwd>

/**********************************************!
 * \brief ParseConfigurationFromIStream
 * Parse file like:
 *
 * [ config ]
 * version = v1.9.0
 * name = abc
 * bitcode
 * format = yml
 * 
 * [ zlib ]
 * version = 1.2
 * url = git@gitlab.zlib.com
 * method = git
 * 
 * # this comment line
 *
 * [ test ]
 * section-name = test
 * section-key  = abc
 *
 *********************************************/
std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromIStream(std::istream& is);

std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromFile(const std::string& filename);

#endif // _LN_SIMPLE_CONFIG_PARSER_H_

