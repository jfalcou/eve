//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
#include <eve/module/core.hpp>
//==================================================================================================
#include "test.hpp"

using eve::fixed;

TTS_CASE("Constant generation for scalar")
{
  TTS_ULP_EQUAL((eve::Constant<float, 0x3F8E38E3>()), 1.111111f, 0.5);
  TTS_IEEE_EQUAL((eve::Constant<float, 0xFFFFFFFF>()), eve::nan(eve::as<float>()));

  TTS_ULP_EQUAL((eve::Constant<double, 0x3FF1C71C71C71C72ULL>()), 1.111111111111111111, 0.5);
  TTS_IEEE_EQUAL((eve::Constant<double, 0xFFFFFFFFFFFFFFFFULL>()), eve::nan(eve::as<double>()));

  TTS_EQUAL((eve::Constant<std::uint8_t, 0xE5>()), 0xE5);
  TTS_EQUAL((eve::Constant<std::int8_t, 0x55>()), 0x55);
  TTS_EQUAL((eve::Constant<std::uint16_t, 0xD455>()), 0xD455);
  TTS_EQUAL((eve::Constant<std::int16_t, 0x4455>()), 0x4455);
  TTS_EQUAL((eve::Constant<std::uint32_t, 0xC1334455>()), 0xC1334455);
  TTS_EQUAL((eve::Constant<std::int32_t, 0x11334455>()), 0x11334455);
  TTS_EQUAL((eve::Constant<std::uint64_t, 0xB122334455667788ULL>()), 0xB122334455667788ULL);
  TTS_EQUAL((eve::Constant<std::int64_t, 0x1122334455667788LL>()), 0x1122334455667788LL);
};

TTS_CASE_TPL("Constant generation for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
<typename T>(::tts::type<T>)
{
  TTS_ULP_EQUAL(
      (eve::Constant<eve::wide<float, T>, 0x3F8E38E3>()), (eve::wide<float, T>(1.111111f)), 0.5);
  TTS_IEEE_EQUAL((eve::Constant<eve::wide<float, T>, 0xFFFFFFFF>()),
                 (eve::nan(eve::as<eve::wide<float, T>>())));

  TTS_ULP_EQUAL((eve::Constant<eve::wide<double, T>, 0x3FF1C71C71C71C72ULL>()),
                (eve::wide<double, T>(1.111111111111111111)),
                0.5);
  TTS_IEEE_EQUAL((eve::Constant<eve::wide<double, T>, 0xFFFFFFFFFFFFFFFFULL>()),
                 (eve::nan(eve::as<eve::wide<double, T>>())));

  TTS_EQUAL((eve::Constant<eve::wide<std::uint8_t, T>, 0xE5>()),
            (eve::wide<std::uint8_t, T>(0xE5)));
  TTS_EQUAL((eve::Constant<eve::wide<std::int8_t, T>, 0x55>()), (eve::wide<std::int8_t, T>(0x55)));
  TTS_EQUAL((eve::Constant<eve::wide<std::uint16_t, T>, 0xD455>()),
            (eve::wide<std::uint16_t, T>(0xD455)));
  TTS_EQUAL((eve::Constant<eve::wide<std::int16_t, T>, 0x4455>()),
            (eve::wide<std::int16_t, T>(0x4455)));
  TTS_EQUAL((eve::Constant<eve::wide<std::uint32_t, T>, 0xC1334455>()),
            (eve::wide<std::uint32_t, T>(0xC1334455)));
  TTS_EQUAL((eve::Constant<eve::wide<std::int32_t, T>, 0x11334455>()),
            (eve::wide<std::int32_t, T>(0x11334455)));
  TTS_EQUAL((eve::Constant<eve::wide<std::uint64_t, T>, 0xB122334455667788ULL>()),
            (eve::wide<std::uint64_t, T>(0xB122334455667788ULL)));
  TTS_EQUAL((eve::Constant<eve::wide<std::int64_t, T>, 0x1122334455667788LL>()),
            (eve::wide<std::int64_t, T>(0x1122334455667788LL)));
};
