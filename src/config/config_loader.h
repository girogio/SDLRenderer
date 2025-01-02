#include <string>

class ConfigLoader
{
public:
    ConfigLoader() = default;
    virtual ~ConfigLoader() = default;

    virtual bool LoadConfig(const std::string &config_file) = 0;
    virtual bool SaveConfig(const std::string &config_file) = 0;
    virtual bool GetConfig(const std::string &key, std::string *value) = 0;
    virtual bool SetConfig(const std::string &key, const std::string &value) = 0;
};
