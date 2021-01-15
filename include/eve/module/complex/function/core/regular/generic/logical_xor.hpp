//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE  auto logical_xor_(EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , U const &b) noexcept
  {
    return apply_over(logical_xor, a, b);
  }

  template<scalar_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    if constexpr(is_logical_v<T>) {
      return logical_xor(a.value(), b);
    }
    else if  constexpr(is_logical_v<U>) {
      return logical_xor(a, b.value());
    }
    else
    {
      using i_t = as_integer_t<T>;
      return as_logical_t<T>(bit_xor(bit_mask(i_t(a)), bit_mask(i_t(b))));
    }
    //return as_logical_t<T>(eve::as_logical_t<T>(a).value() ^ as_logical_t<T>( b).value());
  }

  template<simd_value T, simd_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U> && (cardinal_v<T> == cardinal_v<U>)
  {
    if constexpr(sizeof(T) == sizeof(U)) { return bit_cast(bit_xor(bit_mask(a), bit_mask(b)), as_<as_logical_t<T>>());}
    else                                 { return apply_over(logical_xor, a, b); }
  }

  template<simd_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    return logical_xor(is_nez(a), is_nez(b));
  }

  template<scalar_value T, simd_value U>
  EVE_FORCEINLINE  auto logical_xor_(EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    return logical_xor(is_nez(a), is_nez(b));
  }

  template<simd_value T, simd_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_)
                                               , logical<T> const &a
                                               , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U> && (cardinal_v<T> == cardinal_v<U>)
  {
    if constexpr(sizeof(T) == sizeof(U)) { return bit_cast(bit_xor(a.bits(), b.bits()), as_<as_logical_t<T>>());}
    else                                 { return apply_over(logical_xor, a, b); }
  }

  template<simd_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_)
                                               , logical<T> const &a
                                               , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U>
  {
    using elt_t = element_type_t<T>;
    if constexpr(sizeof(elt_t) == sizeof(U))
    {
      auto bb = is_nez(T(bit_cast(b, as<logical<elt_t>>())));

      return bit_cast(bit_xor(a.bits(), bb.bits()), as_<as_logical_t<T>>());
    }
    else           { return apply_over(logical_xor, a, b); }
  }

  template<scalar_value T, simd_value U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_)
                                   , logical<T> const &a
                                   , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U>
  {
    using elt_t = element_type_t<U>;
    using r_t = as_wide_t<logical<T>, cardinal_t<U>>;
    if constexpr(sizeof(elt_t) == sizeof(T))
    {
      auto aa = r_t(a);

      return bit_cast(bit_xor(aa.bits(), b.bits()), as<r_t>());
    }
    else        { return apply_over(logical_xor, a, b); }
  }
}
