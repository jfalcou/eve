//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

TTS_CASE_TPL("Translatable - ptr", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using trans_t = BaseStruct<T>;

  // basic
  {
    trans_t value { 42 };
    trans_t* ptr = &value;
    T* translated = eve::translate_ptr(ptr);

    TTS_EQUAL(*translated, T{42});

    TTS_EXPECT_NOT((std::is_const_v<std::remove_pointer_t<decltype(translated)>>));
    TTS_EXPECT_NOT((std::is_volatile_v<std::remove_pointer_t<decltype(translated)>>));
  }

  // const
  {
    trans_t value { 42 };
    const trans_t* const_ptr = &value;
    const T* translated_const = eve::translate_ptr(const_ptr);

    TTS_EQUAL(*translated_const, T{42});

    TTS_EXPECT((std::is_const_v<std::remove_pointer_t<decltype(translated_const)>>));
    TTS_EXPECT_NOT((std::is_volatile_v<std::remove_pointer_t<decltype(translated_const)>>));
  }

  // volatile
  {
    trans_t value { 42 };
    volatile trans_t* volatile_ptr = &value;
    volatile T* translated_volatile = eve::translate_ptr(volatile_ptr);

    TTS_EQUAL(*translated_volatile, T{42});

    TTS_EXPECT_NOT((std::is_const_v<std::remove_pointer_t<decltype(translated_volatile)>>));
    TTS_EXPECT((std::is_volatile_v<std::remove_pointer_t<decltype(translated_volatile)>>));
  }

  // const volatile
  {
    trans_t value { 42 };
    const volatile trans_t* const_volatile_ptr = &value;
    const volatile T* translated_const_volatile = eve::translate_ptr(const_volatile_ptr);

    TTS_EQUAL(*translated_const_volatile, T{42});

    TTS_EXPECT((std::is_const_v<std::remove_pointer_t<decltype(translated_const_volatile)>>));
    TTS_EXPECT((std::is_volatile_v<std::remove_pointer_t<decltype(translated_const_volatile)>>));
  }
};
