//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of invgd"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::invgd(T())  , T);
  TTS_EXPR_IS( eve::invgd(v_t()), v_t);
};

//==================================================================================================
// invgd  tests
//==================================================================================================
auto maxi = ::tts::constant([]<typename T>(eve::as<T> const & tgt) { return eve::pio_2(tgt); });
auto mini = ::tts::constant([]<typename T>(eve::as<T> const & tgt) { return -eve::pio_2(tgt); });

TTS_CASE_WITH( "Check behavior of invgd on wide"
        , eve::test::simd::ieee_reals
        , tts::generate( tts::randoms(mini, maxi)
                             , tts::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::invgd;
  using eve::sinh;
  using eve::diff;
  TTS_ULP_EQUAL(invgd(a0), map([](auto e) -> v_t { return std::atanh(std::sin(e)); }, a0) , 4);
  TTS_ULP_EQUAL(invgd(a1), map([](auto e) -> v_t { return std::atanh(std::sin(e)); }, a1) , 4);
};
