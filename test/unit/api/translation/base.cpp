//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Equivalent enum trait impl", eve::test::scalar::integers)
<typename T>(tts::type<T>)
{
  enum class E: T { };

  TTS_CONSTEXPR_EXPECT_NOT((eve::has_plain_translation<T>)) << "T should not have a translated type";
  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<E>)) << "E should have a translated type";
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<E>, T>)) << "The translated type of E should be T";
};

TTS_CASE_TPL("Equivalent struct trait impl", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using S = BaseStruct<T>;

  TTS_CONSTEXPR_EXPECT_NOT((eve::has_plain_translation<T>)) << "T should not have a translated type";
  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<S>)) << "S should have a translated type";
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<S>, T>)) << "The translated type of S should be T";
};

TTS_CASE_TPL("Checks behavior of concepts over translated type", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using S = BaseStruct<T>;

  TTS_CONSTEXPR_EXPECT(eve::value<S>);

  if constexpr(eve::integral_value<T>)
  {
    TTS_CONSTEXPR_EXPECT(eve::integral_value<S>);
    TTS_CONSTEXPR_EXPECT(eve::integral_scalar_value<S>);
    TTS_CONSTEXPR_EXPECT_NOT(eve::floating_value<S>);

    enum class E: T { };

    TTS_CONSTEXPR_EXPECT(eve::value<E>);
    TTS_CONSTEXPR_EXPECT(eve::integral_value<E>);
    TTS_CONSTEXPR_EXPECT(eve::integral_scalar_value<E>);
    TTS_CONSTEXPR_EXPECT_NOT(eve::floating_value<E>);
  }
  else
  {
    TTS_CONSTEXPR_EXPECT_NOT(eve::integral_value<S>);
    TTS_CONSTEXPR_EXPECT_NOT(eve::integral_scalar_value<S>);
    TTS_CONSTEXPR_EXPECT(eve::floating_value<S>);
  }
};

TTS_CASE_TPL("Checks behavior of translate_into", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using N = BaseStruct<T>;
  using L0 = BaseStruct<N>;
  using L1 = BaseStruct<T>;

  TTS_CONSTEXPR_EXPECT((eve::translatable_into<L0, L1>));
  TTS_CONSTEXPR_EXPECT((eve::translatable_into<L1, L0>));

  TTS_CONSTEXPR_EXPECT((std::same_as<decltype(eve::translate_into(L0{}, eve::as<L1>{})), L1>));
  TTS_CONSTEXPR_EXPECT((std::same_as<decltype(eve::translate_into(L1{}, eve::as<L0>{})), L0>));
};

template<typename T>
auto test_invalid_translation(int) -> eve::translate_t<T> { return { }; }

struct NonTrivialCopy {
  float value;
  NonTrivialCopy(const NonTrivialCopy& other) : value(other.value * 2) {}
};

struct NonTrivialAssign {
  float value;
  NonTrivialAssign& operator=(const NonTrivialAssign& other) {
    value = other.value * 2;
    return *this;
  }
};

template<> struct eve::translation_of<NonTrivialCopy> { using type = float; };
template<> struct eve::translation_of<NonTrivialAssign> { using type = float; };

TTS_CASE("Checks compiler rejects invalid translatables")
{
  int v;
  TTS_EXPECT_NOT_COMPILES(v, { test_invalid_translation<NonTrivialCopy>(v); });
  TTS_EXPECT_NOT_COMPILES(v, { test_invalid_translation<NonTrivialAssign>(v); });
};
