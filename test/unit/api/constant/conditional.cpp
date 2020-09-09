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

  std::cout << ignore_all << "\n";
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

  std::cout << ignore_none << "\n";
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

  TTS_EXPECT( conditional_expr<eve::ignore_last_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << ignore_last(0) << "\n";
  TTS_EQUAL( ignore_last(0).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(ignore_last(0),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j < c-i; };
    type          ref   = [i,value](auto j, auto c) { return (j < c-i) ? value[j] : 69.f; };

    std::cout << ignore_last(i) << "\n";
    TTS_EQUAL( ignore_last(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_last(i),value, type(69))), ref);
  }

    std::cout << ignore_last(type::static_size) << "\n";
  TTS_EQUAL( ignore_last(type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_last(type::static_size),value, type(69))) , type(69)                  );
}

TTS_CASE("keep_last behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::keep_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::keep_last_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << keep_last(type::static_size) << "\n";
  TTS_EQUAL( keep_last(type::static_size).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(keep_last(type::static_size),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j >= c-i; };
    type          ref   = [i,value](auto j, auto c) { return (j >= c-i) ? value[j] : 69.f; };

    std::cout << keep_last(i) << "\n";
    TTS_EQUAL( keep_last(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(keep_last(i),value, type(69))), ref);
  }

    std::cout << keep_last(0) << "\n";
  TTS_EQUAL( keep_last(0).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(keep_last(0),value, type(69))) , type(69)                  );
}

TTS_CASE("ignore_first behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::ignore_first;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_first_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << ignore_first(0) << "\n";
  TTS_EQUAL( ignore_first(0).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(ignore_first(0),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j >= i; };
    type          ref   = [i,value](auto j, auto) { return (j >= i) ? value[j] : 69.f; };

    std::cout << ignore_first(i) << "\n";
    TTS_EQUAL( ignore_first(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_first(i),value, type(69))), ref);
  }

  std::cout << ignore_first(type::static_size) << "\n";
  TTS_EQUAL( ignore_first(type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_first(type::static_size),value, type(69))) , type(69)                  );
}

TTS_CASE("keep_first behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::keep_first;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::keep_first_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << keep_first(type::static_size) << "\n";
  TTS_EQUAL( keep_first(type::static_size).mask(as_<type>())         , eve::True( as_<type>() ));
  TTS_EQUAL( (if_else(keep_first(type::static_size),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j < i; };
    type          ref   = [i,value](auto j, auto) { return (j < i) ? value[j] : 69.f; };

    std::cout << keep_first(i) << "\n";
    TTS_EQUAL( keep_first(i).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(keep_first(i),value, type(69))), ref);
  }

  std::cout << keep_first(0) << "\n";
  TTS_EQUAL( keep_first(0).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(keep_first(0),value, type(69))) , type(69)                  );
}

TTS_CASE("ignore_between behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::ignore_between;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_between_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << ignore_between(type::static_size,type::static_size) << "\n";
  TTS_EQUAL ( ignore_between(type::static_size,type::static_size).mask(as_<type>())
            , eve::True( as_<type>() )
            );
  TTS_EQUAL( (if_else(ignore_between(type::static_size,type::static_size),value,type(69))), value);

  std::cout << ignore_between(0,type::static_size) << "\n";
  TTS_EQUAL( ignore_between(0,type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_between(0,type::static_size),value, type(69))) , type(69)                  );

  for(int fi = 0;fi < type::static_size;fi++)
  {
    for(int li = 0;li < type::static_size;li++)
    {
      logical<type> mref  = [=](auto j, auto)       { return !(j >= fi && j <= li); };
      type          ref   = [=](auto j, auto) { return !(j >= fi && j <= li) ? value[j] : 69.f; };

      std::cout << ignore_between(fi,li) << "\n";
      TTS_EQUAL( ignore_between(fi,li).mask(as_<type>()), mref );
      TTS_EQUAL( (if_else(ignore_between(fi,li),value, type(69))), ref);
    }
  }
}

TTS_CASE("keep_between behavior")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::keep_between;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::keep_between_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  std::cout << keep_between(0,type::static_size) << "\n";
  TTS_EQUAL ( keep_between(0,type::static_size).mask(as_<type>())
            , eve::True( as_<type>() )
            );
  TTS_EQUAL( (if_else(keep_between(0,type::static_size),value,type(69))), value);

  std::cout << keep_between(type::static_size,type::static_size) << "\n";
  TTS_EQUAL( keep_between(type::static_size,type::static_size).mask(as_<type>())          , eve::False( as_<type>() ) );
  TTS_EQUAL( (if_else(keep_between(type::static_size,type::static_size),value, type(69))) , type(69)                  );

  for(int fi = 0;fi < type::static_size;fi++)
  {
    for(int li = 0;li < type::static_size;li++)
    {
      logical<type> mref  = [=](auto j, auto)       { return (j >= fi && j <= li); };
      type          ref   = [=](auto j, auto) { return (j >= fi && j <= li) ? value[j] : 69.f; };

      std::cout << keep_between(fi,li) << "\n";
      TTS_EQUAL( keep_between(fi,li).mask(as_<type>()), mref );
      TTS_EQUAL( (if_else(keep_between(fi,li),value, type(69))), ref);
    }
  }
}

TTS_CASE("ignore_first/last combination")
{
  using eve::wide;
  using eve::logical;
  using eve::conditional_expr;
  using eve::ignore_first;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( conditional_expr<eve::ignore_extrema_>  );

  using type = wide<float>;
  type value = [](auto i, auto) { return 1.f+i; };

  // Check that ignore_first(i) === ignore_first(i) && ignore_last(0)
  for(int i = 0;i <= type::static_size; i++)
  {
    logical<type> mref  = ignore_first(i).mask(as_<type>());
    type          ref   = if_else(ignore_first(i), value, 69);

    TTS_EQUAL( (ignore_first(i) && ignore_last(0)).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_first(i) && ignore_last(0),value, type(69))), ref);
  }

  // Check that ignore_last(i) === ignore_first(0) && ignore_last(i)
  for(int i = 0;i <= type::static_size; i++)
  {
    logical<type> mref  = ignore_last(i).mask(as_<type>());
    type          ref   = if_else(ignore_last(i), value, 69);

    TTS_EQUAL( (ignore_first(0) && ignore_last(i)).mask(as_<type>()), mref );
    TTS_EQUAL( (if_else(ignore_first(0) && ignore_last(i),value, type(69))), ref);
  }

  // All masks combo
  for(int fi = 1;fi <= type::static_size;fi++)
  {
    for(int li = 1;li <= type::static_size;li++)
    {
      logical<type> mref  = ignore_first(fi).mask(as_<type>()) && ignore_last(li).mask(as_<type>());
      type          ref   = if_else(mref, value, 69);

      std::cout << (ignore_first(fi) && ignore_last(li)) << "\n";
      std::cout << (ignore_first(fi) && ignore_last(li)).mask(as_<type>()) << "\n";

      TTS_EQUAL( (ignore_first(fi) && ignore_last(li)).mask(as_<type>()), mref );
      TTS_EQUAL( (if_else(ignore_first(fi) && ignore_last(li),value, type(69))), ref);
    }
  }
}
