//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/translation.hpp>

TTS_CASE_TPL("Equivalent enum trait impl", eve::test::scalar::integers)
<typename T>(tts::type<T>)
{
  enum class E: T { };

  TTS_CONSTEXPR_EXPECT_NOT((eve::has_plain_translation<T>)) << "T should not have a translated type";
  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<E>)) << "E should have a translated type";
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<E>, T>)) << "The translated type of E should be T";
};

template <typename E>
struct BaseStruct { E value; };

template<typename E>
struct eve::translation_of<BaseStruct<E>> { using type = E; };

TTS_CASE_TPL("Equivalent struct trait impl", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using S = BaseStruct<T>;

  TTS_CONSTEXPR_EXPECT_NOT((eve::has_plain_translation<T>)) << "T should not have a translated type";
  TTS_CONSTEXPR_EXPECT((eve::has_plain_translation<S>)) << "S should have a translated type";
  TTS_CONSTEXPR_EXPECT((std::same_as<eve::translate_t<S>, T>)) << "The translated type of S should be T";
};
