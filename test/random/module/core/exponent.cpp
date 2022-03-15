//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

EVE_TEST_TYPES("Random check for eve::exponent", eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  using i_t = eve::as_integer_t<e_t>;
  auto internal_f = [](auto e) -> i_t {  int exp; std::frexp(e, &exp); return i_t(exp); };
  auto std_exponent = [internal_f](auto e) { return eve::dec(internal_f(e)); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_exponent, eve::exponent );
};
