//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve
{
  template<typename Callable>
  concept callable_object = requires(Callable)
  {
    typename Callable::tag_type;
    typename Callable::caller_type;
  };

  template<typename Callable>
  concept conditional_callable_object = callable_object<Callable>
  && requires(Callable)
  {
    typename Callable::is_conditional;
  };
}
