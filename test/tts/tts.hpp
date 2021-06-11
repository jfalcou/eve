//==================================================================================================
/**
  TTS - Tiny Test System
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

//==================================================================================================
// Dependencies
//==================================================================================================
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

//==================================================================================================
// Warning Suppressors
//==================================================================================================
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

//==================================================================================================
// Misc. Helpers
//==================================================================================================
namespace tts::detail
{
  inline bool done() { return false; }

  template<typename... T> struct typelist {};
  template<typename T> struct box { using type = T; };

  // Iterate statically over a typelist
  template<typename Function, typename... Types>
  bool for_each_type(Function &&f, typelist<Types...> const &)
  {
    (f(box<Types> {}), ...);
    return true;
  }

  // bit_cast till we got std::bit_cast :(
  template<typename U, typename T> inline U bit_cast(T a) noexcept
  {
    U that;
    void const *src = reinterpret_cast<void const *>(&a);
    void *      dst = reinterpret_cast<void *>(&that);
    std::memcpy(dst, src, sizeof(a));
    return that;
  }

  inline auto as_int(float a)   noexcept  { return bit_cast<std::int32_t>(a); }
  inline auto as_int(double a)  noexcept  { return bit_cast<std::int64_t>(a); }

  template<typename T> inline auto bitinteger(T a) noexcept
  {
    auto ia = as_int(a);
    using r_t = std::remove_cvref_t<decltype(ia)>;
    constexpr auto Signmask = r_t(1) << (sizeof(r_t)*8-1);
    return std::signbit(a) ?  Signmask-ia : ia;
  }

  template<typename It1, typename It2, typename Func>
  std::pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2, Func p)
  {
    while (first1 != last1 && p(*first1, *first2))
      ++first1, ++first2;
    return std::make_pair(first1, first2);
  }

  //==================================================================================================
  // Internal concepts
  //==================================================================================================
  template<typename T>
  concept support_std_to_string = requires(T e) { std::to_string(e); };

  template<typename T>
  concept support_to_string = requires(T e) { to_string(e); };

  template<typename T>
  concept has_to_string = requires(T e) { e.to_string(); };

  template<typename T>
  concept sequence = requires(T e) {std::begin(e); std::end(e); };

  template<typename T>
  concept streamable = requires(T e, std::ostream& o) { o << e; };
}

//==================================================================================================
// Display helpers
//==================================================================================================
namespace tts
{
  template<typename T> struct type_name_
  {
    static constexpr auto value() noexcept
    {
  #if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1,
        j = data.find(">::value");
      return data.substr(i, j - i);
  #else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2,
        j = data.find_last_of(']');
      return data.substr(i, j - i);
  #endif
    }
  };

  template<typename T>
  inline constexpr auto const typename_ = type_name_<T>::value();

  template<typename T> constexpr auto typename_of_(T&&){ return typename_<T>; }

  // Display a result
  template<typename T> std::string as_string(T const& e)
  {
    if constexpr( std::is_pointer_v<T> )
    {
      std::ostringstream os;
      os << std::string(typename_<T>) << "(" << e << ")";
      return os.str();
    }
    else if constexpr( detail::support_std_to_string<T> )
    {
      return std::to_string(e);
    }
    else if constexpr( detail::streamable<T> )
    {
      std::ostringstream os;
      os << e;
      return os.str();
    }
    else if constexpr( detail::support_to_string<T> )
    {
      return to_string(e);
    }
    else if constexpr( detail::sequence<T> )
    {
      std::string that = "{ ";
      for(auto const& v : e) that += as_string(v) + " ";
      that += "}";
      return that;
    }
    else
    {
      std::ostringstream os;
      os << "[" << std::string(typename_<T>) << "]@(" << &e << ")";
      return os.str();
    }
  }

  inline std::string as_string(bool b) { return b ? std::string("true") : std::string("false"); }
  inline std::string as_string(std::string const& e)      { return  e;              }
  inline std::string as_string(std::string_view const& e) { return  std::string(e); }
  inline std::string as_string(std::nullptr_t)            { return  std::string("nullptr"); }
}

//==================================================================================================
// List of types list to use in template cases
//==================================================================================================
#define TTS_SIGNED_INTEGRAL_TYPES   std::int8_t , std::int16_t , std::int32_t , std::int64_t
#define TTS_UNSIGNED_INTEGRAL_TYPES std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t

#define TTS_INTEGRAL_TYPES                                                                         \
  char, std::int8_t, std::int16_t , std::int32_t , std::int64_t,                                   \
       std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t                                   \
/**/

#define TTS_IEEE_TYPES              float, double
#define TTS_SIGNED_NUMERIC_TYPES    TTS_IEEE_TYPES, TTS_SIGNED_INTEGRAL_TYPES
#define TTS_UNSIGNED_NUMERIC_TYPES  TTS_UNSIGNED_INTEGRAL_TYPES
#define TTS_NUMERIC_TYPES           TTS_IEEE_TYPES, TTS_INTEGRAL_TYPES
#define TTS_ALL_TYPES               bool, TTS_NUMERIC_TYPES

