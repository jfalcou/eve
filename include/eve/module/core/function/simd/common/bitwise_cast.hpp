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
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N, typename Target>
  EVE_FORCEINLINE Target bitwise_cast_( EVE_SUPPORTS(simd_)
                                      , pack<T,N,aggregated_> const& v0, as_<Target> const&
                                      ) noexcept
  {
    using small_tgt = pack< typename Target::value_type
                          , typename Target::cardinal_type::split_type
                          >;

    return Target { bitwise_cast<small_tgt>( v0.slice(lower_) )
                  , bitwise_cast<small_tgt>( v0.slice(upper_) )
                  };
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N, typename Target>
  EVE_FORCEINLINE Target bitwise_cast_( EVE_SUPPORTS(simd_)
                                      , pack<T,N,emulated_> const& v0, as_<Target> const&
                                      ) noexcept
  {
    return map( detail::callable_object<tag::bitwise_cast_>{}
              , v0, as_<typename Target::value_type>{}
              );
  }
} }

#endif
