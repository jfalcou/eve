//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/polynomial.hpp>

#include <boost/math/special_functions/jacobi.hpp>


//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::jacobi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::jacobi(i_t(), T(), T(), T())  , T);
  TTS_EXPR_IS( eve::jacobi(i_t(), v_t(), v_t(), v_t())  , v_t);
};

//==================================================================================================
// Tests for eve::jacobi
//==================================================================================================
TTS_CASE_WITH( "Check behavior of diff jacobi on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::between(-1.0, 1.0)
                            , tts::between(-1.0, 1.0)
                            , tts::between(-1.0, 1.0)
                            , tts::as_integer(tts::ramp(0))
                            )
             )
  <typename T, typename I>(T const& a0, T const& a1, T const& a2, I const & i0)
{
  auto dt = eve::jacobi(i0, a0, a1, a2);
  auto bdt1 = [&](auto i, auto e, auto f,  auto g){return boost::math::jacobi(i, e, f, g); };
  TTS_ULP_EQUAL(dt, eve::detail::map(bdt1, i0, a0, a1, a2), 1000);
};
