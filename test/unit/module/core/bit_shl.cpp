/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shl.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_shl"
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
  TTS_EXPR_IS( eve::bit_shl(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_shl(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_shl(v_t(), T()) , T);
  TTS_EXPR_IS( eve::bit_shl(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shl(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shl(T(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shl(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::bit_shl(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shl(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shl(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::bit_shl(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shl(v_t(), vu_t()) , v_t);

};

//================================================================================================
// random size values
//================================================================================================
inline auto const random_bits = []<typename T>(eve::as<T>, auto& gen)
{
  using i_t = eve::as_integer_t<eve::element_type_t<T>>;
  eve::prng<i_t> dist(0,8*sizeof(i_t)-1);

  std::array<i_t,eve::test::amount<T>()> d;
  std::for_each(d.begin(), d.end(), [&](auto& e) { e = dist(gen); });

  return d;
};

//==================================================================================================
// wide tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_shl(wide, wide)"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shl;
  using eve::detail::map;
  using v_t = typename T::value_type;
  TTS_EQUAL( bit_shl(a0, a1), map([](auto e, auto s) ->v_t { return e << s; }, a0, a1));
  TTS_EQUAL( bit_shl[test](a0, a1),  eve::if_else(test, eve::bit_shl(a0, a1), a0));
};

EVE_TEST( "Check behavior of bit_shl(wide, scalar)"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I s, L test)
{
  using eve::bit_shl;
  using eve::detail::map;
  auto val = s.get(0);
  using v_t = typename T::value_type;
  TTS_EQUAL( bit_shl(a0, val), map([&](auto e) ->v_t{ return e << val; }, a0) );
  TTS_EQUAL( bit_shl[test](a0, val),  eve::if_else(test, eve::bit_shl(a0, val), a0));
};


//==================================================================================================
// Scalar tests
//==================================================================================================
EVE_TEST( "Check behavior of bitshl(scalar, scalar)"
        , eve::test::scalar::integers
        , eve::test::generate(eve::test::randoms(-50,50)
                             , random_bits
                             , eve::test::logicals(0, 3))
        )
<typename T, typename I, typename L>(T a0, I a1, L test)
{
  using eve::bit_shl;
  using v_t = typename T::value_type;
  for(std::size_t i = 0;  i < a0.size(); ++i)
  {
    TTS_EQUAL( bit_shl(a0[i], a1[i]), v_t(a0[i] << a1[i]));
    TTS_EQUAL( bit_shl[test[i]](a0[i], a1[i]),  (test[i] ? bit_shl(a0[i], a1[i]) : a0[i]));
  }
};
