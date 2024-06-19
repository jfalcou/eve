//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/equivalent.hpp>

TTS_CASE_TPL("Equivalent enum trait impl", eve::test::scalar::integers)
<typename T>(tts::type<T>)
{
  enum class E: T { };

  static_assert(!eve::has_equivalent<T>, "T should not have an equivalent type");
  static_assert(eve::has_equivalent<E>, "E should have an equivalent type");
  static_assert(std::same_as<eve::as_equivalent_t<E>, T>, "E equivalent type should be T");

  TTS_PASS("All checks passed");
};

template <typename E>
struct BaseStruct { E value; };

template<typename E>
struct eve::equivalent_to<BaseStruct<E>> { using type = E; };

TTS_CASE_TPL("Equivalent struct trait impl", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using S = BaseStruct<T>;

  static_assert(!eve::has_equivalent<T>, "T should not have an equivalent type");
  static_assert(eve::has_equivalent<S>, "S should have an equivalent type");
  static_assert(std::same_as<eve::as_equivalent_t<S>, T>, "S equivalent type should be T");

  TTS_PASS("All checks passed");
};
