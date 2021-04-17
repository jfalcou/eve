//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/regular.hpp>
#include <eve/constant/one.hpp>
#include <eve/module/real/polynomial/detail/newton_impl.hpp>

namespace eve::detail
{
  //================================================================================================
  //== Newton with iterators
  //================================================================================================

  template<value T0, std::input_iterator IT0, std::input_iterator IT1>
  EVE_FORCEINLINE constexpr auto newton_(EVE_SUPPORTS(cpu_)
                                        , T0 xx, IT0 const & firstc, IT0 const & lastc
                                               , IT1 const & firstn, IT1 const & lastn) noexcept
  requires ((compatible_values<T0, typename std::iterator_traits<IT>::value_type>))
  {
    return detail::newton_impl(regular_type(), xx, firstc, lastc, firstn, lastn);
  }

  //================================================================================================
  //== Newton with ranges
  //================================================================================================
  template<value T0, range R1, range R2>
  EVE_FORCEINLINE constexpr auto newton_(EVE_SUPPORTS(cpu_)
                                        , T0 xx, R1 const & rc
                                               , R2 const & rn) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return detail::newton_impl(regular_type(), xx, rc, rn);
  }

//   //================================================================================================
//   //== N parameters (((..(a*x+b)*x+c)*x + ..)..)
//   //================================================================================================

//   template<value T0, value ...Ts>
//   EVE_FORCEINLINE constexpr auto newton_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
//   {
//     return newton_impl(regular_type(), x, args...);
//   }

}
