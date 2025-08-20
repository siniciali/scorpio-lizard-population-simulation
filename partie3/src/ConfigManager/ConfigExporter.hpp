/*
 * infosv
 * feb 2013
 * Marco Antognini
 */

#ifndef INFOSV_CONFIGEXPORTER_HPP
#define INFOSV_CONFIGEXPORTER_HPP

#include <string>
#include <map>
#include <vector>

/*!
 * @brief Export cfg to classic header config
 *
 * @see ConfigManager
 */
class ConfigExporter
{
public:
    ConfigExporter();

    /*!
     * @brief Copy not allowed
     */
    ConfigExporter(ConfigExporter const&) = delete;

    /*!
     * @brief Copy not allowed
     */
    ConfigExporter& operator=(ConfigExporter const&) = delete;

    /*!
     * @brief Export the config.
     *
     * @param filename config file that should be read
     * @param outputfilename output filename (will be overriden)
     * @return true if the export was successful, false overwise
     */
    bool operator()(std::string const& filename, std::string const& outputfilename);

private:
    /*!
     * @brief Perform the main logic of load()
     *
     * @param input data's input, should be valid
     * @return true if success
     */
    bool read(std::istream& input, std::ostream& output);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging an integer
     * @return true if value is an integer
     */
    bool readInt(std::string const& key, std::string const& value, std::ostream& output);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging a real
     * @return true if value is a real
     */
    bool readDouble(std::string const& key, std::string const& value, std::ostream& output);

    /*!
     * @brief Register (key, value)
     *
     * @param key variable's id
     * @param value a string
     * @return true (no error possible)
     */
    bool readString(std::string const& key, std::string const& value, std::ostream& output);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging a bool
     * @return true if value is a bool
     */
    bool readBool(std::string const& key, std::string const& value, std::ostream& output);

    /*!
     * @brief Echoes a message on stderr.
     *
     * @param message error message to print
     */
    void reportError(std::string const& message) const;
};

#endif // INFOSV_CONFIGEXPORTER_HPP
