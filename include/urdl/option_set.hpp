//
// option_set.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2009-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// path LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_OPTION_SET_HPP
#define URDL_OPTION_SET_HPP

#include <list>
#include "urdl/detail/config.hpp"
#include "urdl/detail/option_variant.hpp"

#include "urdl/detail/abi_prefix.hpp"

namespace urdl {

/// The class @c option_set maintains a collection of options.
/**
 * @par Remarks
 * Options are uniquely identified by type, so the @c option_set class is a
 * collection of objects of differing types, indexed by type.
 *
 * The option types stored in the set must meet the type requirements for
 * CopyConstructible.
 *
 * @par Requirements
 * @e Header: @c <urdl/option_set.hpp> @n
 * @e Namespace: @c urdl
 */
class option_set
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// Constructs an object of class @c option_set.
  /**
   * @par Remarks
   * Creates an empty set. Any option queried using the @c get_option member
   * function will return the default value of the option.
   */
  URDL_DECL option_set();

  /// Constructs an object of class @c option_set.
  /**
   * @par Remarks
   * Creates an identical copy of another set. Any option queried using the
   * @c get_option member function will return the same value for both sets.
   */
  URDL_DECL option_set(const option_set& other);

  /// Destroys an object of class @c option_set.
  URDL_DECL ~option_set();

  /// Assignment operator.
  /**
   * @par Remarks
   * Creates an identical copy of another set. Any option queried using the
   * @c get_option member function will return the same value for both sets.
   */
  URDL_DECL option_set& operator=(const option_set& other);
#endif // defined(GENERATING_DOCUMENTATION)
  /// Sets the value of an option in the set.
  /**
   * @param o The option to be set.
   *
   * @par Remarks
   * If the type @c Option is already present in the set, first removes that
   * element. Adds the option to the set.
   */
  template <typename Option>
  void set_option(const Option& o)
  {
    set_option(Option::type, o.value());
  }

  /// Sets multiple options in a set from another set.
  /**
   * @param other An option set containing all options to be set in the target.
   *
   * @par Remarks
   * Performs a deep copy of all option values from the object @c other into
   * the target set.
   */
  URDL_DECL void set_options(const option_set& other);

  /// Gets an option from the set.
  /**
   * @returns If the option is present in the set, an object containing the
   * value of the option. Otherwise, returns a default-constructed option.
   */
  template <typename Option>
  Option get_option() const BOOST_NOEXCEPT
  {
    if (const option_wrapper* o = get_option(Option::type))
      return Option(detail::value<typename Option::value_type>(o->data));
    return Option();
  }

  /// Removes an option from the set.
  /**
   * @par Remarks
   * If the option is queried using the @c get_option member function, it will
   * return the default value of the option.
   */
  template <typename Option>
  void clear_option()
  {
    clear_option(Option::type);
  }

private:
  struct option_wrapper
  {
    int type;
    detail::option_variant data;

    inline BOOST_CONSTEXPR friend bool operator==(const option_wrapper& a,
        int t) BOOST_NOEXCEPT
    { return a.type == t; }
  };

  typedef std::list<option_wrapper> list_type;

  template <typename Option>
  detail::option_variant get_option_data() const
  {
    if (option_wrapper* o = get_option(Option::type))
      return o->data;
    return detail::option_variant();
  }

  URDL_DECL void set_option(int type, detail::option_variant data);
  URDL_DECL const option_wrapper* get_option(int type) const BOOST_NOEXCEPT;
  URDL_DECL void clear_option(int type);

  list_type options_;
};

} // namespace urdl

#include "urdl/detail/abi_suffix.hpp"

#if defined(URDL_HEADER_ONLY)
# include "urdl/impl/option_set.ipp"
#endif

#endif // URDL_OPTION_SET_HPP
