//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <tts/tests/relation.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/if_else.hpp>
#include <eve/wide.hpp>

TTS_CASE("ignore_all behavior")
{
  using eve::wide;
  using eve::conditional_expr;
  using eve::ignore_all;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_all_>  );

  using type = wide<float>;

  TTS_EQUAL( ignore_all.mask( as_<type>() )           , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_all,type(42), type(69))) , type(69)                  );
}

TTS_CASE("ignore_none behavior")
{
  using eve::wide;
  using eve::conditional_expr;
  using eve::ignore_none;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_none_>  );

  using type = wide<float>;

  TTS_EQUAL( ignore_none.mask( as_<type>() )            , eve::True( as_<type>() )  );
  TTS_EQUAL( (if_else(ignore_none,type(42), type(69)))  , type(42)                  );
}

TTS_CASE("ignore_last behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_last>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  TTS_EQUAL( ignore_last(0).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(ignore_last(0),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j < c-i; };
    type          ref   = [i,value](auto j, auto c) { return (j < c-i) ? value[j] : 69.f; };

    TTS_EQUAL( ignore_last(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_last(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_last(type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_last(type::static_size),value, type(69))) , type(69)                  );
}

TTS_CASE("ignore_first behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::ignore_first;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_first>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  TTS_EQUAL( ignore_first(0).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(ignore_first(0),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j >= i; };
    type          ref   = [i,value](auto j, auto) { return (j >= i) ? value[j] : 69.f; };

    TTS_EQUAL( ignore_first(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_first(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_first(type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_first(type::static_size),value, type(69))) , type(69)                  );
}
