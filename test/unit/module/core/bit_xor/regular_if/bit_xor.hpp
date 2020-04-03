//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_xor.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_xor return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((eve::bit_xor[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ EVE_TYPE() ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ EVE_TYPE() ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ EVE_TYPE() ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ EVE_TYPE() ](ui_t(), EVE_TYPE()))  , ui_t  );
              
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<EVE_TYPE>() ](ui_t(), EVE_TYPE()))  , ui_t  );
              
  TTS_EXPR_IS((eve::bit_xor[ true  ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ true  ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ true  ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ true  ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_xor[ true  ](ui_t(), EVE_TYPE()))  , ui_t  );
}

TTS_CASE( "Check eve::bit_xor behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

 
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), (EVE_TYPE(0)))  , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), (EVE_VALUE(0))) , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), (EVE_TYPE(1)))  , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), (EVE_VALUE(1))) , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(1)), (EVE_TYPE(1)))  , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(1)), (EVE_VALUE(1))) , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(1)), (EVE_TYPE(0)))  , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(1)), (EVE_VALUE(0))) , (EVE_TYPE(1)));

  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;
  using si_t = as_integer_t<EVE_TYPE, signed>;
  using wi_t = as_integer_t<EVE_VALUE, signed>;

  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), ui_t(1)), bit_cast(ui_t(0),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), vi_t(1)), bit_cast(ui_t(0),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), si_t(1)), bit_cast(si_t(0),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((EVE_TYPE(0)), wi_t(1)), bit_cast(si_t(0),as<EVE_TYPE>()));

  TTS_EQUAL(eve::bit_xor[ false  ](ui_t(0), (EVE_TYPE(1))), bit_cast(EVE_TYPE(0),as<ui_t>()));
  TTS_EQUAL(eve::bit_xor[ false  ](si_t(0), (EVE_TYPE(1))), bit_cast(EVE_TYPE(0),as<si_t>()));

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::bit_xor[ false  ](EVE_TYPE(3), EVE_TYPE(2) ) , EVE_TYPE(3));
    TTS_EQUAL(eve::bit_xor[ false  ](EVE_TYPE(3), EVE_VALUE(2)) , EVE_TYPE(3));
    TTS_EQUAL(eve::bit_xor[ false  ](EVE_TYPE(3), EVE_TYPE(1) ) , EVE_TYPE(3));
    TTS_EQUAL(eve::bit_xor[ false  ](EVE_TYPE(3), EVE_VALUE(1)) , EVE_TYPE(3));
  }

  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), (EVE_TYPE(0)))  , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), (EVE_VALUE(0))) , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), (EVE_TYPE(1)))  , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), (EVE_VALUE(1))) , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(1)), (EVE_TYPE(1)))  , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(1)), (EVE_VALUE(1))) , (EVE_TYPE(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(1)), (EVE_TYPE(0)))  , (EVE_TYPE(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(1)), (EVE_VALUE(0))) , (EVE_TYPE(1)));

  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), ui_t(1)), bit_cast(ui_t(1),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), vi_t(1)), bit_cast(ui_t(1),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), si_t(1)), bit_cast(si_t(1),as<EVE_TYPE>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((EVE_TYPE(0)), wi_t(1)), bit_cast(si_t(1),as<EVE_TYPE>()));

  TTS_EQUAL(eve::bit_xor[ true  ](ui_t(0), (EVE_TYPE(1))), bit_cast(EVE_TYPE(1),as<ui_t>()));
  TTS_EQUAL(eve::bit_xor[ true  ](si_t(0), (EVE_TYPE(1))), bit_cast(EVE_TYPE(1),as<si_t>()));

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::bit_xor[ true  ](EVE_TYPE(3), EVE_TYPE(2) ) , EVE_TYPE(1));
    TTS_EQUAL(eve::bit_xor[ true  ](EVE_TYPE(3), EVE_VALUE(2)) , EVE_TYPE(1));
    TTS_EQUAL(eve::bit_xor[ true  ](EVE_TYPE(3), EVE_TYPE(1) ) , EVE_TYPE(2));
    TTS_EQUAL(eve::bit_xor[ true  ](EVE_TYPE(3), EVE_VALUE(1)) , EVE_TYPE(2));
  }
}


