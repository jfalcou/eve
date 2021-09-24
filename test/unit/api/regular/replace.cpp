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

EVE_TEST( "Check behavior of replace_ignored(ignore_all/ignore_none)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0), eve::test::ramp(10))
        )
<typename T>(T data, T replacement)
{
  using eve::ignore_all;
  using eve::ignore_none;

  TTS_EQUAL( eve::replace_ignored(data,ignore_all , replacement), replacement );
  TTS_EQUAL( eve::replace_ignored(data,ignore_none, replacement), data        );
};
/*
EVE_TEST( "Check behavior of replace_ignored(ignore_last)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0) )
        )
<typename T>(T data)
{
  using eve::ignore_last;
  auto replacement = data;
  TTS_EQUAL( eve::replace_ignored(data,ignore_last(0),replacement), replacement);

  for(std::ptrdiff_t i = 1;i <= T::size();i++)
  {
    replacement.set(T::size()-i, 99);
    TTS_EQUAL( eve::replace_ignored(data,ignore_last(i),replacement), replacement );
  }
};

EVE_TEST( "Check behavior of replace_ignored(keep_last)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0), eve::test::ramp(100) )
        )
<typename T>(T data, T replacement)
{
  using eve::keep_last;

  for(std::ptrdiff_t i = 0;i < T::size();i++)
  {
    auto const idx = T::size()-i-1;
    replacement.set(idx, data.get(idx));
    TTS_EQUAL( eve::replace_ignored(data,keep_last(i),replacement), replacement );
  }

  TTS_EQUAL( eve::replace_ignored(data,keep_last(T::size()),replacement), data );
};
*/
/*
EVE_TEST( "Check behavior of replace_ignored(ignore_first)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0) )
        )
<typename T>(T data)
{
  using eve::ignore_first;
  T replacement = data;

  TTS_EQUAL( eve::replace_ignored(data,ignore_first(0),replacement), data );

  for(std::ptrdiff_t i = 1;i <= T::size();i++)
  {
    replacement.set(i-1, 10*(i-1));
    TTS_EQUAL( eve::replace_ignored(data,ignore_first(i),replacement), replacement );
  }
};

EVE_TEST( "Check behavior of replace_ignored(keep_first)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0), eve::test::ramp(100) )
        )
<typename T>(T data, T replacement)
{
  using eve::keep_first;

  TTS_EQUAL( eve::replace_ignored(data,keep_first(0),replacement), replacement );

  for(std::ptrdiff_t i = 1;i <= T::size();i++)
  {
    replacement.set(i-1, data.get(i-1));
    TTS_EQUAL( eve::replace_ignored(data,keep_first(i),replacement), replacement );
  }
};

EVE_TEST( "Check behavior of replace_ignored(keep_between)"
        , eve::test::simd::restricted::all_types
        , eve::test::generate ( eve::test::ramp(0) )
        )
<typename T>(T data)
{
  using eve::keep_between;

  for(int fi = 0;fi < T::size();fi++)
  {
    for(int li = 0;li <= T::size();li++)
    {
      if(fi<=li)
      {
        T replacement = [&](auto i, auto) { return (i >= fi && i < li) ? data.get(i) : 10*i; };
        TTS_EQUAL( eve::replace_ignored(data,keep_between(fi,li),replacement), replacement );
      }
    }
  }
};
*/
