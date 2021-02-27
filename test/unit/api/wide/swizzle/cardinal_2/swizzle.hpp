//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/wide.hpp>
#include <eve/logical.hpp>

template<eve::shuffle_pattern Pattern, typename T>
void check_shuffle(T data, Pattern p, auto& runtime, bool verbose)
{
  using ref_type = eve::as_wide_t<T, eve::fixed<2>>;
  using type = typename T::value_type;

  if(verbose) std::cout << "With pattern: "
                        << tts::yellow() << p << tts::reset() << " :"
                        << std::endl;

  ref_type ref( [&](auto i, auto c) { return p(i,c) == eve::na_ ? type{0} : data.get(p(i,c)); });
  TTS_EQUAL( data[p] , ref );
}

TTS_CASE_TPL("Check cardinal-2 swizzle return type", EVE_TYPE)
{
  TTS_EXPR_IS( (T{}[eve::pattern<0,0>]), (eve::as_wide_t<T, eve::fixed<2>>));
}

TTS_CASE_TPL("Check cardinal-2 swizzle behavior - arithmetic register", eve::wide<float>)
{
  T data( [](auto i, auto )   { return 1+i; } );

  auto f = [&]<std::size_t... J>(std::index_sequence<J...>)
  {
    (check_shuffle( data
                  , eve::pattern<std::ptrdiff_t(J-1), std::ptrdiff_t(J)>
                  , runtime, verbose
                  )
    ,...);
  };

  f(std::make_index_sequence<EVE_CARDINAL>{});
}

TTS_CASE_TPL("Check cardinal-2 swizzle behavior - logical register", EVE_TYPE)
{
  eve::logical<T> data( [](auto i, auto )   { return (1+i) % 3 == 1; } );

  auto f = [&]<std::size_t... J>(std::index_sequence<J...>)
  {
    (check_shuffle( data
                  , eve::pattern<std::ptrdiff_t(J-1), std::ptrdiff_t(J)>
                  , runtime, verbose
                  )
    ,...);
  };

  f(std::make_index_sequence<EVE_CARDINAL>{});
}
