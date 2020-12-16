//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/if_else.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("ignore_all behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_all;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_all_>  );

  using type = wide<T>;

  TTS_EXPR_IS(ignore_all.mask( as_<type>() ), logical<type> );

  TTS_EQUAL( ignore_all.mask( as_<type>() )           , eve::false_( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_all,type(42), type(69))) , type(69)                  );
}

TTS_CASE_TPL("ignore_none behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_none;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_none_>  );

  using type = wide<T>;

  TTS_EXPR_IS(ignore_none.mask( as_<type>() ), logical<type> );

  TTS_EQUAL( ignore_none.mask( as_<type>() )            , eve::true_( as_<type>() )  );
  TTS_EQUAL( (if_else(ignore_none,type(42), type(69)))  , type(42)                  );
}

TTS_CASE_TPL("ignore_last behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_last_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(ignore_last(0).mask( as_<type>() ), logical<type> );

  TTS_EQUAL( ignore_last(0).mask(as_<type>()).bits(), eve::true_(as_<type>()).bits());
  TTS_EQUAL( (if_else(ignore_last(0),value, type(69))), value                   );

  for(int i = 1;i <= type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j < c-i; };
    type          ref   = [i,&value](auto j, auto c) { return (j < c-i) ? value[j] : 69; };

    TTS_EQUAL( ignore_last(i).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_last(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_last(type::static_size).mask(as_<type>())          , eve::false_( as_<type>() ) );
  TTS_EQUAL( (if_else(ignore_last(type::static_size),value, type(69))) , type(69)                  );
}

TTS_CASE_TPL("keep_last behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::keep_last_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_last(0).mask( as_<type>() ), logical<type> );

  TTS_EQUAL( keep_last(type::static_size).mask(as_<type>()).bits(), eve::true_(as_<type>()).bits());
  TTS_EQUAL( (if_else(keep_last(type::static_size),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j >= c-i; };
    type          ref   = [i,&value](auto j, auto c) { return (j >= c-i) ? value[j] : 69.f; };

    TTS_EQUAL( keep_last(i).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(keep_last(i),value, type(69))), ref);
  }

  TTS_EQUAL( keep_last(0).mask(as_<type>()).bits(), eve::false_(as_<type>()).bits() );
  TTS_EQUAL( (if_else(keep_last(0),value, type(69))) , type(69)                     );
}

TTS_CASE_TPL("ignore_first behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_first;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_first_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(ignore_first(0).mask( as_<type>() ), logical<type> );

  TTS_EQUAL( ignore_first(0).mask(as_<type>()).bits(), eve::true_(as_<type>()).bits());
  TTS_EQUAL( (if_else(ignore_first(0),value, type(69))), value  );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j >= i; };
    type          ref   = [i,&value](auto j, auto) { return (j >= i) ? value[j] : 69.f; };

    TTS_EQUAL( ignore_first(i).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_first(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_first(type::static_size).mask(as_<type>()).bits(), eve::false_(as_<type>()).bits());
  TTS_EQUAL( (if_else(ignore_first(type::static_size),value, type(69))) , type(69)                );
}

TTS_CASE_TPL("keep_first behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_first;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::keep_first_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_first(0).mask( as_<type>() ), logical<type> );

  TTS_EQUAL( keep_first(type::static_size).mask(as_<type>()).bits(), eve::true_(as_<type>()).bits());
  TTS_EQUAL( (if_else(keep_first(type::static_size),value, type(69))), value                   );

  for(int i = 1;i < type::static_size;i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j < i; };
    type          ref   = [i,&value](auto j, auto) { return (j < i) ? value[j] : 69.f; };

    TTS_EQUAL( keep_first(i).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(keep_first(i),value, type(69))), ref);
  }

  TTS_EQUAL( keep_first(0).mask(as_<type>()).bits(), eve::false_(as_<type>()).bits());
  TTS_EQUAL( (if_else(keep_first(0),value, type(69))) , type(69)                    );
}

TTS_CASE_TPL("keep_between behavior", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_between;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::keep_between_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_between(0,1).mask( as_<type>() ), logical<type> );

  for(int fi = 0;fi < type::static_size;fi++)
  {
    for(int li = 0;li <= type::static_size;li++)
    {
      if(fi<=li)
      {
        logical<type> mref  = [&](auto j, auto) { return (j >= fi && j < li); };
        type          ref   = [&](auto j, auto) { return mref[j] ? value[j] : 69.f; };

        TTS_EQUAL( keep_between(fi,li).mask(as_<type>()).bits(), mref.bits() );
        TTS_EQUAL( (if_else(keep_between(fi,li),value, type(69))), ref);
      }
    }
  }
}

TTS_CASE_TPL("ignore_first/last combination", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_first;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as_;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_extrema_>  );

  using type = wide<T>;
  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS( ((ignore_first(1) && ignore_last(0)).mask( as_<type>() )), logical<type> );

  // Check that ignore_first(i) === ignore_first(i) && ignore_last(0)
  for(int i = 0;i <= type::static_size; i++)
  {
    auto mref  = ignore_first(i).mask(as_<type>());
    type ref   = if_else(ignore_first(i), value, T(69));

    TTS_EQUAL( (ignore_first(i) && ignore_last(0)).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_first(i) && ignore_last(0),value, type(69))), ref);
  }

  // Check that ignore_last(i) === ignore_first(0) && ignore_last(i)
  for(int i = 0;i <= type::static_size; i++)
  {
    auto mref  = ignore_last(i).mask(as_<type>());
    type ref   = if_else(ignore_last(i), value, T(69));

    TTS_EQUAL( (ignore_first(0) && ignore_last(i)).mask(as_<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_first(0) && ignore_last(i),value, type(69))), ref);
  }

  // All masks combo
  for(int fi = 1;fi <= type::static_size;fi++)
  {
    for(int li = 1;li <= type::static_size;li++)
    {
      auto mref  = ignore_first(fi).mask(as_<type>()) && ignore_last(li).mask(as_<type>());
      type ref   = if_else(mref, value, T(69));

      TTS_EQUAL( (ignore_first(fi) && ignore_last(li)).mask(as_<type>()).bits(), mref.bits() );
      TTS_EQUAL( (if_else(ignore_first(fi) && ignore_last(li),value, type(69))), ref);
    }
  }
}
