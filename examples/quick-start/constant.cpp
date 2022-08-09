//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  using eve::wide;

  // Generates the constant Pi of the same type than 4.
  std::cout << eve::pi( eve::as(4.) ) << "\n";

  // Generates a wide<int> filled with the appropriate sign mask
  std::cout << std::hex << eve::signmask( eve::as<wide<int>>{} ) << "\n";
}
