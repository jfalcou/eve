//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ASSERT_UTILS_HPP_INCLUDED
#define EVE_DETAIL_ASSERT_UTILS_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <eve/cardinal.hpp>
#include <eve/function/extract.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename A0, typename A1>
  EVE_FORCEINLINE bool assert_good_shift(A1 const &t) noexcept
  {
    using t_t0       = detail::value_type_t<A0>;
    using t_t1       = detail::value_type_t<A1>;
    constexpr t_t1 N = sizeof(t_t0) * 8;
    for(std::size_t i = 0; i != eve::cardinal_v<A1>; ++i)
    {
      t_t1 v = eve::extract(t, i);
      if(v >= N) return false;
      if constexpr(std::is_unsigned_v<t_t1>)
        if(v < t_t1(0)) return false;
    }

    return true;
  }
}

#endif
