/*
 * infosv
 * jan 2013
 * Marco Antognini
 */

#ifndef INFOSV_CONFIGMANAGER_HPP
#define INFOSV_CONFIGMANAGER_HPP

#include <string>
#include <map>
#include <vector>

/*!
 * @brief Manage variables for application configuration loaded from a file.
 *
 * Each line of the configuration file has the following format :
 *
 *     $NAME:$TYPE:$VALUE
 *
 * where $TYPE can be "int", "double", "string" or "bool".
 *
 * If the specified type is "bool", then the following values map to true :
 *  true, t, yes, y
 * and the follwing map to false :
 *  false, f, no, n
 * Note that the value is case insensitive and that any other value is considered erroneous.
 */
class ConfigManager
{
public:
    /*!
     * @brief Default constructor.
     *
     * Default int is 0, default double is 0.0, default string is "" (empty string)
     * and default boolean is false.
     */
    ConfigManager();

    /*!
     * @brief Customized constructor.
     *
     * @param defaultInt default int value
     * @param defaultDouble default double value
     * @param defaultString default string value
     * @param defaultBool default boolean value
     */
    ConfigManager(int defaultInt, double defaultDouble, std::string const& defaultString, bool defaultBool);

    /*!
     * @brief Copy not allowed
     */
    ConfigManager(ConfigManager const&) = delete;

    /*!
     * @brief Copy not allowed
     */
    ConfigManager& operator=(ConfigManager const&) = delete;

    /*!
     * @brief Load the config.
     *
     * Variable are overriden if read multiple time (the last value is kept).
     * Error are printed on stderr and no exception is thrown.
     *
     * @param filename config file that should be read
     * @param clear if true the manager is cleared before reading the file
     * @return true if the loading was successful, false overwise
     */
    bool load(std::string const& filename, bool clear = false);

    /*!
     * @brief Remove all config variable.
     */
    void clear();

    /*!
     * @brief Get an integer value
     *
     * @param key name of the variable that should be returned
     * @return the integer value associated with key, or the default integer value if key doesn't map to a value
     */
    int getInt(std::string const& key) const;

    /*!
     * @brief Set an integer value
     *
     * @param key name of the variable that should be added/modified
     * @param value value that should be associated with key
     */
    void setInt(std::string const& key, int value);

    /*!
     * @brief Set the default integer value
     *
     * @param defaultInt default value
     */
    void setDefaultInt(int defaultInt);

    /*!
     * @brief Get an real value
     *
     * @param key name of the variable that should be returned
     * @return the real value associated with key, or the default read value if key doesn't map to a value
     */
    double getDouble(std::string const& key) const;

    /*!
     * @brief Set an real value
     *
     * @param key name of the variable that should be added/modified
     * @param value value that should be associated with key
     */
    void setDouble(std::string const& key, double value);

    /*!
     * @brief Set the default real value
     *
     * @param defaultDouble default value
     */
    void setDefaultDouble(double defaultDouble);

    /*!
     * @brief Get an string value
     *
     * @param key name of the variable that should be returned
     * @return the string value associated with key, or the default string value if key doesn't map to a value
     */
    std::string getString(std::string const& key) const;

    /*!
     * @brief Set an string value
     *
     * @param key name of the variable that should be added/modified
     * @param value value that should be associated with key
     */
    void setString(std::string const& key, std::string const& value);

    /*!
     * @brief Set the default string value
     *
     * @param defaultString default value
     */
    void setDefaultString(std::string const& defaultString);

    /*!
     * @brief Get a boolean value
     *
     * @param key name of the variable that should be returned
     * @return the boolean value associated with key, or the default boolean value if key doesn't map to a value
     */
    bool getBool(std::string const& key) const;

    /*!
     * @brief Set an boolean value
     *
     * @param key name of the variable that should be added/modified
     * @param value value that should be associated with key
     */
    void setBool(std::string const& key, bool value);

    /*!
     * @brief Set the default boolean value
     *
     * @param defaultBool default value
     */
    void setDefaultBool(bool defaultBool);

private:
    /*!
     * @brief Perform the main logic of load()
     *
     * @param input data's input, should be valid
     * @return true if success
     */
    bool read(std::istream& input);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging an integer
     * @return true if value is an integer
     */
    bool readInt(std::string const& key, std::string const& value);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging a real
     * @return true if value is a real
     */
    bool readDouble(std::string const& key, std::string const& value);

    /*!
     * @brief Register (key, value)
     *
     * @param key variable's id
     * @param value a string
     * @return true (no error possible)
     */
    bool readString(std::string const& key, std::string const& value);

    /*!
     * @brief Register (key, value)
     *
     * Report conversion error with reportError()
     *
     * @param key variable's id
     * @param value string represenging a bool
     * @return true if value is a bool
     */
    bool readBool(std::string const& key, std::string const& value);

    /*!
     * @brief Echoes a message on stderr.
     *
     * @param message error message to print
     */
    void reportError(std::string const& message) const;

private:
    typedef std::map<std::string, int> IntConfig; ///< a simple alias for int dictionary
    typedef std::map<std::string, double> DoubleConfig; ///< a simple alias for double dictionary
    typedef std::map<std::string, std::string> StringConfig; ///< a simple alias for string dictionary
    typedef std::map<std::string, bool> BoolConfig; ///< a simple alias for bool dictionary

    IntConfig mInts; ///< store the integer config variables
    DoubleConfig mDoubles; ///< store the real config variables
    StringConfig mStrings; ///< store the string config variables
    BoolConfig mBools; ///< store the boolean config variables

    int mDefaultInt; ///< default integer value
    double mDefaultDouble; ///< default real value
    std::string mDefaultString; ///< default string value
    bool mDefaultBool; ///< default boolean value
};

#endif // INFOSV_CONFIGMANAGER_HPP
