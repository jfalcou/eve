//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>


TTS_CASE_WITH( "Check behavior of cos on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-200, 200)
                              , tts::randoms(0.01, +0.01)
                             )
             )
  <typename T>(T const& , T const& )
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  auto mf = eve::maxflint(eve::as<e_t>());
  TTS_EXPECT(eve::pedantic(eve::is_flint)(mf));
  TTS_EXPECT(eve::dec(mf) != mf);
  TTS_EXPECT(eve::inc(mf) == mf);

};
