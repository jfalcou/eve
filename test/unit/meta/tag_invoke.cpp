//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "eve/traits/invoke/protocol.hpp"
#include "test.hpp"

#include <eve/traits/invoke.hpp>
#include <eve/module/core.hpp>

#include <sstream>
#include <stdexcept>
#include <string>

//==================================================================================================
// Internal test - Does eve::tag_invoke let us write the various use case of EVE callable
//==================================================================================================
// Defines some callable for test purpose
namespace eve::tags
{
  struct func1 : elementwise
  {
    EVE_IMPLEMENTS_CALLABLE(func1, func1_);

    template<typename T>
    auto operator()(T const& x) const noexcept -> decltype(eve::tag_invoke(*this, x))
    {
      return eve::tag_invoke(*this, x);
    }

    template<typename... T>
    unsupported_call<func1(T...)> operator()(T... x) const
    requires(!requires { eve::tag_invoke(*this, x...); }) =delete;
  };

  struct func2 : reduction
  {
    EVE_IMPLEMENTS_CALLABLE(func2, func2_);

    auto operator()(auto x) const noexcept -> decltype(eve::tag_invoke(*this, x))
    {
      return eve::tag_invoke(*this, x);
    }

    template<typename... T>
    unsupported_call<func2(T...)> operator()(T... x) const
    requires(!requires { eve::tag_invoke(*this, x...); }) =delete;
  };

  struct func3 : constant
  {
    using callable_tag_type = func3;

    template<typename... T>
    auto operator()(T&&... x) const noexcept -> decltype(eve::tag_invoke(*this, EVE_FWD(x)...))
    {
      return eve::tag_invoke(*this, EVE_FWD(x)...);
    }

    // Custom error handling - Throw an exception at runtime
    template<typename... T>
    unsupported_call<func3(T&&...)> operator()(T&&... x) const
    requires(!requires { eve::tag_invoke(*this, EVE_FWD(x)...); })
    {
      throw std::invalid_argument(tts::typename_<unsupported_call<func3(T&&...)>>);
    }
  };

  struct func4 : support_options<func4>
  {
    EVE_DEFERS_CALLABLE(do_func4);
    using callable_tag_type = func4;

    template<typename... T>
    auto operator()(T const&... x) const noexcept -> decltype(eve::tag_invoke(*this, x...))
    {
      return eve::tag_invoke(*this, x...);
    }
  };
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

    friend std::string tag_invoke(eve::tag_of<func1> const&, auto, sort_of x)
    {
      return "Sort of " + std::to_string(x.value);
    }

    T value;
  };
}

// External tag_invoke setup - must lives in eve::tags
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
  constexpr auto do_func4(EVE_EXPECTS(cpu_), decorators<S> opts, auto x) noexcept
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

  TTS_EQUAL(out1.str(), "eve::tags::func1" );
  TTS_EQUAL(out2.str(), "eve::tags::func2" );
  TTS_EQUAL(out3.str(), "eve::tags::func3" );
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
  // No mask if no support_option
  bool b{};
  TTS_EXPECT_NOT_COMPILES(b, { eve::func1[b]; });
  TTS_EXPECT_NOT_COMPILES(b, { eve::func2[b]; });
  TTS_EXPECT_NOT_COMPILES(b, { eve::func3[b]; });

  // No option if no support_option
  constexpr auto lz = eve::lazy;
  TTS_EXPECT_NOT_COMPILES(lz, { eve::func1[lz]; });
  TTS_EXPECT_NOT_COMPILES(lz, { eve::func2[lz]; });
  TTS_EXPECT_NOT_COMPILES(lz, { eve::func3[lz]; });

  // Options are supported
  TTS_EXPECT_COMPILES(b   , { eve::func4[b];      } );
  TTS_EXPECT_COMPILES(lz  , { eve::func4[lz];     } );
  TTS_EXPECT_COMPILES(b,lz, { eve::func4[b][lz];  } );

  // Check mask/decorators processing
  TTS_EQUAL( eve::func4[true](8.25)                             , -  8.25 );
  TTS_EQUAL( eve::func4[false](8.25)                            ,  132.   );
  TTS_EQUAL( eve::func4[eve::lazy](8.25)                        ,  825    );
  TTS_EQUAL( eve::func4[eve::scale = 4](8.25)                   ,   33    );
  TTS_EQUAL( eve::func4[eve::other = '1'](8.25)                 , - 16.5  );
  TTS_EQUAL( eve::func4[eve::scale = 4][eve::lazy](8.25)        ,   33    );
  TTS_EQUAL( eve::func4[eve::scale = 4][eve::other = '1'](8.25) ,   33    );
};

