//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/has_abi.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for detection of native ABI")
{
  constexpr auto native = eve::wide<float>::size();

  TTS_EXPECT_NOT(( eve::has_native_abi_v<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT_NOT(( eve::has_native_abi_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

#if defined(EVE_NO_SIMD)
  TTS_EXPECT_NOT( eve::has_native_abi_v<eve::wide<float>>                );
  TTS_EXPECT_NOT( eve::has_native_abi_v<eve::logical<eve::wide<float>>>  );
#else
  TTS_EXPECT( eve::has_native_abi_v<eve::wide<float>>                );
  TTS_EXPECT( eve::has_native_abi_v<eve::logical<eve::wide<float>>>  );
#endif

  TTS_EXPECT( eve::has_native_abi_v<float>                           );
  TTS_EXPECT( eve::has_native_abi_v<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of aggregated ABI")
{
  constexpr auto native = eve::wide<float>::size();

#if defined(EVE_NO_SIMD)
  TTS_EXPECT_NOT(( eve::has_aggregated_abi_v<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT_NOT(( eve::has_aggregated_abi_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
#else
  TTS_EXPECT(( eve::has_aggregated_abi_v<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT(( eve::has_aggregated_abi_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
#endif

  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::wide<float>>                );
  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::logical<eve::wide<float>>>  );

  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<float>                           );
  TTS_EXPECT_NOT( eve::has_aggregated_abi_v<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of aggregated ABI in product type")
{
  constexpr auto native = eve::wide<float>::size();

  using tuple_t = kumi::tuple<double, float, std::int16_t>;
  using layer_t = kumi::tuple<int, tuple_t, std::int8_t>;

#if defined(EVE_NO_SIMD)
  TTS_EXPECT_NOT(( eve::has_aggregated_component_v<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT_NOT(( eve::has_aggregated_component_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
#else
  TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT(( eve::has_aggregated_component_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<tuple_t, eve::fixed<2*native>>> ));
  TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<layer_t, eve::fixed<2*native>>> ));
#endif

  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<tuple_t>>             );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<layer_t>>             );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<float>>               );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::logical<eve::wide<float>>> );
};
