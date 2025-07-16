//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

namespace impl { EVE_CALLABLE_NAMESPACE(); }


template<typename Options>
struct TestCallable : eve::callable<TestCallable, Options>
{
  template<typename T>
  T operator()(T v) const
  {
    return EVE_DISPATCH_CALL(v);
  }

  EVE_CALLABLE_OBJECT_FROM(impl, TestCallable, test_);
};

template<typename Options>
struct TestCallableNoTranslate : eve::callable<TestCallableNoTranslate, Options>
{
  template<typename T>
  T operator()(T v) const
  {
    return EVE_DISPATCH_CALL_NT(v);
  }

  EVE_CALLABLE_OBJECT_FROM(impl, TestCallableNoTranslate, test_nt_);
};

inline constexpr auto test_translate = eve::functor<TestCallable>;
inline constexpr auto test_no_translate = eve::functor<TestCallableNoTranslate>;

namespace impl
{
  template<eve::callable_options O, typename T>
  T test_(EVE_REQUIRES(eve::cpu_), O const&, T v)
  {
    TTS_EXPECT(!eve::has_plain_translation<T>) << "T should already have been translated";
    return v;
  }

  template<eve::callable_options O, typename T>
  T test_nt_(EVE_REQUIRES(eve::cpu_), O const&, T v)
  {
    TTS_EXPECT(eve::has_plain_translation<T>) << "T should not have been translated";
    return v;
  }
}

TTS_CASE_TPL("Translatable protocol - scalar", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (std::integral<T>)
  {
    enum class E: T { };

    E v = E { static_cast<T>(0) };

    auto r = test_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back to the original type";

    auto r_nt = test_no_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
  }

  using trans_t = BaseStruct<T>;
  trans_t v = eve::zero(eve::as<trans_t>{});

  auto r = test_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back to the original type";

  auto r_nt = test_no_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
};

TTS_CASE_TPL("Translatable protocol - logical scalar", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  if constexpr (std::integral<T>)
  {
    enum class E: T { };
    using trans_t = eve::logical<E>;
    trans_t v = eve::false_(eve::as<trans_t>{});

    auto r = test_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back to the original type";

    auto r_nt = test_no_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
  }

  using trans_t = eve::logical<BaseStruct<T>>;
  trans_t v = eve::false_(eve::as<trans_t>{});

  auto r = test_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back to the original type";

  auto r_nt = test_no_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
};

TTS_CASE_TPL("Translatable protocol - wide", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using e_t = eve::element_type_t<W>;

  if constexpr (std::integral<e_t>)
  {
    enum class E: e_t { };
    using transw_t = eve::as_wide_as_t<E, W>;
    transw_t v = transw_t{static_cast<E>(0)};

    auto r = test_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back";

    auto r_nt = test_no_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
  }

  using transw_t = eve::as_wide_as_t<BaseStruct<e_t>, W>;
  transw_t v = eve::zero(eve::as<transw_t>{});

  auto r = test_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back";

  auto r_nt = test_no_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed";
};

TTS_CASE_TPL("Translatable protocol - logical wide", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using e_t = eve::element_type_t<eve::as_arithmetic_t<W>>;

  if constexpr (std::integral<e_t>)
  {
    enum class E: e_t { };
    using transw_t = eve::logical<eve::as_wide_as_t<E, W>>;
    transw_t v = eve::false_(eve::as<transw_t>{});

    auto r = test_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back, got " << tts::typename_<decltype(r)>;

    auto r_nt = test_no_translate(v);
    TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed, got " << tts::typename_<decltype(r)>;
  }

  using transw_t = eve::logical<eve::as_wide_as_t<BaseStruct<e_t>, W>>;
  transw_t v = eve::false_(eve::as<transw_t>{});

  auto r = test_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r)>) << "The result should have been translated back, got " << tts::typename_<decltype(r)>;

  auto r_nt = test_no_translate(v);
  TTS_EXPECT(eve::has_plain_translation<decltype(r_nt)>) << "The type should not have changed, got " << tts::typename_<decltype(r)>;
};
