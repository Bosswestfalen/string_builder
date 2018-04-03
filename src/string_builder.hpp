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
#include <numeric>
#include <string>
#include <utility>
#include <deque>


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
     * \param input The string that will be added to the `string_builder`'s internal storage.
     */
    void add(std::string const& input)
    {
        storage.push_back(input);
    }

    /*!
     * \copydoc add
     */
    void add(std::string&& input)
    {
        storage.emplace_back(std::move(input));
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
     * \todo Improvement: Return storage.front() if size == 1
     * \todo Return immediatly if storage.empty() == true
     *
     * \return The concatenation of all stored strings.
     */ 
    std::string build() const
    {
        std::string result;
        using size_type = std::string::size_type;
        auto op{[](size_type const size, std::string const& element)
        {
            return size + element.size();
        }};

        auto const size{std::accumulate(storage.cbegin(), storage.cend(), static_cast<size_type> (0), op)};
        result.reserve(size);
        std::for_each(storage.cbegin(), storage.cend(), [&result](auto const& element)
        {
            result.append(element);
        });
        return result;
    }

  private:
    /// Internal storage
    std::deque<std::string> storage{};

};

}

#endif

