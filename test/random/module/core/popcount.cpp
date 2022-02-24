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
#include <bit>

EVE_TEST_TYPES("Random check for eve::popcount", eve::test::simd::unsigned_integers)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  using u_t =  eve::as_integer_t<T, unsigned>;
  using su_t =  eve::element_type_t<u_t>;
  auto std_popcount = [](auto e) -> su_t { return std::popcount(e); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_popcount, eve::popcount );
 };
