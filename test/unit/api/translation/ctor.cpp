//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Trans wide ctor - splat", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;

  W wr { T { 42 } };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
  
    eve::as_wide_as_t<E, W> wt { E { 42 } };

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 1; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), E { 42 });
    }
  }
  
  eve::as_wide_as_t<trans_t, W> wt { trans_t { 42 } };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 1; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { 42 });
  }
};

TTS_CASE_TPL("Trans wide ctor - generator", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;

  W wr = [](auto i, auto) { return static_cast<T>(i * 3); };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
  
    eve::as_wide_as_t<E, W> wt = [](auto i, auto) { return static_cast<E>(i * 3); };

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 1; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(i * 3));
    }
  }

  eve::as_wide_as_t<trans_t, W> wt = [](auto i, auto) { return static_cast<trans_t>(i * 3); };
  
  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 1; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), static_cast<trans_t>(i * 3));
  }
};

TTS_CASE_TPL("Trans wide ctor - enumerating", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  W wr = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return W { static_cast<T>(1 + N)... };
            }( std::make_index_sequence<W::size()>());

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using WE = eve::as_wide_as_t<E, W>;
  
    WE wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return WE { static_cast<E>(1 + N)... };
          }( std::make_index_sequence<W::size()>());

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 1; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(1 + i));
    }
  }

  WT wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return WT { static_cast<trans_t>(1 + N)... };
          }( std::make_index_sequence<W::size()>());
  
  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 1; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), static_cast<trans_t>(1 + i));
  }
};
