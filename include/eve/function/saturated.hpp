//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SATURATED_HPP_INCLUDED
#define EVE_FUNCTION_SATURATED_HPP_INCLUDED

#include <eve/detail/decorator.hpp>

namespace eve
{
  struct saturated_tag {};
  constexpr inline detail::decorator<saturated_tag> saturated_ = {};
}

#endif
