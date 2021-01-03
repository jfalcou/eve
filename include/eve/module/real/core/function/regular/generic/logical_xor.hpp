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

#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>

namespace eve::detail
{
  // Full scalar case
  template<scalar_value T, scalar_value U>
  EVE_FORCEINLINE as_logical_t<T> logical_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    constexpr auto value = []<typename V>(V const& v)
    {
      if constexpr(is_logical_v<V>) return v.value(); else return !!v;
    };

    return as_logical_t<T>{value(a) != value(b)};
  }

  // Non-native ABI
  template<value T, value U>
  EVE_FORCEINLINE auto logical_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires( (!has_native_abi_v<T> || !has_native_abi_v<U>) && size_compatible_values<T,U> )
  {
    return apply_over(logical_xor, a, b);
  }

  // Other cases
  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  requires( use_is_wide_logical<ABI>::value )
  {
    if constexpr(sizeof(T) == sizeof(U))  return bit_cast ( bit_xor(a.bits(), b.bits())
                                                          , as_<as_logical_t<wide<T,N,ABI>>>()
                                                          );
    else                                  return apply_over(logical_xor, a, b);
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_xor(a, to_logical(b));
  }

  template<typename T, scalar_value U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , logical<wide<T,N,ABI>> const &a
                                    , U const &b
                                    ) noexcept
  {
    return logical_xor(a, logical<wide<T,N,ABI>>(!!b));
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_xor(to_logical(a), to_logical(b));
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , U const &b
                                    ) noexcept
  {
    return logical_xor(to_logical(a), logical<wide<T,N,ABI>>(!!b));
  }
  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , wide<U,N,ABI> const &b
                                    ) noexcept
  {
    return logical_xor(b,a);
  }

  template<typename T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , wide<T,N,ABI> const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  {
    return logical_xor(b,a);
  }

  template<scalar_value T, typename U, typename N, native_abi ABI>
  EVE_FORCEINLINE auto logical_xor_ ( EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , logical<wide<U,N,ABI>> const &b
                                    ) noexcept
  {
    return logical_xor(b,a);
  }
}