//==================================================================================================
// Preprocessor shenanigans
//==================================================================================================
#ifndef TTS_FUNCTION
#define TTS_FUNCTION TTS_UNIQUE(tts_function)
#endif

#ifndef TTS_REGISTRATION
#define TTS_REGISTRATION TTS_UNIQUE(tts_registration)
#endif

#define TTS_UNIQUE3(ID, LINE) ID##LINE
#define TTS_UNIQUE2(ID, LINE) TTS_UNIQUE3(ID, LINE)
#define TTS_UNIQUE(ID)        TTS_UNIQUE2(ID, __COUNTER__)

#define TTS_CAT(x, y)                     TTS_CAT_I(x, y)
#define TTS_CAT_I(x, y)                   x##y

#define TTS_STRING(...)   TTS_STRING_((__VA_ARGS__))
#define TTS_STRING__(...) #__VA_ARGS__
#define TTS_STRING_(TXT)  TTS_STRING__ TXT

// Remove parens around macro token if any are present -- NON TRIVIAL SHIT
#define TTS_REMOVE_PARENS(x)              TTS_EVAL((TTS_REMOVE_PARENS_I x), x)
#define TTS_REMOVE_PARENS_I(...)          1, 1
#define TTS_APPLY(macro, args)            TTS_APPLY_I(macro, args)
#define TTS_APPLY_I(macro, args)          macro args
#define TTS_EVAL_I(test, x)               TTS_MAYBE_STRIP_PARENS(TTS_TEST_ARITY test, x)
#define TTS_EVAL(test, x)                 TTS_EVAL_I(test, x)
#define TTS_TEST_ARITY(...)               TTS_APPLY(TTS_TEST_ARITY_I, (__VA_ARGS__, 2, 1))
#define TTS_TEST_ARITY_I(a, b, c, ...)    c
#define TTS_MAYBE_STRIP_PARENS(cond, x)   TTS_MAYBE_STRIP_PARENS_I(cond, x)
#define TTS_MAYBE_STRIP_PARENS_I(cond, x) TTS_CAT(TTS_MAYBE_STRIP_PARENS_, cond)(x)
#define TTS_MAYBE_STRIP_PARENS_1(x)       x
#define TTS_MAYBE_STRIP_PARENS_2(x)       TTS_APPLY(TTS_MAYBE_STRIP_PARENS_2_I, x)
#define TTS_MAYBE_STRIP_PARENS_2_I(...)   __VA_ARGS__

//==================================================================================================
// Color on *NIX terminal using ANSI control sequence
//==================================================================================================
namespace tts
{
  struct color
  {
    color(char const* cc) : code_(cc), text_(nullptr) {}
    color const& operator()(char const* t)  const noexcept { text_ = t; return *this; }
    color const& operator()()  const noexcept { text_ = nullptr; return *this; }

    char const* code()  const noexcept { return code_; }
    char const* reset() const noexcept { return "\033[0m"; }
    char const* text()  const noexcept { return text_; }

    static bool status;

    private:
            char const *code_;
    mutable char const *text_;
  };

  inline bool color::status = true;

  inline std::ostream & operator<<(std::ostream &stream, color const& c)
  {
    if(color::status) stream << c.code();
    if(c.text())      stream << c.text() << c.reset();

    return stream;
  }

  inline const auto reset   = color("\033[0m");
  inline const auto bold    = color("\033[1m");
  inline const auto red     = color("\033[31m");
  inline const auto green   = color("\033[32m");
  inline const auto yellow  = color("\033[33m");
  inline const auto blue    = color("\033[34m");
  inline const auto magenta = color("\033[35m");
  inline const auto cyan    = color("\033[36m");
  inline const auto white   = color("\033[37m");

  //==================================================================================================
  // Options on the command line
  //==================================================================================================
  inline int usage(const char* name)
  {
    std::cout << "TTS Unit Tests Driver\n";
    std::cout << "Usage:\n";
    std::cout << name << " [OPTION...]\n";
    std::cout << "\nFlags:\n";
    std::cout << "  -h, --help        Display this help message\n";
    std::cout << "  -n, --no-color    Disable colored output\n";
    std::cout << "  -p, --pass        Report passing tests\n";
    std::cout << "  -x, --hex         Print the floating results in hexfloat mode\n";
    std::cout << "\nParameters:\n";
    std::cout << "  -f, --filter=str  Only run tests with `str` in their description\n";
    std::cout << "  -r, --repeat=arg  Repeat each tests arg times\n";
    std::cout << "  -l, --loop=arg    Repeat each range checks arg times\n";
    std::cout << "  -b, --block=arg   Set size of range checks samples (min. 32)\n";
    std::cout << "  -u, --ulpmax=arg  Set global failure ulp threshold for range tests (default is 2.0)\n";
    std::cout << "  -v, --valmin=arg  Set minimal value for range tests (default is code)\n";
    std::cout << "  -w, --valmax=arg  Set maximal value for range tests (default is code)\n";
    std::cout << "  -s, --seed=arg    Set the PRNG seeds (default is time-based)\n";
    std::cout << std::endl;

    return 0;
  }

