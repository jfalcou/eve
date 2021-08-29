//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/traits/common_type.hpp>

TTS_CASE("eve::common_type, small integrals")
{
  // Explanation
  TTS_TYPE_IS((std::common_type_t<std::int32_t,  std::uint32_t>), std::uint32_t);
  TTS_TYPE_IS((std::common_type_t<std::int32_t,  std::uint64_t>), std::uint64_t);
  TTS_TYPE_IS((std::common_type_t<std::uint32_t, std::int64_t> ), std::int64_t);

  // std::int8_t
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::int8_t>  ), std::int8_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::uint8_t> ), std::uint8_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::uint16_t>), std::uint16_t);

  // std::uint8_t
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::uint8_t> ), std::uint8_t );
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::uint16_t>), std::uint16_t);

  // std::int16_t
  TTS_TYPE_IS((eve::common_type_t<std::int16_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::int16_t, std::uint16_t>), std::uint16_t);
}

EVE_TEST_TYPES("eve::common_type for two types comutes", eve::test::scalar::all_types )
<typename T>(eve::as<T>)
{
  auto one_type = []<typename U> (eve::as<U>) {
    TTS_TYPE_IS((eve::common_type_t<T, U>), (eve::common_type_t<U, T>));
  };

  [&]<typename ...Us> (eve::detail::types<Us...>) {
    (one_type(eve::as<Us>{}), ...);
  }(eve::test::scalar::all_types);
};

EVE_TEST_TYPES("eve::common_type matches std::common_type", eve::test::scalar::all_types )
<typename T>(eve::as<T>)
{
  auto one_type = []<typename U> (eve::as<U>) {
    TTS_TYPE_IS((eve::common_type_t<T, U>), (std::common_type_t<T, U>));
  };

  [&]<typename ...Us> (eve::detail::types<Us...>) {
    (one_type(eve::as<Us>{}), ...);
  }(eve::detail::types<
    std::int32_t, std::uint32_t,
    std::int64_t, std::uint64_t,
    float       , double
  >{});
};
