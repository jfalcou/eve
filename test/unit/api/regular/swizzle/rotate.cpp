//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

namespace
{

template <typename T>
T scalar_rotate(T x, std::ptrdiff_t m) {
  std::array<eve::element_type_t<T>, T::size()> buf;
  eve::store(x, buf.data());
  std::rotate(buf.begin(), buf.begin() + m, buf.end());
  return T(buf.data());
}

TTS_CASE_WITH( "Check behavior of rotate swizzle"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(-50, 50)
                        , tts::logicals(0, 1)
                        )
        )
<typename T, typename L>(T simd, L logicals)
{
  eve::detail::for_<0,1,T::size()>
  ( [&]<typename M>(M)
  {
    T ref = scalar_rotate(simd, M{}());
    L lref = scalar_rotate(logicals, M{}());

    TTS_EQUAL(eve::rotate(simd,     eve::index<M{}()>), ref);
    TTS_EQUAL(eve::rotate(logicals, eve::index<M{}()>), lref);

    TTS_EQUAL(eve::shuffle(simd,     eve::rotate_pattern<M{}(), T::size()>), ref);
    TTS_EQUAL(eve::shuffle(logicals, eve::rotate_pattern<M{}(), L::size()>), lref);
  });
};

}
