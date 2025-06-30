//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/overload.hpp>

enum class tests
{
  has_condition_key  = 1
, has_ignore_none
, has_mask
, has_ignore_all
};

enum class OverloadType
{
  regular = 1
, masked
};

namespace eve
{
  template<typename Options>
  struct func_t : callable<func_t, Options, conditional_option>
  {
    bool operator()(tests test_id) const { return EVE_DISPATCH_CALL_NT(test_id); }
    EVE_CALLABLE_OBJECT(func_t, func_);
  };

  template<typename Options>
  struct chained_func_t : callable<chained_func_t, Options, conditional_option>
  {
    auto operator()(tests test_id) const { return EVE_DISPATCH_CALL_NT(test_id); }
    EVE_CALLABLE_OBJECT(chained_func_t, chained_func_);
  };

  template<typename Options>
  struct ew_drop_func_t : strict_elementwise_callable<ew_drop_func_t, Options>
  {
    auto operator()(int a) const { return EVE_DISPATCH_CALL_NT(a); }
    EVE_CALLABLE_OBJECT(ew_drop_func_t, ew_drop_func_);
  };

  inline constexpr auto         func = functor<func_t>;
  inline constexpr auto chained_func = functor<chained_func_t>;
  inline constexpr auto ew_drop_func = functor<ew_drop_func_t>;
};

namespace eve::detail
{
  template<eve::callable_options O>
  bool func_(EVE_REQUIRES(cpu_), O const&, tests test_id)
  {
    if(test_id == tests::has_condition_key) return O::contains(condition_key);
    if(test_id == tests::has_ignore_none)   return match_option<condition_key,O,ignore_none_>;
    if(test_id == tests::has_ignore_all)    return match_option<condition_key,O,ignore_all_>;
    if(test_id == tests::has_mask)          return match_option<condition_key,O,if_<logical<unsigned char>>>;
    return false;
  }

  template<eve::callable_options O>
  auto chained_func_(EVE_REQUIRES(cpu_), O const& o, tests)
  {
    return func[o][keep_first(4)].options()[condition_key];
  }

  template<eve::callable_options O, eve::conditional_expr C>
  auto ew_drop_func_(EVE_REQUIRES(cpu_), C const&, O const&, int)
  {
    TTS_EXPECT(!O::contains(condition_key));
    return wide<int>{ (int) OverloadType::masked };
  }

  template<eve::callable_options O>
  auto ew_drop_func_(EVE_REQUIRES(cpu_), O const&, int)
  {
    TTS_EXPECT(!O::contains(condition_key));
    return eve::wide<int>{ (int) OverloadType::regular };
  }
}

TTS_CASE("Check callable always have conditional_key by default")
{
  TTS_EXPECT(eve::func(tests::has_condition_key)                  );
  TTS_EXPECT(eve::func[true](tests::has_condition_key)            );
  TTS_EXPECT(eve::func[eve::ignore_none](tests::has_condition_key));
  TTS_EXPECT(eve::func[eve::ignore_all](tests::has_condition_key) );
};

TTS_CASE("Check callable sets up ignore_none correctly")
{
  TTS_EXPECT    (eve::func(tests::has_ignore_none)                  );
  TTS_EXPECT_NOT(eve::func[true](tests::has_ignore_none)            );
  TTS_EXPECT    (eve::func[eve::ignore_none](tests::has_ignore_none));
  TTS_EXPECT_NOT(eve::func[eve::ignore_all](tests::has_ignore_none) );
};

TTS_CASE("Check callable sets up mask correctly")
{
  TTS_EXPECT_NOT(eve::func(tests::has_mask)                  );
  TTS_EXPECT    (eve::func[true](tests::has_mask)            );
  TTS_EXPECT_NOT(eve::func[eve::ignore_none](tests::has_mask));
  TTS_EXPECT_NOT(eve::func[eve::ignore_all](tests::has_mask) );
};

TTS_CASE("Check callable sets up other conditions correctly")
{
  TTS_EXPECT_NOT(eve::func(tests::has_ignore_all)                  );
  TTS_EXPECT_NOT(eve::func[true](tests::has_ignore_all)            );
  TTS_EXPECT_NOT(eve::func[eve::ignore_none](tests::has_ignore_all));
  TTS_EXPECT    (eve::func[eve::ignore_all](tests::has_ignore_all) );
};

TTS_CASE("Check callable always have conditional_key when chained")
{
  TTS_EXPR_IS(eve::chained_func(tests::has_condition_key), eve::keep_first);
  TTS_EXPR_IS(eve::chained_func[true](tests::has_condition_key), eve::keep_first);
  TTS_EXPR_IS(eve::chained_func[eve::ignore_none](tests::has_condition_key), eve::keep_first);
  TTS_EXPR_IS(eve::chained_func[eve::ignore_all](tests::has_condition_key), eve::keep_first);
};

TTS_CASE("Check elementwise callable condition_key drop")
{
  TTS_EQUAL(eve::ew_drop_func(3011).get(0), (int) OverloadType::regular);
  TTS_EQUAL(eve::ew_drop_func[eve::ignore_none](3011).get(0), (int) OverloadType::regular);
  TTS_EQUAL(eve::ew_drop_func[true](3011).get(0), (int) OverloadType::masked);
  TTS_EQUAL(eve::ew_drop_func[eve::ignore_all](3011).get(0), (int) OverloadType::masked);
};