// Outside functions using eve::func2 in a SFINAE context
template<typename T>
int dependent_call(T x) requires requires{ eve::func2(x); }
{
  return eve::func2(x);
}

template<typename T>
auto sfinae_call(T x) -> decltype(eve::func2(x))
{
  return eve::func2(x);
}

TTS_CASE("Check tag_invoke error checks")
{
  int x{};
  auto y = "some text";

  TTS_EXPECT_NOT_COMPILES(x, { eve::func1(x,x); } );
  TTS_EXPECT_NOT_COMPILES(x, { eve::func1(x);   } );
  TTS_EXPECT_NOT_COMPILES(y, { eve::func2(y);   } );

  // Special error reporting is allowed
  TTS_THROW(eve::func3(6.6), std::invalid_argument);

  // Dependent call are honored
  TTS_EXPECT_COMPILES    (x, { dependent_call(x); } );
  TTS_EXPECT_NOT_COMPILES(y, { dependent_call(y); } );
  TTS_EXPECT_COMPILES    (x, { sfinae_call(x);    } );
  TTS_EXPECT_NOT_COMPILES(y, { sfinae_call(y);    } );
};

//==================================================================================================
// Outsider test - Does eve::tag_invoke let us write callable in a side project
//==================================================================================================

// Short cut
#define MYLIB_CALLABLE(TYPE,NAME) EVE_IMPLEMENTS_CALLABLE_FROM(my_lib::detail, TYPE, NAME)

// Register some namespace into the calalble invoke system
namespace my_lib::detail  { EVE_DEFERRED_NAMESPACE(); }
namespace my_lib::funcs   { EVE_DEFERRED_INVOKE();    }

namespace my_lib
{
  namespace funcs
  {
    // By inheriting from eve::elementwise, we have access to the tag streaming operator
    struct my_func : eve::elementwise
    {
      MYLIB_CALLABLE(my_func, func_);

      template<typename T>
      auto operator()(T& x) const -> decltype(eve::tag_invoke(*this, x))
      {
        return eve::tag_invoke(*this, x);
      }

      template<typename T, typename U>
      auto operator()(T x, U y) const -> decltype(eve::tag_invoke(*this, x, y))
      {
        return eve::tag_invoke(*this, x, y);
      }
    };
  }

  inline constexpr funcs::my_func func = {};
}

namespace my_lib
{
  struct my_data
  {
    // Support my_lib callable
    friend void tag_invoke(funcs::my_func  , auto, my_data& x) { x.value = 99; }

    // Support eve callable
    friend void tag_invoke(eve::tags::func3, auto, my_data& x) { x.value = 44; }

    int value;
  };
}

// Deferred call inside eve for eve callable
namespace eve::detail
{
  constexpr auto func2_(EVE_EXPECTS(cpu_), my_lib::my_data x) noexcept { return 3.5 * x.value; }
}

// Deferred call inside my_lib for my_lib callable
namespace my_lib::detail
{
  constexpr auto func_(EVE_EXPECTS(eve::cpu_), my_data const& x, double d) noexcept { return d * x.value; }
}

TTS_CASE("Check callable streaming for external usage")
{
  std::ostringstream out;
  out << my_lib::func;

  TTS_EQUAL(out.str(), "my_lib::funcs::my_func" );
};

TTS_CASE("Check tag_invoke call stack for external usage")
{
  my_lib::my_data x{0};
  TTS_EQUAL( x.value  , 0 );

  my_lib::func(x);
  TTS_EQUAL( x.value, 99 );

  eve::func3(x);
  TTS_EQUAL( x.value, 44 );

  TTS_EQUAL( my_lib::func(x,10.), 440. );

  // EVE callable on my_lib data structure
  TTS_EQUAL( eve::func2(x), 154. );
};
