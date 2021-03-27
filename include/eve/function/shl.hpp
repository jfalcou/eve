//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct shl_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shl_), T const&, [[maybe_unused]] S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(s),
                  "[eve::shl] Shifting by " << s
                                            << " is out of the range [0, "
                                            << sizeof(value_type_t<T>) * 8
                                            << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(shl_, shl);

  namespace detail
  {
    template<integral_value T, integral_value U>
    EVE_FORCEINLINE auto shl_(EVE_SUPPORTS(cpu_), T a, U s) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return  static_cast<T>(a << s);
      else if constexpr( scalar_value<T>)
      {
        using w_t = as_wide_t<T, cardinal_t<U>>;
                                                          return w_t(a) << s;
      }
      else                                                return a << s;
    }
  }
}
