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

auto data = []<typename T>(eve::as_<T>, auto)
{
  using d_t = std::array<eve::element_type_t<T>,eve::cardinal_v<T>>;

  d_t v;
  for(std::size_t i=0;i<v.size();++i) v[i] = i%2 == 0 ? 69 : 0;

  return std::make_tuple(v);
};

auto wide_to_logical = []<typename T> ( auto& runtime, bool verbose, auto const&
                                      , T mixed_values
                                      )
{
  eve::as_logical_t<T> all_true(true);
  eve::as_logical_t<T> all_false(false);
  eve::as_logical_t<T> mixed_bool([](auto i, auto) { return i%2 == 0; });

  TTS_EQUAL( eve::detail::to_logical(T(42))       , all_true  );
  TTS_EQUAL( eve::detail::to_logical(T(0))        , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_values), mixed_bool);

  TTS_EQUAL( eve::detail::to_logical(all_true)   , all_true  );
  TTS_EQUAL( eve::detail::to_logical(all_false)  , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_bool) , mixed_bool);
};

EVE_TEST_BED( "Check detail::to_logical"
            , eve::test::simd::all_types
            , data, wide_to_logical
            );