  struct option
  {
    option() = default;
    option( std::string const& arg )
    {
      auto pos = arg.rfind( '=' );

      if(pos == std::string::npos)
      {
        flag  = arg.data();
        value = "";
      }
      else
      {
        flag  = arg.substr(0, pos);
        value = arg.substr(pos+1);
      }
    }

    bool is_valid() const { return !flag.empty(); }

    template<typename T> T get(T const& def = T{}) const
    {
      T that;

      if(is_valid())
      {
        std::istringstream os(value);
        if(os >> that) return that;
        else           return def;
      }
      else
      {
        return def;
      }
    }

    std::string flag;
    std::string value;
  };

  struct options
  {
    template<typename... Flags> option find(Flags const&... flags ) const
    {
      for(int i=1;i<argc;++i)
      {
        option o(argv[i]);
        if( ((o.flag == flags) || ... ) ) return o;
      }

      return option{};
    }

    template<typename... Flags> bool is_set(Flags const&... flags ) const
    {
      auto o = find(flags...);
      return o.is_valid();
    }

    template<typename T, typename... Flags> T value(Flags const&... flags ) const
    {
      T that;

      if( auto o = find(flags...); o.is_valid())
        that = o.template get<T>();

      return that;
    }

    template<typename T, typename... Flags>
    T value_or(T const& def,  Flags const&... flags ) const
    {
      T that(def);

      if( auto o = find(flags...); o.is_valid())
        that = o.template get<T>(def);

      return that;
    }

    int argc;
    char const** argv;
  };
}

//==================================================================================================
// Test environment
//==================================================================================================
namespace tts::detail
{
  struct env
  {
    void pass()     { test_count++; success_count++; }
    void fail()     { test_count++; failure_count++; }
    void invalid()  { test_count++; invalid_count++; }

    int report(std::ptrdiff_t fails, std::ptrdiff_t invalids) const
    {
      auto test_txt = test_count    > 1 ? "tests" : "test";
      auto pass_txt = success_count > 1 ? "successes" : "success";
      auto fail_txt = failure_count > 1 ? "failures" : "failure";
      auto inv_txt  = invalid_count > 1 ? "invalids" : "invalid";

      std::cout << reset << std::string(80, '-') << "\n";
      std::cout << "Results: "  << test_count     << " "  << test_txt
                << " - "        << success_count  << " "  << green(pass_txt)
                << " - "        << failure_count  << "/"  << fails    << " " << red(fail_txt)
                << " - "        << invalid_count  << "/"  << invalids << " " << magenta(inv_txt)
                << std::endl;

      if(!fails && !invalids)
        return test_count == success_count ? 0 : 1;
      else
        return (failure_count == fails && invalid_count == invalids) ? 0 : 1;
    }

    int test_count    = 0,
        success_count = 0,
        failure_count = 0,
        invalid_count = 0;
  };
}

//==================================================================================================
// Test case wrapper class
//==================================================================================================
namespace tts::detail
{
  struct test
  {
    using behavior_t = std::function<void()>;

    void operator()()  { behaviour(); }

    static inline bool acknowledge(test&& f);

    std::string name;
    behavior_t  behaviour;
  };

  // Global tests suite
  inline std::vector<test> suite = {};

  bool inline test::acknowledge(test&& f)
  {
    suite.emplace_back( std::forward<test>(f));
    return true;
  }
}

//==================================================================================================
// Test application entry-point customization
//==================================================================================================
#if !defined(TTS_CUSTOM_DRIVER_FUNCTION)
#  define TTS_CUSTOM_DRIVER_FUNCTION main
namespace tts::detail
{
  constexpr bool use_main = true;
}
#else
namespace tts::detail
{
  constexpr bool use_main = false;
}
#endif

namespace tts
{
  inline ::tts::detail::env global_runtime;
  inline bool               verbose_status;
  inline ::tts::options     arguments;

  inline int report(std::ptrdiff_t fails, std::ptrdiff_t invalids)
  {
    return global_runtime.report(fails,invalids);
  }
}

