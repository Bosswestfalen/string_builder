#ifndef BOSSWESTFALEN_STRING_BUILDER_HPP
#define BOSSWESTFALEN_STRING_BUILDER_HPP

/*!
 * \file 
 * \author Bosswestfalen (https://github.com/Bosswestfalen)
 * \version @PROJECT_VERSION@
 * \date 2018
 * \copyright @LICENSE@
 */

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

  private:
};

}

#endif

