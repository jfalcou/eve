//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , T const &b) noexcept
  requires(T, vectorizable<T>)
  {
    return rem(a, b, toward_zero_);
  }

 //-----------------------------------------------------------------------------------------------
  //Pedantic_
   template<typename T>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const & pdt_
                                     , T const &a
                                     , T const &b) noexcept
  requires(T, vectorizable<T>)
  {
    return pedantic_(rem)(a, b, toward_zero_);
  }

  //-----------------------------------------------------------------------------------------------
  //Tagged
  template<typename T, typename Tag>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , T const &a0
                                     , T const &a1
                                     , Tag const & tag_) noexcept
  requires(T, vectorizable<T>)
  {
    return  fnma(a1, div(a0, a1, tag_), a0);
  }

  //-----------------------------------------------------------------------------------------------
  //Pedantic_,  Tagged
  template<typename T, typename Tag>
  EVE_FORCEINLINE constexpr auto rem_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const & pdt_
                                     , T const &a0
                                     , T const &a1
                                     , Tag const & tag_
 ) noexcept
  requires(T, vectorizable<T>)
  {
    return if_else(is_nez(a1), fnma(a1, div(a0, a1, tag_), a0), a0); 
  }


  
}

#endif
