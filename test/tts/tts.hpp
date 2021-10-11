//==================================================================================================
/**
  TTS - Tiny Test System
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif
#if defined(_WIN32) || defined(_WIN64)
#define TTS_COLOR_WINDOWS
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#endif
#if defined(TTS_COLOR_WINDOWS)
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <cstdio>
#include <iostream>
namespace tts::detail
{
  inline bool color_status = true;
  inline std::ostream & modifiy_stream(std::ostream &stream, int foreground)
  {
    if(color_status)
    {
#if defined(TTS_COLOR_WINDOWS)
      static WORD defaultAttributes = 0;
      HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)  hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
      else  if (&stream == &std::cerr)  hTerminal = GetStdHandle(STD_ERROR_HANDLE);
      if (!defaultAttributes)
      {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(hTerminal, &info)) return stream;
        defaultAttributes = info.wAttributes;
      }
      if (foreground > 7) return stream;
      if (foreground == -1)
      {
        SetConsoleTextAttribute(hTerminal, defaultAttributes);
        return stream;
      }
      CONSOLE_SCREEN_BUFFER_INFO info;
      if (!GetConsoleScreenBufferInfo(hTerminal, &info)) return stream;
      info.wAttributes &= ~(info.wAttributes & 0x0F);
      info.wAttributes |= static_cast<WORD>(FOREGROUND_INTENSITY | foreground);
      SetConsoleTextAttribute(hTerminal, info.wAttributes);
      return stream;
#else
    static char const* modifier[] =
    {
      "\033[00m",
      "\033[30m",
      "\033[34m",
      "\033[32m",
      "\033[36m",
      "\033[31m",
      "\033[35m",
      "\033[33m",
      "\033[37m",
      "\033[1m" ,
    };
    return stream << modifier[foreground+1];
#endif
    }
    else
    {
      return stream;
    }
  }
}
#undef TTS_COLOR_WINDOWS
namespace tts
{
  inline std::ostream& reset  (std::ostream &stream) { return detail::modifiy_stream(stream, -1); }
  inline std::ostream& grey   (std::ostream &stream) { return detail::modifiy_stream(stream,  0); }
  inline std::ostream& blue   (std::ostream &stream) { return detail::modifiy_stream(stream,  1); }
  inline std::ostream& green  (std::ostream &stream) { return detail::modifiy_stream(stream,  2); }
  inline std::ostream& cyan   (std::ostream &stream) { return detail::modifiy_stream(stream,  3); }
  inline std::ostream& red    (std::ostream &stream) { return detail::modifiy_stream(stream,  4); }
  inline std::ostream& magenta(std::ostream &stream) { return detail::modifiy_stream(stream,  5); }
  inline std::ostream& yellow (std::ostream &stream) { return detail::modifiy_stream(stream,  6); }
  inline std::ostream& white  (std::ostream &stream) { return detail::modifiy_stream(stream,  7); }
  inline std::ostream& bold   (std::ostream &stream) { return detail::modifiy_stream(stream,  8); }
}
#include <iostream>
namespace tts
{
  inline int usage(const char* name)
  {
    std::cout << bold << cyan << "TTS Unit Tests Driver\n" << reset;
    std::cout << bold << white << "Usage: " << name << grey << " [OPTION...]\n" << reset;
    std::cout << bold << yellow << "\nFlags:\n" << reset;
    std::cout << green << "  -h, --help        " << reset
              << bold << white << "Display this help message\n" << reset;
    std::cout << green << "  -n, --no-color    " << reset
              << bold << white << "Disable colored output\n" << reset;
    std::cout << green << "  -p, --pass        " << reset
              << bold << white << "Report passing tests\n" << reset;
    std::cout << green << "  -x, --hex         " << reset
              << bold << white << "Print the floating results in hexfloat mode\n" << reset;
    std::cout << green << "  -s, --scientific  " << reset
              << bold << white << "Print the floating results in scientific mode\n" << reset;
    std::cout << bold << yellow << "\nParameters:\n" << reset;
    std::cout << green << "  --filter=str      " << reset
              << bold << white << "Only run tests with `str` in their description\n" << reset;
    std::cout << green << "  --precision=arg   " << reset
              << bold << white << "Set the precision for displaying floating pint values\n" << reset;
    std::cout << green << "  --repeat=arg      " << reset
              << bold << white << "Repeat each tests arg times\n" << reset;
    std::cout << green << "  --seed=arg        " << reset
              << bold << white << "Set the PRNG seeds (default is time-based)\n";
    std::cout << bold << yellow << "\nRange specifics Parameters:\n" << reset;
    std::cout << green << "  --block=arg       " << reset
              << bold << white << "Set size of range checks samples (min. 32)\n" << reset;
    std::cout << green << "  --loop=arg        " << reset
              << bold << white << "Repeat each range checks arg times\n" << reset;
    std::cout << green << "  --ulpmax=arg      " << reset
              << bold << white << "Set global failure ulp threshold for range tests (default is 2.0)\n" << reset;
    std::cout << green << "  --valmax=arg      " << reset
              << bold << white << "Set maximal value for range tests (default is code)\n" << reset;
    std::cout << green << "  --valmin=arg      " << reset
              << bold << white << "Set minimal value for range tests (default is code)\n" << reset;
    std::cout << std::endl;
    return 0;
  }
}
#include <utility>
namespace tts
{
  template <typename> struct callable;
  template <typename Return, typename... Params>
  struct callable<Return(Params...)>
  {
  public:
    using signature_t = Return(*)(void*, Params...);
    using deleter_t   = void(*)(void*);
    signature_t invoker = {};
    deleter_t   cleanup = {};
    void*       payload = {};
    constexpr callable() = default;
    template<typename Function>
    constexpr callable(Function f)
            : invoker{invoke<Function>}, cleanup{destroy<Function>}
            , payload{new Function{std::move(f)}}
    {}
    constexpr callable(callable&& other) noexcept
            : invoker{std::move(other.invoker)}, cleanup{std::move(other.cleanup)}
            , payload{std::move(other.payload)}
    {
      other.payload = {};
    }
    ~callable() { cleanup(payload); }
    constexpr callable(const callable&)             = delete;
    constexpr callable& operator=(const callable&)  = delete;
    constexpr callable& operator=(callable&&)       = delete;
    constexpr Return operator()(Params... args)       { return invoker(payload, args...); }
    constexpr Return operator()(Params... args) const { return invoker(payload, args...); }
    private:
    template <typename T>
    static Return invoke(void* data, Params... args) { return (*static_cast<T*>(data))(args...); }
    template <typename T>
    static void destroy(void* data) { delete static_cast<T*>(data); }
  };
}
#include <string>
#include <vector>
namespace tts::detail
{
  struct test
  {
    using behavior_t = tts::callable<void()>;
    void operator()()  { behaviour(); }
    static inline bool acknowledge(test&& f);
    std::string name;
    behavior_t  behaviour;
  };
  inline std::vector<test> suite = {};
  bool inline test::acknowledge(test&& f)
  {
    suite.emplace_back( std::forward<test>(f));
    return true;
  }
}
#include <cstddef>
#include <iostream>
namespace tts::detail
{
  struct env
  {
    void pass()     { test_count++; success_count++; }
    void fail()     { test_count++; failure_count++; }
    void fatal()    { test_count++; failure_count++; fatal_count++; }
    void invalid()  { test_count++; invalid_count++; }
    int report(std::ptrdiff_t fails, std::ptrdiff_t invalids) const
    {
      auto test_txt = test_count    > 1 ? "tests" : "test";
      auto pass_txt = success_count > 1 ? "successes" : "success";
      auto fail_txt = failure_count > 1 ? "failures" : "failure";
      auto inv_txt  = invalid_count > 1 ? "invalids" : "invalid";
      std::cout << reset << std::string(80, '-') << std::endl;
      std::cout << bold << "Results: "
                << test_count << " "  << test_txt
                << " - "      << success_count   << "/"   << test_count << " "
                << green      << pass_txt       << reset  << bold
                << " - "      << failure_count  << "/"    << fails << " "
                << red        << fail_txt       << reset  << bold
                << " - "      << invalid_count  << "/"    << invalids << " " << bold
                << magenta    << inv_txt        << reset
                << std::endl;
      if(!fails && !invalids) return test_count == success_count ? 0 : 1;
      else                    return (failure_count == fails && invalid_count == invalids) ? 0 : 1;
    }
    int test_count    = 0,
        success_count = 0,
        failure_count = 0,
        fatal_count   = 0,
        invalid_count = 0;
  };
}
namespace tts
{
  inline ::tts::detail::env global_runtime;
  inline int report(std::ptrdiff_t fails, std::ptrdiff_t invalids)
  {
    return global_runtime.report(fails,invalids);
  }
}
#include <initializer_list>
#include <sstream>
#include <string>
namespace tts
{
  struct option
  {
    option() = default;
    option( std::string arg ) : token(std::move(arg)), position(token.rfind( '=' )) {}
    auto flag()     const { return token.substr(0, position); }
    bool is_valid() const { return !flag().empty(); }
    template<typename T> T get(T const& def = T{}) const
    {
      T that;
      if(is_valid())
      {
        std::istringstream os(token.substr(position+1));
        if(os >> that) return that;
        else           return def;
      }
      else
      {
        return def;
      }
    }
    std::string token     = "";
    size_t      position  = std::string::npos;
  };
  struct options
  {
    using params_t = std::initializer_list<const char*>;
    option find(const char* f ) const { return find({f}); }
    option find(params_t    fs) const
    {
      for(int i=1;i<argc;++i)
      {
        option o(argv[i]);
        for(auto f : fs)
          if( o.flag() == f ) return o;
      }
      return option{};
    }
    bool operator[](params_t    fs) const { return find(fs).is_valid(); }
    bool operator[](const char* f ) const { return operator[]({f}); }
    template<typename T> T value(params_t fs, T that = {}) const
    {
      if( auto o = find(fs); o.is_valid()) that = o.template get<T>(that);
      return that;
    }
    template<typename T> T value(const char* f, T that = {}) const
    {
      return value({f},that);
    }
    int argc;
    char const** argv;
  };
  inline ::tts::options arguments;
  inline bool           verbose_status;
}
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
namespace tts::detail
{
  struct fatal_signal {};
}
#if defined(TTS_MAIN)
int TTS_CUSTOM_DRIVER_FUNCTION([[maybe_unused]] int argc,[[maybe_unused]] char const** argv)
{
  ::tts::arguments = ::tts::options{argc,argv};
  ::tts::detail::color_status = !::tts::arguments[{"-n","--no-color"}];
  if( ::tts::arguments[{"-h","--help"}] )
    return ::tts::usage(argv[0]);
  ::tts::verbose_status       =  ::tts::arguments[{"-p","--pass"}];
  std::size_t repetitions     =  ::tts::arguments.value( "--repeat", 1            );
  std::string filter          =  ::tts::arguments.value( "--filter", std::string{});
  try
  {
    for(auto &t: ::tts::detail::suite)
    {
      if(filter.empty() || (t.name.find(filter) != std::string::npos) )
      {
        auto count = ::tts::global_runtime.test_count;
        std::cout << ::tts::yellow << ::tts::bold
                  << "[SCENARIO]" << " - " << t.name
                  << ::tts::reset << std::endl;
        for(std::size_t i = 0; i < repetitions; ++i) t();
        if(count == ::tts::global_runtime.test_count)
          ::tts::global_runtime.invalid();
      }
    }
  }
  catch( ::tts::detail::fatal_signal& )
  {
    std::cout << "\n" << ::tts::red
              << ::tts::bold << "** ABORTING AFTER FIRST FAILURE **"
              << "\n";
  }
  if constexpr( ::tts::detail::use_main ) return ::tts::report(0,0);
  else                                    return 0;
}
#endif
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
#include <sstream>
namespace tts
{
  template<typename     T > struct type  {};
  template<typename...  Ts> struct types {};
}
namespace tts::detail
{
  template<typename TestBed> struct lambda_test
  {
    lambda_test(TestBed f) : base_test(f) {}
    auto operator+(auto TestBody) const
    {
      base_test( TestBody );
      return true;
    }
    TestBed base_test;
  };
}
#define TTS_CASE_TPL(DESCRIPTION,...)                                                               \
static bool const TTS_CAT(register_,TTS_FUNCTION) =  ::tts::detail::lambda_test{                    \
[](auto tests)                                                                                      \
  {                                                                                                 \
    auto const single_test = [=]<typename T>( ::tts::type<T> )                                      \
    {                                                                                               \
      ::tts::detail::test::acknowledge(::tts::detail::test                                          \
      {                                                                                             \
          std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"         \
        , [=]() {tests(::tts::type<T>{}); }                                                         \
        });                                                                                         \
    };                                                                                              \
                                                                                                    \
    [&]<template<class...> class L,typename... Ts>(L<Ts...>)                                        \
    {                                                                                               \
      (single_test( ::tts::type<Ts>() ),...);                                                       \
    }( ::tts::types<__VA_ARGS__>{} );                                                               \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                           \

#define TTS_CASE(...)                                                                               \
static bool const TTS_CAT(register_,TTS_FUNCTION) =  ::tts::detail::lambda_test{                    \
[](auto tests)                                                                                      \
  {                                                                                                 \
    std::ostringstream title;                                                                       \
    title << __VA_ARGS__;                                                                           \
    return ::tts::detail::test::acknowledge(::tts::detail::test{ title.str(), [=](){ tests(); } }); \
  }} + []()                                                                                         \

namespace tts::detail
{
  struct section_guard
  {
    int &      id;
    int const &section;
    section_guard(int &id_, int const &section_, int &count) : id(id_) , section(section_)
    {
      if(section == 0) id = count++ - 1;
    }
    template<typename Desc> bool check(Desc const& desc)
    {
      if(id == section) std::cout << "  And then: " << desc << std::endl;
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
  std::cout << "When      : " << ::tts::yellow << STORY << ::tts::reset << std::endl;               \
  for(int tts_section = 0, tts_count = 1; tts_section < tts_count; tts_count -= 0==tts_section++)   \
    for( tts::detail::only_once tts_only_once_setup{}; tts_only_once_setup; )                       \

#define TTS_AND_THEN_IMPL(TTS_LOCAL_ID, ...)                                                        \
  static int TTS_LOCAL_ID = 0;                                                                      \
  std::ostringstream TTS_CAT(desc_,TTS_LOCAL_ID);                                                   \
  if(::tts::detail::section_guard(TTS_LOCAL_ID, tts_section, tts_count )                            \
                  .check( ((TTS_CAT(desc_,TTS_LOCAL_ID)  << __VA_ARGS__)                            \
                          , TTS_CAT(desc_,TTS_LOCAL_ID).str())                                      \
                        )                                                                           \
    )                                                                                               \
  for(int tts_section = 0, tts_count = 1; tts_section < tts_count; tts_count -= 0==tts_section++ )  \
    for(tts::detail::only_once tts__only_once_section{}; tts__only_once_section; )                  \

#define TTS_AND_THEN(...) TTS_AND_THEN_IMPL(TTS_UNIQUE(id), __VA_ARGS__)
#include <cstdint>
#define TTS_SIGNED_INTEGRAL_TYPES   std::int8_t , std::int16_t , std::int32_t , std::int64_t
#define TTS_UNSIGNED_INTEGRAL_TYPES std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t
#define TTS_INTEGRAL_TYPES TTS_SIGNED_INTEGRAL_TYPES, TTS_UNSIGNED_INTEGRAL_TYPES
#define TTS_IEEE_TYPES              float, double
#define TTS_SIGNED_NUMERIC_TYPES    TTS_IEEE_TYPES, TTS_SIGNED_INTEGRAL_TYPES
#define TTS_UNSIGNED_NUMERIC_TYPES  TTS_UNSIGNED_INTEGRAL_TYPES
#define TTS_NUMERIC_TYPES           TTS_IEEE_TYPES, TTS_INTEGRAL_TYPES
#define TTS_ALL_TYPES               TTS_NUMERIC_TYPES, char, bool
#include <string_view>
#include <ostream>
#include <sstream>
namespace tts
{
  class source_location
  {
    public:
    [[nodiscard]] static constexpr auto current ( const char* file  = __builtin_FILE()
                                                , int line          = __builtin_LINE()
                                                ) noexcept
    {
      source_location sl{};
      sl.file_ = file;
      sl.line_ = line;
      return sl;
    }
    [[nodiscard]] constexpr auto filename() const noexcept
    {
      std::string_view f(file_);
      return f.substr(f.find_last_of('/')+1);
    }
    [[nodiscard]] constexpr auto line() const noexcept { return line_; }
    friend std::ostream& operator<<(std::ostream& os, source_location const& s)
    {
      return os << tts::bold << tts::blue << s.filename()
                << tts::white << "[" << tts::blue << s.line() << tts::white << "]"
                << tts::reset;
    }
    private:
    const char* file_{"unknown"};
    int         line_{};
  };
}
#define TTS_PASS(Message)                                                                           \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.pass();                                                                   \
    if(::tts::verbose_status)                                                                       \
      std::cout << ::tts::source_location::current() << " - " << ::tts::bold                        \
                << ::tts::green << "!!SUCCESS!!" << ::tts::reset                                    \
                << " - " << Message << std::endl;                                                   \
  }()
#define TTS_FAIL(Message)                                                                           \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.fail();                                                                   \
    std::cout << ::tts::source_location::current() << " - " << ::tts::bold                          \
              << ::tts::red << "**FAILURE**" << ::tts::reset                                        \
              << " - " << Message << std::endl;                                                     \
  }()
#define TTS_FATAL(Message)                                                                          \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.fatal();                                                                  \
    std::cout << ::tts::source_location::current() << " - " << ::tts::bold                          \
              << ::tts::red << "** FATAL **" << ::tts::reset                                        \
              << " - " << Message << std::endl;                                                     \
    throw ::tts::detail::fatal_signal();                                                            \
  }()
#define TTS_INVALID(Message)                                                                        \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.invalid();                                                                \
    std::cout << ::tts::source_location::current() << " - " << ::tts::bold                          \
              << ::tts::magenta << "@@INVALID@@" << ::tts::reset                                    \
              << " - " << Message << std::endl;                                                     \
  }()
#include <string>
#include <iomanip>
#include <sstream>
#include <type_traits>
#include <string_view>
namespace tts::detail
{
  template<typename T> struct typename_
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
}
namespace tts
{
  template<typename T> inline constexpr auto const typename_ = detail::typename_<T>::value();
  template<typename T> constexpr auto typename_of(T&&){ return typename_<T>; }
}
namespace tts
{
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
  template<typename T> std::string as_string(T const& e)
  {
    if constexpr( std::is_pointer_v<T> )
    {
      std::ostringstream os;
      os << std::string(typename_<T>) << "(" << e << ")";
      return os.str();
    }
    else if constexpr( std::floating_point<T> )
    {
      auto precision = ::tts::arguments.value({"--precision"}, 2);
      bool hexmode   = ::tts::arguments[{"-x","--hex"}];
      bool scimode   = ::tts::arguments[{"-s","--scientific"}];
      std::ostringstream os;
      os << std::setprecision(precision);
            if(hexmode) os << std::hexfloat << e << std::defaultfloat;
      else  if(scimode) os << std::scientific << e << std::defaultfloat;
      else              os << e;
      return os.str();
    }
    else if constexpr( support_std_to_string<T> )
    {
      return std::to_string(e);
    }
    else if constexpr( streamable<T> )
    {
      std::ostringstream os;
      os << e;
      return os.str();
    }
    else if constexpr( support_to_string<T> )
    {
      return to_string(e);
    }
    else if constexpr( sequence<T> )
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
  inline std::string as_string(std::string const& e)      { return  e;                          }
  inline std::string as_string(std::string_view const& e) { return  std::string(e);             }
  inline std::string as_string(std::nullptr_t)            { return  std::string("nullptr");     }
  inline std::string as_string(const char* e)
  {
    std::ostringstream os;
    os << "char*(" << (void*)e << ")";
    return os.str();
  }
  inline std::string as_string(char* e )
  {
    std::ostringstream os;
    os << "char*(" << (void*)e << ")";
    return os.str();
  }
}
namespace tts::detail
{
  template<typename L, typename R>
  concept comparable_equal  = requires(L l, R r) { compare_equal(l,r); };
  template<typename L, typename R>
  concept comparable_less   = requires(L l, R r) { compare_less(l,r); };
  template<typename L, typename R> inline constexpr bool eq(L const &l, R const &r)
  {
    if constexpr( comparable_equal<L,R> ) return compare_equal(l,r);
    else                                  return l == r;
  }
  template<typename L, typename R> inline constexpr bool lt(L const &l, R const &r)
  {
    if constexpr( comparable_less<L,R> )  return compare_less(l,r);
    else                                  return l < r;
  }
}
namespace tts
{
  struct result
  {
    bool        status;
    std::string lhs,op,rhs;
    explicit operator bool() const { return status; }
  };
  template<typename Expression> struct lhs_expr
  {
    Expression lhs;
    lhs_expr(Expression x) : lhs(x) {}
    lhs_expr(lhs_expr const &)            = delete;
    lhs_expr &operator=(lhs_expr const &) = delete;
    operator result() const { return result {bool(lhs),as_string(bool(lhs)),"",""}; }
    explicit operator bool() const { return bool(lhs); }
    template<typename R> result operator &&(R const &rhs)
    {
      return { lhs && rhs, as_string(lhs), "&&", as_string(rhs) };
    }
    template<typename R> result operator ||(R const &rhs)
    {
      return { lhs || rhs, as_string(lhs), "||", as_string(rhs) };
    }
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
  struct decomposer
  {
    template<typename Expression> lhs_expr<Expression const &> operator->*(Expression const &expr)
    {
      return {expr};
    }
  };
}
#define TTS_DECOMPOSE(XPR) (::tts::decomposer{}->*XPR)
#include <iostream>
namespace tts
{
  struct logger
  {
    logger(bool d = false) : display(d), done(false) {}
    template<typename Result, typename Validator>
    logger& check(Result const& res, Validator validate, auto pass, auto fail)
    {
      display = validate(res) ? pass(res) : fail(res);
      return *this;
    }
    template<typename Result>
    logger& check(Result const& res, auto pass, auto fail)
    {
      return check(res, [](auto const& r) { return static_cast<bool>(r); }, pass, fail);
    }
    template<typename Data>
    logger& operator<<(Data const& d)
    {
      if(display)
      {
        if(!done)
        {
          std::cout << tts::yellow << ">> Additonnal information: " << ::tts::reset << "\n";
          done = true;
        }
        std::cout << d;
      }
      return *this;
    }
    bool display, done;
  };
}
#define TTS_EXPECT_IMPL(EXPR,FAILURE)                                                               \
::tts::logger{}.check                                                                               \
( TTS_DECOMPOSE(EXPR)                                                                               \
, [](tts::result const& res)                                                                        \
  {                                                                                                 \
    TTS_PASS( ::tts::green  << TTS_STRING(EXPR) << tts::reset                                       \
                            << " evaluates as " << ::tts::green                                     \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " as expected.");                                    \
    return false;                                                                                   \
  }                                                                                                 \
, [](tts::result const& res)                                                                        \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(EXPR)  << tts::reset                      \
                            << " but " << ::tts::red                                                \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " occured instead.");                                \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_CONSTEXPR_EXPECT_IMPL(EXPR,FAILURE)                                                     \
::tts::logger{}.check                                                                               \
( TTS_DECOMPOSE(EXPR)                                                                               \
, [](auto const&) { return std::bool_constant<(EXPR)>::value; }                                     \
, [](::tts::result const& res)                                                                      \
  {                                                                                                 \
    TTS_PASS( ::tts::green  << TTS_STRING(EXPR) << tts::reset                                       \
                            << " evaluates as " << ::tts::green                                     \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " at compile-time as expected.");                    \
    return false;                                                                                   \
  }                                                                                                 \
, [](tts::result const& res)                                                                        \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(EXPR)  << tts::reset                      \
                            << " but " << ::tts::red                                                \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " occured at compile-time instead.");                \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_EXPECT(EXPR, ...)     TTS_EXPECT_ ## __VA_ARGS__ ( EXPR )
#define TTS_EXPECT_(EXPR)         TTS_EXPECT_IMPL(EXPR,TTS_FAIL)
#define TTS_EXPECT_REQUIRED(EXPR) TTS_EXPECT_IMPL(EXPR,TTS_FATAL)
#define TTS_CONSTEXPR_EXPECT(EXPR, ...)     TTS_CONSTEXPR_EXPECT_ ## __VA_ARGS__ ( EXPR )
#define TTS_CONSTEXPR_EXPECT_(EXPR)         TTS_CONSTEXPR_EXPECT_IMPL(EXPR,TTS_FAIL)
#define TTS_CONSTEXPR_EXPECT_REQUIRED(EXPR) TTS_CONSTEXPR_EXPECT_IMPL(EXPR,TTS_FATAL)
#define TTS_EXPECT_NOT_IMPL(EXPR,FAILURE)                                                           \
::tts::logger{}.check                                                                               \
( TTS_DECOMPOSE(EXPR)                                                                               \
, [](::tts::result res)                                                                             \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(EXPR) << tts::reset                       \
                            << " to not evaluate to " << ::tts::red                                 \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " but occured anyway."                               \
                            );                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
, [](::tts::result res)                                                                             \
  {                                                                                                 \
    TTS_PASS ( ::tts::green << TTS_STRING(EXPR) << tts::reset                                       \
                            << " does not evaluate to " << ::tts::green                             \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " as expected.");                                    \
    return false;                                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_CONSTEXPR_EXPECT_NOT_IMPL(EXPR,FAILURE)                                                 \
::tts::logger{}.check                                                                               \
( TTS_DECOMPOSE(EXPR)                                                                               \
, [](auto const&) { return std::bool_constant<(EXPR)>::value; }                                     \
, [](tts::result const& res)                                                                        \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(EXPR) << tts::reset                       \
                            << " to not evaluate to " << ::tts::red                                 \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " at compile-time but occured anyway."               \
                            );                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
, [](tts::result const& res)                                                                        \
  {                                                                                                 \
    TTS_PASS ( ::tts::green << TTS_STRING(EXPR) << tts::reset                                       \
                            << " does not evaluate to " << ::tts::green                             \
                            << res.lhs << " " << res.op << " " << res.rhs                           \
                            << ::tts::reset << " at compile-time as expected.");                    \
    return false;                                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_EXPECT_NOT(EXPR, ...)     TTS_EXPECT_NOT_ ## __VA_ARGS__ ( EXPR )
#define TTS_EXPECT_NOT_(EXPR)         TTS_EXPECT_NOT_IMPL((EXPR),TTS_FAIL)
#define TTS_EXPECT_NOT_REQUIRED(EXPR) TTS_EXPECT_NOT_IMPL((EXPR),TTS_FATAL)
#define TTS_CONSTEXPR_EXPECT_NOT(EXPR, ...)     TTS_CONSTEXPR_EXPECT_NOT_ ## __VA_ARGS__ ( EXPR )
#define TTS_CONSTEXPR_EXPECT_NOT_(EXPR)         TTS_CONSTEXPR_EXPECT_NOT_IMPL((EXPR),TTS_FAIL)
#define TTS_CONSTEXPR_EXPECT_NOT_REQUIRED(EXPR) TTS_CONSTEXPR_EXPECT_NOT_IMPL((EXPR),TTS_FATAL)
#define TTS_THROW_IMPL(EXPR, EXCEPTION, FAILURE)                                                    \
::tts::logger{}.check                                                                               \
( ::tts::result{}                                                                                   \
, [&](auto const&) { try { EXPR; } catch(EXCEPTION&) { return true; } catch(...) {} return false; } \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    TTS_PASS( ::tts::green  << TTS_STRING(EXPR) << tts::reset                                       \
                            << " throws: " << ::tts::green                                          \
                            << TTS_STRING(EXCEPTION)                                                \
                            << ::tts::reset << " as expected."                                      \
            );                                                                                      \
    return false;                                                                                   \
  }                                                                                                 \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(EXPR)  << tts::reset                      \
                            << " failed to throw " << ::tts::red                                    \
                            << TTS_STRING(EXCEPTION)                                                \
            );                                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_THROW(EXPR, EXCEPTION, ...)     TTS_THROW_ ## __VA_ARGS__ ( EXPR, EXCEPTION )
#define TTS_THROW_(EXPR, EXCEPTION)         TTS_THROW_IMPL(EXPR, EXCEPTION,TTS_FAIL)
#define TTS_THROW_REQUIRED(EXPR, EXCEPTION) TTS_THROW_IMPL(EXPR, EXCEPTION,TTS_FATAL)
#define TTS_NO_THROW_IMPL(EXPR,FAILURE)                                                             \
::tts::logger{}.check                                                                               \
( ::tts::result{}                                                                                   \
, [&](auto const&) { try { EXPR; } catch(...) { return false; } return true; }                      \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    TTS_PASS( ::tts::green  << TTS_STRING(EXPR) << tts::reset                                       \
                            << " does not throw as expected."                                       \
            );                                                                                      \
    return false;                                                                                   \
  }                                                                                                 \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    FAILURE ( "Expected: "  << ::tts::red << TTS_STRING(EXPR)  << tts::reset                        \
                            << " throws unexpectedly."                                              \
            );                                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_NO_THROW(EXPR, ...)     TTS_NO_THROW_ ## __VA_ARGS__ ( EXPR )
#define TTS_NO_THROW_(EXPR)         TTS_NO_THROW_IMPL(EXPR,TTS_FAIL)
#define TTS_NO_THROW_REQUIRED(EXPR) TTS_NO_THROW_IMPL(EXPR,TTS_FATAL)
#include <bit>
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <utility>
namespace tts::detail
{
  inline auto as_int(float a)   noexcept  { return std::bit_cast<std::int32_t>(a); }
  inline auto as_int(double a)  noexcept  { return std::bit_cast<std::int64_t>(a); }
  template<typename T> inline auto bitinteger(T a) noexcept
  {
    auto ia = as_int(a);
    using r_t = std::remove_cvref_t<decltype(ia)>;
    constexpr auto Signmask = r_t(1) << (sizeof(r_t)*8-1);
    return std::signbit(a) ?  Signmask-ia : ia;
  }
}
#include <cmath>
#include <limits>
#include <type_traits>
namespace tts
{
  template<typename T, typename U> inline double absolute_distance(T const &a, U const &b)
  {
    if constexpr(std::is_same_v<T, U>)
    {
      if constexpr(std::is_same_v<T, bool>)
      {
        return a == b ? 0. : 1.;
      }
      else if constexpr(std::is_floating_point_v<T>)
      {
        if((a == b) || (std::isnan(a) && std::isnan(b))) return 0.;
        if(std::isinf(a) || std::isinf(b) || std::isnan(a) || std::isnan(b))
          return std::numeric_limits<double>::infinity();
        return std::abs(a - b);
      }
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>)
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
      if constexpr(std::is_same_v<T, bool>)
      { return a == b ? 0. : 100.; }
      else if constexpr(std::is_floating_point_v<T>)
      {
        if((a == b) || (std::isnan(a) && std::isnan(b))) return 0.;
        if(std::isinf(a) || std::isinf(b) || std::isnan(a) || std::isnan(b))
          return std::numeric_limits<double>::infinity();
        return 100. * (std::abs(a - b) / std::max(T(1), std::max(std::abs(a), std::abs(b))));
      }
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>)
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
      if constexpr(std::is_same_v<T, bool>)
      {
        return a == b ? 0. : std::numeric_limits<double>::infinity();
      }
      else if constexpr(std::is_floating_point_v<T>)
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
      else if constexpr(std::is_integral_v<T> && !std::is_same_v<T, bool>)
      {
        using u_t = typename std::make_unsigned<T>::type;
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
namespace tts
{
  template<typename T, typename U> struct precision_result
  {
    std::string lhs,rhs;
    std::string lhs_val,rhs_val;
    T           value;
    U           maxi;
    bool        status;
    explicit operator bool() const { return status; }
  };
}
#define TTS_PRECISION_IMPL(LHS, RHS, N, UNIT, FUNC, FAILURE)                                        \
::tts::logger{}.check                                                                               \
( []<typename M>(auto eval_a, auto eval_b, M maxi)                                                  \
  {                                                                                                 \
    auto r = FUNC(eval_a,eval_b);                                                                   \
    return  ::tts::precision_result<decltype(r),decltype(maxi)>                                     \
            { TTS_STRING(LHS), TTS_STRING(RHS), ::tts::as_string(eval_a), ::tts::as_string(eval_b)  \
            , r, maxi, r <= maxi                                                                    \
            };                                                                                      \
  }(LHS,RHS,N)                                                                                      \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    auto& fmt_n = res.maxi  < 1000  ? std::defaultfloat : std::scientific;                          \
    auto& fmt_r = res.value < 1000  ? std::defaultfloat : std::scientific;                          \
    TTS_PASS( ::tts::green  << res.lhs << " == " << res.rhs << tts::reset                           \
                            << " evaluates as " << ::tts::green                                     \
                            << res.lhs_val << " == " << res.rhs_val                                 \
                            << " within " << std::setprecision(2) << fmt_r                          \
                            << ::tts::green  << res.value << ::tts::reset << std::defaultfloat      \
                            << " " << UNIT << ::tts::reset << " when "                              \
                            << std::setprecision(2) << fmt_n                                        \
                            << ::tts::green  << res.maxi << ::tts::reset << std::defaultfloat       \
                            << " " << UNIT << " was expected."                                      \
                            );                                                                      \
    return false;                                                                                   \
  }                                                                                                 \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    auto& fmt_n = res.maxi  < 1000  ? std::defaultfloat : std::scientific;                          \
    auto& fmt_r = res.value < 1000  ? std::defaultfloat : std::scientific;                          \
    FAILURE ( "Expected: "  << ::tts::green << res.lhs << " == " << res.rhs                         \
                            << tts::reset << " but " << ::tts::red                                  \
                            << res.lhs_val << " == " << res.rhs_val                                 \
                            << " within " << std::setprecision(2) << fmt_r                          \
                            << ::tts::red  << res.value << ::tts::reset << std::defaultfloat        \
                            << " " << UNIT << ::tts::reset << " when "                              \
                            << std::setprecision(2) << fmt_n                                        \
                            << ::tts::green  << res.maxi << ::tts::reset << std::defaultfloat       \
                            << " " << UNIT << " was expected."                                      \
            );                                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_PRECISION(L,R,N,U,F, ...)     TTS_PRECISION_ ## __VA_ARGS__ (L,R,N,U,F)
#define TTS_PRECISION_(L,R,N,U,F)         TTS_PRECISION_IMPL(L,R,N,U,F,TTS_FAIL)
#define TTS_PRECISION_REQUIRED(L,R,N,U,F) TTS_PRECISION_IMPL(L,R,N,U,F,TTS_FATAL)
#define TTS_ABSOLUTE_EQUAL(L,R,N,...) TTS_PRECISION(L,R,N,"unit", ::tts::absolute_distance, __VA_ARGS__ )
#define TTS_RELATIVE_EQUAL(L,R,N,...) TTS_PRECISION(L,R,N,"%"   , ::tts::relative_distance, __VA_ARGS__ )
#define TTS_ULP_EQUAL(L,R,N,...)      TTS_PRECISION(L,R,N,"ULP" , ::tts::ulp_distance     , __VA_ARGS__ )
#define TTS_IEEE_EQUAL(L,R,...)       TTS_ULP_EQUAL(L, R, 0, __VA_ARGS__ )
#define TTS_EQUAL(LHS, RHS, ...)         TTS_EXPECT(LHS == RHS, __VA_ARGS__)
#define TTS_NOT_EQUAL(LHS, RHS, ...)     TTS_EXPECT(LHS != RHS, __VA_ARGS__)
#define TTS_LESS(LHS, RHS, ...)          TTS_EXPECT(LHS  < RHS, __VA_ARGS__)
#define TTS_GREATER(LHS, RHS, ...)       TTS_EXPECT(LHS  > RHS, __VA_ARGS__)
#define TTS_LESS_EQUAL(LHS, RHS, ...)    TTS_EXPECT(LHS <= RHS, __VA_ARGS__)
#define TTS_GREATER_EQUAL(LHS, RHS, ...) TTS_EXPECT(LHS >= RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_EQUAL(LHS, RHS, ...)         TTS_CONSTEXPR_EXPECT(LHS == RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_NOT_EQUAL(LHS, RHS, ...)     TTS_CONSTEXPR_EXPECT(LHS != RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_LESS(LHS, RHS, ...)          TTS_CONSTEXPR_EXPECT(LHS  < RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_GREATER(LHS, RHS, ...)       TTS_CONSTEXPR_EXPECT(LHS  > RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_LESS_EQUAL(LHS, RHS, ...)    TTS_CONSTEXPR_EXPECT(LHS <= RHS, __VA_ARGS__)
#define TTS_CONSTEXPR_GREATER_EQUAL(LHS, RHS, ...) TTS_CONSTEXPR_EXPECT(LHS >= RHS, __VA_ARGS__)
namespace tts::detail
{
  template<typename It1, typename It2, typename Func>
  std::pair<It1, It2> mismatch(It1 first1, It1 last1, It2 first2, Func p)
  {
    while (first1 != last1 && p(*first1, *first2))
      ++first1, ++first2;
    return std::make_pair(first1, first2);
  }
}
#define TTS_ALL_PRECISION_IMPL(LHS, RHS, N, UNIT, FUNC, FAILURE)                                  \
[&]()                                                                                             \
{                                                                                                 \
  if( std::size(LHS) == std::size(RHS) )                                                          \
  {                                                                                               \
    auto found = ::tts::detail::mismatch( std::begin(LHS), std::end(LHS), std::begin(RHS)         \
                                        , [](auto l, auto r) { return ::tts::FUNC(l,r) <= N; }    \
                                        );                                                        \
    auto distance = std::end(LHS)-found.first;                                                    \
    auto& fmt_n = N<1000 ? std::defaultfloat : std::scientific;                                   \
                                                                                                  \
    if( distance == 0)                                                                            \
    {                                                                                             \
      TTS_PASS( ::tts::green  << TTS_STRING(LHS) << " == " << TTS_STRING(RHS) << tts::reset       \
                              << " evaluates within " << std::setprecision(2) << fmt_n            \
                              << ::tts::green  << N << ::tts::reset << std::defaultfloat          \
                              << " " << UNIT << " for all values."                                \
                              );                                                                  \
      return ::tts::logger{false};                                                                \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
      FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(LHS) << " == " << TTS_STRING(RHS)     \
                              << ::tts::reset << " but value at index " << ::tts::yellow          \
                              << distance     << ::tts::reset << " is " << ::tts::red             \
                              << ::tts::as_string(*found.first) << ::tts::reset                   \
                              << " instead of " << ::tts::red                                     \
                              << ::tts::as_string(*found.second)<< ::tts::reset                   \
                              << " within " << ::tts::red                                         \
                              << ::tts::FUNC(*found.first,*found.second)                          \
                              << " " << UNIT << " instead of " << N                               \
              );                                                                                  \
    return ::tts::logger{::tts::verbose_status};                                                  \
    }                                                                                             \
  }                                                                                               \
  else                                                                                            \
  {                                                                                               \
    FAILURE ( "Expected: "  << ::tts::green << TTS_STRING(LHS) << " == " << TTS_STRING(RHS)       \
                            << ::tts::reset << " but sizes mismatch between: "                    \
                            << ::tts::red << std::size(LHS) << ::tts::reset                       \
                            << " and "  << ::tts::red << std::size(RHS) << ::tts::reset           \
            );                                                                                    \
    return ::tts::logger{::tts::verbose_status};                                                  \
  }                                                                                               \
}()
#define TTS_ALL_PRECISION(L,R,N,U,F, ...)     TTS_ALL_PRECISION_ ## __VA_ARGS__ (L,R,N,U,F)
#define TTS_ALL_PRECISION_(L,R,N,U,F)         TTS_ALL_PRECISION_IMPL(L,R,N,U,F,TTS_FAIL)
#define TTS_ALL_PRECISION_REQUIRED(L,R,N,U,F) TTS_ALL_PRECISION_IMPL(L,R,N,U,F,TTS_FATAL)
#define TTS_ALL_ABSOLUTE_EQUAL(L,R,N,...) TTS_ALL_PRECISION(L,R,N,"unit",absolute_distance, __VA_ARGS__)
#define TTS_ALL_RELATIVE_EQUAL(L,R,N,...) TTS_ALL_PRECISION(L,R,N,"%"   ,relative_distance, __VA_ARGS__)
#define TTS_ALL_ULP_EQUAL(L,R,N,...)      TTS_ALL_PRECISION(L,R,N,"ULP" ,ulp_distance     , __VA_ARGS__)
#define TTS_ALL_IEEE_EQUAL(L,R ,...)      TTS_ALL_ULP_EQUAL(L,R,0., __VA_ARGS__)
#define TTS_ALL_EQUAL(L,R, ...)           TTS_ALL_ABSOLUTE_EQUAL(L,R,0, __VA_ARGS__)
#define TTS_TYPE_IS_IMPL(T, TYPE, FAILURE)                                                          \
::tts::logger{}.check                                                                               \
( ::tts::result{}                                                                                   \
, [](auto const&) { return std::is_same_v<TTS_REMOVE_PARENS(TYPE), TTS_REMOVE_PARENS(T)>; }         \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    TTS_PASS( ::tts::green  << TTS_STRING(TTS_REMOVE_PARENS(T)) << tts::reset                       \
                            << " evaluates as " << ::tts::green                                     \
                            << tts::typename_<TTS_REMOVE_PARENS(TYPE)>                              \
                            << ::tts::reset << " as expected.");                                    \
    return false;                                                                                   \
  }                                                                                                 \
, [](auto const& res)                                                                               \
  {                                                                                                 \
    FAILURE( ::tts::green  << TTS_STRING(TTS_REMOVE_PARENS(T)) << tts::reset                        \
                            << " evaluates as " << ::tts::red                                       \
                            << tts::typename_<TTS_REMOVE_PARENS(T)>                                 \
                            << ::tts::reset << " instead of "                                       \
                            << ::tts::green << tts::typename_<TTS_REMOVE_PARENS(TYPE)>              \
            );                                                                                      \
    return ::tts::verbose_status;                                                                   \
  }                                                                                                 \
)                                                                                                   \

#define TTS_TYPE_IS(T, TYPE, ...)     TTS_TYPE_IS_ ## __VA_ARGS__ ( T, TYPE )
#define TTS_TYPE_IS_(T, TYPE)         TTS_TYPE_IS_IMPL(T, TYPE,TTS_FAIL)
#define TTS_TYPE_IS_REQUIRED(T, TYPE) TTS_TYPE_IS_IMPL(T, TYPE,TTS_FATAL)
#define TTS_EXPR_IS(EXPR, TYPE, ...)  TTS_TYPE_IS(decltype(TTS_REMOVE_PARENS(EXPR)), TYPE, __VA_ARGS__)

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