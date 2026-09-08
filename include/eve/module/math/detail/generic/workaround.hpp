//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
namespace eve::_
{

template<typename T>
 auto
prevent_gcc_abusive_contract(const T& ab) noexcept
{
  return ab + 0;
}

}
