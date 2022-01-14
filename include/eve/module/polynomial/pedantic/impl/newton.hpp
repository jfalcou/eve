//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/newton_impl.hpp>

namespace eve::detail
{
  //================================================================================================
  //== Newton with iterators
  //================================================================================================

  template<value T0, std::input_iterator IT0, std::input_iterator IT1>
  EVE_FORCEINLINE constexpr auto newton_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T0 xx, IT0 const & firstc, IT0 const & lastc
                                               , IT1 const & firstn) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT0>::value_type>
            && compatible_values<T0, typename std::iterator_traits<IT1>::value_type>)
  {
    return detail::newton_impl(pedantic_type(), xx, firstc, lastc, firstn);
  }

  //================================================================================================
  //== Newton with ranges
  //================================================================================================
  template<value T0, range R1, range R2>
  EVE_FORCEINLINE constexpr auto newton_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T0 xx, R1 const & rc
                                        , R2 const & rn) noexcept
  requires (compatible_values<T0, typename R1::value_type> && (!simd_value<R1>)
            && compatible_values<T0, typename R2::value_type> && (!simd_value<R2>))
  {
    return detail::newton_impl(pedantic_type(), xx, rc, rn);
  }
}
