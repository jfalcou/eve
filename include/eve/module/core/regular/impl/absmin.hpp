//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  absmin_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
  {
    auto tmp1 =  rbr::drop(saturated2, o);
    auto omin = options<decltype(tmp1)>{tmp1};

    auto tmp2 =  rbr::drop(pedantic2, o);
    auto oabs1 = options<decltype(tmp2)>{tmp2};
    auto tmp3 =  rbr::drop(numeric2, oabs1);
    auto oabs = options<decltype(tmp3)>{tmp3};


     return eve::abs[oabs](eve::min[omin](r0, r1, rs...));
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  absmin_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  //  requires (kumi::size_v<Ts> >=  2)
  {
    auto tmp1 =  rbr::drop(saturated2, o);
    auto omin = options<decltype(tmp1)>{tmp1};

    auto tmp2 =  rbr::drop(pedantic2, o);
    auto oabs1 = options<decltype(tmp2)>{tmp2};
    auto tmp3 =  rbr::drop(numeric2, oabs1);
    auto oabs = options<decltype(tmp3)>{tmp3};

    return eve::abs[oabs](eve::min[omin](tup));

  }

}

// template<ordered_value T, ordered_value U>
// EVE_FORCEINLINE auto
// absmin_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
// -> decltype(eve::abs(eve::min(a, b)))
// {
//   return arithmetic_call(absmin, a, b);
// }

// template<ordered_value T>
// EVE_FORCEINLINE auto
// absmin_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
// -> decltype(eve::abs(a))
// {
//   if constexpr(has_native_abi_v<T>)
//     return eve::abs(eve::min(a, b));
//   else
//     return apply_over(absmin, a, b);
// }

// //================================================================================================
// // Masked case
// //================================================================================================
// template<decorator D, conditional_expr C, ordered_value U, ordered_value V>
// EVE_FORCEINLINE auto
// absmin_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
// -> decltype(absmin(t, f))
// {
//   return mask_op(cond, D()(eve::absmin), t, f);
// }

// template<conditional_expr C, ordered_value U, ordered_value V>
// EVE_FORCEINLINE auto
// absmin_(EVE_SUPPORTS(cpu_),
//         C const& cond,
//         U const& t,
//         V const& f) noexcept
// -> decltype(absmin(t, f))
// {
//   return mask_op(cond, eve::absmin, t, f);
// }

// //================================================================================================
// // N parameters
// //================================================================================================
// template<ordered_value T0, ordered_value T1, ordered_value... Ts>
// auto
// absmin_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
// -> decltype(eve::abs(eve::min(a0, a1, args...)))
// {
//   return eve::abs(eve::min(a0, a1, args...));
// }
// //================================================================================================
// // tuples
// //================================================================================================
// template<kumi::non_empty_product_type Ts>
// auto
// absmin_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
// {
//   if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
//   else return eve::abs(kumi::apply( [&](auto... m) { return min(m...); }, tup));
// }


// template<decorator D, kumi::non_empty_product_type Ts>
// auto
// absmin_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
// {
//   if constexpr(std::same_as<D,saturated_type>)
//   {
//     if constexpr( kumi::size_v<Ts> == 1) return eve::abs[d](get<0>(tup));
//     else return eve::abs[d](kumi::apply( [&](auto... m) { return d(min)(m...); }, tup));
//   }
//   else
//   {
//     if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
//     else return eve::abs(kumi::apply( [&](auto... m) { return d(min)(m...); }, tup));
//   }
// }

// // -----------------------------------------------------------------------------------------
// // Masked case
// template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
// EVE_FORCEINLINE auto
// absmin_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
// ->decltype(absmin(a0, a1, args...))
// {
//   return mask_op(cond, eve::absmin, a0, a1, args...);
// }

// }
