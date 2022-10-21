//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), T0 xx, IT0 const& firstc, IT0 const& lastc, IT1 const& firstn) noexcept
    requires((compatible_values<T0, typename std::iterator_traits<IT0>::value_type>)&&(
        compatible_values<T0, typename std::iterator_traits<IT1>::value_type>))
{
  return detail::newton_impl(regular_type(), xx, firstc, lastc, firstn);
}

//================================================================================================
//== Newton with ranges
//================================================================================================
template<value T0, range R1, range R2>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), T0 xx, R1 const& rc, R2 const& rn) noexcept requires(
    compatible_values<
        T0,
        typename R1::
            value_type> && (!simd_value<R1>)&&compatible_values<T0, typename R2::value_type> && (!simd_value<R2>))
{
  return detail::newton_impl(regular_type(), xx, rc, rn);
}
//================================================================================================
//== Newton with tuples
//================================================================================================
// template<value T0, product_type R1, product_type R2>
// EVE_FORCEINLINE constexpr auto
// newton_(EVE_SUPPORTS(cpu_), T0 xx, R1 const& rc, R2 const& rn) noexcept requires(
//     compatible_values<
//         T0,
//         typename R1::
//             value_type> && (!simd_value<R1>)&&compatible_values<T0, typename R2::value_type> && (!simd_value<R2>))
// {
//   using r_t = T0;
//   auto x    = r_t(xx);
//   if( size_v<rc> == 0) return r_t(0);
//   if( size_v<rc> == 1 ) return r_t(get<0>(rc));
//   else
//   {
// //     auto curc = get<0>(rc);
// //     auto curn = get<0>(rn);
// //     advance(curc, 1);
// //     advance(curn, 1);
//     auto dfma = d(fma);
//     r_t  that(dfma(sub(x, get<0>(rn), get<1>(rc), get<1>(rn)));
//     auto step = [&](auto that, auto argc, auto argn) { return dfma(sub(x, argn), that, argc); };
//     for( advance(curc, 1); curc != lastc; advance(curc, 1), advance(curn, 1) )
//       that = step(that, *curc, *curn);
//     return that;
// //  return detail::newton_impl(regular_type(), xx, rc, rn);
// }


}
