#ifndef BOSSWESTFALEN_STRING_BUILDER_HPP
#define BOSSWESTFALEN_STRING_BUILDER_HPP

/*!
 * \file 
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version 0.1.0
 * \date 2018
 * \copyright MIT License 
 * > Copyright (c) 2018 Bosswestfalen (https://github.com/Bosswestfalen)
 * > 
 * > Permission is hereby granted, free of charge, to any person obtaining a copy
 * > of this software and associated documentation files (the "Software"), to deal
 * > in the Software without restriction, including without limitation the rights
 * > to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * > copies of the Software, and to permit persons to whom the Software is
 * > furnished to do so, subject to the following conditions:
 * > 
 * > The above copyright notice and this permission notice shall be included in all
 * > copies or substantial portions of the Software.
 * >
 * > THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * > IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * > FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * > AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * > LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * > OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * > SOFTWARE.
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
 *
 * \tparam Container The container that stores the added strings.
 * Default is `std::deque`
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
    void add(std::string&& input)
    {
        storage.emplace_back(std::move(input));
    }

    /// \copydoc add
    void add(std::string const& input)
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
     * \todo Improvement: Return storage.front() if size == 1
     * \todo Return immediatly if storage.empty() == true
     *
     * \return The concatenation of all stored strings.
     */ 
    std::string build() const
    {
        using size_type = std::string::size_type;
        auto op{[](size_type const size, std::string const& element)
        {
            return size + element.size();
        }};

        auto const size{std::accumulate(storage.cbegin(), storage.cend(), static_cast<size_type> (0), op)};
        std::string result;
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

