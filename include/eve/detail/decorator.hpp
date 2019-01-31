//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_DECORATOR_HPP_INCLUDED
#define EVE_DETAIL_DECORATOR_HPP_INCLUDED

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename Functor, typename Decorator>
  struct decorated_functor : private Functor
  {
    using parent = Functor;

    template<typename... Args>
    EVE_FORCEINLINE constexpr auto operator()(Args &&... args) const noexcept
        -> decltype(std::declval<parent const>()(Decorator(), std::forward<Args>(args)...))
    {
      return static_cast<parent const &>(*this)(Decorator(), std::forward<Args>(args)...);
    }
  };

  template<typename Flag>
  struct decorator
  {
    template<typename Function>
    constexpr detail::decorated_functor<Function, Flag> operator()(Function const &) const noexcept
    {
      return {};
    }
  };
}

#endif
