//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/detail/meta.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/quaternion.hpp>
#include <boost/math/quaternion.hpp>

namespace bm = boost::math;
template < typename T> auto cvtbq_eq(bm::quaternion<T> const & bq){
  eve::quaternion<T> eq{bq.R_component_1(),bq.R_component_2(),bq.R_component_3(),bq.R_component_4()};
  return eq;
}

template < typename T> auto cvteq_bq(eve::quaternion<T> const & eq){
  bm::quaternion<T> bq{eve::real(eq), eve::ipart(eq), eve::jpart(eq), eve::kpart(eq)};
  return bq;
}

TTS_CASE_WITH( "Check behavior of exp2 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = typename T::value_type;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  using bq_t = bm::quaternion<e_t>;
  using eq_t = eve::quaternion<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    auto z = eq_t(a0[i],a1[i],a2[i],a3[i]);
    auto l2 = eve::log_2(eve::as<e_t>());
    bq_t bz = bq_t(a0[i],a1[i],a2[i],a3[i])*l2;
    TTS_RELATIVE_EQUAL(eve::exp2(z),  cvtbq_eq(bm::exp(bz)), tol);
  }
};

TTS_CASE_WITH( "Check behavior of exp2 on wide"
        , eve::test::simd::ieee_reals
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = eve::element_type_t<T>;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  using z_t = eve::as_quaternion_t<T>;
  auto z = z_t{a0,a1,a2,a3};
  z_t r;
  auto l2 = eve::log_2(eve::as<e_t>());
  for(int i = 0; i < eve::cardinal_v<T>; ++i){
    bm::quaternion<e_t> bq(a0.get(i), a1.get(i), a2.get(i), a3.get(i));
    eve::quaternion<e_t> eq= cvtbq_eq(bm::exp(bq*l2));
    r.set(i, eq);
  }

  TTS_RELATIVE_EQUAL(eve::exp2(z), r, tol);
};
