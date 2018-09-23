#include <vector>
#include <utility>
#include <string>
#include <map>
#include <algorithm>

#include <istream>
#include <fstream>

#include <cctype>
#include <cstring>

static std::string lstrip(const std::string& str)
{
    for (std::size_t i = 0; i < str.size(); ++i)
    {
        if (!std::isspace(str[i])) {
            return str.substr(i);
        }
    }
    return std::string();
}

static std::string rstrip(const std::string& str)
{
    std::size_t non_space_idx = str.size();
    for (; non_space_idx > 0; --non_space_idx)
    {
        if (!std::isspace(str[non_space_idx - 1])) {
            return str.substr(0, non_space_idx);
        }
    }
    return std::string();
}

static std::string strip(const std::string& str)
{
    std::size_t non_space_idx_beg = 0;
    std::size_t non_space_idx_end = str.size();
    while (non_space_idx_beg < non_space_idx_end)
    {
        if (!std::isspace(str[non_space_idx_beg])
            && !std::isspace(str[non_space_idx_end - 1]))
        {
            return str.substr(non_space_idx_beg, non_space_idx_end - non_space_idx_beg);
        }
        else if (std::isspace(str[non_space_idx_beg])) {
            ++non_space_idx_beg;
        }
        else {
            --non_space_idx_end;
        }
    }
    return std::string();
}

static bool is_comment(
    const std::string& line,
    size_t* idx = NULL)
{
    for (size_t i = 0; i < line.size(); ++i)
    {
        if (std::isspace(line[i])) {
            continue;
        }
        if (line[i] == '#') {
            return true;
        }
        else {
            if (idx) { *idx = i; }
            return false;
        }
    }
    return true;
}

static std::string parse_section(const std::string& str, size_t beg)
{
    std::string ret;
    std::size_t non_space_idx = beg;
    for (; non_space_idx < str.size(); ++non_space_idx)
    {
        if (std::isspace(str[non_space_idx])) {
            continue;
        }
        else if (str[non_space_idx] == ']') {
            return std::string();
        }
        else {
            ret.push_back(str[non_space_idx]);
            break;
        }
    }
    for (std::size_t i = non_space_idx + 1; i < str.size(); ++i)
    {
        if (str[i] == ']') {
            break;
        }
        else {
            ret.push_back(str[i]);
        }
    }
    return rstrip(ret);
}

static void parse_pair(const std::string& str, std::string* key, std::string* value)
{
    const std::size_t equal_sign_idx = str.find_first_of("=:");
    if (equal_sign_idx == std::string::npos)
    {
        *key = strip(str);
    }
    else
    {
        *key   = strip(str.substr(0, equal_sign_idx));
        *value = strip(str.substr(equal_sign_idx + 1));
    }
}

std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromIStream(std::istream& is)
{
    using std::map;
    using std::pair;
    using std::vector;
    using std::string;

    vector<pair<string, map<string, string>>> result;

    string tmp_name;
    map<string, string> tmp_kv;
   
    string tmp_line;
    std::size_t idx = 0;
    while (std::getline(is, tmp_line))
    {
        if (is_comment(tmp_line, &idx)) {
            continue;
        }
        if (tmp_line[idx] == '[') {
            std::string name = parse_section(tmp_line, idx + 1);
            if (name.empty()) {
                continue;
            }
            if (tmp_kv.empty()) {
                tmp_name = name;
            }
            else {
                result.push_back({tmp_name, tmp_kv});
                tmp_name = name;
                tmp_kv.clear();
            }
        }
        else {
            std::string key, value;
            parse_pair(tmp_line, &key, &value);
            tmp_kv.emplace(key, value);
        }
    }
    if (!tmp_name.empty() && !tmp_kv.empty()) {
        result.push_back({tmp_name, tmp_kv});
    }
    return result;
}

std::vector<std::pair<std::string, std::map<std::string, std::string>>>
ParseConfigurationFromFile(const std::string& filename)
{
    std::ifstream configuration_file(filename);
    return ParseConfigurationFromIStream(configuration_file);
}

bool SerializeConfigurationToOStream(const std::vector<std::pair<std::string, std::map<std::string, std::string>>>& config, std::ostream& os)
{
    for (const auto& c : config)
    {
        os << "[ " << c.first << " ]" << std::endl;
        for (const auto& item : c.second)
        {
            os << item.first << " = " << item.second << std::endl;
        }
        os << std::endl;
    }
    return os.good();
}

bool SerializeConfigurationToFile(const std::vector<std::pair<std::string, std::map<std::string, std::string>>>& config, const std::string& filename)
{
    std::ofstream configuration_fs(filename);
    if (!configuration_fs.is_open()) {
        return false;
    }
    return SerializeConfigurationToOStream(config, configuration_fs);
}

