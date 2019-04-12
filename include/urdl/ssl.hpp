//
// ssl.hpp
// ~~~~~~~
//
// Copyright (c) 2018 Tim Niederhausen (tim@rnc-ag.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_SSL_HPP
#define URDL_SSL_HPP

#include <string>
#include "urdl/option_type.hpp"
#include "urdl/detail/config.hpp"
#include "urdl/detail/string_view.hpp"

#if !defined(URDL_DISABLE_SSL)
# include <boost/asio/ssl/verify_mode.hpp>
#endif

#include "urdl/detail/abi_prefix.hpp"

namespace urdl {
namespace ssl {

#if !defined(URDL_DISABLE_SSL)
/// Option to specify the SSL peer certificate validation mode.
/**
 * @par Remarks
 * Defaults to @c boost::asio::ssl::verify_peer.
 *
 * @par Example
 * To set the request method for an object of class @c urdl::istream:
 * @code
 * urdl::istream is;
 * is.set_option(urdl::ssl::verify_mode(boost::asio::ssl::verify_none));
 * is.open("https://www.boost.org");
 * @endcode
 *
 * To set the request method for an object of class @c urdl::read_stream:
 * @code
 * urdl::read_stream stream;
 * stream.set_option(urdl::ssl::verify_mode(boost::asio::ssl::verify_none));
 * stream.open("https://www.boost.org");
 * @endcode
 *
 * @par Requirements
 * @e Header: @c <urdl/ssl.hpp> @n
 * @e Namespace: @c urdl::ssl
 */
class verify_mode
{
public:
  /// Type of the option's value.
  typedef std::size_t value_type;

  /// The unique type constant of this option class.
  BOOST_STATIC_CONSTEXPR int type = option_type::verify_mode;

  /// Constructs an object of class @c verify_mode.
  /**
   * @par Remarks
   * Postcondition: <tt>value() == "GET"</tt>.
   */
  verify_mode()
    : value_(boost::asio::ssl::verify_peer)
  {
  }

  /// Constructs an object of class @c verify_mode.
  /**
   * @param v The desired value for the option.
   *
   * @par Remarks
   * Postcondition: <tt>value() == v</tt>
   */
  explicit verify_mode(value_type v)
    : value_(v)
  {
  }

  /// Gets the value of the option.
  /**
   * @returns The value of the option.
   */
  boost::asio::ssl::verify_mode value() const BOOST_NOEXCEPT
  {
    return static_cast<boost::asio::ssl::verify_mode>(value_);
  }

  /// Sets the value of the option.
  /**
   * @param v The desired value for the option.
   *
   * @par Remarks
   * Postcondition: <tt>value() == v</tt>
   */
  void value(value_type v)
  {
    value_ = v;
  }

private:
  value_type value_;
};
#endif

} // namespace ssl
} // namespace urdl

#include "urdl/detail/abi_suffix.hpp"

#endif // URDL_SSL_HPP
