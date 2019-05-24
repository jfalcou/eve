//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_WIDE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_WIDE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  // Required by the aggregate skeleton - IF YOU END UP HERE, YOU'VE BEEN A NAUGHTY USER
  template<typename T, typename U>
  U wide_cast_(EVE_SUPPORTS(simd_),T const &,as_<U> const&);


  // Don't do anything if we idem-cast
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto wide_cast_ ( EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const & v0, as_<T> const&
                                  ) noexcept
  {
    return v0;
  }

  // Generic case for arithmetic
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE wide<U,N> wide_cast_( EVE_SUPPORTS(simd_),
                                        wide<T, N, ABI> const & v0, as_<U> const& tgt
                                      ) noexcept
  {
    // Both source and target needs to be aggregate for the optimization to make sense
    if constexpr( is_aggregated_v<ABI> && is_aggregated_v<typename wide<U,N>::abi_type>)
    {
      return aggregate(eve::wide_cast, v0, tgt);
    }
    else
    {
      // If not, just map static_cast
      return map( [](auto e, auto) { return static_cast<U>(e); }, v0, tgt );
    }
  }
}

#endif
