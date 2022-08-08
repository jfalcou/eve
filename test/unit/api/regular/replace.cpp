//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: BSL-1.0-1.0
**/
#include <eve/module/core.hpp>
//==================================================================================================
#include "test.hpp"

TTS_CASE_WITH( "Check behavior of replace_ignored(ignore_all/ignore_none)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0), tts::ramp(10))
        )
<typename T>(T data, T replacement)
{
  using eve::ignore_all;
  using eve::ignore_none;

  TTS_EQUAL( eve::replace_ignored(data,ignore_all , replacement), replacement );
  TTS_EQUAL( eve::replace_ignored(data,ignore_none, replacement), data        );
};

TTS_CASE_WITH( "Check behavior of replace_ignored(ignore_last)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0) )
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

TTS_CASE_WITH( "Check behavior of replace_ignored(keep_last)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0), tts::ramp(100) )
        )
<typename T>(T data, T replacement)
{
  using eve::keep_last;

  for(std::ptrdiff_t i = 0;i <= T::size();i++)
  {
    T reference = [&](auto e, auto){ return e >= (T::size()-i) ? data.get(e) : replacement.get(e);};
    TTS_EQUAL( eve::replace_ignored(data,keep_last(i),replacement), reference );
  }
};

TTS_CASE_WITH( "Check behavior of replace_ignored(ignore_first)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0) )
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

TTS_CASE_WITH( "Check behavior of replace_ignored(keep_first)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0), tts::ramp(100) )
        )
<typename T>(T data, T replacement)
{
  using eve::keep_first;

  TTS_EQUAL( eve::replace_ignored(data,keep_first(0),replacement), replacement );

  for(std::ptrdiff_t i = 1;i <= T::size();i++)
  {
    T reference = [&](auto e, auto) { return e < i ? data.get(e) : replacement.get(e); };
    TTS_EQUAL( eve::replace_ignored(data,keep_first(i),replacement), reference );
  }
};

TTS_CASE_WITH( "Check behavior of replace_ignored(keep_between)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0) )
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

TTS_CASE_WITH( "Check behavior of replace_ignored(ignore_extrema)"
        , eve::test::simd::all_types
        , tts::generate ( tts::ramp(0) )
        )
<typename T>(T data)
{
  using eve::ignore_extrema;

  for(int fi = 0;fi < T::size();fi++)
  {
    for(int li = 0;li <= T::size();li++)
    {
      if(fi+li <= T::size())
      {
        T replacement = [&](auto i, auto) { return (i >= fi && i < (T::size()-li)) ? data.get(i) : 10*i; };
        TTS_EQUAL( eve::replace_ignored(data,ignore_extrema(fi,li),replacement), replacement );
      }
    }
  }
};
