#ifndef BOSSWESTFALEN_STRING_BUILDER_HPP
#define BOSSWESTFALEN_STRING_BUILDER_HPP

/// \file 
/// \author Bosswestfalen (https://github.com/Bosswestfalen)
///  \version 0.1.0
///  \date 2018
/// \copyright MIT License 
/// > Copyright (c) 2018 Bosswestfalen (https://github.com/Bosswestfalen)
/// > 
/// > Permission is hereby granted, free of charge, to any person obtaining a copy
/// > of this software and associated documentation files (the "Software"), to deal
/// > in the Software without restriction, including without limitation the rights
/// > to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// > copies of the Software, and to permit persons to whom the Software is
/// > furnished to do so, subject to the following conditions:
/// > 
/// > The above copyright notice and this permission notice shall be included in all
/// > copies or substantial portions of the Software.
/// >
/// > THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// > IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// > FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// > AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// > LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// > OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// > SOFTWARE.

#include <algorithm>
#include <cassert>
#include <deque>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>


/// \brief Bosswestfalen's namespace
/// \see https://github.com/Bosswestfalen
namespace bosswestfalen
{

/// \brief Helper namespace for type_traits needed for string conversion
namespace type_traits
{

/// Available if `T` is not convertible to `std::string`
template <typename T, 
          typename = std::void_t<>>
struct is_automatically_convertible : std::false_type
{
};

/// Available if `T` can be converted to `std::string` with `static_cast`
template <typename T>
struct is_automatically_convertible<T, std::void_t<
    std::enable_if_t
    <
        std::is_same_v
        <
            decltype(static_cast<std::string>(std::declval<T>()))
            ,
            std::string
        >
    >>> : std::true_type
{
};

/// Available if `T` (without reference) is no `arithmetic` built-in type (e.g. `int`)
template <typename T,
          typename = std::void_t<>>
struct is_builtin_type : std::false_type
{
};

/// Available if `T` (without reference) is an `arithmetic`built-in type (e.g. `int`)
template <typename T>
struct is_builtin_type<T, std::void_t<
    std::enable_if_t
    <
        std::is_arithmetic_v
        <
            std::remove_reference_t<T>
        >
    >>> : std::true_type
{
};

/// Available if `to_string(T)` is not callable or its result is not convertible to `std::string`
template <typename T,
          typename = std::void_t<>>
struct has_external_to_string : std::false_type
{
};

/// Available if `to_string(T)` can be called and its result is convertible to `std::string`
template <typename T>
struct has_external_to_string<T, std::void_t< 
    std::enable_if_t
    <
        is_automatically_convertible
        <
            decltype(to_string(std::declval<T>()))
        >::value
    >>> : std::true_type
{
};


/// Available if `stream << T` cannot be called (includes implicit type conversion)
template <typename T,
          typename = std::void_t<>>
struct has_stream_operator : std::false_type
{
};

/// Available if `stream << T` can be called (includes implicit type conversion)
template <typename T>
struct has_stream_operator<T, std::void_t<
    std::enable_if_t
    <
        std::is_same_v
        <
            std::ostream
            ,
            std::remove_reference_t
            <
                decltype(operator<<(std::declval<std::ostream>(), std::declval<T>()))
            >
        >
    >>> : std::true_type
{
};

}

#ifdef BOSSWESTFALEN_ONLY_FOR_DOXYGEN

/// \brief Convert a value of an arbitrary type to `std::string`.
///
/// To convert the value to `std::string` its type `T` must meet at
/// least one of the following requirements:
/// * `T` is an `arithmetic`type, like `bool`, `int`, `double`, etc.
/// * `static_cast<std::string>(T)` is possible
/// * a function `to_string(T)` exists
/// * `operator<<(ostream, U)` exists, where `U` is `T` or a type `T` can be implicitly converted to
/// The decision tree below shows the order of checks.
///
/// \tparam T The type of the input value.
/// \param value The value that will be converted to `std::string`.
///
/// \return `std::string` representation of input `value`.
///
/// \attention A function with this signature does not actually exist. 
///     Instead several `make_string` functions are checked and the 
///     *best match* is selected via SFINEA.
///
/// \startuml{to_string_decision.png} "How template type T is converted"
/// :bosswestfalen::make_string<T>(input);
/// -> Analyze template type T;
/// if (T is an arithmetic type) then (yes)
///   :return std::to_string(value);
///   stop
/// else (no)
///   if (static_cast<std::string>(T) possible) then (yes)
///     :return static_cast<std::string>(value);
///     stop
///   else (no)
///     if (to_string(T) is available and the result can be converted to `std::string`) then (yes)
///       : return bosswestfalen::make_string(to_string(value));
///       stop
///     else (no)
///     if (operator<<(std::ostream, T) is available) then (yes)
///       : ostream << value \nreturn ostream.str();
///       stop
///   else (no)
///     -> compilation fails;
///     stop
/// \enduml
template <typename T>
std::string make_string(T&& value);

#else // BOSSWESTFALEN_ONLY_FOR_DOXYGEN

template <typename T>
auto make_string(T&& value) -> std::enable_if_t
    <
        type_traits::is_builtin_type<T>::value
    ,
    std::string
    >
{
    return std::to_string(value);
}

template <typename T>
auto make_string(T&& value) -> std::enable_if_t
    <
        type_traits::is_automatically_convertible<T>::value
    , 
    std::string
    >
{
    return static_cast<std::string>(value);
}

template <typename T>
auto make_string(T&& value) -> std::enable_if_t
    <
        type_traits::has_external_to_string<T>::value
        and not type_traits::is_automatically_convertible<T>::value
    ,
    std::string
    >
{
    return make_string(to_string(std::forward<T>(value)));
}

template <typename T>
auto make_string(T&& value) -> std::enable_if_t
    <
        type_traits::has_stream_operator<T>::value
        and not type_traits::is_builtin_type<T>::value
        and not type_traits::is_automatically_convertible<T>::value
        and not type_traits::has_external_to_string<T>::value
    ,
    std::string
    >
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#endif // BOSSWESTFALEN_ONLY_FOR_DOXYGEN


/// \brief The `basic_string_builder` allows to easily concatenate strings.
///
/// Strings are collected and concatenated on demand.
/// Concatenating *a*, *b*, and *c* yields the string *abc*.
///
/// \tparam Cont The container used to store the `std::strings`.
///     Must support 
///     * `emplace_back`
///     * `back`, 
///     * `pop_back`
///     * `std::cbegin`
///     * `std::cend`
///
/// \note `basic_string_builder` is not thread-safe.
template <template <typename> typename Cont>
class basic_string_builder final
{
  public:
    /// Default Ctor is sufficient.
    basic_string_builder() = default;

