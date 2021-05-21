//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/rat.hpp>
#include <tuple>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::rat(scalar)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  using v_t =  eve::element_type_t<T>;
  TTS_EXPR_IS( eve::rat(T())                    , (std::tuple<T, T>)  );
  TTS_EXPR_IS( eve::rat(T(), T())               , (std::tuple<T, T>) );
  TTS_EXPR_IS( eve::rat(T(), v_t())             , (std::tuple<T, T>) );
  TTS_EXPR_IS( eve::rat(v_t(), v_t())           , (std::tuple<v_t, v_t>)  );
};



//==================================================================================================
// Tests for eve::rat
//==================================================================================================
EVE_TEST( "Check behavior of eve::rat(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(1.0))
        )
<typename T>(T const& a0)
{
//   using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto [n, d] = eve::rat(a0/17);
  TTS_EQUAL(n, map([](auto e) -> v_t { return  e; }, a0));
  TTS_EQUAL(d, T(17));
};
