//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/transparent.hpp>

TTS_CASE_TPL("Transparent enum trait impl", eve::test::scalar::integers)
<typename T>(tts::type<T>)
{
  enum class E: T { };

  static_assert(!eve::transparent_value<T>, "T is not transparent");
  static_assert(eve::transparent_value<E>, "E is transparent");
  static_assert(std::same_as<eve::transparent_inner_t<E>, T>, "E inner type is T");
};

template <typename E>
struct BS { E value; };

template<typename E>
struct eve::transparent_trait<BS<E>> { using type = E; };

TTS_CASE_TPL("Transparent struct trait impl", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using S = BS<T>;

  static_assert(!eve::transparent_value<T>, "T is not transparent");
  static_assert(eve::transparent_value<S>, "S is transparent");
  static_assert(std::same_as<eve::transparent_inner_t<S>, T>, "S inner type is T");
};
