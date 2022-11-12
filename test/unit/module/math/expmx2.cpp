//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of exp", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::expmx2(T()), T);
  TTS_EXPR_IS(eve::expmx2(T()), T);
  TTS_EXPR_IS(eve::expmx2(v_t()), v_t);
};

//==================================================================================================
// expmx2  tests
//==================================================================================================
auto mini =
    tts::constant([]<typename T>(eve::as<T> const& tgt) { return -eve::sqrt(eve::maxlog(tgt)); });
auto maxi =
    tts::constant([]<typename T>(eve::as<T> const& tgt) { return eve::sqrt(eve::maxlog(tgt)); });

TTS_CASE_WITH("Check behavior of exp on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi))
             )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::expmx2(a0),
                map(
                    [](auto e) -> v_t
                    {
                      long double le = e;
                      return std::exp(-le * le);
                    },
                    a0),
                200);
};

TTS_CASE_TPL("Check expmx2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL(eve::expmx2(T(1)), eve::exp(-T(1)), 0.5);
  TTS_ULP_EQUAL(eve::expmx2(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::expmx2(T(4)), eve::exp(-T(16)), 0.5);
  TTS_ULP_EQUAL(eve::expmx2(T(-4)), eve::exp(-T(16)), 0.5);
  TTS_IEEE_EQUAL(eve::expmx2(eve::nan(as<T>())), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(eve::expmx2(eve::inf(as<T>())), eve::zero(as<T>()));
  TTS_IEEE_EQUAL(eve::expmx2(eve::minf(as<T>())), eve::zero(as<T>()));
  TTS_IEEE_EQUAL(eve::expmx2(T(-0.)), T(1));
  TTS_ULP_EQUAL(eve::expmx2(T(-1)), eve::exp(-T(1)), 0.5);
};


//==================================================================================================
// Tests for masked expmx2
//==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::expmx2)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//               tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::expmx2[mask](a0),
//             eve::if_else(mask, eve::expmx2(a0), a0));
// };
