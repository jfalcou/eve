//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/rat.hpp>
#include <array>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::rat(scalar)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  using v_t =  eve::element_type_t<T>;
  TTS_EXPR_IS( eve::rat(T())                    , (std::array<T, 2>)  );
  TTS_EXPR_IS( eve::rat(T(), T())               , (std::array<T, 2>) );
  TTS_EXPR_IS( eve::rat(T(), v_t())             , (std::array<T, 2>) );
  TTS_EXPR_IS( eve::rat(v_t(), v_t())           , (std::array<v_t, 2>)  );
};



//==================================================================================================
// Tests for eve::rat
//==================================================================================================
EVE_TEST( "Check behavior of eve::rat(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0.0))
        )
<typename T>(T const& a0)
{
//   using eve::detail::map;
//   using v_t = eve::element_type_t<T>;
  if constexpr(eve::has_native_abi_v<T>)
  {
    auto [n, d] = eve::rat(a0/17);
    std::cout << "a0/17 " << a0/17 << std::endl;
    std::cout << "n " << n << std::endl;
    std::cout << "d " << d << std::endl;
  }

//   TTS_EQUAL(n, map([](auto e) -> v_t { return  e; }, a0));
//   TTS_EQUAL(d, v_t(17));
};

// EVE_TEST( "Check behavior of eve::rat(scalar)"
//         , eve::test::scalar::ieee_reals
//         , eve::test::generate ( eve::test::ramp(-1.0, 1.0))
//         )
// <typename T>(T const& data)
// {
//   using eve::detail::map;
//   using v_t = typename T::value_type;

//   for(auto a0 :data)
//   {
//     TTS_EQUAL(eve::rat(a0), (a0 >= 0 ? 0 : eve::pi(eve::as(v_t()))) );
//   }
// };

// //==================================================================================================
// // Tests for eve::pedantic(eve::rat)
// //==================================================================================================
// EVE_TEST( "Check behavior of eve::pedantic(eve::rat)(simd)"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate ( eve::test::ramp(-1.0, 1.0)
//                               , eve::test::limits()
//                               )
//         )
// <typename T>(T a0, auto cases )
// {
//   using eve::detail::map;
//   using v_t = eve::element_type_t<T>;

//   TTS_EQUAL(eve::pedantic(eve::rat)(a0), map([](auto e) -> v_t { return  e >= 0 ? 0 : eve::pi(eve::as(v_t())); }, a0));
//   TTS_IEEE_EQUAL( eve::pedantic(eve::rat)(cases.nan    ), cases.nan   );
// };

// EVE_TEST( "Check behavior of eve::pedantic(eve::rat)(scalar)"
//         , eve::test::scalar::ieee_reals
//         , eve::test::generate ( eve::test::ramp(-1.0, 1.0)
//                               , eve::test::limits()
//                               )
//         )
// <typename T>(T const& data, auto cases )
// {
//   using v_t = typename T::value_type;
//   for(auto a0 :data) TTS_EQUAL(eve::pedantic(eve::rat)(a0), (a0 < 0)*eve::pi(eve::as(v_t())) );
//   TTS_IEEE_EQUAL( eve::pedantic(eve::rat)(cases.nan), cases.nan   );
// };

// //==================================================================================================
// // Test for eve::diff(eve::rat)
// //==================================================================================================
// EVE_TEST( "Check behavior of eve::diff(eve::rat)(simd)"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
//         )
// <typename T>(T const& a0)
// {
//   TTS_EQUAL ( eve::diff(eve::rat)(a0), eve::zero(eve::as(a0)));
// };

// EVE_TEST( "Check behavior of eve::diff(eve::rat)(scalar)"
//         , eve::test::scalar::ieee_reals
//         , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
//         )
// <typename T>(T const& data )
// {
//   for(auto a0 :data) TTS_EQUAL( eve::diff(eve::rat)(a0), eve::zero(eve::as(a0)) );
// };
