//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COPYSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/signnz.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto copysign_(EVE_SUPPORTS(simd_)
                                , T const &a
                                , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return copysign(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return copysign(U{a},b);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::copysign, a, b);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::copysign, a, b);
        }
        else
        {
          if constexpr(std::is_floating_point_v<T>)
            return bitwise_or(bitofsign(b), bitwise_notand(Signmask(as(a)), a));
          else
          {
            if constexpr(std::is_unsigned_v<T>)
              return  a; 
            else
              return if_else(a == Valmin(as(a)) && is_ltz(b), Valmax(as(a)), eve::abs(a)*signnz(b));
          }
        }
      }
    }
  }
}

#endif
