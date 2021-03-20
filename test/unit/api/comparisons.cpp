//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/value.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Type tests
//==================================================================================================
auto type_tests = []<typename T>(T)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS((T() == T())                  , logical<T>);
  TTS_EXPR_IS((T() != T())                  , logical<T>);
  TTS_EXPR_IS((T() <  T())                  , logical<T>);
  TTS_EXPR_IS((T() <= T())                  , logical<T>);
  TTS_EXPR_IS((T() >  T())                  , logical<T>);
  TTS_EXPR_IS((T() >= T())                  , logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<T>()), logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<T>()), logical<T>);

  TTS_EXPR_IS((T() == v_t())                  , logical<T>);
  TTS_EXPR_IS((T() != v_t())                  , logical<T>);
  TTS_EXPR_IS((T() <  v_t())                  , logical<T>);
  TTS_EXPR_IS((T() <= v_t())                  , logical<T>);
  TTS_EXPR_IS((T() >  v_t())                  , logical<T>);
  TTS_EXPR_IS((T() >= v_t())                  , logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<v_t>()), logical<T>);
  TTS_EXPR_IS((logical<T>() != logical<v_t>()), logical<T>);

  TTS_EXPR_IS((v_t() == T())                  , logical<T>);
  TTS_EXPR_IS((v_t() != T())                  , logical<T>);
  TTS_EXPR_IS((v_t() <  T())                  , logical<T>);
  TTS_EXPR_IS((v_t() <= T())                  , logical<T>);
  TTS_EXPR_IS((v_t() >  T())                  , logical<T>);
  TTS_EXPR_IS((v_t() >= T())                  , logical<T>);
  TTS_EXPR_IS((logical<v_t>() != logical<T>()), logical<T>);
  TTS_EXPR_IS((logical<v_t>() != logical<T>()), logical<T>);
};

EVE_TEST_BED( "Check comparison operators' return types"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , type_tests
            );

//==================================================================================================
// Value tests
//==================================================================================================
auto basic_tests = []<typename T> (T lhs, T rhs)
{
  TTS_EQUAL((lhs == lhs), eve::true_ (eve::as(lhs)));
  TTS_EQUAL((lhs != lhs), eve::false_(eve::as(lhs)));
  TTS_EQUAL((lhs <= lhs), eve::true_ (eve::as(lhs)));
  TTS_EQUAL((lhs <  lhs), eve::false_(eve::as(lhs)));
  TTS_EQUAL((lhs >= lhs), eve::true_ (eve::as(lhs)));
  TTS_EQUAL((lhs >  lhs), eve::false_(eve::as(lhs)));

  eve::logical<T> ref_eq  = [&](auto i, auto) { return lhs.get(i) == rhs.get(i); };
  eve::logical<T> ref_neq = [&](auto i, auto) { return lhs.get(i) != rhs.get(i); };
  eve::logical<T> ref_lt  = [&](auto i, auto) { return lhs.get(i) <  rhs.get(i); };
  eve::logical<T> ref_lte = [&](auto i, auto) { return lhs.get(i) <= rhs.get(i); };
  eve::logical<T> ref_gt  = [&](auto i, auto) { return lhs.get(i) >  rhs.get(i); };
  eve::logical<T> ref_gte = [&](auto i, auto) { return lhs.get(i) >= rhs.get(i); };

  TTS_EQUAL((lhs == rhs), ref_eq  );
  TTS_EQUAL((lhs != rhs), ref_neq );
  TTS_EQUAL((lhs <  rhs), ref_lt  );
  TTS_EQUAL((lhs <= rhs), ref_lte );
  TTS_EQUAL((lhs >  rhs), ref_gt  );
  TTS_EQUAL((lhs >= rhs), ref_gte );
};

auto mixed_tests = []<typename T> (T lhs, T rhs)
{
  using v_t = eve::element_type_t<T>;
  v_t val   = rhs.get(0);

  eve::logical<T> ref_eq  = [&](auto i, auto) { return lhs.get(i) == val; };
  eve::logical<T> ref_neq = [&](auto i, auto) { return lhs.get(i) != val; };
  eve::logical<T> ref_lt  = [&](auto i, auto) { return lhs.get(i) <  val; };
  eve::logical<T> ref_lte = [&](auto i, auto) { return lhs.get(i) <= val; };
  eve::logical<T> ref_gt  = [&](auto i, auto) { return lhs.get(i) >  val; };
  eve::logical<T> ref_gte = [&](auto i, auto) { return lhs.get(i) >= val; };

  TTS_EQUAL((lhs == val), ref_eq  );
  TTS_EQUAL((lhs != val), ref_neq );
  TTS_EQUAL((lhs <  val), ref_lt  );
  TTS_EQUAL((lhs <= val), ref_lte );
  TTS_EQUAL((lhs >  val), ref_gt  );
  TTS_EQUAL((lhs >= val), ref_gte );
};

auto nan_tests = []<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  // Corners cases
  if constexpr(eve::platform::supports_nans)
  {
    TTS_EQUAL((eve::nan(eve::as<T>()) == eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) != eve::nan(eve::as<T>()) ), eve::true_ (eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) <  eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) <= eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) >  eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) >= eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));

    TTS_EQUAL((eve::nan(eve::as<T>()) == v_t(4) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) != v_t(4) ), eve::true_ (eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) <  v_t(4) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) <= v_t(4) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) >  v_t(4) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) >= v_t(4) ), eve::false_(eve::as<T>()));

    TTS_EQUAL((v_t(4) == eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((v_t(4) != eve::nan(eve::as<T>()) ), eve::true_ (eve::as<T>()));
    TTS_EQUAL((v_t(4) <  eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((v_t(4) <= eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((v_t(4) >  eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((v_t(4) >= eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
  }
};

EVE_TEST_BED( "Check comparison operators behavior with NaNs"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::no_data)
            , nan_tests
            );

EVE_TEST_BED( "Check comparison operators behavior between wide"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::randoms(-50, 50)
                                  )
            , basic_tests
            );

EVE_TEST_BED( "Check comparison operators behavior between wide & scalar"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(-50, 50)
                                  , eve::test::randoms(-50, 50)
                                  )
            , mixed_tests
            );
