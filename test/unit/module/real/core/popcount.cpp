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
#include <eve/function/popcount.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::popcount(simd)"
              , eve::test::simd::integers
              )
<typename T>(eve::as<T>)
{
  using i_t = eve::as_integer_t<T, unsigned>;
  using v_t = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;
  TTS_EXPR_IS( eve::popcount(T()), i_t  );
  TTS_EXPR_IS( eve::popcount(v_t()), vi_t );
};

//==================================================================================================
// Tests for eve::popcount
//==================================================================================================
EVE_TEST( "Check behavior of eve::popcount(simd)"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using i_t = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::popcount(a0), map([](auto e) -> vi_t { return std::popcount(std::bit_cast<vi_t>(e)); }, a0));
};
