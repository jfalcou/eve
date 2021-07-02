//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/sinhcosh.hpp>
#include <eve/function/diff/cos.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of coshsinh"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinhcosh(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::sinhcosh(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// coshsinh  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const &)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  return T(ovl);
};
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return -maxi(tgt);
};EVE_TEST( "Check behavior of cos on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(  eve::test::randoms(mini, maxi))
                             )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::sinhcosh;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return std::cosh(e); };
  auto refs = [](auto e) -> v_t { return std::sinh(e); };
  auto [s, c] = sinhcosh(a0);
  TTS_ULP_EQUAL(s      , map(refs, a0), 2);
  TTS_ULP_EQUAL(c      , map(refc, a0), 2);
};
