//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/is_logical.hpp>
#include <eve/is_wide.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                , wide<U, N, ABI> const& v0
                                , wide<T, N, ABI> const& v1
                                , wide<T, N, ABI> const& v2
                                ) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      if constexpr( is_logical_v<T> )
      {
        using out_t = as_logical_t<wide<T, N, ABI>>;
        return bitwise_cast<out_t>( bitwise_select( bitwise_mask(v0),
                                                    bitwise_mask(v1),bitwise_mask(v2)
                                                  )
                                  );
      }
      else
      {
        return bitwise_select( bitwise_mask(v0), v1, v2);
      }
    }

    if constexpr( std::is_same_v<ABI,aggregated_> )
    {
      return aggregate( eve::if_else, v0, v1, v2);
    }

    if constexpr( std::is_same_v<ABI,emulated_> )
    {
      return map( eve::if_else, v0, v1, v2);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename U, typename V, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_), wide<T, N, ABI> const &v0, U const &v1, V const &v2) noexcept
  {
    if constexpr(is_wide_v<U> && !is_wide_v<V>)
    {
      return eve::if_else(v0, v1, wide<V, N>(v2));
    }

    if constexpr(!is_wide_v<U> && is_wide_v<V>)
    {
      return eve::if_else(v0, wide<U, N>(v1), v2);
    }

    if constexpr(!is_wide_v<U> && !is_wide_v<V>)
    {
      using t_t = std::common_type_t<U,V>;
      return eve::if_else(v0, wide<t_t, N>(v1), wide<t_t, N>(v2));
    }
  }
}

#endif
