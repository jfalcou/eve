/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_not"
        , eve::test::simd::all_types
        )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_not(T()  ) , T);
  TTS_EXPR_IS( eve::bit_not(v_t()) , v_t);

  // conditional
  TTS_EXPR_IS( eve::bit_not[logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::bit_not[logical<v_t>()](T()), T);
  TTS_EXPR_IS( eve::bit_not[logical<T>()](v_t()), T);
};

//==================================================================================================
//  bit_not simd tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_not(simd) on integral types"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>( T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::map;
  using eve::bit_not;
  TTS_EQUAL( bit_not(a0), map([](auto e) -> v_t{ return ~e; }, a0));
};

EVE_TEST( "Check behavior of bit_not(simd) on floating types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::as;
  using eve::bit_not;
  using eve::bit_cast;
  using eve::detail::map;
   using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_not(a0), map([](auto e)
                                   { return  bit_cast(~bit_cast(e, as(i_t())), as(v_t())); }, a0
                                  ));
};
//==================================================================================================
//  bit_not scalar tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_not(scalar) on integral types"
        , eve::test::scalar::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>( T const& a0)
{
  using v_t =  typename T::value_type;
  using eve::detail::map;
  using eve::bit_not;
  for(auto a : a0)
    TTS_EQUAL( bit_not(a), static_cast<v_t>(~a));
};

EVE_TEST( "Check behavior of bit_not(scalar) on floating types"
        , eve::test::scalar::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::as;
  using eve::bit_not;
  using eve::bit_cast;
  using v_t = typename T::value_type;
  using i_t = eve::as_integer_t<v_t, signed>;
  for(auto a : a0)
    TTS_IEEE_EQUAL( bit_not(a), bit_cast(~bit_cast(a, as(i_t())), as(v_t())));;
};
