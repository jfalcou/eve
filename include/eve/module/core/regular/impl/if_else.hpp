//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_ornot.hpp>
#include <eve/module/core/regular/bit_select.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
// Local helper for product_type if_else implementation
template<typename T, kumi::product_type U, kumi::product_type V>
EVE_FORCEINLINE constexpr auto tuple_select(T cond, U const& t, V const& f)
{
  using r_t = std::conditional_t<simd_value<U>, U, V>;
  return r_t {kumi::map([&](auto const& vv, auto const& fv) { return if_else(cond, vv, fv); }, t, f)};
}

template<scalar_value T, value U, value V, callable_options O>
EVE_FORCEINLINE constexpr auto if_else_(EVE_REQUIRES(cpu_), O const&, T cond, U const& t, V const& f)
{
  if      constexpr( simd_value<U> && simd_value<V> ) return  is_nez(cond) ? t    : f;
  else if constexpr( simd_value<U> )                  return  is_nez(cond) ? t    : U(f);
  else if constexpr( simd_value<V> )                  return  is_nez(cond) ? V(t) : f;
  else                                                return  is_nez(cond) ? t    : f;
}

template<simd_value T, value U, value V, callable_options O>
EVE_FORCEINLINE constexpr auto if_else_(EVE_REQUIRES(cpu_), O const&, T const& cond, U const& t, V const& f)
{
  if constexpr( !is_logical_v<T> ) return if_else(is_nez(cond), t, f);
  else
  {
    using r_t = as_wide_as_t<common_compatible_t<U, V>,T>;
    using e_t = element_type_t<r_t>;

    if      constexpr(kumi::product_type<U> && kumi::product_type<V>) return tuple_select(cond, t, f);
    else if constexpr(has_emulated_abi_v<T>)                          return map(as<r_t>{}, if_else, cond, r_t(t), r_t(f));
    else if constexpr(has_aggregated_abi_v<T>)                        return aggregate(if_else, cond, r_t(t), r_t(f));
    else if constexpr(std::same_as<logical<e_t>, element_type_t<T>>)
    {
      if constexpr( std::same_as<U, V> )  return bit_select(cond.mask(), r_t(t), r_t(f));
      else                                return if_else(cond, r_t(t), r_t(f));
    }
    else return if_else(convert(cond, as<as_logical_t<e_t>>()), r_t(t), r_t(f));
  }
}

//------------------------------------------------------------------------------------------------
// Supports if_else(conditional_expr,a,b)
template<conditional_expr C, typename U, typename V, callable_options O>
EVE_FORCEINLINE constexpr auto if_else_(EVE_REQUIRES(cpu_), O const&, C cond, U const& t, V const& f)
{
  if constexpr( generator<V> )
  {
    if      constexpr( C::is_complete && C::is_inverted  ) return t;
    else if constexpr( C::is_complete && !C::is_inverted ) return f(as<U>());
    else                                                   return if_else(cond.mask(eve::as<U>()),t,f);
  }
  else if constexpr( generator<U> )
  {
    if      constexpr( C::is_complete && C::is_inverted  ) return t(as<V>());
    else if constexpr( C::is_complete && !C::is_inverted ) return f;
    else                                                   return if_else(cond.mask(eve::as<V>()),t,f);
  }
  else
  {
    using r_t = typename std::conditional_t < logical_value<U> || logical_value<V>
                                            , common_logical<U,V>
                                            , common_value<U,V>
                                            >::type;

    if      constexpr( C::is_complete && C::is_inverted  ) return r_t(t);
    else if constexpr( C::is_complete && !C::is_inverted ) return r_t(f);
    else
    {
      auto const mask = cond.mask(eve::as<r_t>());
      if constexpr( C::is_inverted )  return if_else(mask, f, t);
      else                            return if_else(mask, t, f);
    }
  }
}

//------------------------------------------------------------------------------------------------
// Optimizes if_else(c,t,constant)
template<value T, value U, generator Constant, callable_options O>
EVE_FORCEINLINE constexpr auto
if_else_(EVE_REQUIRES(cpu_), O const&, T const& cond, U const& u, Constant const& v) noexcept
{
  using tgt = as<U>;

  if      constexpr( scalar_value<T> )        return static_cast<bool>(cond) ? u : v(tgt {});
  else if constexpr( kumi::product_type<U> )  return if_else(cond, u, v(tgt {}));
  else if constexpr( !T::abi_type::is_wide_logical )  return if_else(cond, u, v(tgt {}));
  else
  {
    using           cvt   = as<as_logical_t<element_type_t<U>>>;
    auto            mask  = convert(to_logical(cond),cvt{});
    constexpr auto  cst   = Constant{};

    if constexpr( cst == eve::zero || (std::is_unsigned_v<U> && cst == eve::valmin) )
    {
      if constexpr(logical_value<U>)  return to_logical(bit_and(u.mask(), bit_mask(mask)));
      else                            return bit_and(u, bit_mask(mask));
    }
    else if constexpr( cst == eve::allbits || (std::is_unsigned_v<U> && cst == valmax) )
    {
      if constexpr(logical_value<U>)  return to_logical(bit_ornot(u.mask(), bit_mask(mask)));
      else                            return bit_ornot(u, bit_mask(mask));
    }
    else if constexpr( integral_value<U> && cst == eve::one)
    {
      using r_t = as_wide_as_t<U, decltype(bit_mask(mask))>;
      return minus(bit_ornot(minus(r_t(u)), bit_mask(mask)));
    }
    else if constexpr( integral_value<U> && cst == eve::mone )  return bit_ornot(u, bit_mask(mask));
    else                                                        return if_else(cond, u, v(tgt {}));
  }
}

//------------------------------------------------------------------------------------------------
// Optimizes if_else(c,constant, t)
template<value T, value U, generator Constant, callable_options O>
EVE_FORCEINLINE constexpr auto
if_else_(EVE_REQUIRES(cpu_), O const&, T const& cond, Constant const& v, U const& u) noexcept
{
  using tgt = as<U>;

  if      constexpr( scalar_value<T> )        return static_cast<bool>(cond) ? v(tgt {}) : u;
  else if constexpr( kumi::product_type<U> )  return if_else(cond, v(tgt {}), u);
  else if constexpr( current_api >= avx512 )  return if_else(cond, v(tgt {}), u);
  else
  {
    using           cvt   = as<as_logical_t<element_type_t<U>>>;
    auto            mask  = convert(to_logical(cond),cvt{});
    constexpr auto  cst   = Constant{};

    if constexpr( cst == eve::zero || (std::is_unsigned_v<U> && cst == eve::valmin) )
    {
      if constexpr(logical_value<U>)  return to_logical(bit_and(u.mask(), bit_mask(mask)));
      else                            return bit_andnot(u, bit_mask(mask));
    }
    else if constexpr( cst == eve::allbits || (std::is_unsigned_v<U> && cst == valmax) )
    {
      if constexpr(logical_value<U>)  return to_logical(bit_ornot(u.mask(), bit_mask(mask)));
      else                            return bit_or(u, bit_mask(mask));
    }
    else if constexpr( integral_value<U> && cst == eve::one)
    {
      using r_t = as_wide_as_t<U, decltype(bit_mask(mask))>;
      return minus(bit_or(minus(r_t(u)), bit_mask(mask)));
    }
    else if constexpr( integral_value<U> && cst == eve::mone )  return bit_or(u, bit_mask(mask));
    else                                                        return if_else(cond, v(tgt {}), u);
  }
}
}
