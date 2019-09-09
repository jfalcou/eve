//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ATAN2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ATAN2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/tags.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <eve/module/core/detail/scalar/atan_kernel.hpp>
#include <eve/module/core/detail/simd/atan_kernel.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                                        , T const &a0
                                        , U const &a1    
                                        ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return atan2(a0, T{a1});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return atan2(U{a0},a1);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::atan2, a0, a1); 
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::atan2, a0, a1);
        }
        else if constexpr(std::is_floating_point_v<detail::value_type_t<T>>)
        {
          auto q = eve::abs(a0/a1); 
          auto z = detail::atan_kernelw(q, eve::rec(q));
          return if_else(is_positive(a1), z, Pi(as(a0))*signnz(a0));
        }
        else 
        {
          static_assert(std::is_floating_point_v<detail::value_type_t<T>>
                       , "[atan2 simd] - vectorized type is not an IEEEValue"); 
        }
      }
    }
  }

  
  template<typename T, typename U>
  EVE_FORCEINLINE auto atan2_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &  
                             , T const &a0
                             , U const &a1    
                             ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    if constexpr( !is_vectorized_v<U> )
    {
      return atan2(a0, T{a1});
    }
    else if constexpr( !is_vectorized_v<T> )
    {
      return atan2(U{a0},a1);
    }
    else
    {
      if constexpr(std::is_same_v<T,U>)
      {
        if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::atan2, eve::pedantic_, a0, a1); 
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::atan2, eve::pedantic_, a0, a1);
        }
        else if constexpr(std::is_floating_point_v<detail::value_type_t<T>>)
        {
          T a00 = a0, a10 = a1;
#ifndef EVE_NO_INFINITIES
          auto test1 =  eve::logical_and(eve::is_infinite(a0),  eve::is_infinite(a1));
          a00 =  eve::if_else(test1, eve::copysign(One(as(a0)), a00), a00);
          a10 =  eve::if_else(test1, eve::copysign(One(as(a0)), a10), a10);
#endif
          T q = eve::abs(a00/a10);
          T z = atan_kernelw(q, rec(q));
          //T z = atan(abs(a0/a1));  // case a1 > 0,  a0 > 0
          T sgn = signnz(a0);
          z = eve::if_else(eve::is_positive(a10), z, eve::Pi(as(a0))-z)*sgn;
          z = eve::if_else( eve::is_eqz(a00),
                            eve::if_else( eve::is_negative(a10),  eve::Pi(as(a0))*sgn, eve::zero_),
                            z);
#ifdef EVE_NO_NANS
          return z;
#else
          return  eve::if_else( eve::logical_or( eve::is_nan(a00), eve::is_nan(a10))
                              ,  eve::allbits_, z);
#endif
        }
        else 
        {
          static_assert(std::is_floating_point_v<T>
                       , "[atan2[pedantic_] simd] - not supported for integral types"); 
        }    
      }
    }
  }
}

#endif
