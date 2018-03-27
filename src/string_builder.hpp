#ifndef BOSSWESTFALEN_STRING_BUILDER_HPP
#define BOSSWESTFALEN_STRING_BUILDER_HPP

/*!
 * \file 
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version @PROJECT_VERSION@
 * \date 2018
 * \copyright @LICENSE@
 */

#include <string>

/*!
 * \brief Bosswestfalen's namespace
 * @see https://github.com/Bosswestfalen
 */
namespace bosswestfalen
{

/*!
 * \brief The string_builder allows to easily concatenate strings.
 *
 * Strings are collected and concatenated on demand.
 * Concatenating a, b, and c yields the string abc.
 *
 * \note string_builder is not thread-safe.
 * 
 * \todo Go into detail, when this class evolves.
 */
class string_builder final
{
  public:
    /// Default Ctor is sufficient.
    string_builder() = default;

    /// Nothing special to do on destruction.
    ~string_builder() = default;

    //void add();
   
    /*!
     * \brief Concatenate stored strings.
     *
     * All strings added so far will be concatenated without any delimiter.
     * Stored strings *a*, *b*, and *c* will result in *abc*.
     * 
     * \note The result is not stored.
     * Additional calls to `build()` will result in re-building, even if nothing changed.
     *
     * \return The concatenation of all stored strings.
     */ 
    std::string build() const
    {
        return std::string{""};
    }

  private:
};

}

#endif

