//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto self_negate(wide<T,N,ABI> const& v) noexcept
  {
    if constexpr(floating_value<T>)
    {
      auto that = v;
      that ^= signmask(eve::as(v));
      return that;
    }
    else
    {
      return T{0} - v;
    }
  }

  //================================================================================================
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    if constexpr(is_native_v<ABI>)
    {
      auto that = v;
      that ^= allbits(eve::as(v));
      return that;
    }
    else
    {
      return  apply_over([]<typename E>(E const& e)
              {
                if constexpr(floating_scalar_value<E>)
                  return bit_cast( ~bit_cast(e, as_<as_integer_t<E>>{}), as(e));
                else
                  return E(~e);
              }, v
              );
    }
  }

  //================================================================================================
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto self_logand(logical<wide<T,N>> v, logical<wide<U,N>> w) noexcept
  {
    if constexpr(sizeof(T) == sizeof(U))
    {
      return bit_cast ( v.bits() & w.bits(), as(v) );
    }
    else
    {
      return map([]<typename E>(E e,auto f){ return as_logical_t<E>(e && f); }, v, w);
    }
  }

  //================================================================================================
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE auto self_logor(logical<wide<T,N>> v, logical<wide<U,N>> w) noexcept
  {
    if constexpr(sizeof(T) == sizeof(U))
    {
      return bit_cast ( v.bits() | w.bits(), as(v) );
    }
    else
    {
      return map([]<typename E>(E e,auto f){ return as_logical_t<E>(e || f); }, v, w);
    }
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_lognot(Wide const& v) noexcept
  {
    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr( is_logical_v<Wide> )  return bit_cast(~v.bits(), as_<Wide>{});
      else                                return !to_logical(v);
    }
    else
    {
      return apply_over([]<typename E>(E const& e){ return as_logical_t<E>(!e); }, v);
    }
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_eq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto eq = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e == f); };

    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr(is_logical_v<Wide>)  return bit_cast(v.bits() == w.bits(), as(v));
      else                              return apply_over(eq, v, w);
    }
    else
    {
      return apply_over(eq, v, w);
    }
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_neq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto eq = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e != f); };

    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr(is_logical_v<Wide>)  return bit_cast(v.bits() != w.bits(), as(v));
      else                              return apply_over(eq, v, w);
    }
    else
    {
      return apply_over(eq, v, w);
    }
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_less(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto lt = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e < f); };
    return apply_over(lt, v, w);
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_leq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto ge = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e <= f); };
    return apply_over(ge, v, w);
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_greater(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto gt = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e > f); };
    return apply_over(gt, v, w);
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_geq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto ge = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e >= f); };
    return apply_over(ge, v, w);
  }
}
