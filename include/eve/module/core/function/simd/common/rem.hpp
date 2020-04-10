//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/roundings.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    return rem(a, b, toward_zero_);
  }

 //-----------------------------------------------------------------------------------------------
  //Pedantic_
   template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const & pdt_
                                     , T const &a
                                     , U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    return pedantic_(rem)(a, b, toward_zero_);
  }

  //-----------------------------------------------------------------------------------------------
  //Tagged
  template<typename T, typename U, typename Tag>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , U const &b
                                     , Tag const & tag_) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::rem, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b), tag_ );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::rem, abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b), tag_ );
    }
    else if constexpr( is_Vectorized_v<T> && is_Vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        return  fnma(b, div(a, b, tag_), a);
      }
    }
    else //if constexpr( is_Vectorized_v<T> || is_Vectorized_v<U> )
    {
      return eve::rem(abi_cast<U>(a), abi_cast<T>(b), tag_);
    }
  }

  //-----------------------------------------------------------------------------------------------
  //Pedantic_,  Tagged
  template<typename T, typename U, typename Tag>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const & pdt_
                                     , T const &a
                                     , U const &b
                                     , Tag const & tag_) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( pdt_(eve::rem), abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b), tag_ );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( pdt_(eve::rem), abi_cast<value_type_t<U>>(a)
                      , abi_cast<value_type_t<T>>(b), tag_ );
    }
    else if constexpr( is_Vectorized_v<T> && is_Vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        return  fnma(b, div(a, b, tag_), a);
      }
    }
    else //if constexpr( is_Vectorized_v<T> || is_Vectorized_v<U> )
    {
      return if_else (is_nez(b), fnma(b, div(a, b, tag_), a), a); 
    } 
  }
}

#endif
