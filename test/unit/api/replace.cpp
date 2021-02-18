//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/replace.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("replace with ignore_all", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::ignore_all;

  wide<T> data([](auto i, auto) { return 1+i; } );
  wide<T> ref([](auto i, auto) { return 10*i; } );

  TTS_EQUAL( eve::replace_ignored(data,ignore_all,ref), ref );
}

TTS_CASE_TPL("replace with ignore_none", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::ignore_none;

  wide<T> data([](auto i, auto) { return 1+i; } );

  TTS_EQUAL( eve::replace_ignored(data,ignore_none,69), data );
}

TTS_CASE_TPL("replace with ignore_last", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::ignore_last;

  wide<T> data([](auto i, auto) { return 1+i; } );
  wide<T> ref = data;

  TTS_EQUAL( eve::replace_ignored(data,ignore_last(0),ref), ref );

  for(std::ptrdiff_t i = 1;i <=wide<T>::size();i++)
  {
    ref.set(wide<T>::size()-i, 99);
    TTS_EQUAL( eve::replace_ignored(data,ignore_last(i),ref), ref );
  }
}

TTS_CASE_TPL("replace with keep_last", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::keep_last;

  wide<T> data([](auto i, auto) { return 1+i; } );
  wide<T> ref([](auto i, auto) { return 10*i; } );

  for(std::ptrdiff_t i = 0;i < wide<T>::size();i++)
  {
    auto const idx = wide<T>::size()-i-1;
    ref.set(idx, data.get(idx));
    TTS_EQUAL( eve::replace_ignored(data,keep_last(i),ref), ref );
  }

  TTS_EQUAL( eve::replace_ignored(data,keep_last(wide<T>::size()),ref), data );
}

TTS_CASE_TPL("replace with ignore_first", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::ignore_first;

  wide<T> data([](auto i, auto) { return 1+i; } );
  wide<T> ref = data;

  TTS_EQUAL( eve::replace_ignored(data,ignore_first(0),ref), data );

  for(std::ptrdiff_t i = 1;i <= wide<T>::size();i++)
  {
    ref.set(i-1, 10*(i-1));
    TTS_EQUAL( eve::replace_ignored(data,ignore_first(i),ref), ref );
  }
}

TTS_CASE_TPL("replace with keep_first", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::keep_first;

  wide<T> data([](auto i, auto) { return 1+i; } );
  wide<T> ref([](auto i, auto) { return 10*i; } );

  TTS_EQUAL( eve::replace_ignored(data,keep_first(0),ref), ref );

  for(std::ptrdiff_t i = 1;i <= wide<T>::size();i++)
  {
    ref.set(i-1, data.get(i-1));
    TTS_EQUAL( eve::replace_ignored(data,keep_first(i),ref), ref );
  }
}


TTS_CASE_TPL("replace with keep_between", TTS_NUMERIC_TYPES)
{
  using eve::wide;
  using eve::keep_between;

  wide<T> data([](auto i, auto) { return 1+i; } );

  for(int fi = 0;fi < wide<T>::size();fi++)
  {
    for(int li = 0;li <= wide<T>::size();li++)
    {
      if(fi<=li)
      {
        wide<T> ref = [&](auto i, auto) { return (i >= fi && i < li) ? 1+i : 10*i; };
        TTS_EQUAL( eve::replace_ignored(data,keep_between(fi,li),ref), ref );
      }
    }
  }
}
