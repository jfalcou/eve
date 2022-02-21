//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE("Checck that non-decorator types don't satisfy decorator" )
{
  TTS_EXPECT_NOT( eve::decorator<int>   );
  TTS_EXPECT_NOT( eve::decorator<char>  );
  TTS_EXPECT_NOT( eve::decorator<float> );
  TTS_EXPECT_NOT( eve::decorator<double>);

  TTS_EXPECT_NOT( eve::decorator<eve::logical<short>>);
  TTS_EXPECT_NOT( eve::decorator<eve::logical<float>>);
};

TTS_CASE("Checck that decorators satisfies decorator" )
{
  TTS_EXPECT( eve::decorator<eve::downward_type>    );
  TTS_EXPECT( eve::decorator<eve::musl_type>        );
  TTS_EXPECT( eve::decorator<eve::numeric_type>     );
  TTS_EXPECT( eve::decorator<eve::pedantic_type>    );
  TTS_EXPECT( eve::decorator<eve::plain_type>       );
  TTS_EXPECT( eve::decorator<eve::raw_type>         );
  TTS_EXPECT( eve::decorator<eve::regular_type>     );
  TTS_EXPECT( eve::decorator<eve::saturated_type>   );
  TTS_EXPECT( eve::decorator<eve::to_nearest_type>  );
  TTS_EXPECT( eve::decorator<eve::toward_zero_type> );
  TTS_EXPECT( eve::decorator<eve::upward_type>      );
};