    /// Nothing special to do on destruction.
    ~basic_string_builder() = default;

    /// \brief Add new content to the `basic_string_builder`.
    ///
    /// If required *input* will be converted to a std::string.
    /// It then is stored internally and will be used in `build()`.
    ///
    /// \tparam T The type of the input value.
    /// \param value The value that will be converted to `std::string`
    ///     and added to the internal storage.
    ///
    /// \throws std::length_error if the size of the result of `build()`
    ///     would be larger than the `std::string::max_size()`
    /// \throws any exception that occurs during creation and storing
    ///     (e.g. exceptions when creating the `std::string` or adding it
    ///     to the container, with `emplace_back`)
    template <typename T>
    void add(T&& value)
    {
        storage.emplace_back(bosswestfalen::make_string(std::forward<T>(value)));

        auto const new_size = storage.back().size();
        static auto max_size = storage.back().max_size();

        if (result_size > max_size - new_size)
        {
            storage.pop_back();
            throw std::length_error{""};
        }

        result_size += new_size;
    }

    /// \brief Concatenate stored strings.
    ///
    /// All strings added so far will be concatenated without any delimiter.
    /// Stored strings *a*, *b*, and *c* will result in *abc*.
    /// 
    /// \note The result is not stored.
    /// Additional calls to `build()` will result in re-building, even if nothing changed.
    ///
    /// \return The concatenation of all stored strings.
    std::string build() const
    {
        if (storage.empty())
        {
            return std::string{};
        }

        if (storage.size() == 1)
        {
            return storage.front();
        }

        return concatenate();
    }

  private:
    /// Size of the resulting string
    std::string::size_type result_size{0};
    /// Internal storage
    Cont<std::string> storage{};

    /// Concatenate stored strings.
    std::string concatenate() const
    { 
        std::string result;
        result.reserve(result_size);
        std::for_each(std::cbegin(storage), std::cend(storage), [&result](auto const& element)
        {
            result.append(element);
        });
        return result;
    }
};

using string_builder = basic_string_builder<std::deque>;

}

#endif