#if defined(TTS_MAIN)
int TTS_CUSTOM_DRIVER_FUNCTION([[maybe_unused]] int argc,[[maybe_unused]] char const** argv)
{
  ::tts::arguments = ::tts::options{argc,argv};

  if( ::tts::arguments.is_set("-h","--help") )
    return ::tts::usage(argv[0]);

  ::tts::verbose_status   =  ::tts::arguments.is_set("-p","--pass");
  ::tts::color::status    = !::tts::arguments.is_set("-n","--no-color");
  std::size_t repetitions =  ::tts::arguments.value_or<int>(1, "-r","--repeat");
  std::string filter      =  ::tts::arguments.value_or<std::string>("", "-f","--filter");

  for(auto &t: ::tts::detail::suite)
  {
    if(filter.empty() || (t.name.find(filter) != std::string::npos) )
    {
      auto count = ::tts::global_runtime.test_count;

      std::cout << ::tts::yellow("[SCENARIO]") << " - " << t.name << std::endl;
      for(std::size_t i = 0; i < repetitions; ++i) t();

      if(count == ::tts::global_runtime.test_count)
        ::tts::global_runtime.invalid();
    }
  }

  if constexpr( ::tts::detail::use_main ) return ::tts::report(0,0);
  else                                    return 0;
}
#endif

//==================================================================================================
// Wrapper for source location
//==================================================================================================
namespace tts
{
  struct location
  {
    char const* file;
    int line;

    std::string_view filename() const
    {
      std::string_view f(file);
      return f.substr(f.find_last_of('/')+1);
    }

    friend std::ostream& operator<<(std::ostream& os, location const& l)
    {
      os  << ::tts::blue << l.filename() << ::tts::reset
          << ":"
          << ::tts::blue << l.line << tts::reset;
      return os;
    }
  };
}

//==================================================================================================
// Wrappers for comparisons with external setup
//==================================================================================================
namespace tts::detail
{
  template<typename L, typename R>
  concept comparable_equal = requires(L l, R r) { compare_equal(l,r); };

  template<typename L, typename R>
  concept comparable_less = requires(L l, R r) { compare_less(l,r); };

  template<typename L, typename R> inline bool eq(L const &l, R const &r)
  {
    if constexpr( comparable_equal<L,R> ) return compare_equal(l,r);
    else                                            return l == r;
  }

  template<typename L, typename R> inline bool lt(L const &l, R const &r)
  {
    if constexpr( comparable_less<L,R> )  return compare_less(l,r);
    else                                            return l < r;
  }
}

//==================================================================================================
// TNumerical precision tests
//==================================================================================================
namespace tts
{
  template<typename T, typename U> inline double absolute_distance(T const &a, U const &b)
  {
    if constexpr(std::is_same_v<T, U>)
    {
      if constexpr(std::is_same_v<T, bool>) // Boolean case
      {
        return a == b ? 0. : 1.;
      }
      else if constexpr(std::is_floating_point_v<T>) // IEEE cases
      {
        if((a == b) || (std::isnan(a) && std::isnan(b))) return 0.;

        if(std::isinf(a) || std::isinf(b) || std::isnan(a) || std::isnan(b))
          return std::numeric_limits<double>::infinity();

        return std::abs(a - b);
      }
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>) // Natural case
      {
        auto d0 = static_cast<double>(a), d1 = static_cast<double>(b);
        return absolute_distance(d0, d1);
      }
    }
    else
    {
      using common_t = std::common_type_t<T, U>;
      return absolute_distance(static_cast<common_t>(a), static_cast<common_t>(b));
    }
  }

  template<typename T, typename U> inline double relative_distance(T const &a, U const &b)
  {
    if constexpr(std::is_same_v<T, U>)
    {
      if constexpr(std::is_same_v<T, bool>) // Boolean case
      { return a == b ? 0. : 100.; }
      else if constexpr(std::is_floating_point_v<T>) // IEEE cases
      {
        if((a == b) || (std::isnan(a) && std::isnan(b))) return 0.;

        if(std::isinf(a) || std::isinf(b) || std::isnan(a) || std::isnan(b))
          return std::numeric_limits<double>::infinity();

        return 100. * (std::abs(a - b) / std::max(T(1), std::max(std::abs(a), std::abs(b))));
      }
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>) // Natural case
      {
        auto d0 = static_cast<double>(a), d1 = static_cast<double>(b);
        return relative_distance(d0, d1);
      }
    }
    else
    {
      using common_t = std::common_type_t<T, U>;
      return relative_distance(static_cast<common_t>(a), static_cast<common_t>(b));
    }
  }

  template<typename T, typename U> inline double ulp_distance(T const &a, U const &b)
  {
    if constexpr(std::is_same_v<T, U>)
    {
      if constexpr(std::is_same_v<T, bool>) // Boolean case
      {
        return a == b ? 0. : std::numeric_limits<double>::infinity();
      }
      else if constexpr(std::is_floating_point_v<T>) // IEEE cases
      {
        using ui_t = std::conditional_t<std::is_same_v<T, float>, std::uint32_t, std::uint64_t>;

        if((a == b) || (std::isnan(a) && std::isnan(b)))
        {
          return 0.;
        }
        else if (std::isunordered(a, b))
        {
          return std::numeric_limits<double>::infinity();
        }
        else
        {
          auto aa = detail::bitinteger(a);
          auto bb = detail::bitinteger(b);

          if(aa > bb) std::swap(aa, bb);

          auto z = static_cast<ui_t>(bb-aa);

          if( std::signbit(a) ^ std::signbit(b) ) ++z;
          return z/2.;
        }
      }
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>) // Natural case
      {
        using u_t = typename std::make_unsigned<T>::type;

        // TODO: Fix overflow in case of very huge integral value
        return ((a < b) ? u_t(b - a) : u_t(a - b))/2.;
      }
    }
    else
    {
      using common_t = std::common_type_t<T, U>;
      return ulp_distance(static_cast<common_t>(a), static_cast<common_t>(b));
    }
  }
}

