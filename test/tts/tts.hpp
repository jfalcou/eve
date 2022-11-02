//==================================================================================================
/**
  TTS - Tiny Test System
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif
#include <iostream>
namespace tts
{
  inline int usage(const char* name)
  {
    std::cout << "TTS Unit Tests Driver\n";
    std::cout << "Usage: " << name  << " [OPTION...]\n";
    std::cout << "\nFlags:\n";
    std::cout << "  -h, --help        Display this help message\n";
    std::cout << "  -x, --hex         Print the floating results in hexfloat mode\n";
    std::cout << "  -s, --scientific  Print the floating results in scientific mode\n";
    std::cout << "\nParameters:\n";
    std::cout << "  --precision=arg   Set the precision for displaying floating pint values\n";
    std::cout << "  --seed=arg        Set the PRNG seeds (default is time-based)\n";
    std::cout << "\nRange specifics Parameters:\n";
    std::cout << "  --block=arg       Set size of range checks samples (min. 32)\n";
    std::cout << "  --loop=arg        Repeat each range checks arg times\n";
    std::cout << "  --ulpmax=arg      Set global failure ulp threshold for range tests (default is 2.0)\n";
    std::cout << "  --valmax=arg      Set maximal value for range tests (default is code)\n";
    std::cout << "  --valmin=arg      Set minimal value for range tests (default is code)\n";
    std::cout << std::endl;
    return 0;
  }
}
#include <utility>
namespace tts
{
  struct callable
  {
    public:
    using signature_t = void(*)(void*);
    signature_t invoker = {};
    signature_t cleanup = {};
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
    constexpr void operator()()       { invoker(payload); }
    constexpr void operator()() const { invoker(payload); }
    explicit constexpr operator bool() const { return payload != nullptr; }
    private:
    template <typename T>
    static void invoke(void* data) { (*static_cast<T*>(data))(); }
    template <typename T>
    static void destroy(void* data) { delete static_cast<T*>(data); }
  };
}
#include <vector>
#include <string>
namespace tts::detail
{
  inline std::string current_test = "";
  struct test
  {
    void operator()()
    {
      current_test = name;
      behaviour();
    }
    static inline bool acknowledge(test&& f);
    std::string     name;
    tts::callable   behaviour;
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
      auto passes   = (fails || invalids) ?  0 : test_count;
      std::cout << "----------------------------------------------------------------\n";
      std::cout << "Results: " << test_count << " " << test_txt << " - "
                << success_count << "/" << passes << " " << pass_txt << " - "
                << failure_count << "/" << fails << " " << fail_txt << " - "
                << invalid_count << "/" << invalids << " " << inv_txt << "\n";
      if(!fails && !invalids) return test_count == success_count ? 0 : 1;
      else                    return (failure_count == fails && invalid_count == invalids) ? 0 : 1;
    }
    int test_count    = 0,
        success_count = 0,
        failure_count = 0,
        fatal_count   = 0,
        invalid_count = 0;
    bool fail_status = false;
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
#include <chrono>
#include <cmath>
#include <initializer_list>
#include <random>
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
    bool is_valid() { return argc && argv != nullptr; }
    int argc;
    char const** argv;
  };
  namespace detail
  {
    inline ::tts::options current_arguments = {0,nullptr};
    inline std::int32_t   current_seed      = -1;
  }
  inline void initialize(int argc, const char** argv)
  {
    if(!detail::current_arguments.is_valid())
      detail::current_arguments = ::tts::options{argc,argv};
  }
  inline ::tts::options const& arguments()
  {
    return detail::current_arguments;
  }
  inline std::int32_t random_seed(int base_seed = -1)
  {
    if(detail::current_seed == -1)
    {
      auto s = ::tts::arguments().value( "--seed", base_seed );
      if(s == -1 )
      {
        auto now = std::chrono::high_resolution_clock::now();
        s        = static_cast<std::int32_t>(now.time_since_epoch().count());
      }
      detail::current_seed = s;
    }
    return detail::current_seed;
  }
}
#if !defined(TTS_CUSTOM_DRIVER_FUNCTION)
#  define TTS_CUSTOM_DRIVER_FUNCTION main
namespace tts::detail { constexpr bool use_main = true; }
#else
namespace tts::detail { constexpr bool use_main = false; }
#endif
namespace tts::detail { struct fatal_signal {}; }
#if defined(TTS_MAIN)
int TTS_CUSTOM_DRIVER_FUNCTION([[maybe_unused]] int argc,[[maybe_unused]] char const** argv)
{
  ::tts::initialize(argc,argv);
  if( ::tts::arguments()[{"-h","--help"}] )
    return ::tts::usage(argv[0]);
  auto nb_tests = ::tts::detail::suite.size();
  std::size_t done_tests = 0;
  try
  {
    for(auto &t: ::tts::detail::suite)
    {
      auto test_count     = ::tts::global_runtime.test_count;
      auto failure_count  = ::tts::global_runtime.failure_count;
      ::tts::global_runtime.fail_status = false;
      t();
      done_tests++;
      if(test_count     == ::tts::global_runtime.test_count)
      {
        ::tts::global_runtime.invalid();
        std::cout << "[!] - " << ::tts::detail::current_test << " : EMPTY TEST CASE\n";
      }
      else if(failure_count  == ::tts::global_runtime.failure_count)
      {
        std::cout << "[V] - " << ::tts::detail::current_test << "\n";
      }
    }
  }
  catch( ::tts::detail::fatal_signal& )
  {
    std::cout << "@@ ABORTING DUE TO EARLY FAILURE @@ - "
              << (nb_tests - done_tests - 1) << " Tests not run\n";
  }
  if constexpr( ::tts::detail::use_main )   return ::tts::report(0,0);
  else                                      return 0;
}
#endif
#include <iomanip>
#include <sstream>
#include <type_traits>
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
}
#ifndef TTS_FUNCTION
#define TTS_FUNCTION TTS_UNIQUE(tts_function)
#endif
#ifndef TTS_REGISTRATION
#define TTS_REGISTRATION TTS_UNIQUE(tts_registration)
#endif
#define TTS_UNIQUE3(ID, LINE) ID##LINE
#define TTS_UNIQUE2(ID, LINE) TTS_UNIQUE3(ID, LINE)
#define TTS_UNIQUE(ID)        TTS_UNIQUE2(ID, __COUNTER__)
#define TTS_CAT(x, y)   TTS_CAT_I(x, y)
#define TTS_CAT_I(x, y) x##y
#define TTS_STRING(...)   TTS_STRING_((__VA_ARGS__))
#define TTS_STRING__(...) #__VA_ARGS__
#define TTS_STRING_(TXT)  TTS_STRING__ TXT
#define TTS_COUNT(...) TTS_COUNT_(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1, 0)
#define TTS_COUNT_(A0, A1, A2, A3, A4, A5, A6, A7, ...) A7
#define TTS_ARG0()
#define TTS_ARG1(A0)                          auto A0
#define TTS_ARG2(A0, A1)                      auto A0, auto A1
#define TTS_ARG3(A0, A1, A2)                  TTS_ARG2(A0, A1)                , auto A2
#define TTS_ARG4(A0, A1, A2, A3)              TTS_ARG3(A0, A1, A2)            , auto A3
#define TTS_ARG5(A0, A1, A2, A3, A4)          TTS_ARG4(A0, A1, A2, A3)        , auto A4
#define TTS_ARG6(A0, A1, A2, A3, A4, A5)      TTS_ARG5(A0, A1, A2, A3, A4)    , auto A5
#define TTS_ARG7(A0, A1, A2, A3, A4, A5, A6)  TTS_ARG6(A0, A1, A2, A3, A4, A5), auto A6
#define TTS_ARG(...) TTS_CAT(TTS_ARG, TTS_COUNT(__VA_ARGS__))(__VA_ARGS__)
#define TTS_VAL(x)                    x
#define TTS_REVERSE_1(a)              (a)
#define TTS_REVERSE_2(a,b)            (b, a)
#define TTS_REVERSE_3(a,b,c)          (c, b, a)
#define TTS_REVERSE_4(a,b,c,d)        (d, c, b, a)
#define TTS_REVERSE_5(a,b,c,d,e)      (e, d, c, b, a)
#define TTS_REVERSE_6(a,b,c,d,e,f)    (f, e, d, c, b, a)
#define TTS_REVERSE_7(a,b,c,d,e,f,g)  (g, f, e, d, c, b, a)
#define TTS_REVERSE_IMPL(N,...) TTS_VAL(TTS_REVERSE_ ## N(__VA_ARGS__))
#define TTS_REVERSE_(N,...)     TTS_REVERSE_IMPL( N, __VA_ARGS__)
#define TTS_REVERSE(...)        TTS_REVERSE_( TTS_COUNT(__VA_ARGS__), __VA_ARGS__)
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
#include <string_view>
#include <string>
namespace tts::detail
{
  template<typename T> struct typename_impl
  {
    static auto value() noexcept
    {
  #if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1,
        j = data.find(">::value");
      auto name = data.substr(i, j - i);
  #else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2,
        j = data.find_last_of(']');
      auto name = data.substr(i, j - i);
  #endif
      return std::string(name.data(), name.size());
    }
  };
}
namespace tts
{
  template<typename T> inline auto const typename_ = detail::typename_impl<T>::value();
  template<typename T> constexpr auto name(T const&){ return typename_<T>; }
}
#include <cstdint>
namespace tts
{
  template<typename... Ts>
  struct types
  {
    template<typename... Us> constexpr types<Ts...,Us...> operator+( types<Us...> const&) const;
  };
  template<typename... Ls> struct concatenate { using type = decltype( (Ls{} + ...) ); };
  template<typename... Ls> using concatenate_t = typename concatenate<Ls...>::type;
  template<typename... T> struct type {};
  using real_types        = types < double,float>;
  using int_types         = types < std::int64_t , std::int32_t , std::int16_t , std::int8_t>;
  using signed_types      = concatenate_t<real_types,int_types>;
  using uint_types        = types < std::uint64_t , std::uint32_t , std::uint16_t , std::uint8_t>;
  using integral_types    = concatenate_t<int_types,int_types>;
  using arithmetic_types  = concatenate_t<real_types,int_types,uint_types>;
}
#include <tuple>
namespace tts::detail
{
  struct test_capture
  {
    test_capture(const char* id) : name(id) {}
    auto operator+(auto body) const { return test::acknowledge( {name, body} ); }
    const char* name;
  };
  inline std::string current_type = {};
  template<typename... Types> struct test_captures
  {
    test_captures(const char* id) : name(id) {}
    auto operator+(auto body) const
    {
      return test::acknowledge( { name
                                , [=]()
                                  {
                                    ( ( (current_type = " with [T = " + typename_<Types> + "]")
                                      , body(type<Types>())
                                      )
                                    , ...
                                    );
                                    current_type.clear();
                                  }
                                }
                              );
    }
    std::string name;
  };
  template<typename... Types>
  struct test_captures<types<Types...>> : test_captures<Types...>
  {};
  template<typename Generator>
  requires requires(Generator g) { typename Generator::types_list; }
  struct test_captures<Generator> : test_captures<typename Generator::types_list>
  {};
}
namespace tts::detail
{
  template<typename Generator, typename... Types> struct test_generators
  {
    test_generators(const char* id, Generator g, Types...) : name(id), generator(g) {}
    friend auto operator<<(test_generators tg, auto body)
    {
      return test::acknowledge( { tg.name
                                , [tg,body]() mutable
                                  {
                                    std::mt19937 gen(::tts::random_seed());
                                    ( ( (current_type = " with [T = " + typename_<Types> + "]")
                                      , std::apply(body, tg.generator(type<Types>{}, gen))
                                      ), ...
                                    );
                                    current_type.clear();
                                  }
                                }
                              );
    }
    std::string name;
    Generator   generator;
  };
  template<typename Generator, typename... Types>
  test_generators(const char*,Generator,Types...) -> test_generators<Generator,Types...>;
  template<typename Generator, typename... Types>
  struct  test_generators<Generator, types<Types...>>
        : test_generators<Generator,Types...>
  {
    using parent = test_generators<Generator,Types...>;
    test_generators(const char* id, Generator g, types<Types...>) : parent(id,g,Types{}...) {}
  };
  template<typename Generator, typename TypeGenerator>
  requires requires(TypeGenerator g) { typename TypeGenerator::types_list; }
  struct  test_generators<Generator,TypeGenerator>
        : test_generators<Generator,typename TypeGenerator::types_list>
  {
    using parent = test_generators<Generator,typename TypeGenerator::types_list>;
    test_generators ( const char* id, Generator g, TypeGenerator )
                    : parent(id,g,typename TypeGenerator::types_list{}) {}
  };
}
#define TTS_PROTOTYPE(...) [] __VA_ARGS__
#define TTS_CASE(ID)                                                                                \
static bool const TTS_CAT(case_,TTS_FUNCTION) = ::tts::detail::test_capture{ID} + TTS_PROTOTYPE(()) \

#define TTS_CASE_TPL(ID,...)                                                                        \
static bool const TTS_CAT(case_,TTS_FUNCTION) = ::tts::detail::test_captures<__VA_ARGS__>{ID}       \
                                              + TTS_PROTOTYPE()                                     \

#define TTS_CASE_WITH(ID, TYPES, GENERATOR)                                                         \
static bool const TTS_CAT(case_,TTS_FUNCTION)                                                       \
                  = ::tts::detail::test_generators{ID,GENERATOR,TYPES{}} << TTS_PROTOTYPE()         \

#include <string_view>
#include <ostream>
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
      return os << "[" << s.filename() << ":" << s.line() << "]";
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
  }()
#define TTS_FAIL(Message)                                                                           \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.fail();                                                                   \
    if(!::tts::global_runtime.fail_status)                                                          \
    {                                                                                               \
      ::tts::global_runtime.fail_status = true;                                                     \
      std::cout << "[X] - " << ::tts::detail::current_test << "\n";                                 \
    }                                                                                               \
    if( !::tts::detail::current_type.empty())                                                       \
    {                                                                                               \
      std::cout << "  > " << ::tts::detail::current_type << "\n";                                   \
    }                                                                                               \
    std::cout << "    " << ::tts::source_location::current() << " - ** FAILURE **"                  \
              << " : " << Message << std::endl;                                                     \
  }()
#define TTS_FATAL(Message)                                                                          \
  [&]()                                                                                             \
  {                                                                                                 \
    ::tts::global_runtime.fatal();                                                                  \
    if(!::tts::global_runtime.fail_status)                                                          \
    {                                                                                               \
      ::tts::global_runtime.fail_status = true;                                                     \
      std::cout << "[@] - " << ::tts::detail::current_test<< "\n";                                  \
    }                                                                                               \
    if( !::tts::detail::current_type.empty())                                                       \
    {                                                                                               \
      std::cout << "  > " << ::tts::detail::current_type << "\n";                                   \
    }                                                                                               \
    std::cout << "    " << ::tts::source_location::current() << " - @@ FATAL @@"                    \
              << " : " << Message << std::endl;                                                     \
    throw ::tts::detail::fatal_signal();                                                            \
  }()
#include <iostream>
namespace tts
{
  struct logger
  {
    logger(bool status = true) : display(status), done(false) {}
    template<typename Data> logger& operator<<(Data const& d)
    {
      if(display)
      {
        if(!done)
        {
          std::cout << ">> Additionnal information: \n";
          done = true;
        }
        std::cout << d;
      }
      return *this;
    }
    ~logger() { if(display && done) std::cout << "\n"; }
    bool display, done;
  };
}
#define TTS_EXPECT(EXPR, ...)     TTS_EXPECT_ ## __VA_ARGS__ ( EXPR )
#define TTS_EXPECT_(EXPR)         TTS_EXPECT_IMPL((EXPR),TTS_FAIL)
#define TTS_EXPECT_REQUIRED(EXPR) TTS_EXPECT_IMPL((EXPR),TTS_FATAL)
#define TTS_EXPECT_IMPL(EXPR,FAILURE)                                                               \
[&](auto&& expr)                                                                                    \
{                                                                                                   \
  if( expr )                                                                                        \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expression: "  << TTS_STRING(TTS_REMOVE_PARENS(EXPR)) << " evaluates to false." );   \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(EXPR)                                                                                             \

#define TTS_EXPECT_NOT(EXPR, ...)       TTS_EXPECT_NOT_ ## __VA_ARGS__ ( EXPR )
#define TTS_EXPECT_NOT_(EXPR)           TTS_EXPECT_NOT_IMPL(EXPR,TTS_FAIL)
#define TTS_EXPECT_NOT_REQUIRED(EXPR)   TTS_EXPECT_NOT_IMPL(EXPR,TTS_FATAL)
#define TTS_EXPECT_NOT_IMPL(EXPR,FAILURE)                                                           \
[&](auto&& expr)                                                                                    \
{                                                                                                   \
  if( !expr )                                                                                       \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expression: "  << TTS_STRING(EXPR) << " evaluates to true." );                       \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(EXPR)                                                                                             \

#define TTS_CONSTEXPR_EXPECT(EXPR, ...) TTS_CEXPR_EXPECT_ ## __VA_ARGS__ ( EXPR )
#define TTS_CEXPR_EXPECT_(EXPR)         TTS_CEXPR_EXPECT_IMPL(EXPR,TTS_FAIL)
#define TTS_CEXPR_EXPECT_REQUIRED(EXPR) TTS_CEXPR_EXPECT_IMPL(EXPR,TTS_FATAL)
#define TTS_CEXPR_EXPECT_IMPL(EXPR,FAILURE)                                                         \
[&]()                                                                                               \
{                                                                                                   \
  using result_tts = std::bool_constant<EXPR>;                                                      \
  if constexpr( result_tts::value )                                                                 \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expression: "  << TTS_STRING(EXPR) << " evaluates to false." );                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}()                                                                                                 \

#define TTS_CONSTEXPR_EXPECT_NOT(EXPR, ...) TTS_CEXPR_EXPECT_NOT_ ## __VA_ARGS__ ( EXPR )
#define TTS_CEXPR_EXPECT_NOT_(EXPR)         TTS_CEXPR_EXPECT_NOT_IMPL(EXPR,TTS_FAIL)
#define TTS_CEXPR_EXPECT_NOT_REQUIRED(EXPR) TTS_CEXPR_EXPECT_NOT_IMPL(EXPR,TTS_FATAL)
#define TTS_CEXPR_EXPECT_NOT_IMPL(EXPR,FAILURE)                                                     \
[&]()                                                                                               \
{                                                                                                   \
  using result_tts = std::bool_constant<EXPR>;                                                      \
  if constexpr( !result_tts::value )                                                                \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expression: "  << TTS_STRING(EXPR) << " evaluates to true." );                       \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}()                                                                                                 \

#include <cstring>
#include <array>
namespace tts::detail
{
  template<typename T, std::size_t N>
  struct block
  {
    block() : nbelems{0} {}
    block(std::size_t sz) : storage{} ,nbelems{sz} {}
    std::size_t size()      const { return nbelems; }
    std::size_t capacity()  const { return N; }
    std::size_t empty()     const { return nbelems == 0; }
    void resize(std::size_t n)  { nbelems = n; }
    void push_back(T v)         { storage[nbelems] = v; nbelems++; }
    void push_front(T v)        { insert(begin(),v); }
    void insert(auto it, T v)
    {
      std::memmove(it+1, it, size()*sizeof(T));
      *it = v;
      nbelems++;
    }
    void clear() { nbelems = 0; }
    T&  back()       { return storage[size()-1]; }
    T   back() const { return storage[size()-1]; }
    T&  front()       { return storage[0]; }
    T   front() const { return storage[0]; }
    T&  operator[](std::size_t i)       { return storage[i]; }
    T   operator[](std::size_t i) const { return storage[i]; }
    auto begin()  { return  &storage[0]; }
    auto end()    { return begin() + nbelems; }
    auto begin()  const { return &storage[0]; }
    auto end()    const { return begin() + nbelems; }
    private:
    std::array<T,N> storage;
    std::size_t     nbelems;
  };
}
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <type_traits>
namespace tts
{
  template<typename T>
  struct fp_dist
  {
    using result_type = T;
    struct param_type
    {
      param_type( T pa = 0, T pb = 1
                , std::size_t sz = 65536
                , T mnp = std::numeric_limits<T>::epsilon()
                , T mxp = 1./std::numeric_limits<T>::epsilon()
                )
                : a(pa), b(pb), n(sz), minpos(mnp), maxpos(mxp)
      {
        if(b<a) std::swap(a,b);
        if(a < -maxpos)             a = -maxpos;
        else if(a>0 && a < minpos)  a =  minpos;
        if(b > maxpos)              b =  maxpos;
        else if(b<0 && b < -minpos) b = -minpos;
      }
      T a, b;
      std::size_t n;
      T minpos, maxpos;
    };
    fp_dist()                                     noexcept : fp_dist(param_type{}) {}
    fp_dist(T a, T b)                             noexcept : fp_dist(param_type{a,b}) {}
    fp_dist(T a, T b, std::size_t n)              noexcept : fp_dist(param_type{a,b,n}) {}
    fp_dist(T a, T b, std::size_t n, T mn )       noexcept : fp_dist(param_type{a,b,n,mn}) {}
    fp_dist(T a, T b, std::size_t n, T mn, T mx)  noexcept : fp_dist(param_type{a,b,n,mn,mx}) {}
    fp_dist(param_type const& pr)                 noexcept { param(pr); }
    param_type const& param() const { return params; }
    void param(param_type const& p)
    {
      params = p;
      find_limits();
      find_indexes(1+params.minpos/2);
      selector.param( std::uniform_int_distribution<std::size_t>::param_type(0, size()-1));
    }
    auto size() const noexcept  { return sizes.back(); }
    auto min()  const noexcept  { return params.a; }
    auto max()  const noexcept  { return params.b; }
    template< class Generator > result_type operator()( Generator& gen )
    {
      auto p  = selector(gen);
      auto it = std::upper_bound(sizes.begin(), sizes.end(), p) - 1;
      auto i  = std::distance(sizes.begin(),it);
      return generate(limits[i],limits[i+1],p - *it,params.n);
    }
    tts::detail::block<T,7>                     limits;
    tts::detail::block<std::size_t,7>           sizes;
    std::uniform_int_distribution<std::size_t>  selector;
    param_type                                  params;
    private:
    void find_limits() noexcept
    {
      limits.clear();
      std::array<T,7> zs{-params.maxpos,-1,-params.minpos,0,params.minpos,1,params.maxpos};
      for(auto z : zs)
      {
        if(z>=params.a && z<=params.b) limits.push_back(z);
      }
      if(limits.empty()) { limits.push_back(params.a); limits.push_back(params.b);}
      else
      {
        if(limits.front() > params.a)  { limits.push_front(params.a); }
        if(limits.back()  < params.b)  { limits.push_back(params.b);  }
      }
    }
    void find_indexes(std::size_t nbzero) noexcept
    {
      sizes.resize(limits.size());
      std::size_t t = 0;
      sizes[0]    = 0;
      for(std::size_t i=1;i<limits.size()-1;++i)
      {
        t += (limits[i] == 0 || limits[i-1] == 0)  ? nbzero : params.n;
        sizes[i] = t;
      }
      sizes.back() = t + (limits.back() == 0 ? nbzero : params.n);
    }
   static T generate(T va, T vb, std::size_t p, std::size_t n) noexcept
    {
      const auto eval = [](double x, double y, double i, double sz) -> double
      {
        if(x<1) return 1./std::exp2(std::lerp(std::log2(1./y), std::log2(1./x), i/sz));
        else    return    std::exp2(std::lerp(std::log2(x)   , std::log2(y)   , i/sz));
      };
      if(va==0 || vb==0)  return 0.;
      auto f = va<0 ? -1 : 1;
      return f * eval(f * va, f * vb,p,n-1);
    }
  };
  template<typename T>
  struct  char_dist
       : std::uniform_int_distribution < std::conditional_t< std::is_signed_v<T>
                                                            , short
                                                            , unsigned short
                                        > >
  {
    using parent = std::uniform_int_distribution< std::conditional_t<std::is_signed_v<T>
                                                                    , short
                                                                    , unsigned short
                                                                    >
                                                >;
    using result_type = T;
    using parent::parent;
    template< class Generator > result_type operator()( Generator& gen )
    {
      return static_cast<result_type>(parent::operator()(gen));
    }
  };
  template<typename T>
  struct choose_distribution;
  template<std::integral T>
  requires(sizeof(T) > 1)
  struct choose_distribution<T>
  {
    using type = std::uniform_int_distribution<T>;
  };
  template<std::integral T>
  requires(sizeof(T) == 1)
  struct choose_distribution<T>
  {
    using type = char_dist<T>;
  };
  template<std::floating_point T>
  struct choose_distribution<T>
  {
    using type = fp_dist<T>;
  };
  template<typename T>
  using realistic_distribution = typename choose_distribution<T>::type;
}
#include <tuple>
namespace tts
{
  template<typename T, typename V> auto as_value(V const& v) { return static_cast<T>(v); }
  template<typename T> auto produce(type<T> const& t, auto g, auto& rng, auto... others)
  {
    return g(t,rng, others...);
  }
  template<typename... G> inline auto generate(G... g)
  {
    return [=](auto const& t, auto& rng, auto... others)
    {
      return std::make_tuple(produce(t,g,rng,others...)...);
    };
  }
  template<tts::sequence Seq, typename U> struct rebuild;
  template<template<class,class...> class Seq, typename T, typename... S, typename U>
  struct rebuild<Seq<T,S...>,U> { using type = Seq<U,S...>; };
  template<template<class,std::size_t> class Seq, typename T, std::size_t N, typename U>
  struct rebuild<Seq<T,N>,U>    { using type = Seq<U,N>; };
  template<tts::sequence T>
  auto produce(type<T> const&, auto g, auto& rng, auto... args)
  {
    using elmt_type   = std::remove_cvref_t<decltype(*std::begin(std::declval<T>()))>;
    using value_type  = decltype(g(tts::type<elmt_type>{},rng,0,0ULL,args...));
    typename rebuild<T,value_type>::type that;
    auto b = std::begin(that);
    auto e = std::end(that);
    auto sz = e - b;
    for(std::ptrdiff_t i=0;i<sz;++i)
    {
      *b++ = as_value<value_type>(g(tts::type<value_type>{},rng,i,sz,args...));
    }
    return that;
  }
  template<typename T> struct value
  {
    value(T v) : seed(v) {}
    template<typename U>
    auto operator()(tts::type<U>, auto&, auto...) const
    {
      return as_value<U>(seed);
    }
    T seed;
  };
  template<typename T, typename U = T> struct ramp
  {
    ramp(T s)       : start(s), step(1)   {}
    ramp(T s, U st) : start(s), step(st)  {}
    template<typename D>
    auto operator()(tts::type<D>, auto&) const { return as_value<D>(start); }
    template<typename D>
    auto operator()(tts::type<D>, auto&, auto idx, auto...) const
    {
      return as_value<D>(start+idx*step);
    }
    T start;
    U step;
  };
  template<typename T, typename U = T> struct reverse_ramp
  {
    reverse_ramp(T s)       : start(s), step(1)   {}
    reverse_ramp(T s, U st) : start(s), step(st)  {}
    template<typename D>
    auto operator()(tts::type<D>, auto&) const { return as_value<D>(start); }
    template<typename D>
    auto operator()(tts::type<D>, auto&, auto idx, auto sz, auto...) const
    {
      return as_value<D>(start+(sz-1-idx)*step);
    }
    T start;
    U step;
  };
  template<typename T, typename U = T> struct between
  {
     between(T s, U st) : first(s), last(st)  {}
    template<typename D>
    auto operator()(tts::type<D>, auto&) const { return as_value<D>(first); }
    template<typename D>
    auto operator()(tts::type<D>, auto&, auto idx, auto sz, auto...) const
    {
      auto w1   = as_value<D>(first);
      auto w2   = as_value<D>(last);
      auto step = (sz-1) ? (w2-w1)/(sz-1) : 0;
      return std::min( as_value<D>(w1 + idx*step), w2);
    }
    T first;
    U last;
  };
  template<typename Distribution> struct sample
  {
    sample(Distribution d)  : dist(std::move(d))  {}
    template<typename D> auto operator()(tts::type<D>, auto& rng, auto...)
    {
      return dist(rng);
    }
    Distribution dist;
  };
  template<typename Mx, typename Mn> struct randoms
  {
    randoms(Mn mn, Mx mx)  : mini(mn), maxi(mx)  {}
    template<typename D> auto operator()(tts::type<D>, auto& rng, auto...)
    {
      tts::realistic_distribution<D> dist(as_value<D>(mini), as_value<D>(maxi));
      return  dist(rng);
    }
    Mn mini;
    Mx maxi;
  };
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
  template<typename L, typename R> inline constexpr bool neq(L const &l, R const &r)
  {
    return !eq(l,r);
  }
  template<typename L, typename R> inline constexpr bool lt(L const &l, R const &r)
  {
    if constexpr( comparable_less<L,R> )  return compare_less(l,r);
    else                                  return l < r;
  }
  template<typename L, typename R> inline constexpr bool le(L const &l, R const &r)
  {
    return lt(l, r) || eq(l, r);
  }
  template<typename L, typename R> inline constexpr bool gt(L const &l, R const &r)
  {
    return !le(l,r);
  }
  template<typename L, typename R> inline constexpr bool ge(L const &l, R const &r)
  {
    return !lt(l,r);
  }
}
#include <iomanip>
#include <sstream>
#include <type_traits>
namespace tts
{
  template<typename T> std::string as_string(T const& e)
  {
    if constexpr( std::is_pointer_v<T> )
    {
      std::ostringstream os;
      os << typename_<T> << "(" << (void*)(e) << ")";
      return os.str();
    }
    else if constexpr( std::floating_point<T> )
    {
      auto precision = ::tts::arguments().value({"--precision"}, -1);
      bool hexmode   = ::tts::arguments()[{"-x","--hex"}];
      bool scimode   = ::tts::arguments()[{"-s","--scientific"}];
      std::ostringstream os;
      if(precision != -1 ) os << std::setprecision(precision);
            if(hexmode) os << std::hexfloat   << e << std::defaultfloat;
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
      auto precision = ::tts::arguments().value({"--precision"}, -1);
      bool hexmode   = ::tts::arguments()[{"-x","--hex"}];
      bool scimode   = ::tts::arguments()[{"-s","--scientific"}];
      if(precision != -1 ) os << std::setprecision(precision);
            if(hexmode) os << std::hexfloat;
      else  if(scimode) os << std::scientific << e << std::defaultfloat;
      os << e;
      if(hexmode || scimode) os << std::defaultfloat;
      return os.str();
    }
    else if constexpr( support_to_string<T> )
    {
      return to_string(e);
    }
    else if constexpr( std::is_enum_v<T> )
    {
      std::ostringstream os;
      os << typename_<T> << "(" << static_cast<std::underlying_type_t<T>>(e) << ")";
      return os.str();
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
      os << "[" << typename_<T> << "]@(" << &e << ")";
      return os.str();
    }
  }
  inline std::string as_string(bool b) { return b ? std::string("true") : std::string("false"); }
  inline std::string as_string(std::string const& e)      { return  e;                          }
  inline std::string as_string(std::string_view const& e) { return  std::string(e);             }
  inline std::string as_string(std::nullptr_t)            { return  std::string("nullptr");     }
}
#define TTS_RELATION(A, B, OP, T, F, ...)     TTS_RELATION_ ## __VA_ARGS__ (A,B,OP,T,F)
#define TTS_RELATION_(A, B, OP, T, F)         TTS_RELATION_IMPL(A,B,OP,T,F,TTS_FAIL)
#define TTS_RELATION_REQUIRED(A, B, OP, T, F) TTS_RELATION_IMPL(A,B,OP,T,F,TTS_FATAL)
#define TTS_RELATION_IMPL(A, B, OP, T, F, FAILURE)                                                  \
[&](auto&& a, auto&& b)                                                                             \
{                                                                                                   \
  if( ::tts::detail::OP(a,b) )                                                                      \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE (   "Expression: "  << TTS_STRING(A) << " " T " " << TTS_STRING(B)                      \
            <<  " is false because: " << ::tts::as_string(a) << " " F " " << ::tts::as_string(b)    \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(A,B)                                                                                              \

#define TTS_EQUAL(LHS, RHS, ...)          TTS_RELATION(LHS,RHS, eq , "==" , "!=" , __VA_ARGS__)
#define TTS_NOT_EQUAL(LHS, RHS, ...)      TTS_RELATION(LHS,RHS, neq, "!=" , "==" , __VA_ARGS__)
#define TTS_LESS(LHS, RHS, ...)           TTS_RELATION(LHS,RHS, lt , "<"  , ">=" , __VA_ARGS__)
#define TTS_GREATER(LHS, RHS, ...)        TTS_RELATION(LHS,RHS, gt , ">"  , "<=" , __VA_ARGS__)
#define TTS_LESS_EQUAL(LHS, RHS, ...)     TTS_RELATION(LHS,RHS, le , "<=" , ">"  , __VA_ARGS__)
#define TTS_GREATER_EQUAL(LHS, RHS, ...)  TTS_RELATION(LHS,RHS, ge , ">=" , "<=" , __VA_ARGS__)
#define TTS_CEXPR_RELATION(A, B, OP, T, F, ...)     TTS_CEXPR_RELATION_ ## __VA_ARGS__ (A,B,OP,T,F)
#define TTS_CEXPR_RELATION_(A, B, OP, T, F)         TTS_CEXPR_RELATION_IMPL(A,B,OP,T,F,TTS_FAIL)
#define TTS_CEXPR_RELATION_REQUIRED(A, B, OP, T, F) TTS_CEXPR_RELATION_IMPL(A,B,OP,T,F,TTS_FATAL)
#define TTS_CEXPR_RELATION_IMPL(A, B, OP, T, F, FAILURE)                                            \
[&](auto&& a, auto&& b)                                                                             \
{                                                                                                   \
  using result_tts = std::bool_constant<::tts::detail::OP(A,B)>;                                    \
  if constexpr( result_tts::value )                                                                 \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE (   "Expression: "  << TTS_STRING(A) << " " << T << " " << TTS_STRING(B)                \
            <<  " is false because: "                                                               \
            << ::tts::as_string(a) << " " << F << " " << ::tts::as_string(b)                        \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(A,B)                                                                                              \

#define TTS_CONSTEXPR_EQUAL(LHS, RHS, ...)          TTS_CEXPR_RELATION(LHS,RHS, eq , "==" , "!=", __VA_ARGS__)
#define TTS_CONSTEXPR_NOT_EQUAL(LHS, RHS, ...)      TTS_CEXPR_RELATION(LHS,RHS, neq, "!=" , "==", __VA_ARGS__)
#define TTS_CONSTEXPR_LESS(LHS, RHS, ...)           TTS_CEXPR_RELATION(LHS,RHS, lt , "<"  , ">=", __VA_ARGS__)
#define TTS_CONSTEXPR_GREATER(LHS, RHS, ...)        TTS_CEXPR_RELATION(LHS,RHS, gt , ">"  , "<=", __VA_ARGS__)
#define TTS_CONSTEXPR_LESS_EQUAL(LHS, RHS, ...)     TTS_CEXPR_RELATION(LHS,RHS, le , "<=" , ">" , __VA_ARGS__)
#define TTS_CONSTEXPR_GREATER_EQUAL(LHS, RHS, ...)  TTS_CEXPR_RELATION(LHS,RHS, ge , ">=" , "<=", __VA_ARGS__)
#define TTS_TYPE_IS(TYPE, REF, ...)     TTS_TYPE_IS_ ## __VA_ARGS__ (TYPE, REF)
#define TTS_TYPE_IS_(TYPE, REF)         TTS_TYPE_IS_IMPL(TYPE, REF,TTS_FAIL)
#define TTS_TYPE_IS_REQUIRED(TYPE, REF) TTS_TYPE_IS_IMPL(TYPE, REF,TTS_FATAL)
#define TTS_TYPE_IS_IMPL(TYPE, REF, FAILURE)                                                        \
[&]<typename TTS_T, typename TTS_R>(::tts::type<TTS_T>, ::tts::type<TTS_R>)                         \
{                                                                                                   \
  if constexpr( std::is_same_v<TTS_T,TTS_R> )                                                       \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Type: "  << TTS_STRING(TTS_REMOVE_PARENS(TYPE)) << " is not the same as "            \
                        << TTS_STRING(TTS_REMOVE_PARENS(REF))  << " because "                       \
                        << ::tts::typename_<TTS_T> << " is not " << ::tts::typename_<TTS_R>         \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(::tts::type<TTS_REMOVE_PARENS(TYPE)>{}, ::tts::type<TTS_REMOVE_PARENS(REF)>{})                    \

#define TTS_EXPR_IS(EXPR, TYPE, ...)     TTS_EXPR_IS_ ## __VA_ARGS__ (EXPR, TYPE)
#define TTS_EXPR_IS_(EXPR, TYPE)         TTS_EXPR_IS_IMPL(EXPR, TYPE,TTS_FAIL)
#define TTS_EXPR_IS_REQUIRED(EXPR, TYPE) TTS_EXPR_IS_IMPL(EXPR, TYPE,TTS_FATAL)
#define TTS_EXPR_IS_IMPL(EXPR, TYPE, FAILURE)                                                       \
[&]<typename TTS_T, typename TTS_R>(::tts::type<TTS_T>, ::tts::type<TTS_R>)                         \
{                                                                                                   \
  if constexpr( std::is_same_v<TTS_T,TTS_R> )                                                       \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE (   "Type: "  << TTS_STRING(TTS_REMOVE_PARENS(EXPR))  << " is not the same as "         \
                          << TTS_STRING(TTS_REMOVE_PARENS(TYPE)) << " because "                     \
                          << ::tts::typename_<TTS_T> << " is not " << ::tts::typename_<TTS_R>       \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(::tts::type<decltype(TTS_REMOVE_PARENS(EXPR))>{}, ::tts::type<TTS_REMOVE_PARENS(TYPE)>{})         \

#define TTS_EXPECT_COMPILES_IMPL(EXPR, ...)                                                         \
[&]( TTS_ARG(__VA_ARGS__) )                                                                         \
{                                                                                                   \
  if constexpr( requires TTS_REMOVE_PARENS(EXPR) )                                                  \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    TTS_FAIL(     "Expression: " << TTS_STRING(TTS_REMOVE_PARENS(EXPR))                             \
              <<  " does not compile as expected."                                                  \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(__VA_ARGS__)                                                                                      \

#define TTS_EXPECT_COMPILES(...) TTS_VAL(TTS_EXPECT_COMPILES_IMPL TTS_REVERSE(__VA_ARGS__) )
#define TTS_EXPECT_NOT_COMPILES_IMPL(EXPR, ...)                                                     \
[&]( TTS_ARG(__VA_ARGS__) )                                                                         \
{                                                                                                   \
  if constexpr( !(requires TTS_REMOVE_PARENS(EXPR)) )                                               \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    TTS_FAIL("Expression: " << TTS_STRING(TTS_REMOVE_PARENS(EXPR)) << " compiles unexpectedly." );  \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(__VA_ARGS__)                                                                                      \

#define TTS_EXPECT_NOT_COMPILES(...) TTS_VAL(TTS_EXPECT_NOT_COMPILES_IMPL TTS_REVERSE(__VA_ARGS__))
#define TTS_THROW_IMPL(EXPR, EXCEPTION, FAILURE)                                                    \
[&]()                                                                                               \
{                                                                                                   \
  bool tts_caught = false;                                                                          \
                                                                                                    \
  try                 { EXPR; }                                                                     \
  catch(EXCEPTION&  ) { tts_caught = true; }                                                        \
  catch(...)          { }                                                                           \
                                                                                                    \
  if(tts_caught)                                                                                    \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expected: " << TTS_STRING(EXPR) << " failed to throw " << TTS_STRING(EXCEPTION) );   \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}()
#define TTS_THROW(EXPR, EXCEPTION, ...)     TTS_THROW_ ## __VA_ARGS__ ( EXPR, EXCEPTION )
#define TTS_THROW_(EXPR, EXCEPTION)         TTS_THROW_IMPL(EXPR, EXCEPTION,TTS_FAIL)
#define TTS_THROW_REQUIRED(EXPR, EXCEPTION) TTS_THROW_IMPL(EXPR, EXCEPTION,TTS_FATAL)
#define TTS_NO_THROW_IMPL(EXPR,FAILURE)                                                             \
[&]()                                                                                               \
{                                                                                                   \
  bool tts_caught = false;                                                                          \
                                                                                                    \
  try        { EXPR; }                                                                              \
  catch(...) { tts_caught = true; }                                                                 \
                                                                                                    \
  if(!tts_caught)                                                                                   \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expected: "  << TTS_STRING(EXPR) << " throws unexpectedly." );                       \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}()
#define TTS_NO_THROW(EXPR, ...)     TTS_NO_THROW_ ## __VA_ARGS__ ( EXPR )
#define TTS_NO_THROW_(EXPR)         TTS_NO_THROW_IMPL(EXPR,TTS_FAIL)
#define TTS_NO_THROW_REQUIRED(EXPR) TTS_NO_THROW_IMPL(EXPR,TTS_FATAL)
#include <bit>
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <utility>
#if !defined(__cpp_lib_bit_cast)
# include <cstring>
#endif
namespace tts::detail
{
#if !defined(__cpp_lib_bit_cast)
  template <class To, class From>
  To bit_cast(const From& src) noexcept requires(sizeof(To) == sizeof(From))
  {
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
  }
#else
  using std::bit_cast;
#endif
  inline auto as_int(float a)   noexcept  { return bit_cast<std::int32_t>(a); }
  inline auto as_int(double a)  noexcept  { return bit_cast<std::int64_t>(a); }
  template<typename T> inline auto bitinteger(T a) noexcept
  {
    auto ia = as_int(a);
    using r_t = std::remove_cvref_t<decltype(ia)>;
    constexpr auto Signmask = r_t(1) << (sizeof(r_t)*8-1);
    return std::signbit(a) ?  Signmask-ia : ia;
  }
}
#include <type_traits>
#include <limits>
#include <cmath>
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
#define TTS_PRECISION_IMPL(LHS, RHS, N, UNIT, FUNC, PREC,FAILURE)                                   \
[&](auto lhs, auto rhs)                                                                             \
{                                                                                                   \
  auto r = FUNC (lhs,rhs);                                                                          \
                                                                                                    \
  if(r <= N)                                                                                        \
  {                                                                                                 \
    ::tts::global_runtime.pass(); return ::tts::logger{false};                                      \
  }                                                                                                 \
  else                                                                                              \
  {                                                                                                 \
    FAILURE ( "Expected: " << TTS_STRING(LHS) << " == " << TTS_STRING(RHS)                          \
                            << " but "                                                              \
                            << ::tts::as_string(lhs) << " == " << ::tts::as_string(rhs)             \
                            << " within " << std::setprecision(PREC) << std::fixed                  \
                            << r << std::defaultfloat                                               \
                            << " " << UNIT << " when "                                              \
                            << std::setprecision(PREC) <<  std::fixed                               \
                            << N << std::defaultfloat                                               \
                            << " " << UNIT << " was expected."                                      \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
}(LHS,RHS)                                                                                          \

#define TTS_PRECISION(L,R,N,U,F,P,...)      TTS_PRECISION_ ## __VA_ARGS__ (L,R,N,U,F,P)
#define TTS_PRECISION_(L,R,N,U,F,P)         TTS_PRECISION_IMPL(L,R,N,U,F,P,TTS_FAIL)
#define TTS_PRECISION_REQUIRED(L,R,N,U,F,P) TTS_PRECISION_IMPL(L,R,N,U,F,P,TTS_FATAL)
#define TTS_ABSOLUTE_EQUAL(L,R,N,...) TTS_PRECISION(L,R,N,"unit", ::tts::absolute_distance, 8, __VA_ARGS__ )
#define TTS_RELATIVE_EQUAL(L,R,N,...) TTS_PRECISION(L,R,N,"%"   , ::tts::relative_distance, 8, __VA_ARGS__ )
#define TTS_ULP_EQUAL(L,R,N,...)      TTS_PRECISION(L,R,N,"ULP" , ::tts::ulp_distance     , 2, __VA_ARGS__ )
#define TTS_IEEE_EQUAL(L,R,...)       TTS_ULP_EQUAL(L, R, 0, __VA_ARGS__ )
#include <type_traits>
namespace tts::detail
{
  template<typename T, typename U> struct failure
  {
    std::size_t index;
    T original;
    U other;
  };
}
#define TTS_ALL_IMPL(SEQ1,SEQ2,OP,N,UNIT,FAILURE)                                                   \
[](auto const& a, auto const& b)                                                                    \
{                                                                                                   \
  if( std::size(b) != std::size(a) )                                                                \
  {                                                                                                 \
    FAILURE ( "Expected: "  << TTS_STRING(SEQ1) << " == " << TTS_STRING(SEQ2)                       \
                            << " but sizes does not match: "                                        \
                            << "size(" TTS_STRING(SEQ1) ") = " << std::size(a)                      \
                            << " while size(" TTS_STRING(SEQ2) ") = " << std::size(b)               \
            );                                                                                      \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
                                                                                                    \
  auto ba = std::begin(a);                                                                          \
  auto bb = std::begin(b);                                                                          \
  auto ea = std::end(a);                                                                            \
                                                                                                    \
  std::vector < ::tts::detail::failure< std::remove_cvref_t<decltype(*ba)>                          \
                                      , std::remove_cvref_t<decltype(*bb)>                          \
                                      >                                                             \
              > failures;                                                                           \
  std::size_t i = 0;                                                                                \
                                                                                                    \
  while(ba != ea)                                                                                   \
  {                                                                                                 \
    if( OP(*ba,*bb) > N )  failures.push_back({i++,*ba,*bb});                                       \
    ba++;                                                                                           \
    bb++;                                                                                           \
  }                                                                                                 \
                                                                                                    \
  if( !failures.empty( ) )                                                                          \
  {                                                                                                 \
    FAILURE ( "Expected: "  << TTS_STRING(SEQ1) << " == " << TTS_STRING(SEQ2)                       \
                            << " but values differ by more than " << N << " "<< UNIT                \
            );                                                                                      \
                                                                                                    \
    for(auto f : failures)                                                                          \
      std::cout << "    @[" << f.index << "] : " << f.original << " and " << f.other                \
                << " differ by " << OP(f.original,f.other) << " " << UNIT << "\n";                  \
                                                                                                    \
    std::cout << "\n";                                                                              \
    return ::tts::logger{};                                                                         \
  }                                                                                                 \
                                                                                                    \
  ::tts::global_runtime.pass();                                                                     \
  return ::tts::logger{false};                                                                      \
}(SEQ1, SEQ2)                                                                                       \

#define TTS_ALL(L,R,F,N,U, ...)     TTS_ALL_ ## __VA_ARGS__ (L,R,F,N,U)
#define TTS_ALL_(L,R,F,N,U)         TTS_ALL_IMPL(L,R,F,N,U,TTS_FAIL)
#define TTS_ALL_REQUIRED(L,R,F,N,U) TTS_ALL_IMPL(L,R,F,N,U,TTS_FATAL)
#define TTS_ALL_ABSOLUTE_EQUAL(L,R,N,...) TTS_ALL(L,R, ::tts::absolute_distance,N,"unit", __VA_ARGS__ )
#define TTS_ALL_RELATIVE_EQUAL(L,R,N,...) TTS_ALL(L,R, ::tts::relative_distance,N,"%"   , __VA_ARGS__ )
#define TTS_ALL_ULP_EQUAL(L,R,N,...)      TTS_ALL(L,R, ::tts::ulp_distance     ,N,"ULP" , __VA_ARGS__ )
#define TTS_ALL_IEEE_EQUAL(S1,S2,...)     TTS_ALL_ULP_EQUAL(S1,S2,0, __VA_ARGS__)
#define TTS_ALL_EQUAL(L,R,...)            TTS_ALL_ABSOLUTE_EQUAL(L,R, 0 __VA_ARGS__ )
#include <iostream>
namespace tts::detail
{
  struct section_guard
  {
    int &       id;
    int const & section;
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
  std::cout << "[?] - For: " << ::tts::detail::current_test << "\n";                                \
  std::cout << "When      : " << STORY << std::endl;                                                \
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
