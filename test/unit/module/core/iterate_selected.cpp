//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE("Iterate Selected, bool")
{
  // type is annoying to test the interface
  auto not_called = [](std::same_as<std::ptrdiff_t> auto) mutable
  {
    TTS_FAIL("");
    return false;
  };
  eve::iterate_selected(false, not_called);
  eve::iterate_selected[eve::ignore_first(1)](false, not_called);
  eve::iterate_selected[eve::ignore_first(1)](true, not_called);
  eve::iterate_selected[eve::ignore_all](true, not_called);
  eve::iterate_selected[eve::ignore_last(1)](true, not_called);

  bool yes_called = false;
  auto was_called = [&](std::ptrdiff_t i)
  {
    TTS_EQUAL(0, i);
    yes_called = true;
    return false;
  };

  eve::iterate_selected(true, was_called);
  TTS_EXPECT(yes_called);
  yes_called = false;

  eve::iterate_selected[eve::ignore_first(0)](true, was_called);
  TTS_EXPECT(yes_called);
  yes_called = false;
};

std::vector<std::ptrdiff_t>
expected(auto what, std::ptrdiff_t untilBreak, auto ignore)
{
  std::vector<std::ptrdiff_t> res;

  std::ptrdiff_t first_i = ignore.offset(eve::as(what));
  std::ptrdiff_t last_i  = first_i + ignore.count(eve::as(what));

  for( std::ptrdiff_t i = first_i; i != last_i; ++i )
  {
    if( what.get(i) )
    {
      if( untilBreak-- == 0 )
      {
        res.push_back(-1);
        break;
      }
      res.push_back(i);
    }
  }

  return res;
}

std::vector<std::ptrdiff_t>
actual(auto what, std::ptrdiff_t untilBreak, auto ignore)
{
  std::vector<std::ptrdiff_t> res;
  bool                        wasBroken = eve::iterate_selected[ignore](what,
                                                 [&](std::same_as<std::ptrdiff_t> auto i) mutable
                                                 {
                                                   if( untilBreak-- == 0 ) return true;
                                                   res.push_back(i);
                                                   return false;
                                                 });
  if( wasBroken ) { res.push_back(-1); }
  return res;
}

void
tst(auto what, std::ptrdiff_t untilBreak, auto ignore)
{
  TTS_EQUAL(expected(what, untilBreak, ignore), actual(what, untilBreak, ignore), REQUIRED)
      << "what: " << what << " untilBreak: " << untilBreak << " ignore: " << ignore;
}

template<typename L>
void
tstOne(L what)
{
  tst(what, -1, eve::ignore_none);

  for( std::ptrdiff_t until = 0; until != L::size(); ++until )
  {
    tst(what, until, eve::ignore_none);
  }

  tst(what, -1, eve::ignore_all);

  for( std::ptrdiff_t from = 0; from != L::size(); ++from )
  {
    tst(what, -1, eve::ignore_first(from));
    tst(what, -1, eve::ignore_last(from));
    for( std::ptrdiff_t to = 0; to != L::size() - from; ++to )
    {
      tst(what, -1, eve::ignore_extrema(from, to));
    }
  }
}

template<typename L>
void
tstLogical(L what)
{
  tstOne(what);
  tstOne(eve::top_bits {what});
}

TTS_CASE_TPL("iterate_selected, explicit cases", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  tstLogical(eve::logical<T> {true});
  tstLogical(eve::logical<T> {false});
};

TTS_CASE_WITH("iterate_selected, random cases",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(1, 2)))
<typename L>(L logical_data) { tstLogical(logical_data); };
