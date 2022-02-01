/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/function/bit_shr.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_shr"
        , eve::test::simd::unsigned_types
        )
<typename T>(eve::as<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  //regular
  TTS_EXPR_IS( eve::bit_shr(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), T()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shr(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shr(v_t(), vu_t()) , v_t);

};

//================================================================================================
// random size values
//================================================================================================
inline auto const random_bits = []<typename T>(eve::as<T>, auto& gen)
{
  using i_t = eve::as_integer_t<eve::element_type_t<T>>;
  eve::prng<i_t> dist(0,8*sizeof(i_t)-1);

  std::array<i_t, eve::test::amount<T>()> d;
  std::for_each(d.begin(), d.end(), [&](auto& e) { e = dist(gen); });

  return d;
};

//==================================================================================================
// wide tests
//==================================================================================================
EVE_TEST( "Check behavior of shr(wide, wide)"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shr;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EQUAL( bit_shr(a0, a1), map([](auto e, auto s) ->v_t { return v_t(u_t(e) >> s); }, a0, a1));
  TTS_EQUAL( bit_shr[test](a0, a1),  eve::if_else(test, eve::bit_shr(a0, a1), a0));
};

EVE_TEST( "Check behavior of shift(wide, scalar)"
        , eve::test::simd::integers
         , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I s, L test)
{
  using eve::bit_shr;
  using eve::detail::map;
  auto val = s.get(0);
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EQUAL( bit_shr(a0, val), map([&](auto e) ->v_t{ return v_t(u_t(e) >> val); }, a0) );
  TTS_EQUAL( bit_shr[test](a0, val),  eve::if_else(test, eve::bit_shr(a0, val), a0));
};


//==================================================================================================
// Scalar tests
//==================================================================================================
EVE_TEST( "Check behavior of shl(scalar, scalar)"
        , eve::test::scalar::integers
         , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shr;
  using eve::detail::map;
  using v_t = typename T::value_type;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  for(std::size_t i = 0;  i < a0.size(); ++i)
  {
    TTS_EQUAL( bit_shr(a0[i], a1[i]),   v_t(u_t(a0[i]) >> a1[i]));
    TTS_EQUAL( bit_shr[test[i]](a0[i], a1[i]),  (test[i] ? bit_shr(a0[i], a1[i]) : a0[i]));
  }
};
