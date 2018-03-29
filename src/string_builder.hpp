#ifndef BOSSWESTFALEN_STRING_BUILDER_HPP
#define BOSSWESTFALEN_STRING_BUILDER_HPP

/*!
 * \file 
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version @PROJECT_VERSION@
 * \date 2018
 * \copyright @LICENSE@
 */

#include <algorithm>
#include <cassert>
#include <list>
#include <numeric>
#include <string>


/*!
 * \brief Bosswestfalen's namespace
 * @see https://github.com/Bosswestfalen
 */
namespace bosswestfalen
{

/*!
 * \brief The `string_builder` allows to easily concatenate strings.
 *
 * Strings are collected and concatenated on demand.
 * Concatenating *a*, *b*, and *c* yields the string *abc*.
 *
 * \note `string_builder` is not thread-safe.
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

    /*!
     * \brief Add new content to the `string_builder`.
     *
     * *input* is stored internally and will be used in `build()`.
     *
     * \todo Other versions? (&&, copy)
     *
     * \param input The string that will be added to the `string_builder`'s internal storage.
     */
    void add(const std::string& input)
    {
        storage.push_back(input);
    }

    /*!
     * \brief Concatenate stored strings.
     *
     * All strings added so far will be concatenated without any delimiter.
     * Stored strings *a*, *b*, and *c* will result in *abc*.
     * 
     * \note The result is not stored.
     * Additional calls to `build()` will result in re-building, even if nothing changed.
     *
     * \todo Include error checks.
     *
     * \return The concatenation of all stored strings.
     */ 
    std::string build() const
    {
        std::string result;
        using size_type = std::string::size_type;
        auto op = [](const size_type size, const std::string& element)
        {
            return size + element.size();
        };

        const auto size = std::accumulate(storage.cbegin(), storage.cend(), static_cast<size_type> (0), op);
        result.reserve(size);
        std::for_each(storage.cbegin(), storage.cend(), [&result](const auto& element)
        {
            result.append(element);
        });
        return result;
    }

  private:
    /// Internal storage
    /// \todo Use something else?
    std::list<std::string> storage{};

};

}

#endif

