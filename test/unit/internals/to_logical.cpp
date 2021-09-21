//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/function/to_logical.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

EVE_TEST( "Check detail::to_logical"
        , eve::test::simd::all_types
        , eve::test::generate( eve::test::randoms(0,2) )
        )
<typename T>(T mixed_values)
{
  eve::as_logical_t<T> all_true(true);
  eve::as_logical_t<T> all_false(false);
  eve::as_logical_t<T> mixed_bool([&](auto i, auto) { return mixed_values.get(i) != 0; });

  TTS_EQUAL( eve::detail::to_logical(T(42))       , all_true  );
  TTS_EQUAL( eve::detail::to_logical(T(0))        , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_values), mixed_bool);

  TTS_EQUAL( eve::detail::to_logical(all_true)   , all_true  );
  TTS_EQUAL( eve::detail::to_logical(all_false)  , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_bool) , mixed_bool);
};
