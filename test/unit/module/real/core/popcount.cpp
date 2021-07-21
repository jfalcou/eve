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
#include <eve/function/bit_cast.hpp>
//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::popcount(simd)"
              , eve::test::simd::unsigned_integers
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::popcount(T()), T  );
  TTS_EXPR_IS( eve::popcount(v_t()), v_t );
};

//==================================================================================================
// Tests for eve::popcount
//==================================================================================================
EVE_TEST( "Check behavior of eve::popcount(simd)"
        , eve::test::simd::unsigned_integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, M const& )
{
  using eve::detail::map;
  using i_t = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::popcount(a0), map([](auto e) -> vi_t { return std::popcount(std::bit_cast<vi_t>(e)); }, a0));
//  TTS_EQUAL(eve::popcount[t](a0), eve::if_else(t, eve::popcount(a0), a0));
};
