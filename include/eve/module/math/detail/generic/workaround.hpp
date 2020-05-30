/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_DETAIL_GENERIC_WORKAROUND_HPP_INCLUDED
#define EVE_MODULE_MATH_DETAIL_GENERIC_WORKAROUND_HPP_INCLUDED
namespace eve::detail
{
  
  template < typename T>
  EVE_FORCEINLINE auto prevent_gcc_abusive_contract(const T & ab) noexcept
  {
    return ab+0;
  }
  
}

#endif
