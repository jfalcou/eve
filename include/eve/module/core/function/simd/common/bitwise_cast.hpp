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
#include <eve/detail/function/slice.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  template< typename T, typename N, typename X1
          , typename U, typename M, typename X2
          , typename = std::enable_if_t<!is_native<X1>::value || ! is_native<X2>::value>
          >
  EVE_FORCEINLINE auto bitwise_cast_( EVE_SUPPORTS(simd_)
                                    , pack<T,N,X1> const& v0, as_<pack<U,M,X2>> const& tgt
                                    ) noexcept
  {
    if constexpr( std::is_same_v<X1, aggregated_> && std::is_same_v<X2, aggregated_> )
    {
      using small_tgt = pack<U, typename M::split_type>;
      return pack<U,M,X2> { bitwise_cast<small_tgt>( v0.slice(lower_) )
                          , bitwise_cast<small_tgt>( v0.slice(upper_) )
                          };
    }
    else
    {
      using type = pack<U,M,X2>;
      constexpr auto sz = (sizeof(v0) < sizeof(type)) ? sizeof(v0) :sizeof(type);

      type that;
      std::memcpy(&that, &v0, sz);

      return that;
    }
  }
} }

#endif
