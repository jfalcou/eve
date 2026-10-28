//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <array>
#include <numeric>

//==================================================================================================
// Unaligned store tests
//==================================================================================================
TTS_CASE_WITH ( "Check store behavior with unaligned pointers"
              , eve::test::simd::all_types_wf16
              , tts::ramp(1),tts::logicals(1,2)
              )
<typename T, typename L> (T data, L logical_data)
{
  std::array<eve::element_type_t<T>, 3 * T::size()> ref;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_ref;

  for(int i = 0; i < T::size(); ++i)
  {
    ref[ i              ] =  1 + i;
    ref[ i + T::size()  ] =  1 + i;
    ref[ i + 2*T::size()] =  1 + i;

    logical_ref[ i              ] = ((1+i) % 2) == 0;
    logical_ref[ i + T::size()  ] = ((1+i) % 2) == 0;
    logical_ref[ i + 2*T::size()] = ((1+i) % 2) == 0;
  }

  std::array<eve::element_type_t<T>, 3 * T::size()> target;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_target;

  eve::store(data, &target[ 0            ]);
  eve::store(data, &target[ T::size()    ]);
  eve::store(data, &target[ 2 * T::size()]);

  eve::store(logical_data, &logical_target[ 0            ]);
  eve::store(logical_data, &logical_target[ T::size()    ]);
  eve::store(logical_data, &logical_target[ 2 * T::size()]);

  TTS_ALL_EQUAL(target        , ref         );
  TTS_ALL_EQUAL(logical_target, logical_ref );
};

//==================================================================================================
// A pointer to const is refused at the signature
//==================================================================================================
TTS_CASE_TPL("Check store refuses a pointer to const", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using l_t = eve::logical<T>;
  using e_t = eve::logical<v_t>;

  [[maybe_unused]] T   v  = {};
  [[maybe_unused]] l_t lv = {};
  [[maybe_unused]] v_t*       p   = nullptr;
  [[maybe_unused]] v_t const* cp  = nullptr;
  [[maybe_unused]] e_t*       lp  = nullptr;
  [[maybe_unused]] e_t const* lcp = nullptr;
  [[maybe_unused]] eve::aligned_ptr<v_t, T::size()>       ap  = {};
  [[maybe_unused]] eve::aligned_ptr<v_t const, T::size()> acp = {};

  TTS_EXPECT_COMPILES    (v, p,    { eve::store(v, p);    });
  TTS_EXPECT_COMPILES    (v, ap,   { eve::store(v, ap);   });
  TTS_EXPECT_NOT_COMPILES(v, cp,   { eve::store(v, cp);   });
  TTS_EXPECT_NOT_COMPILES(v, acp,  { eve::store(v, acp);  });
  TTS_EXPECT_COMPILES    (lv, lp,  { eve::store(lv, lp);  });
  TTS_EXPECT_NOT_COMPILES(lv, lcp, { eve::store(lv, lcp); });
};
