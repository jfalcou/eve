//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template< typename T, typename N, typename X1
          , typename U, typename M, typename X2
          , typename = std::enable_if_t<!is_native<X1>::value || ! is_native<X2>::value>
          >
  EVE_FORCEINLINE auto bitwise_cast_( EVE_SUPPORTS(simd_)
                                    , wide<T,N,X1> const& v0, as_<wide<U,M,X2>> const& tgt
                                    ) noexcept
  {
    wide<U,M,X2> that;

    constexpr auto sz = std::min(sizeof(v0), sizeof(that));
    std::memcpy(&that, &v0, sz);

    return that;
  }
}

#endif
