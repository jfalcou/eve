//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Translatable logical types", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using Lt = eve::logical<T>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using trans_t = eve::logical<E>;

    TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<trans_t>));
    TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<trans_t>, Lt>));
  }

  using trans_t = eve::logical<BaseStruct<T>>;

  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<trans_t>));
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<trans_t>, Lt>));
};

TTS_CASE_TPL("Translatable wide types", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using e_t = eve::element_type_t<W>;

  if constexpr (std::integral<e_t>)
  {
    enum class E: e_t { };
    using transw_t = eve::as_wide_as_t<E, W>;

    TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<transw_t>));
    TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<transw_t>, W>));
  }

  using transw_t = eve::as_wide_as_t<BaseStruct<e_t>, W>;

  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<transw_t>));
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<transw_t>, W>));
};

TTS_CASE_TPL("Translatable logical wide types", eve::test::simd::all_types)
<typename B>(tts::type<B>)
{
  using W = eve::logical<B>;
  using e_t = eve::element_type_t<typename W::mask_type>;

  if constexpr (std::integral<e_t>)
  {
    enum class E: e_t { };
    using transw_t = eve::as_wide_as_t<eve::logical<E>, W>;

    TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<transw_t>));
    TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<transw_t>, W>));
  }

  using transw_t = eve::as_wide_as_t<eve::logical<BaseStruct<e_t>>, W>;

  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<transw_t>));
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<transw_t>, W>));
};

TTS_CASE_TPL("Translatable wide ctor - splat", eve::test::simd::all_types)
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
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), E { 42 });
    }
  }

  eve::as_wide_as_t<trans_t, W> wt { trans_t { 42 } };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { 42 });
  }
};

TTS_CASE_TPL("Translatable wide ctor - from pointer", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using N = typename W::cardinal_type;
  using trans_t = BaseStruct<T>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    std::array<E, N::value> scratch;
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      scratch[i] = static_cast<E>(i);
    }

    eve::wide<E, N> wt(&scratch[0]);
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      TTS_EQUAL(wt.get(i), scratch[i]);
    }
  }

  std::array<trans_t, N::value> scratch;
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    scratch[i] = trans_t { static_cast<T>(i) };
  }

  eve::wide<trans_t, N> wt(&scratch[0]);
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    TTS_EQUAL(wt.get(i), scratch[i]);
  }
};

TTS_CASE_TPL("Translatable wide ctor - generator", eve::test::simd::all_types)
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
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(i * 3));
    }
  }

  eve::as_wide_as_t<trans_t, W> wt = [](auto i, auto) { return trans_t { static_cast<T>(i * 3) }; };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { static_cast<T>(i * 3) });
  }
};

TTS_CASE_TPL("Translatable wide ctor - enumerating", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using trans_t = BaseStruct<T>;
  using WT = eve::as_wide_as_t<trans_t, W>;

  W wr = [](auto i, auto) { return static_cast<T>(1 + i); };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using WE = eve::as_wide_as_t<E, W>;

    WE wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return WE { static_cast<E>(1 + N)... };
          }( std::make_index_sequence<W::size()>());

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(1 + i));
    }
  }

  WT wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return WT { trans_t { static_cast<T>(1 + N) }... };
          }( std::make_index_sequence<W::size()>());

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { static_cast<T>(1 + i) });
  }
};

