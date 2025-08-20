/*
 * infosv
 * jan 2013
 * Marco Antognini
 */

#include "ConfigExporter.hpp"
#include "../Utility/Utility.hpp"

#include <iostream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <ios>

int main(int, char** argv)
{
    // Get the launch command (e.g. ./build/application)
    std::string appDirectory = argv[0];
    // and keep only the directory (i.e. until the last '/')
    std::string::size_type lastSlashPos = appDirectory.rfind('/');
    if (lastSlashPos == std::string::npos) {
        appDirectory = "./";
    } else {
        appDirectory = appDirectory.substr(0, lastSlashPos + 1);
    }

    // Get the input filename
    std::cout << "You are in " << appDirectory << std::endl;
    std::cout << "Enter the input filename : ";
    std::string input;
    std::getline(std::cin, input);

    // And output
    std::cout << "Enter the output filename : ";
    std::string output;
    std::getline(std::cin, output);

    ConfigExporter ce;
    bool const state = ce(appDirectory + input, appDirectory + output);

    std::cout << std::boolalpha;
    std::cout << "Is everything right ? " << state << std::endl;

    return EXIT_SUCCESS;
}

ConfigExporter::ConfigExporter()
{
    // Nothing
}

bool ConfigExporter::operator()(std::string const& filename, std::string const& outputfilename)
{
    std::ifstream input(filename);
    std::ofstream output(outputfilename);

    if (input && output) {
        return read(input, output);
    } else {
        reportError("Couldn't open " + filename);
        return false;
    }
}

bool ConfigExporter::read(std::istream& input, std::ostream& output)
{
    // until an error is found we have a success.
    bool success = true;

    char const delim = ':';

    // inclusion guard
    output << "#ifndef CONFIGURATION\n#define CONFIGURATION\n\n";

    // Read each line at a time
    std::string line;
    while (std::getline(input, line)) {
        // Skip empty line without complaining
        if (line == "") {
            output << std::endl;
            continue;
        }

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
                success = readInt(key, value, output) && success;
            } else if (type == "double") {
                success = readDouble(key, value, output) && success;
            } else if (type == "string") {
                success = readString(key, value, output) && success;
            } else if (type == "bool") {
                success = readBool(key, value, output) && success;
            } else {
                reportError("Invalid type [" + type + "] on line [" + line + "]");
                success = false;
            }
        }
    }

    // Endif
    output << "#endif\n";

    return success;
}

bool ConfigExporter::readInt(std::string const& key, std::string const& value, std::ostream& output)
try
{
    std::size_t pos = 0;
    int const integer = std::stoi(value, &pos);
    if (pos == value.size()) {
        // Write it to the output file
        output << "int const " << key << " = " << integer << ";\n";
        return output.good();
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

bool ConfigExporter::readDouble(std::string const& key, std::string const& value, std::ostream& output)
try
{
    std::size_t pos = 0;
    double const real = std::stod(value, &pos);
    if (pos == value.size()) {
        // Write it to the output file
        output << "double const " << key << " = " << real << ";\n";
        return output.good();
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

bool ConfigExporter::readString(std::string const& key, std::string const& value, std::ostream& output)
{
    // Write it to the output file
    output << "std::string const " << key << " = \"" << value << "\";\n";
    return output.good();
}

bool ConfigExporter::readBool(std::string const& key, std::string const& value, std::ostream& output)
{
    std::string lowercase = value;
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(),
                   std::bind2nd(std::ptr_fun(std::tolower<char>), std::locale("")));

    if (lowercase == "true" || lowercase == "t" || lowercase == "yes" || lowercase == "y") {
        // Write it to the output file
        output << "bool const " << key << " = true;\n";
        return output.good();
    } else if (lowercase == "false" || lowercase == "f" || lowercase == "no" || lowercase == "n") {
        // Write it to the output file
        output << "bool const " << key << " = false;\n";
        return output.good();
    } else {
        reportError("value [" + value + "] is not a valid boolean value");
        return false;
    }
}

void ConfigExporter::reportError(std::string const& message) const
{
    std::cerr << "ConfigManager has encounter an error : " << message << std::endl;
}