//==================================================================================================
// Expression decomposition
// This code is a direct adaptation of the similar technique used by Martin Moene in LEST
//==================================================================================================
namespace tts
{
  // Represent a test result and its displayable representation
  struct result
  {
    bool        status;
    std::string lhs,op,rhs;
    explicit operator bool() { return status; }
  };

  // Carry value around up to display point inside test macro
  template<typename Expression> struct lhs_expr
  {
    Expression lhs;
    lhs_expr(Expression x) : lhs(x) {}
    lhs_expr(lhs_expr const &)            = delete;
    lhs_expr &operator=(lhs_expr const &) = delete;

    operator result() { return result {bool(lhs),as_string(bool(lhs)),"",""}; }

    template<typename R> result operator ==(R const &rhs)
    {
      return { detail::eq(lhs, rhs), as_string(lhs), "==", as_string(rhs) };
    }

    template<typename R> result operator !=(R const &rhs)
    {
      return { !detail::eq(lhs, rhs), as_string(lhs), "!=", as_string(rhs) };
    }

    template<typename R> result operator <(R const &rhs)
    {
      return { detail::lt(lhs, rhs), as_string(lhs), "<", as_string(rhs) };
    }

    template<typename R> result operator <=(R const &rhs)
    {
      return { detail::lt(lhs, rhs) || detail::eq(lhs, rhs), as_string(lhs), "<=", as_string(rhs) };
    }

    template<typename R> result operator >(R const &rhs)
    {
      return { !detail::lt(lhs, rhs) && !detail::eq(lhs, rhs), as_string(lhs), ">", as_string(rhs) };
    }

    template<typename R> result operator >=(R const &rhs)
    {
      return { !detail::lt(lhs, rhs), as_string(lhs), ">=", as_string(rhs) };
    }
  };

  // Trampoline type for custom display of value injected from a macro.
  struct decomposer
  {
    template<typename Expression> lhs_expr<Expression const &> operator->*(Expression const &expr)
    {
      return {expr};
    }
  };
}

#define TTS_DECOMPOSE(XPR) (::tts::decomposer{}->*XPR)

//==================================================================================================
// Tests macros - Basic information
//==================================================================================================
#define TTS_PASS(Message)                                                                           \
  do                                                                                                \
  {                                                                                                 \
    ::tts::global_runtime.pass();                                                                   \
    if(::tts::verbose_status) std::cout << ::tts::location{__FILE__,__LINE__} << " - "              \
                          << ::tts::bold << ::tts::green("PASSED") << ::tts::reset                  \
                          << " - " << Message << std::endl;                                         \
                                                                                                    \
  } while(::tts::detail::done())
/**/

#define TTS_FAIL(Message)                                                                           \
  do                                                                                                \
  {                                                                                                 \
    ::tts::global_runtime.fail();                                                                   \
    std::cout << ::tts::location{__FILE__,__LINE__} << " - "                                        \
              << ::tts::bold << ::tts::red("**FAILED**") << ::tts::reset                            \
              << " - " << Message << std::endl;                                                     \
                                                                                                    \
  } while(::tts::detail::done())
/**/

#define TTS_INVALID(Message)                                                                        \
  do                                                                                                \
  {                                                                                                 \
    ::tts::global_runtime.invalid();                                                                \
    std::cout << ::tts::location{__FILE__,__LINE__} << " - "                                        \
              << ::tts::bold << ::tts::magenta("!!INVALID!!") << ::tts::reset                       \
              << " - " << Message << std::endl;                                                     \
                                                                                                    \
  } while(::tts::detail::done())
/**/

