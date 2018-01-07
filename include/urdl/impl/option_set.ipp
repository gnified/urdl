//
// option_set.ipp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2009-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_OPTION_SET_IPP
#define URDL_OPTION_SET_IPP

#include "urdl/detail/abi_prefix.hpp"

namespace urdl {

struct option_type_predicate
{
  BOOST_CONSTEXPR option_type_predicate(int type) BOOST_NOEXCEPT
    : type_(type)
  {
    // ctor
  }

  BOOST_CONSTEXPR bool operator(
      const option_set::option_wrapper& w) BOOST_NOEXCEPT
  {
    return w.type == type_;
  }

  int type_;
};

void option_set::set_options(const option_set& other)
{
  options_ = other.options_;
}

void option_set::set_option(int type, detail::option_variant data)
{
  clear_option(type);
  option_wrapper w;
  w.type = type;
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  w.data = std::move(data);
  options_.push_front(std::move(w));
#else
  w.data = data;
  options_.push_front(w);
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
}

const option_set::option_wrapper* option_set::get_option(
    int type) const BOOST_NOEXCEPT
{
  const list_type::const_iterator it = std::find(options_.begin(),
      options_.end(), type);
  if (it != options_.end())
    return &(*it);
  return 0;
}

void option_set::clear_option(int type)
{
  options_.remove_if(option_type_predicate(type));
}

} // namespace urdl

#include "urdl/detail/abi_suffix.hpp"

#endif // URDL_OPTION_SET_IPP
