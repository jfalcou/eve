//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/hi.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hi on wide"
            , eve::test::simd::unsigned_integers

            )
<typename T>(eve::as_<T>)
{
  using elt_t = eve::element_type_t<T>;
  using si_t = eve::detail::downgrade_t<eve::as_integer_t<elt_t, unsigned>>;
  using r_t = eve::as_wide_t<si_t, typename eve::cardinal_t<T>>;

  TTS_EXPR_IS( eve::hi(T())  , r_t);
  TTS_EXPR_IS( eve::hi(elt_t()), si_t);
};

//==================================================================================================
// hi signed tests
//==================================================================================================
EVE_TEST( "Check behavior of hi on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using elt_t = eve::element_type_t<T>;
  using si_t = eve::detail::downgrade_t<eve::as_integer_t<elt_t, unsigned>>;
  using ui_t = eve::as_wide_t<si_t, typename eve::cardinal_t<T>>;
  TTS_EQUAL( eve::hi(a0), ui_t([&](auto i, auto) { return eve::hi(a0.get(i)); }));
};
