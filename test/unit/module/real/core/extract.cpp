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
#include <eve/function/extract.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::extract", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using vi_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::extract(T(), int()), v_t );
  TTS_EXPR_IS( eve::extract(T(), vi_t()), v_t );
};

//==================================================================================================
// Tests for eve::extract
//==================================================================================================
EVE_TEST( "Check behavior of eve::extract(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  for(std::size_t i=0; i < eve::cardinal_v<T> ; ++i)
  {
    TTS_EQUAL(eve::extract(a0, i), a0.get(i));
  }
};
