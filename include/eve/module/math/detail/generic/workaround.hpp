//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
