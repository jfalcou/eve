//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAXNUMMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE auto maxnummag_(EVE_SUPPORTS(simd_),
                               T const &a,
                               U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return maxnummag(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return maxnummag(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::maxnummag, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::maxnummag, a, b);
        }
        else
        {
          if constexpr(std::is_floating_point_v<typename T::value_type>)
            return maxmag(if_else(is_nan(a),b,a), b);
          else
            return maxmag(a, b);
         }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::maxnummag] - Incompatible types.");
        return {};
      }
    }
  }
}

#endif
  
