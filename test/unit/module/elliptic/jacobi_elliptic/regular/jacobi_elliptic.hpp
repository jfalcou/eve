//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/jacobi_elliptic.hpp>
#include <boost/math/special_functions/jacobi_elliptic.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/wide.hpp>



TTS_CASE_TPL("Check eve::jacobi_elliptic behavior", EVE_TYPE)
{
  using eve::jacobi_elliptic;
  using eve::tag::jacobi_elliptic_;
  using elt_t = eve::element_type_t<T>;
  using eve::as;

//  auto inf   =  eve::inf(as<elt_t>());
//   auto minf  =  eve::minf(as<elt_t>());
  auto nan   =  eve::nan(as<elt_t>());
  auto pio_2 =  eve::pio_2(as<elt_t>());
  auto one   =  eve::one(as<elt_t>());
  auto zero  =  eve::zero(as<elt_t>());

// #ifndef boost_simd_no_invalids
//   TTS_ULP_EQUAL(eve::jacobi_elliptic(inf, elt_t(0)), inf, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(minf, elt_t(0)), minf, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(nan, elt_t(0)), nan, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(inf, elt_t(0.5)), nan, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(minf, elt_t(0.5)), nan, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(nan, elt_t(0.5)), nan, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(inf, elt_t(1)), pio_2, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(minf, elt_t(1)), -pio_2, 1.0);
//   TTS_ULP_EQUAL(jacobi_elliptic(nan, elt_t(1)), nan, 1.0);
// #endif
  auto refje = []<typename U>(U x,  U y){
    U cn, dn;
    U sn = boost::math::jacobi_elliptic(y, x, &cn, &dn);
    return std::make_tuple(sn, cn, dn);
  };

  {
    auto [esn, ecn, edn] = jacobi_elliptic(one,elt_t(0));
    auto [bsn, bcn, bdn] = refje(one,elt_t(0));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(zero,elt_t(0));
    auto [bsn, bcn, bdn] = refje(zero,elt_t(0));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(pio_2,elt_t(0));
    auto [bsn, bcn, bdn] = refje(pio_2,elt_t(0));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 3.5);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }

  {
    auto [esn, ecn, edn] = jacobi_elliptic(one,elt_t(0.5));
    auto [bsn, bcn, bdn] = refje(one,elt_t(0.5));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(zero,elt_t(0.5));
    auto [bsn, bcn, bdn] = refje(zero,elt_t(0.5));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(pio_2,elt_t(0.5));
    auto [bsn, bcn, bdn] = refje(pio_2,elt_t(0.5));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 9);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(pio_2,elt_t(0.5));
    auto [bsn, bcn, bdn] = refje(pio_2,elt_t(0.5));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 9);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }

  {
    auto [esn, ecn, edn] = jacobi_elliptic(one,elt_t(1.0));
    auto [bsn, bcn, bdn] = refje(one,elt_t(1.0));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(pio_2,elt_t(1.0));
    auto [bsn, bcn, bdn] = refje(pio_2,elt_t(1.0));
    TTS_ULP_EQUAL(esn, bsn, 1);
    TTS_ULP_EQUAL(ecn, bcn, 1);
    TTS_ULP_EQUAL(edn, bdn, 1.5);
  }
  {
    auto [esn, ecn, edn] = jacobi_elliptic(nan,elt_t(1.0));
    TTS_ULP_EQUAL(esn, nan, 1);
    TTS_ULP_EQUAL(ecn, nan, 1);
    TTS_ULP_EQUAL(edn, nan, 1);
  }
//   {
//     auto [esn, ecn, edn] = jacobi_elliptic(inf,elt_t(1.0));
//     TTS_ULP_EQUAL(esn, elt_t(1), 1);
//     TTS_ULP_EQUAL(ecn, elt_t(0), 1);
//     TTS_ULP_EQUAL(edn, elt_t(0), 1);
//   }
}
