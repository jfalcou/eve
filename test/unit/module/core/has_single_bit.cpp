//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of has_single_bit on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::has_single_bit(T())  , eve::logical<T>);
  TTS_EXPR_IS( eve::has_single_bit(v_t()), eve::logical<v_t>);
};


//==================================================================================================
// has_single_bit(simd) tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of has_single_bit(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , tts::generate(tts::ramp(1))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_floating_point_t<v_t>;
  TTS_EQUAL( eve::has_single_bit(a0), map([](auto e) -> eve::logical<v_t> { return std::exp2(std::trunc(std::log2(f_t(e)))) == f_t(e); }, a0));
};
