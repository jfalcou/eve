//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/sign.hpp>

namespace eve::detail
{
//================================================================================================
// saturated case
//================================================================================================
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
mul_(EVE_SUPPORTS(cpu_),
     saturated_type const&,
     T const& a,
     U const& b) noexcept
-> decltype(mul(a, b))
{
  return arithmetic_call(saturated(mul), a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
mul_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a, T const& b) noexcept
{
  if constexpr(scalar_value<T>)
  {
    if constexpr( floating_value<T> ) { return static_cast<T>(a * b); }
    else if constexpr( std::is_signed_v<T> )
    {
      if constexpr( sizeof(T) <= 2 )
      {
        using up_t = upgrade_t<T>;
        return static_cast<T>(saturate(static_cast<up_t>(a) * static_cast<up_t>(b), as<T>()));
      }
      else if constexpr( sizeof(T) == 4 )
      {
        using un_t = std::make_unsigned_t<T>;
        using up_t = int64_t;
        enum Sizee { value = sizeof(T) * 8 - 1 };

        up_t res  = up_t(a) * up_t(b);
        un_t res2 = (un_t(a ^ b) >> Sizee::value) + valmax(eve::as<T>());
        T    hi   = (res >> (Sizee::value + 1));
        T    lo   = res;
        if( hi != (lo >> Sizee::value) ) res = res2;
        return static_cast<T>(res);
      }
      else if constexpr( sizeof(T) == 8 )
      {
        using un_t = std::make_unsigned_t<T>;
        if( b == 0 || a == 0 ) return zero(eve::as<T>());
        T sgn = bit_xor(bitofsign(a), bitofsign(b));
        if( b == valmin(eve::as<T>()) || a == valmin(eve::as<T>()) )
          return sgn ? valmin(eve::as<T>()) : valmax(eve::as<T>());
        un_t aa  = eve::abs(a);
        un_t bb  = eve::abs(b);
        auto aux = [sgn](const T& mini, const T& maxi, const un_t& amini, const un_t& amaxi)
          {
            un_t z = valmax(eve::as<T>()) / amaxi;
            return (z < amini) ? (sgn ? valmin(eve::as<T>()) : valmax(eve::as<T>())) : mini * maxi;
          };
        if( bb >= aa ) return aux(a, b, aa, bb);
        else return aux(b, a, bb, aa);
      }
    }
    else if constexpr( std::is_unsigned_v<T> )
    {
      if constexpr( sizeof(T) <= 4 )
      {
        using up_t = upgrade_t<T>;
        up_t res   = up_t(a) * up_t(b);
        return (res > valmax(eve::as<T>())) ? valmax(eve::as<T>()) : static_cast<T>(res);
      }
      else
      {
        auto aux = [](const T& mini, const T& maxi)
          {
            T z = valmax(eve::as<T>()) / maxi;
            return (z < mini) ? valmax(eve::as<T>()) : mini * maxi;
          };
        if( b == 0 || a == 0 ) return zero(eve::as<T>());
        if( b >= a ) return aux(a, b);
        else return aux(b, a);
      }
    }
  }
  else //simd case
  {
    using elt_t = element_type_t<T>;
    if constexpr( floating_value<T> ) { return a * b; }
    else if constexpr( integral_value<T> )
    {
      if constexpr( sizeof(elt_t) <= 4 )
      {
        using sup_t = upgrade_t<elt_t>;
        auto z      = mul(convert(a, as<sup_t>()), convert(b, as<sup_t>()));
        auto s      = saturate(z, as<elt_t>());
        return convert(s, as<elt_t>());
      }
      else
      {
        auto that = map(eve::mul[saturated], a, b);
        return that;
      }
    }
  }
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
mul_(EVE_SUPPORTS(cpu_), saturated_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(mul(a0, a1, args...))
{
  using r_t = decltype(mul(a0, a1, args...));
  r_t that(mul[saturated](r_t(a0), r_t(a1)));
  ((that = mul[saturated](that, r_t(args))), ...);
  return that;
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
mul_(EVE_SUPPORTS(cpu_),
     C const& cond,
     saturated_type const&,
     U const& t,
     V const& f) noexcept
->decltype(if_else(cond, mul(t, f), t))
{
  return mask_op(cond, mul[saturated], t, f);
}
}
