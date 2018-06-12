//
// detail/string_view.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2009-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef URDL_DETAIL_STRING_VIEW_HPP
#define URDL_DETAIL_STRING_VIEW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/string_view.hpp>

#include "urdl/detail/abi_prefix.hpp"

#if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
namespace urdl {
using boost::asio::basic_string_view;
using boost::asio::string_view;
} // namespace urdl
#endif

#define URDL_STRING_VIEW_PARAM BOOST_ASIO_STRING_VIEW_PARAM

#include "urdl/detail/abi_suffix.hpp"

#endif // URDL_DETAIL_SCOPED_PTR_HPP
