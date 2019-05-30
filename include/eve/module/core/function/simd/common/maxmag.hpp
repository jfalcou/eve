//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAXMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MAXMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/max.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename U>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(simd_),
                               T const &a,
                               U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return maxmag(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return maxmag(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::maxmag, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::maxmag, a, b);
        }
        else
        {
          auto aa = eve::abs(a);
          auto ab = eve::abs(b);
          return if_else( is_not_greater_equal(ab, aa), a
                        , if_else( is_not_greater_equal(aa, ab), b
                                 , eve::max(a, b) ) );
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::maxmag] - Incompatible types.");
        return {};
      }
    }
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic
  template<typename T, typename U>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(simd_),
                               pedantic_type const &, 
                               T const &a,
                               U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return maxmag[eve::pedantic_](a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return maxmag[eve::pedantic_](U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::maxmag, eve::pedantic_, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::maxmag, eve::pedantic_, a, b);
        }
        else
        {
          auto aa = eve::abs(a);
          auto ab = eve::abs(b);
          return if_else( is_not_greater_equal(ab, aa), a
                        , if_else( is_not_greater_equal(aa, ab), b
                                 , eve::max[eve::pedantic_](a, b) ) );
        }
      }
      else
      {
        static_assert( std::is_same_v<T,U>, "[eve::maxmag[pedantic_]] - Incompatible types.");
        return {};
      }
    }
  }
}

#endif
  