//==================================================================================================
// Test macros - Basic expectation
//==================================================================================================
#define TTS_EXPECT_IMPL(EXPR)                                                                       \
  do                                                                                                \
  {                                                                                                 \
    ::tts::result tts_var_d = TTS_DECOMPOSE(EXPR);                                                  \
    if(tts_var_d)                                                                                   \
    {                                                                                               \
      TTS_PASS("Expecting: "  << ::tts::green(TTS_STRING(EXPR)) );                                  \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      TTS_FAIL( "Expecting: " << ::tts::green(TTS_STRING(EXPR)) << " but " << ::tts::red()          \
                              << tts_var_d.lhs << " " << tts_var_d.op << " " << tts_var_d.rhs       \
                              << ::tts::reset() << " occured instead.");                            \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_EXPECT_NOT_IMPL(EXPR)                                                                   \
  do                                                                                                \
  {                                                                                                 \
    ::tts::result tts_var_d = TTS_DECOMPOSE(EXPR);                                                  \
    if(tts_var_d)                                                                                   \
    {                                                                                               \
      TTS_FAIL( "Not Expecting: " << ::tts::green(TTS_STRING(EXPR)) << " but " << ::tts::red()      \
                                  << tts_var_d.lhs << " " << tts_var_d.op << " " << tts_var_d.rhs   \
                                  << ::tts::reset() << " occured instead.");                        \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      TTS_PASS("Not Expecting: "  << ::tts::green(TTS_STRING(EXPR)) );                              \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_EXPECT(EXPR)      TTS_EXPECT_IMPL((EXPR))
#define TTS_EXPECT_NOT(EXPR)  TTS_EXPECT_NOT_IMPL((EXPR))

//==================================================================================================
// Test macros - Constexpr expectation
//==================================================================================================
#define TTS_CONSTEXPR_EXPECT(EXPR)      TTS_EXPECT_IMPL( std::bool_constant<EXPR>::value )
#define TTS_CONSTEXPR_EXPECT_NOT(EXPR)  TTS_EXPECT_NOT_IMPL( std::bool_constant<EXPR>::value )

//==================================================================================================
// Test macros - Relationship
//==================================================================================================
#define TTS_EQUAL(LHS, RHS)         TTS_EXPECT_IMPL(LHS == RHS)
#define TTS_NOT_EQUAL(LHS, RHS)     TTS_EXPECT_IMPL(LHS != RHS)
#define TTS_LESS(LHS, RHS)          TTS_EXPECT_IMPL(LHS  < RHS)
#define TTS_GREATER(LHS, RHS)       TTS_EXPECT_IMPL(LHS  > RHS)
#define TTS_LESS_EQUAL(LHS, RHS)    TTS_EXPECT_IMPL(LHS <= RHS)
#define TTS_GREATER_EQUAL(LHS, RHS) TTS_EXPECT_IMPL(LHS >= RHS)

//==================================================================================================
// Test macros - Constexpr Relationship
//==================================================================================================
#define TTS_CONSTEXPR_EQUAL(LHS, RHS)         TTS_CONSTEXPR_EXPECT((LHS == RHS))
#define TTS_CONSTEXPR_NOT_EQUAL(LHS, RHS)     TTS_CONSTEXPR_EXPECT((LHS != RHS))
#define TTS_CONSTEXPR_LESS(LHS, RHS)          TTS_CONSTEXPR_EXPECT((LHS  < RHS))
#define TTS_CONSTEXPR_GREATER(LHS, RHS)       TTS_CONSTEXPR_EXPECT((LHS  > RHS))
#define TTS_CONSTEXPR_LESS_EQUAL(LHS, RHS)    TTS_CONSTEXPR_EXPECT((LHS <= RHS))
#define TTS_CONSTEXPR_GREATER_EQUAL(LHS, RHS) TTS_CONSTEXPR_EXPECT((LHS >= RHS))

//==================================================================================================
// Test macros - Type checking
//==================================================================================================
#define TTS_TYPE_IS(T, TYPE)                                                                        \
  do                                                                                                \
  {                                                                                                 \
    constexpr auto check = std::is_same_v<TTS_REMOVE_PARENS(TYPE), TTS_REMOVE_PARENS(T)>;           \
    if constexpr(check)                                                                             \
    {                                                                                               \
      TTS_PASS("Expecting " << ::tts::green(TTS_STRING(TTS_REMOVE_PARENS(T))) << " to be "          \
                            << ::tts::green() << tts::typename_<TTS_REMOVE_PARENS(TYPE)>            \
                            << ::tts::reset                                                         \
              );                                                                                    \
    }                                                                                               \
                                                                                                    \
    if constexpr(!check)                                                                            \
    {                                                                                               \
      TTS_FAIL("Expecting " << ::tts::green(TTS_STRING(TTS_REMOVE_PARENS(T))) << " to be "          \
                            << ::tts::green() << tts::typename_<TTS_REMOVE_PARENS(TYPE)>            \
                            << ::tts::reset << " but found "                                        \
                            << ::tts::red() << tts::typename_<TTS_REMOVE_PARENS(T)>                 \
                            << ::tts::reset << " instead"                                           \
              );                                                                                    \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_EXPR_IS(EXPRESSION, TYPE)  TTS_TYPE_IS(decltype(TTS_REMOVE_PARENS(EXPRESSION)), TYPE)

//==================================================================================================
// Test macros - Exception
//==================================================================================================
#define TTS_THROW(EXPR, EXCEPTION)                                                                  \
  do                                                                                                \
  {                                                                                                 \
    bool tts_caught = false;                                                                        \
                                                                                                    \
    try                 { EXPR; }                                                                   \
    catch(EXCEPTION&  ) { tts_caught = true; }                                                      \
    catch(...)          { }                                                                         \
                                                                                                    \
    if(tts_caught)                                                                                  \
    {                                                                                               \
      TTS_PASS(   ::tts::green(TTS_STRING(EXPR)) << " throws "                                      \
              <<  ::tts::green(TTS_STRING(EXCEPTION))                                               \
              );                                                                                    \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      TTS_FAIL(   ::tts::green(TTS_STRING(EXPR)) << " does not throw "                              \
              <<  ::tts::red(TTS_STRING(EXCEPTION))                                                 \
              );                                                                                    \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_NO_THROW(EXPR)                                                                          \
  do                                                                                                \
  {                                                                                                 \
    bool tts_caught = false;                                                                        \
                                                                                                    \
    try        { EXPR; }                                                                            \
    catch(...) { tts_caught = true; }                                                               \
                                                                                                    \
    if(!tts_caught) { TTS_PASS(::tts::green(TTS_STRING(EXPR)) << " does not throw"); }              \
    else            { TTS_FAIL(::tts::green(TTS_STRING(EXPR)) << " throws ");        }              \
  } while(::tts::detail::done())
/**/

//==================================================================================================
// Test macros - Precision checking base macros
//==================================================================================================
#define TTS_PRECISION_EQUAL(LHS, RHS, N, UNIT, FUNC)                                                \
  do                                                                                                \
  {                                                                                                 \
    auto eval_a = (LHS);                                                                            \
    auto eval_b = (RHS);                                                                            \
    auto r      = FUNC(eval_a,eval_b);                                                              \
    auto tts_fmt_n = (N<1000 ? std::defaultfloat : std::scientific);                                \
    auto tts_fmt_r = (r<1000 ? std::defaultfloat : std::scientific);                                \
                                                                                                    \
    if(r <= N)                                                                                      \
    {                                                                                               \
      TTS_PASS( "Expecting: "                                                                       \
                << ::tts::green() << ::tts::as_string(eval_a)                                       \
                << " == "         << ::tts::as_string(eval_b) << ::tts::reset()                     \
                << " within " << std::setprecision(2) << tts_fmt_n                                  \
                              << ::tts::green() << N << ::tts::reset << " " << UNIT                 \
                << " and found: " << std::setprecision(2)  << tts_fmt_r                             \
                              << ::tts::green() << r << ::tts::reset << " " << UNIT                 \
              );                                                                                    \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      TTS_FAIL( "Expecting: "                                                                       \
                << ::tts::green() << ::tts::as_string(eval_a)                                       \
                << " == "         << ::tts::as_string(eval_b) << ::tts::reset()                     \
                << " within " << std::setprecision(2) << tts_fmt_n                                  \
                              << ::tts::green() << N << ::tts::reset << " " << UNIT                 \
                << " but found: " << std::setprecision(2)  << tts_fmt_r                             \
                              << ::tts::red() << r << ::tts::reset << " " << UNIT << " instead"     \
              );                                                                                    \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_ABSOLUTE_EQUAL(L, R, N) TTS_PRECISION_EQUAL(L, R, N, " unit", ::tts::absolute_distance)
#define TTS_RELATIVE_EQUAL(L, R, N) TTS_PRECISION_EQUAL(L, R, N, "%"    , ::tts::relative_distance)
#define TTS_ULP_EQUAL(L, R, N)      TTS_PRECISION_EQUAL(L, R, N, "ULP"  , ::tts::ulp_distance)
#define TTS_IEEE_EQUAL(L,R)         TTS_ULP_EQUAL(L, R, 0.)

//==================================================================================================
// Test macros - Sequence tests
//==================================================================================================
#define TTS_SEQUENCE_EQUAL(L,R,N,UNIT,FUNC)                                                         \
  do                                                                                                \
  {                                                                                                 \
    if( std::size(L) == std::size(R) )                                                              \
    {                                                                                               \
      auto found = tts::detail::mismatch( std::begin(L), std::end(L), std::begin(R)                 \
                                        , [](auto l, auto r) { return FUNC(l,r) <= N; }             \
                                        );                                                          \
      auto distance = std::end(L)-found.first;                                                      \
      if( distance == 0)                                                                            \
      {                                                                                             \
        TTS_PASS( "Expecting: " << ::tts::green()                                                   \
                << TTS_STRING(L) << " == " << TTS_STRING(R) << ::tts::reset()                       \
                << " within " << ::tts::green() << N << ::tts::reset() << " " << UNIT               \
                );                                                                                  \
      }                                                                                             \
      else                                                                                          \
      {                                                                                             \
        TTS_FAIL(  "Expecting: " << ::tts::green() << TTS_STRING(L) << " == " << TTS_STRING(R)      \
                << ::tts::reset()                                                                   \
                << " but value at index " << ::tts::yellow() << distance    << ::tts::reset()       \
                << " is " << ::tts::red() << ::tts::as_string(*found.first) << ::tts::reset()       \
                << " instead of "                                                                   \
                << ::tts::red() << ::tts::as_string(*found.second)<< ::tts::reset()                 \
                << " within " << ::tts::red() << FUNC(*found.first,*found.second)                   \
                << " " << UNIT << " instead of " << N                                               \
                );                                                                                  \
      }                                                                                             \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      TTS_FAIL(  "Expecting: " << TTS_STRING(L) << " == " << TTS_STRING(R)                          \
              << " but sizes mismatch between: " << ::tts::red() << std::size(L) << ::tts::reset()  \
              << " and "  << ::tts::red() << std::size(R) << ::tts::reset()                         \
              );                                                                                    \
    }                                                                                               \
  } while(::tts::detail::done())
/**/

#define TTS_ALL_RELATIVE_EQUAL(L, R, N) TTS_SEQUENCE_EQUAL(L,R,N,"%"   , ::tts::relative_distance )
#define TTS_ALL_ULP_EQUAL(L, R, N)      TTS_SEQUENCE_EQUAL(L,R,N,"ULP" , ::tts::ulp_distance      )
#define TTS_ALL_ABSOLUTE_EQUAL(L, R, N) TTS_SEQUENCE_EQUAL(L,R,N,"unit", ::tts::absolute_distance )
#define TTS_ALL_EQUAL(L,R)              TTS_ALL_ABSOLUTE_EQUAL(L,R,0)
#define TTS_ALL_IEEE_EQUAL(L,R)         TTS_ALL_ULP_EQUAL(L, R, 0.)

//==================================================================================================
// Test sub-case registrations
//==================================================================================================
namespace tts::detail
{
  // Setup/section environment guard
  struct section_guard
  {
    int &      id;
    int const &section;

    section_guard(int &id_, int const &section_, int &count) : id(id_) , section(section_)
    {
      if(section == 0) id = count++ - 1;
    }

    template<typename... Desc> bool check(Desc const&... desc)
    {
      if(id == section)
      {
        ((std::cout << desc),...);
        std::cout << std::endl;
      }

      return id == section;
    }
  };

  struct only_once
  {
    bool once = true;
    explicit operator bool() { bool result = once; once = false; return result; }
  };
}

#define TTS_WHEN(STORY)                                                                             \
  std::cout << "When      : " << ::tts::yellow(STORY) << std::endl;                                 \
  for(int tts_section = 0, tts_count = 1; tts_section < tts_count; tts_count -= 0==tts_section++)   \
    for( tts::detail::only_once tts_only_once_setup{}; tts_only_once_setup; )                       \
/**/

#define TTS_AND_THEN_IMPL(DESCRIPTION,TTS_LOCAL_ID)                                                 \
  static int TTS_LOCAL_ID = 0;                                                                      \
  if(::tts::detail::section_guard(TTS_LOCAL_ID, tts_section, tts_count )                            \
                  .check("  And then: ", DESCRIPTION)                                               \
    )                                                                                               \
  for(int tts_section = 0, tts_count = 1; tts_section < tts_count; tts_count -= 0==tts_section++ )  \
    for(tts::detail::only_once tts__only_once_section{}; tts__only_once_section; )                  \
/**/

#define TTS_AND_THEN(DESCRIPTION) TTS_AND_THEN_IMPL(DESCRIPTION, TTS_UNIQUE(id))

//==================================================================================================
// Test case registration macros
//==================================================================================================
#define TTS_CASE_IMPL(DESCRIPTION, FUNC)                                                            \
  static void FUNC();                                                                               \
  namespace                                                                                         \
  {                                                                                                 \
    inline bool TTS_CAT(register_,FUNC) =                                                           \
        ::tts::detail::test::acknowledge(::tts::detail::test{DESCRIPTION, FUNC});                   \
  }                                                                                                 \
  static void FUNC()                                                                                \
/**/

#define TTS_CASE(DESCRIPTION) TTS_CASE_IMPL(DESCRIPTION,TTS_FUNCTION)

#define TTS_CASE_TPL_IMPL(DESCRIPTION, FUNC, ...)                                                   \
  template<typename T> static void FUNC();                                                          \
  namespace                                                                                         \
  {                                                                                                 \
    inline bool TTS_CAT(register_,FUNC) =                                                           \
      ::tts::detail::for_each_type                                                                  \
      (                                                                                             \
        [](auto t) {                                                                                \
        ::tts::detail::test::acknowledge(::tts::detail::test{                                       \
            std::string{DESCRIPTION}                                                                \
            + " (with T = " + std::string{::tts::typename_<typename decltype(t)::type>} + ")"       \
          , []() { FUNC<typename decltype(t)::type>(); }                                            \
          }                                                                                         \
        );                                                                                          \
        },::tts::detail::typelist<__VA_ARGS__> {});                                                 \
  }                                                                                                 \
  template<typename T> static void FUNC()                                                           \
/**/

#define TTS_CASE_TPL(DESCRIPTION, ...)  TTS_CASE_TPL_IMPL(DESCRIPTION,TTS_FUNCTION,__VA_ARGS__)
