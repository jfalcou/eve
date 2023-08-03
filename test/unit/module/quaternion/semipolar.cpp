//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>
#include <boost/math/quaternion.hpp>

namespace bm = boost::math;
template < typename T> auto cvtbq_eq(bm::quaternion<T> const & bq){
  eve::quaternion<T> eq{bq.R_component_1(),bq.R_component_2(),bq.R_component_3(),bq.R_component_4()};
  return eq;
}


TTS_CASE_WITH( "Check behavior of semipolar on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate( tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            )
             )
<typename T>(T const& a0, T const& a1)
{
  using e_t = typename T::value_type;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_RELATIVE_EQUAL( eve::from_semipolar(e, f, f, e)
                        , cvtbq_eq(bm::semipolar(e,f, f, e)), tol);
    }
  }
};

TTS_CASE_WITH( "Check behavior of semipolar on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            )
             )
  <typename T>(T const& a0 , T const& a1, T const& a2, T const& a3)
{
  using e_t = eve::element_type_t<T>;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  using z_t = eve::as_quaternion_t<T>;
  z_t r;
  for(int i = 0; i < eve::cardinal_v<T>; ++i){
    eve::quaternion<e_t> eq= cvtbq_eq(bm::semipolar(a0.get(i), a1.get(i), a2.get(i), a3.get(i)));
    r.set(i, eq);
  }

  TTS_RELATIVE_EQUAL(eve::from_semipolar(a0, a1, a2, a3), r, tol);
};
