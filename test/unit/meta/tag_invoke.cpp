//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "eve/detail/raberu.hpp"
#include "eve/traits/invoke/decorator.hpp"
#include "test.hpp"

#include <eve/traits/invoke.hpp>
#include <eve/module/core.hpp>
#include <string>
#include <sstream>

// Defines some callable for test purpose
namespace eve::tags
{
  struct func1 : elementwise  { EVE_CALLABLE(func1, func1_, "eve::func1");  };
  struct func2 : reduction    { EVE_CALLABLE(func2, func2_, "func2");       };

  struct func3 : constant
  {
    EVE_DEFINES_CALLABLE(func3, "the func III");
    EVE_CALLABLE_INTERFACE(func3);
  };

  struct func4 : support_options<func4> { EVE_CALLABLE(func4, func4_, "eve::func4"); };
}

namespace eve
{
  // Callable objects
  inline constexpr tags::func1 func1 = {};
  inline constexpr tags::func2 func2 = {};
  inline constexpr tags::func3 func3 = {};
  inline constexpr tags::func4 func4 = {};

  // Some specific flags
  struct lazy_t {};
  struct scale_t {};
  struct other_t {};
  inline constexpr auto lazy  = rbr::flag(lazy_t{});
  inline constexpr auto scale = rbr::keyword(scale_t{});
  inline constexpr auto other = rbr::keyword(other_t{});
}

// Fake type providing a hidden friend tag_invoke
namespace eve
{
  template<typename T> struct sort_of
  {
    sort_of(T v) : value(v) {}

    // The way we expect to use tag_invoke on most types
    friend std::string tag_invoke(eve::tag_of<func1> const&, auto, sort_of x)
    {
      return "Sort of " + std::to_string(x.value);
    }

    T value;
  };
}

// Actual external tag_invoke setup - must lives in eve::tags
namespace eve::tags
{
  constexpr auto tag_invoke(func3, auto, eve::integral_value auto v)
  {
    return 1.5f * eve::convert(v,eve::as(1.5f));
  }

  // Regular func4
  constexpr auto tag_invoke(func4, auto, auto x) noexcept { return 10*x; }
}

// Deferred call implementation - must lives in eve::detail
namespace eve::detail
{
  constexpr auto func2_(EVE_EXPECTS(cpu_), scalar_value auto x) noexcept { return -x; }

  // Decorated func4 - function can mix tag_invoke and deferred call if needed
  template<typename S>
  constexpr auto func4_(EVE_EXPECTS(cpu_), decorators<S> opts, auto x) noexcept
  {
    if constexpr(S::contains(detail::mask))
    {
      return  opts[detail::mask].mask(as(x)) ? -x : 16. * x;
    }
    else
    {
      return opts[lazy] ? opts[scale | 100.] * x : opts[scale | -2.] * x;
    }
  }
}

TTS_CASE("Check callable concepts")
{
  // func1/2/3 are callable but a random type is not
  TTS_CONSTEXPR_EXPECT    ( eve::callable<eve::tag_of<eve::func1>> );
  TTS_CONSTEXPR_EXPECT    ( eve::callable<eve::tag_of<eve::func2>> );
  TTS_CONSTEXPR_EXPECT    ( eve::callable<eve::tag_of<eve::func3>> );
  TTS_CONSTEXPR_EXPECT_NOT( eve::callable<std::plus<>> );

  // only func1/2 use a deferred call
  TTS_CONSTEXPR_EXPECT    ( eve::deferred_callable<eve::tag_of<eve::func1>> );
  TTS_CONSTEXPR_EXPECT    ( eve::deferred_callable<eve::tag_of<eve::func2>> );
  TTS_CONSTEXPR_EXPECT_NOT( eve::deferred_callable<eve::tag_of<eve::func3>> );

  // checks callable sub-category
  TTS_CONSTEXPR_EXPECT( eve::elementwise_callable<eve::tag_of<eve::func1>>);
  TTS_CONSTEXPR_EXPECT( eve::reduction_callable<eve::tag_of<eve::func2>>  );
  TTS_CONSTEXPR_EXPECT( eve::constant_callable<eve::tag_of<eve::func3>>   );
};

TTS_CASE("Check callable streaming")
{
  std::ostringstream out1,out2,out3;
  out1 << eve::func1;
  out2 << eve::func2;
  out3 << eve::func3;

  TTS_EQUAL(out1.str(), "eve::func1"  );
  TTS_EQUAL(out2.str(), "func2"       );
  TTS_EQUAL(out3.str(), "the func III");
};

TTS_CASE("Check tag_invoke call stack")
{
  TTS_EQUAL( eve::func1(eve::sort_of{9})  , "Sort of 9"             );
  TTS_EQUAL( eve::func2(4)                , -4                      );
  TTS_EQUAL( eve::func3(eve::wide<int>{7}), eve::wide<float>{10.5f} );
  TTS_EQUAL( eve::func4(8.25)             , 82.5                    );
};

TTS_CASE("Check tag_invoke with options")
{
  bool b{};

  eve::func2("lol");

  // No option if no support_option
  TTS_EXPECT_NOT_COMPILES(b, { eve::func1[b]; });
  TTS_EXPECT_NOT_COMPILES(b, { eve::func2[b]; });
  TTS_EXPECT_NOT_COMPILES(b, { eve::func3[b]; });

  // Options are supported but duplicates are not allowed
  TTS_EXPECT_COMPILES     (b, { eve::func4[b]; }   );
  TTS_EXPECT_NOT_COMPILES (b, { eve::func4[b][b]; });

  // Check mask/decorators processing
  TTS_EQUAL( eve::func4[true](8.25)                             , -  8.25 );
  TTS_EQUAL( eve::func4[false](8.25)                            ,  132.   );
  TTS_EQUAL( eve::func4[eve::lazy](8.25)                        ,  825    );
  TTS_EQUAL( eve::func4[eve::scale = 4](8.25)                   ,   33    );
  TTS_EQUAL( eve::func4[eve::other = '1'](8.25)                 , - 16.5  );
  TTS_EQUAL( eve::func4[eve::scale = 4][eve::lazy](8.25)        ,   33    );
  TTS_EQUAL( eve::func4[eve::scale = 4][eve::other = '1'](8.25) ,   33    );
};

TTS_CASE("Check tag_invoke error checks")
{
  int x{};
  auto y = "some text";
  double z{};

  TTS_EXPECT_NOT_COMPILES(x,  { eve::func1(x); } );
  TTS_EXPECT_NOT_COMPILES(y,  { eve::func2(y); } );
  TTS_EXPECT_NOT_COMPILES(z,  { eve::func3(z); } );
};

