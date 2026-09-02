//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/arch/abi_traits.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check prebuilt ABI match expected concepts")
{
  TTS_EXPECT_NOT( eve::native_abi<eve::bundle_>     );
  TTS_EXPECT_NOT( eve::native_abi<eve::aggregated_> );
  TTS_EXPECT_NOT( eve::native_abi<eve::emulated_>   );

  TTS_EXPECT( eve::non_native_abi<eve::bundle_>     );
  TTS_EXPECT( eve::non_native_abi<eve::aggregated_> );
  TTS_EXPECT( eve::non_native_abi<eve::emulated_>   );

  TTS_EXPECT    ( eve::regular_abi<eve::bundle_>    );
  TTS_EXPECT_NOT( eve::regular_abi<eve::aggregated_>);
  TTS_EXPECT    ( eve::regular_abi<eve::emulated_>  );
};

TTS_CASE( "Check for detection of native ABI")
{
  constexpr auto native = eve::wide<float>::size();
  
  TTS_EXPECT_NOT(( eve::native_abi<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT_NOT(( eve::native_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

  TTS_EXPECT(( eve::non_native_abi<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT(( eve::non_native_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

  if constexpr(eve::current_api == eve::undefined_simd)
  {
    TTS_EXPECT_NOT( eve::native_abi<eve::wide<float>>                );
    TTS_EXPECT_NOT( eve::native_abi<eve::logical<eve::wide<float>>>  );

    TTS_EXPECT( eve::non_native_abi<eve::wide<float>>                );
    TTS_EXPECT( eve::non_native_abi<eve::logical<eve::wide<float>>>  );
  }
  else
  {
    TTS_EXPECT( eve::native_abi<eve::wide<float>>                );
    TTS_EXPECT( eve::native_abi<eve::logical<eve::wide<float>>>  );

    TTS_EXPECT_NOT( eve::non_native_abi<eve::wide<float>>                );
    TTS_EXPECT_NOT( eve::non_native_abi<eve::logical<eve::wide<float>>>  );
  }

  TTS_EXPECT( eve::native_abi<float>                           );
  TTS_EXPECT( eve::native_abi<eve::logical<float>>             );

  TTS_EXPECT_NOT( eve::non_native_abi<float>                           );
  TTS_EXPECT_NOT( eve::non_native_abi<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of aggregated ABI")
{
  constexpr auto native = eve::wide<float>::size();

  if constexpr(eve::current_api == eve::undefined_simd)
  {
    TTS_EXPECT_NOT(( eve::aggregated_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT_NOT(( eve::aggregated_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  }
  else
  {
    TTS_EXPECT(( eve::aggregated_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT(( eve::aggregated_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  }

  TTS_EXPECT_NOT( eve::aggregated_abi<eve::wide<float>>                );
  TTS_EXPECT_NOT( eve::aggregated_abi<eve::logical<eve::wide<float>>>  );

  TTS_EXPECT_NOT( eve::aggregated_abi<float>                           );
  TTS_EXPECT_NOT( eve::aggregated_abi<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of regular ABI")
{
  constexpr auto native = eve::wide<float>::size();

  if constexpr(eve::current_api == eve::undefined_simd)
  {
    TTS_EXPECT(( eve::regular_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT(( eve::regular_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  }
  else
  {
    TTS_EXPECT_NOT(( eve::regular_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT_NOT(( eve::regular_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  }

  TTS_EXPECT( eve::regular_abi<eve::wide<float>>                );
  TTS_EXPECT( eve::regular_abi<eve::logical<eve::wide<float>>>  );

  TTS_EXPECT( eve::regular_abi<float>                           );
  TTS_EXPECT( eve::regular_abi<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of emulated ABI")
{
  constexpr auto native = eve::wide<float>::size();

  if constexpr(eve::current_api == eve::undefined_simd)
  {
    TTS_EXPECT(( eve::emulated_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT(( eve::emulated_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

    TTS_EXPECT( eve::emulated_abi<eve::wide<float>>                );
    TTS_EXPECT( eve::emulated_abi<eve::logical<eve::wide<float>>>  );
  }
  else
  {
    TTS_EXPECT_NOT(( eve::emulated_abi<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT_NOT(( eve::emulated_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

    TTS_EXPECT_NOT( eve::emulated_abi<eve::wide<float>>                );
    TTS_EXPECT_NOT( eve::emulated_abi<eve::logical<eve::wide<float>>>  );
  }

  TTS_EXPECT_NOT( eve::emulated_abi<float>                           );
  TTS_EXPECT_NOT( eve::emulated_abi<eve::logical<float>>             );
};

TTS_CASE( "Check for detection of bundle ABI")
{
  constexpr auto native = eve::wide<float>::size();
  using tuple_t = kumi::tuple<double, float, std::int8_t>;
  using layer_t = kumi::tuple<int, tuple_t, std::int8_t>;

  TTS_EXPECT_NOT(( eve::bundle_abi<eve::wide<float, eve::fixed<2*native>>>              ));
  TTS_EXPECT_NOT(( eve::bundle_abi<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));

  TTS_EXPECT_NOT( eve::bundle_abi<eve::wide<float>>                 );
  TTS_EXPECT_NOT( eve::bundle_abi<eve::logical<eve::wide<float>>>   );
  TTS_EXPECT    ( eve::bundle_abi<eve::wide<tuple_t>>               );
  TTS_EXPECT    ( eve::bundle_abi<eve::wide<layer_t>>               );
};

TTS_CASE( "Check for detection of aggregated ABI in product type")
{
  constexpr auto native = eve::wide<float>::size();

  using tuple_t = kumi::tuple<double, float, std::int16_t>;
  using layer_t = kumi::tuple<int, tuple_t, std::int8_t>;

  if constexpr(eve::current_api == eve::undefined_simd)
  {
    TTS_EXPECT_NOT(( eve::has_aggregated_component_v<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT_NOT(( eve::has_aggregated_component_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
  }
  else
  {
    TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<float, eve::fixed<2*native>>>              ));
    TTS_EXPECT(( eve::has_aggregated_component_v<eve::logical<eve::wide<float, eve::fixed<2*native>>>>));
    TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<tuple_t, eve::fixed<2*native>>> ));
    TTS_EXPECT(( eve::has_aggregated_component_v<eve::wide<layer_t, eve::fixed<2*native>>> ));
  }

  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<tuple_t>>             );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<layer_t>>             );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::wide<float>>               );
  TTS_EXPECT_NOT( eve::has_aggregated_component_v<eve::logical<eve::wide<float>>> );
};
