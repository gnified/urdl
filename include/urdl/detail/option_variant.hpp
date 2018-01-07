//
// detail/option_variant.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2018 Tim Niederhausen (tim@rnc-ag.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_DETAIL_OPTION_VARIANT_HPP
#define URDL_DETAIL_OPTION_VARIANT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/config.hpp>

#include "urdl/detail/abi_prefix.hpp"

namespace urdl {
namespace detail {

class option_variant
{
  typedef std::string string_type;
  typedef std::size_t size_type;

public:
  option_variant() BOOST_NOEXCEPT
    : active_type_(none)
  {
    // ctor
  }

  option_variant(size_type v) BOOST_NOEXCEPT
    : active_type_(size)
  {
    // ctor
  }

  option_variant(const string_type& v) BOOST_NOEXCEPT
    : active_type_(string)
  {
    new (&string_val_) string_type(v);
  }

  option_variant(const option_variant& o)
    : active_type_(o.active_type_)
  {
    switch (o.active_type_) {
      case size:
        size_val_ = o.size_val_;
        break;
      case string:
        new (&string_val_) string_type(o.string_val_);
        break;
      default: break;
    }
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  option_variant(string_type&& v) BOOST_NOEXCEPT
    : active_type_(string)
  {
    new (&string_val_) string_type(std::move(v));
  }

  option_variant(option_variant&& o)
    : active_type_(o.active_type_)
  {
    switch (o.active_type_) {
      case size:
        size_val_ = o.size_val_;
        break;
      case string:
        new (&string_val_) string_type(std::move(o.string_val_));
        break;
      default: break;
    }
    o.active_type_ = none;
  }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

  ~option_variant()
  {
    if (active_type_ == string)
      string_val_.~string_type();
  }

  template <typename T>
  const T& value() const BOOST_NOEXCEPT;

  template <>
  const size_type& value<size_type>() const BOOST_NOEXCEPT
  { return size_val_; }

  template <>
  const string_type& value<string_type>() const BOOST_NOEXCEPT
  { return string_val_; }

  option_variant& operator=(size_type v) BOOST_NOEXCEPT
  {
    if (active_type_ == string)
      string_val_.~string_type();

    size_val_ = v;
    active_type_ = size;
    return *this;
  }

  option_variant& operator=(const string_type& v)
  {
    if (active_type_ == string) {
      string_val_ = v;
    } else {
      new (&string_val_) string_type(v);
      active_type_ = string;
    }
    return *this;
  }

  option_variant& operator=(const option_variant& o)
  {
    switch (o.active_type_) {
      case size:
        size_val_ = o.size_val_;
        active_type_ = o.active_type_;
        break;
      case string: {
        if (active_type_ != string)
          new (&string_val_) string_type(o.string_val_);
        else
          string_val_ = o.string_val_;
        active_type_ = o.active_type_;
      }
      default: break;
    }
    return *this;
  }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
  option_variant& operator=(string_type&& v)
  {
    if (active_type_ == string) {
      string_val_ = std::move(v);
    } else {
      new (&string_val_) string_type(std::move(v));
      active_type_ = string;
    }
  }

  option_variant& operator=(option_variant&& o)
  {
    switch (o.active_type_) {
      case size:
        size_val_ = o.size_val_;
        active_type_ = o.active_type_;
        break;
      case string: {
        if (active_type_ != string)
          new (&string_val_) string_type(std::move(o.string_val_));
        else
          string_val_ = std::move(o.string_val_);
        active_type_ = o.active_type_;
      }
      default: break;
    }
    o.active_type_ = none;
    return *this;
  }
#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

private:
  enum
  {
    none, size, string
  } active_type_;

  union
  {
    size_type size_val_;
    string_type string_val_;
  };
};

} // namespace detail
} // namespace urdl

#include "urdl/detail/abi_suffix.hpp"

#endif // URDL_DETAIL_SCOPED_PTR_HPP