TTS_CASE_TPL("Translatable wide - load", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;
  using N = typename W::cardinal_type;
  using trans_t = BaseStruct<T>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    std::array<E, N::value> scratch;
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      scratch[i] = static_cast<E>(i);
    }

    eve::wide<E, N> wt = eve::load(scratch.data(), N{});
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(i));
    }

    wt = eve::load(scratch.data(), eve::as(wt));
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      TTS_EQUAL(wt.get(i), static_cast<E>(i));
    }
  }

  std::array<trans_t, N::value> scratch;
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    scratch[i] = trans_t { static_cast<T>(i) };
  }

  eve::wide<trans_t, N> wt = eve::load(scratch.data(), N{});
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { static_cast<T>(i) });
  }

  wt = eve::load(scratch.data(), eve::as(wt));
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { static_cast<T>(i) });
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - splat", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using trans_t = eve::logical<BaseStruct<T>>;

  LW wr { false };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    eve::as_wide_as_t<eve::logical<E>, LW> wt { eve::logical<E> { false } };

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), eve::logical<E> { false });
    }
  }

  eve::as_wide_as_t<trans_t, LW> wt { trans_t { false } };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { false });
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - from pointer", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using N = typename W::cardinal_type;
  using trans_t = eve::logical<BaseStruct<T>>;

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    std::array<eve::logical<E>, N::value> scratch;
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      scratch[i] = eve::logical<E>{ (i % 2) == 0 };
    }

    eve::as_wide_as_t<eve::logical<E>, LW> wt(&scratch[0]);
    for (std::ptrdiff_t i = 0; i < N::value; ++i)
    {
      TTS_EQUAL(wt.get(i), scratch[i]);
    }
  }

  std::array<trans_t, N::value> scratch;
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    scratch[i] = trans_t { (i % 2) == 0 };
  }

  eve::as_wide_as_t<trans_t, LW> wt(&scratch[0]);
  for (std::ptrdiff_t i = 0; i < N::value; ++i)
  {
    TTS_EQUAL(wt.get(i), scratch[i]);
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - generator(bool...)", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using trans_t = eve::logical<BaseStruct<T>>;

  LW wr = [](auto i, auto) { return (i % 2) == 0; };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    eve::as_wide_as_t<eve::logical<E>, LW> wt = [](auto i, auto) { return (i % 2) == 0; };

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), eve::logical<E>{ (i % 2) == 0 });
    }
  }

  eve::as_wide_as_t<trans_t, LW> wt = [](auto i, auto) { return (i % 2) == 0; };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { (i % 2) == 0 });
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - generator(logical...)", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using trans_t = eve::logical<BaseStruct<T>>;

  LW wr = [](auto i, auto) { return (i % 2) == 0; };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    eve::as_wide_as_t<eve::logical<E>, LW> wt = [](auto i, auto) { return trans_t { (i % 2) == 0 }; };

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), eve::logical<E>{ (i % 2) == 0 });
    }
  }

  eve::as_wide_as_t<trans_t, LW> wt = [](auto i, auto) { return trans_t { (i % 2) == 0 }; };

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { (i % 2) == 0 });
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - enumerating", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using trans_t = eve::logical<BaseStruct<T>>;

  LW wr = [](auto i, auto) { return (i % 2) == 0; };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    eve::as_wide_as_t<eve::logical<E>, LW> wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return eve::as_wide_as_t<eve::logical<E>, LW> { eve::logical<E>((N % 2) == 0)... };
          }( std::make_index_sequence<W::size()>());

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), eve::logical<E>{ (i % 2) == 0 });
    }
  }

  eve::as_wide_as_t<trans_t, LW> wt = [&]<std::size_t... N>(std::index_sequence<N...>)
          {
            return eve::as_wide_as_t<trans_t, LW> { trans_t { (N % 2) == 0 }... };
          }( std::make_index_sequence<W::size()>());

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { (i % 2) == 0 });
  }
};

TTS_CASE_TPL("Translatable logical wide ctor - enumerating mixed types", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using LW = eve::logical<W>;
  using T = eve::element_type_t<W>;
  using N = typename W::cardinal_type;
  using trans_t = eve::logical<BaseStruct<T>>;

  LW wr = [](auto i, auto) { return (i % 3) == 0; };

  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    auto mixed = kumi::generate<N::value>([]<typename I>(I)
      {
        if constexpr(I::value % 2) return eve::logical<E>{ (I::value % 3) == 0 };
        else                       return (I::value % 3) == 0;
      }
    );

    eve::as_wide_as_t<eve::logical<E>, LW> wt = kumi::apply([](auto... args) {
      return eve::as_wide_as_t<eve::logical<E>, LW> { args... };
    }, mixed);

    TTS_EQUAL(eve::translate(wt), wr);
    for (std::ptrdiff_t i = 0; i < W::size(); ++i)
    {
      TTS_EQUAL(wt.get(i), eve::logical<E>{ (i % 3) == 0 });
    }
  }

  auto mixed_trans = kumi::generate<N::value>([]<typename I>(I)
    {
      if constexpr(I::value % 2) return trans_t{ (I::value % 3) == 0 };
      else                       return (I::value % 3) == 0;
    }
  );

  eve::as_wide_as_t<trans_t, LW> wt = kumi::apply([](auto... args) {
    return eve::as_wide_as_t<trans_t, LW> { args... };
  }, mixed_trans);

  TTS_EQUAL(eve::translate(wt), wr);
  for (std::ptrdiff_t i = 0; i < W::size(); ++i)
  {
    TTS_EQUAL(wt.get(i), trans_t { (i % 3) == 0 });
  }
};
