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
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_xor return type", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS((eve::bit_xor[ T() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ T() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_xor[ T() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ T() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ T() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_xor[ eve::logical<T>() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<T>() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<T>() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<T>() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ eve::logical<T>() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_xor[ true  ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ true  ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_xor[ true  ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ true  ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_xor[ true  ](ui_t(), T()))  , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_xor behavior", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), (T(0)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), (v_t(0))) , (T(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), (T(1)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), (v_t(1))) , (T(0)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(1)), (T(1)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(1)), (v_t(1))) , (T(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(1)), (T(0)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(1)), (v_t(0))) , (T(1)));

  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;
  using si_t = as_integer_t<T, signed>;
  using wi_t = as_integer_t<v_t, signed>;

  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), ui_t(1)), bit_cast(ui_t(0),as<T>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), vi_t(1)), bit_cast(ui_t(0),as<T>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), si_t(1)), bit_cast(si_t(0),as<T>()));
  TTS_EQUAL(eve::bit_xor[ false  ]((T(0)), wi_t(1)), bit_cast(si_t(0),as<T>()));

  TTS_EQUAL(eve::bit_xor[ false  ](ui_t(0), (T(1))), bit_cast(T(0),as<ui_t>()));
  TTS_EQUAL(eve::bit_xor[ false  ](si_t(0), (T(1))), bit_cast(T(0),as<si_t>()));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::bit_xor[ false  ](T(3), T(2) ) , T(3));
    TTS_EQUAL(eve::bit_xor[ false  ](T(3), v_t(2)) , T(3));
    TTS_EQUAL(eve::bit_xor[ false  ](T(3), T(1) ) , T(3));
    TTS_EQUAL(eve::bit_xor[ false  ](T(3), v_t(1)) , T(3));
  }

  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), (T(0)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), (v_t(0))) , (T(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), (T(1)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), (v_t(1))) , (T(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(1)), (T(1)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(1)), (v_t(1))) , (T(0)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(1)), (T(0)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(1)), (v_t(0))) , (T(1)));

  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), ui_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), vi_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), si_t(1)), bit_cast(si_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor[ true  ]((T(0)), wi_t(1)), bit_cast(si_t(1),as<T>()));

  TTS_EQUAL(eve::bit_xor[ true  ](ui_t(0), (T(1))), bit_cast(T(1),as<ui_t>()));
  TTS_EQUAL(eve::bit_xor[ true  ](si_t(0), (T(1))), bit_cast(T(1),as<si_t>()));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::bit_xor[ true  ](T(3), T(2) ) , T(1));
    TTS_EQUAL(eve::bit_xor[ true  ](T(3), v_t(2)) , T(1));
    TTS_EQUAL(eve::bit_xor[ true  ](T(3), T(1) ) , T(2));
    TTS_EQUAL(eve::bit_xor[ true  ](T(3), v_t(1)) , T(2));
  }
}


