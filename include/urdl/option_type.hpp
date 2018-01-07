//
// option_type.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2018 Tim Niederhausen (tim@rnc-ag.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_OPTION_TYPE_HPP
#define URDL_OPTION_TYPE_HPP

#include "urdl/detail/abi_prefix.hpp"

namespace urdl {
namespace option_type {

// TODO(tim): Replace this with a class option_id
// that is instantiated once per option class
// and whose address is therefore unique for a certain option.

enum http_option_type
{
  request_method,
  request_content,
  request_content_type,
  max_redirects,
  user_agent,
};

}
} // namespace urdl

#include "urdl/detail/abi_suffix.hpp"

#endif // URDL_HTTP_HPP
