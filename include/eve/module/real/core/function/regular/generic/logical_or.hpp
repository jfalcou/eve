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
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // Full scalar case
  template<scalar_value T, scalar_value U>
  EVE_FORCEINLINE as_logical_t<T> logical_or_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    constexpr auto value = []<typename V>(V const& v)
    {
      if constexpr(is_logical_v<V>) return v.value(); else return v;
    };

    return as_logical_t<T>{value(a) || value(b)};
  }

  // Non-native ABI
  template<value T, value U>
  EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( (!has_native_abi_v<T> || !has_native_abi_v<U>) && size_compatible_values<T,U> )
  {
    return apply_over(logical_or, a, b);
  }

  // Other cases
  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  requires( use_is_wide_logical<ABI>::value )
  {
    if constexpr(sizeof(T) == sizeof(U))  return bit_cast ( bit_or(a.bits(), b.bits())
                                                          , as_<as_logical_t<wide<T,N,ABI>>>()
                                                          );
    else                                  return apply_over(logical_or, a, b);
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_or(a, is_nez(b));
  }

  template<typename T, scalar_value U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , U const &b
                                    ) noexcept
  {
    return logical_or(a, logical<wide<T,N,ABI>>(is_nez(b)));
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_or(is_nez(a), is_nez(b));
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , U const &b
                                    ) noexcept
  {
    return logical_or(is_nez(a), logical<wide<T,N,ABI>>(is_nez(b)));
  }
  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_or(b,a);
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  {
    return logical_or(b,a);
  }

  template<scalar_value T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_or_ ( EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  {
    return logical_or(b,a);
  }
}

namespace eve
{
  template<value T, value U>
  EVE_FORCEINLINE auto operator ||(T const &v0, U const &v1) noexcept
  -> decltype( eve::logical_or(v0,v1) )
  {
    return eve::logical_or(v0, v1);
  }
}
