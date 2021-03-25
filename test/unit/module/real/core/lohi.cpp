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
#include <eve/function/lohi.hpp>
#include <eve/function/lo.hpp>
#include <eve/function/hi.hpp>
#include <array>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of lohi on wide"
            , eve::test::simd::unsigned_integers

            )
<typename T>(eve::as_<T>)
{
  using elt_t = eve::element_type_t<T>;
  using si_t = eve::detail::downgrade_t<eve::as_integer_t<elt_t, unsigned>>;
  using r_t = eve::as_wide_t<si_t, typename eve::cardinal_t<T>>;

  TTS_EXPR_IS( eve::lohi(T())  , (std::array<r_t, 2>));
  TTS_EXPR_IS( eve::lohi(elt_t()), (std::array<si_t, 2>));
};

//==================================================================================================
// lohi signed tests
//==================================================================================================
EVE_TEST( "Check behavior of lohi on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using elt_t = eve::element_type_t<T>;
  using si_t = eve::detail::downgrade_t<eve::as_integer_t<elt_t, unsigned>>;
  using ui_t = eve::as_wide_t<si_t, typename eve::cardinal_t<T>>;
  auto [lo, hi] = eve::lohi(a0);
  TTS_EQUAL( lo, ui_t([&](auto i, auto) { return eve::lo(a0.get(i)); }));
  TTS_EQUAL( hi, ui_t([&](auto i, auto) { return eve::hi(a0.get(i)); }));
};
