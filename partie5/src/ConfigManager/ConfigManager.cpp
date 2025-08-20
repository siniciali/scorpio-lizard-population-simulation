/*
 * infosv
 * jan 2013
 * Marco Antognini
 */

#include "ConfigManager.hpp"
#include "../Utility/Utility.hpp"

#include <iostream>
#include <fstream>
#include <iostream>
#include <stdexcept>

ConfigManager::ConfigManager()
    : ConfigManager(0, 0.0, "", false)
{
    /* That's it */
}

ConfigManager::ConfigManager(int defaultInt, double defaultDouble, std::string const& defaultString, bool defaultBool)
    : mDefaultInt(defaultInt)
    , mDefaultDouble(defaultDouble)
    , mDefaultString(defaultString)
    , mDefaultBool(defaultBool)
{
    /* That's it */
}

bool ConfigManager::load(std::string const& filename, bool clearBeforeLoad)
{
    if (clearBeforeLoad) clear();

    std::ifstream input(filename);

    if (input) {
        return read(input);
    } else {
        reportError("Couldn't open " + filename);
        return false;
    }
}

void ConfigManager::clear()
{
    mInts.clear();
    mDoubles.clear();
    mStrings.clear();
    mBools.clear();
}

int ConfigManager::getInt(const std::string &key) const
{
    auto const& it = mInts.find(key);
    if (it != mInts.end()) return it->second;
    else {
        reportError("Integer for " + key + " is unknown");
        return mDefaultInt;
    }
}

void ConfigManager::setInt(const std::string &key, int value)
{
    mInts[key] = value;
}

void ConfigManager::setDefaultInt(int defaultInt)
{
    mDefaultInt = defaultInt;
}

double ConfigManager::getDouble(const std::string &key) const
{
    auto const& it = mDoubles.find(key);
    if (it != mDoubles.end()) return it->second;
    else {
        reportError("Real for " + key + " is unknown");
        return mDefaultDouble;
    }
}

void ConfigManager::setDouble(const std::string &key, double value)
{
    mDoubles[key] = value;
}

void ConfigManager::setDefaultDouble(double defaultDouble)
{
    mDefaultDouble = defaultDouble;
}

std::string ConfigManager::getString(const std::string &key) const
{
    auto const& it = mStrings.find(key);
    if (it != mStrings.end()) return it->second;
    else {
        reportError("String for " + key + " is unknown");
        return mDefaultString;
    }
}

void ConfigManager::setString(const std::string &key, std::string const& value)
{
    mStrings[key] = value;
}

void ConfigManager::setDefaultString(std::string const& defaultString)
{
    mDefaultString = defaultString;
}

bool ConfigManager::getBool(std::string const& key) const
{
    auto const& it = mBools.find(key);
    if (it != mBools.end()) return it->second;
    else {
        reportError("Real for " + key + " is unknown");
        return mDefaultBool;
    }
}

void ConfigManager::setBool(std::string const& key, bool value)
{
    mBools[key] = value;
}

void ConfigManager::setDefaultBool(bool defaultBool)
{
    mDefaultBool = defaultBool;
}

bool ConfigManager::read(std::istream& input)
{
    // until an error is found we have a success.
    bool success = true;

    char const delim = ':';

    // Read each line at a time
    std::string line;
    while (std::getline(input, line)) {
        // Skip empty line without complaining
        if (line == "") continue;

        // Split the line to get the key, type and value substrings
        std::vector<std::string> const tokens = split(line, delim);

        // We need three tokens
        if (tokens.size() != 3) {
            reportError("Invalid line [" + line + "]");
            success = false;
        } else {
            std::string key   = tokens[0];
            std::string type  = tokens[1];
            std::string value = tokens[2];

            // Make sure the substring are valid
            if (key == "") {
                reportError("Invalid variable identifier [" + key + "] on line [" + line + "]");
                success = false;
            } else if (type == "int") {
                success = readInt(key, value) && success;
            } else if (type == "double") {
                success = readDouble(key, value) && success;
            } else if (type == "string") {
                success = readString(key, value) && success;
            } else if (type == "bool") {
                success = readBool(key, value) && success;
            } else {
                reportError("Invalid type [" + type + "] on line [" + line + "]");
                success = false;
            }
        }
    }

    return success;
}

bool ConfigManager::readInt(std::string const& key, std::string const& value)
try
{
    std::size_t pos = 0;
    int const integer = std::stoi(value, &pos);
    if (pos == value.size()) {
        setInt(key, integer);
        return true;
    } else {
        reportError("value [" + value + "] is not an integer at " + value[pos]);
        return false;
    }
} catch (std::invalid_argument e)
{
    reportError("value [" + value + "] is not an integer");
    return false;
} catch (std::out_of_range e)
{
    reportError("value [" + value + "] is out of range");
    return false;
}

bool ConfigManager::readDouble(std::string const& key, std::string const& value)
try
{
    std::size_t pos = 0;
    double const real = std::stod(value, &pos);
    if (pos == value.size()) {
        setDouble(key, real);
        return true;
    } else {
        reportError("value [" + value + "] is not a real at " + value[pos]);
        return false;
    }
} catch (std::invalid_argument e)
{
    reportError("value [" + value + "] is not a real");
    return false;
} catch (std::out_of_range e)
{
    reportError("value [" + value + "] is out of range");
    return false;
}

bool ConfigManager::readString(std::string const& key, std::string const& value)
{
    setString(key, value);
    return true;
}

bool ConfigManager::readBool(std::string const& key, std::string const& value)
{
    std::string lowercase = value;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(),
                   std::bind2nd(std::ptr_fun(std::tolower<char>), std::locale("")));

    if (lowercase == "true" || lowercase == "t" || lowercase == "yes" || lowercase == "y") {
        setBool(key, true);
        return true;
    } else if (lowercase == "false" || lowercase == "f" || lowercase == "no" || lowercase == "n") {
        setBool(key, false);
        return true;
    } else {
        reportError("value [" + value + "] is not a valid boolean value");
        return false;
    }
}

void ConfigManager::reportError(std::string const& message) const
{
    std::cerr << "ConfigManager has encounter an error : " << message << std::endl;
}


