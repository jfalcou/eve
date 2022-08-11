//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
namespace eve::detail
{
  
  template < typename T>
  EVE_FORCEINLINE auto prevent_gcc_abusive_contract(const T & ab) noexcept
  {
    return ab+0;
  }
  
}

