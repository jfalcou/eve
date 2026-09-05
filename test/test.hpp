//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION eve_entry_point

//==================================================================================================
// EVE Specific testing overloads
//==================================================================================================
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/module/core.hpp>
#include <eve/traits.hpp>
#include <eve/wide.hpp>

#include <tts/tts.hpp>

//==================================================================================================
// The suite leans on these everywhere. Kept in one place rather than sprinkled over seven
// hundred test files.
//==================================================================================================
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace tts
{
  //================================================================================================
  // A wide and a logical answer a comparison lane by lane, so equality is the whole register being
  // equal rather than the register the operator hands back. Only the same-type pairs are given:
  // comparing a wide against something else keeps the built-in path.
  //
  // Neither carries `less`. The free functions these replace defined none either, so ordering two
  // registers has never compiled, and settling here what `a < b` means for a register would be
  // deciding it in passing.
  //================================================================================================
  template<typename T, typename N>
  struct comparison<eve::wide<T, N>, eve::wide<T, N>>
  {
    using w_t = eve::wide<T, N>;

    static bool equal(w_t const& l, w_t const& r) { return eve::all(l == r); }
  };

  template<typename T>
  struct comparison<eve::logical<T>, eve::logical<T>>
  {
    using l_t = eve::logical<T>;

    static bool equal(l_t const& l, l_t const& r)
    {
      if constexpr(eve::simd_value<T>)  return eve::all(l == r);
      else                              return l == r;
    }
  };

  //================================================================================================
  // EVE measures distances its own way on the three shapes it adds. Specializing the trait rather
  // than overloading a free function means a name that no longer matches is a compilation error
  // instead of a silent fall back onto the built-in path.
  //================================================================================================
  template<typename T, typename N>
  struct precision<eve::wide<T, N>>
  {
    using w_t = eve::wide<T, N>;

    static double ulp(w_t const& l, w_t const& r)
    {
      double max_ulp = 0;
      for(auto i = 0; i < l.size(); ++i)
        max_ulp = std::max(max_ulp, precision<T>::ulp(T(l.get(i)), T(r.get(i))));
      return max_ulp;
    }

    // Every lane goes through precision<T>::relative, including the floating ones, which used to
    // call eve::reldist. The two now compute the same quotient, but going through the trait keeps
    // one implementation of the convention rather than two that only happened to agree.
    static double relative(w_t const& l, w_t const& r)
    {
      double max_dr = 0;
      for(auto i = 0; i < l.size(); ++i)
      {
        auto dr = precision<T>::relative(T(l.get(i)), T(r.get(i)));
        max_dr = (dr > max_dr) ? dr : max_dr;
      }
      return max_dr;
    }

    // Through precision<T> rather than eve::dist, for the same reason as relative: dist reports an
    // unordered pair as allbits, and a NaN loses `(d > max_d)`, so a lane that could never match
    // contributed nothing at all. The built-in path answers infinity instead.
    static double absolute(w_t const& l, w_t const& r)
    {
      double max_d = 0;
      for(auto i = 0; i < l.size(); ++i)
      {
        auto d = precision<T>::absolute(T(l.get(i)), T(r.get(i)));
        max_d = (d > max_d) ? d : max_d;
      }
      return max_d;
    }

    static bool ieee(w_t const& a, w_t const& b)
    {
      for(auto i = 0; i < a.size(); ++i)
        if((a.get(i) != b.get(i)) && !(eve::is_nan(a.get(i)) && eve::is_nan(b.get(i))))
          return false;
      return true;
    }
  };

  template<typename T>
  struct precision<eve::logical<T>>
  {
    using l_t = eve::logical<T>;

    static bool same(l_t const& l, l_t const& r) { return comparison<l_t>::equal(l, r); }

    static double ulp(l_t const& l, l_t const& r)
    {
      return same(l, r) ? 0. : std::numeric_limits<double>::infinity();
    }
    static double relative(l_t const& l, l_t const& r) { return same(l, r) ? 0. : 1.; }
    static double absolute(l_t const& l, l_t const& r) { return same(l, r) ? 0. : 1.; }
    static bool   ieee    (l_t const& l, l_t const& r) { return same(l, r); }
  };

  //================================================================================================
  // float16_t defines all four members. relative and ieee take the built-in path in double rather
  // than inheriting it: the built-in branches on std::is_floating_point_v, false for _Float16 in
  // C++20, so an inherited member would refuse to compile. None of the three shapes inherits, for
  // the same reason — no built-in member works on a type the standard traits do not recognize.
  //================================================================================================
  template<>
  struct precision<eve::float16_t>
  {
    using f_t = eve::float16_t;

    static double ulp(f_t const& l, f_t const& r)
    {
      return eve::convert(eve::ulpdist(l, r), eve::as<double>());
    }
    // Through the built-in path in double, like relative: eve::dist answers allbits on an unordered
    // pair, which the caller's maximum would drop instead of reporting.
    static double absolute(f_t const& l, f_t const& r)
    {
      return _::builtin_precision<double>::absolute( eve::convert(l, eve::as<double>())
                                                   , eve::convert(r, eve::as<double>())
                                                   );
    }

    // A relative distance is a ratio, so it is worth more than half precision can hold: the two
    // values are exact in double, and the quotient is taken there. Measured in half, a ratio of the
    // size the tolerances use would be rounded as coarsely as the tolerance itself.
    static double relative(f_t const& l, f_t const& r)
    {
      return _::builtin_precision<double>::relative( eve::convert(l, eve::as<double>())
                                                   , eve::convert(r, eve::as<double>())
                                                   );
    }

    static bool ieee(f_t const& l, f_t const& r)
    {
      return _::builtin_precision<double>::ieee( eve::convert(l, eve::as<double>())
                                               , eve::convert(r, eve::as<double>())
                                               );
    }
  };

  //================================================================================================
  // Without these, TTS falls back on a byte dump and a failure on a wide<double> reads as sixteen
  // hex pairs. Specializing the trait rather than overloading to_text means a shape TTS cannot
  // render is a compilation error instead of that dump.
  //================================================================================================
  template<typename T, typename N> struct display<eve::wide<T, N>>
  {
    static text render(eve::wide<T, N> const& v)
    {
      text that("(");
      for(std::ptrdiff_t i = 0; i < v.size(); ++i)
      {
        if(i) that += ", ";
        that += as_text(T(v.get(i)));
      }
      return that + ")";
    }
  };

  // _Float16 is not std::floating_point in C++20, so TTS has no branch for it and falls back on the
  // byte dump. Rendered through double, which holds every half exactly.
  template<> struct display<eve::float16_t>
  {
    static text render(eve::float16_t const& v) { return as_text(eve::convert(v, eve::as<double>())); }
  };

  template<typename T> struct display<eve::logical<T>>
  {
    static text render(eve::logical<T> const& v)
    {
      if constexpr(eve::simd_value<T>)
      {
        text that("(");
        for(std::ptrdiff_t i = 0; i < v.size(); ++i)
        {
          if(i) that += ", ";
          that += v.get(i) ? "true" : "false";
        }
        return that + ")";
      }
      else return text(v.value() ? "true" : "false");
    }
  };

  //================================================================================================
  // The suite also logs index constants and shuffle patterns; both stream to an ostream.
  //================================================================================================
  template<typename T, T V> struct display<std::integral_constant<T, V>>
  {
    static text render(std::integral_constant<T, V> const&) { return as_text(T(V)); }
  };

  template<std::ptrdiff_t... I> struct display<eve::pattern_t<I...>>
  {
    static text render(eve::pattern_t<I...> const& p)
    {
      std::ostringstream os; os << p; return text(os.str().c_str());
    }
  };
}


//==================================================================================================
// EVE Specific types
//==================================================================================================
#include <array>

namespace eve::test
{
  template<typename T, typename Indexes> struct to_wide;

  template<typename T, std::size_t... N>
  struct to_wide<T, std::index_sequence<N...>>
  {
    using type = ::tts::types<as_wide_t<T,eve::fixed<1ULL << N>>...>;
  };

  template<typename T, typename I>
  using to_wide_t = typename to_wide<T,I>::type;

  template<typename L> struct wides;
  template<typename... Ts> struct wides<::tts::types<Ts...>>
  {
    // Precomputed # of repetitions based on ABI and sizeof(T)
    static constexpr std::array<std::size_t,9> cardinals()
    {
      // This is a precomputed map of the maximum number of cardinal to generate depending
      // on the current ABI bits size. This prevents us to use std::bit_width and other complex
      // computations.
      switch(eve::current_abi_type::bits)
      {
        case 64 : return {0,5,4,0,3,0,0,0,2};
        case 128: return {0,6,5,0,4,0,0,0,3};
        case 256: return {0,7,6,0,5,0,0,0,4};
        case 512: return {0,8,7,0,6,0,0,0,5};
        case 1024: return {0, 9, 8, 0, 7, 0, 0, 0, 6};
        case 2048: return {0, 10, 9, 0, 8, 0, 0, 0, 7};
        default : return {};
      };
    };

    using type_all =
        tts::concatenate<to_wide_t<Ts, std::make_index_sequence<cardinals()[sizeof(Ts)]>>...>;

    template<typename Type> struct rvv_pred
    {
      static consteval bool is_enabled()
      {
        // For vlen = 128, we test every type up to lmul==4
        constexpr auto bit_size = 512;
        if( sizeof(Type) <= bit_size / 8 ) return true;
        using scalar_t                   = typename Type::value_type;
        constexpr auto cardinal          = eve::cardinal_v<Type>;
        constexpr auto expected_cardinal = eve::expected_cardinal_v<scalar_t>;
        // and double, int64, uint64
        if( sizeof(scalar_t) != 8 ) return false;
        // for expected cardinal (lmul==8)
        if( expected_cardinal == cardinal ) return true;
        // for combined type
        if( 2 * expected_cardinal == cardinal ) return true;
        return false;
      }

      static constexpr bool value = is_enabled();
    };
#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
    using type = tts::filter<rvv_pred, type_all>::type;
#else
    using type                 = type_all;
#endif
  };

  // Prevent calling remove_cvref_t
  template<typename L> struct wides<L const>  : wides<L>  {};
  template<typename L> struct wides<L&>       : wides<L>  {};

  template<typename L> using wides_t = typename wides<L>::type;

  using sizes = tts::types< std::integral_constant<int,    8>
                          , std::integral_constant<int,   16>
                          , std::integral_constant<int,   32>
                          , std::integral_constant<int,   64>
                          , std::integral_constant<int,  128>
                          , std::integral_constant<int,  256>
                          , std::integral_constant<int,  512>
                          , std::integral_constant<int, 1024>
                          >;

  using cardinals = tts::types< eve::fixed<   1>
                              , eve::fixed<   2>
                              , eve::fixed<   4>
                              , eve::fixed<   8>
                              , eve::fixed<  16>
                              , eve::fixed<  32>
                              , eve::fixed<  64>
                              , eve::fixed< 128>
                              , eve::fixed< 256>
                              , eve::fixed< 512>
                              , eve::fixed<1024>
                              >;

  EVE_FORCEINLINE auto is_near(auto a,  auto b){
    return eve::if_else( a < b
                       , (eve::next(a) == b) && (eve::prev(b) == a)
                       , a == b);
  }
}

namespace eve::test::scalar
{
  using ieee_reals        = ::tts::real_types;
  using ieee_reals_wf16   = ::tts::concatenate<::tts::real_types, ::tts::types<eve::float16_t>>;
  using signed_integers   = ::tts::int_types;
  using signed_types      = ::tts::signed_types;
  using signed_types_wf16 = ::tts::concatenate<::tts::signed_types, ::tts::types<eve::float16_t>>;
  using signed_integers   = ::tts::int_types;
  using unsigned_integers = ::tts::uint_types;
  using integers          = ::tts::integral_types;
  using integers_wf16     = ::tts::concatenate<::tts::integral_types, ::tts::types<eve::float16_t>>;
  using all_types         = ::tts::arithmetic_types;
  using all_types_wf16    = ::tts::concatenate<::tts::arithmetic_types, ::tts::types<eve::float16_t>>;
}

namespace eve::test::simd
{
  using ieee_reals        = eve::test::wides<::tts::real_types>::type;
  using ieee_reals_wf16   = eve::test::wides<tts::concatenate<::tts::real_types, ::tts::types<eve::float16_t>>>::type;
  using signed_integers   = eve::test::wides<::tts::int_types>::type;
  using signed_types      = eve::test::wides<::tts::signed_types>::type;
  using signed_types_wf16 = eve::test::wides<::tts::concatenate<::tts::signed_types, ::tts::types<eve::float16_t>>>::type;
  using signed_integers   = eve::test::wides<::tts::int_types>::type;
  using unsigned_integers = eve::test::wides<::tts::uint_types>::type;
  using integers          = eve::test::wides<::tts::integral_types>::type;
  using integers_wf16     = eve::test::wides<eve::test::scalar::integers_wf16>::type;
  using all_types         = eve::test::wides<::tts::arithmetic_types>::type;
  using all_types_wf16    = eve::test::wides<eve::test::scalar::all_types_wf16>::type;
}

//==================================================================================================
// EVE Data generators
//==================================================================================================


namespace tts
{

  template<typename T> struct bunch
  {
    template<typename L> struct make;
    template<typename... Ls> struct make<tts::types<Ls...>>
    {
      using type = tts::types<std::array<Ls,10>...>;
    };

    using types_list = typename make<T>::type;
  };

  //================================================================================================
  // Constant wrapper
  //
  // A generator has to be structural: the type carries the lambda, the object stores nothing.
  //================================================================================================
  template<typename F> struct constant
  {
    constexpr constant(F) {}
    template<typename D> constexpr auto operator()(D d) const { return F{}(d); }
  };

  //================================================================================================
  // An eve constant is a per-type recipe: evaluate it against T rather than casting it. The
  // constraint alone makes this the better match, so anything not callable with an eve::as keeps
  // the plain cast.
  //================================================================================================
  template<typename T, typename V> requires( requires(V v) { v(eve::as<T>{}); } )
  struct conversion<T, V>
  {
    static auto from(V const& v)
    {
      auto r = v(eve::as<T>{});
      // Both bounds of a generator must land on T. A recipe answers in whatever type it finds
      // natural, and `-128 : 0` is an int even when T is double.
      if constexpr(std::convertible_to<decltype(r), T>) return static_cast<T>(r);
      else                                              return r;
    }
  };

  //================================================================================================
  // Poison wide data when using sub-sized types
  //================================================================================================
  template<eve::simd_value W> auto poison(W data)
  {
    using v_t = eve::element_type_t<W>;

    // Add garbage at the end of sub-native registers
    // For emulated type, there is no such gap so we don't do anything
    if constexpr( (W::size() < eve::fundamental_cardinal_v<v_t>) && !eve::has_emulated_abi_v<W> )
    {
      using p_t   = eve::as_arithmetic_t<eve::as_integer_t<v_t, unsigned>>;
      using ftype = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;

      ftype these(data.storage());

      // Compute a recognizable filler
      for(std::ptrdiff_t i=data.size();i<these.size();++i)
      {
        p_t filler = eve::constant<p_t, static_cast<p_t>(0xDEADBEEFBABE0000)>() + p_t(i);
        these.set(i, eve::bit_cast(filler,eve::as<v_t>()) );
      }

      return W(these.storage());
    }
    else
    {
      return data;
    }
  }

  //================================================================================================
  // A wide has to name its element here, or its integer counterpart gets sized against
  // sizeof(wide<T,N>) rather than sizeof(T).
  //================================================================================================
  template<typename T, typename N> struct base_type<eve::wide<T,N>>    { using type = T; };
  template<typename T, typename N> struct boolean_type<eve::wide<T,N>>  { using type = eve::logical<eve::wide<T,N>>; };
  template<typename T>             struct boolean_type<eve::logical<T>> { using type = eve::logical<T>; };
  template<typename T> requires(std::is_arithmetic_v<T> && !std::is_same_v<T,bool>)
  struct boolean_type<T> { using type = eve::logical<T>; };
  template<typename T>             struct base_type<eve::logical<T>>   { using type = base_type_t<T>; };

  //================================================================================================
  // std::numeric_limits knows nothing of eve::wide and static_asserts on it. Every member here
  // comes from an eve constant, which answers for a register as readily as for a scalar.
  //================================================================================================
  template<typename T> requires(eve::floating_value<T>)
  struct limits_set<T>
  {
    using type = T;

    type nan            = eve::nan           (eve::as<type>{});
    type inf            = eve::inf           (eve::as<type>{});
    type minf           = eve::minf          (eve::as<type>{});
    type mzero          = eve::mzero         (eve::as<type>{});
    type zero           = eve::zero          (eve::as<type>{});
    type maxflint       = eve::maxflint      (eve::as<type>{});
    type valmax         = eve::valmax        (eve::as<type>{});
    type valmin         = eve::valmin        (eve::as<type>{});
    type mindenormal    = eve::mindenormal   (eve::as<type>{});
    type smallestposval = eve::smallestposval(eve::as<type>{});
    type mone           = eve::mone          (eve::as<type>{});
    type one            = eve::one           (eve::as<type>{});
  };

  template<typename T> requires(eve::value<T> && !eve::floating_value<T>)
  struct limits_set<T>
  {
    using type = T;

    type valmax = eve::valmax(eve::as<type>{});
    type valmin = eve::valmin(eve::as<type>{});
  };

  //================================================================================================
  // Customization point for argument building. A register is drawn as an array of its element type
  // and loaded, so a generator only ever has to answer for a scalar.
  //================================================================================================
  template<typename T> requires(eve::simd_value<T>)
  struct generation<T>
  {
    static auto make(auto g, auto... args)
    {
      using e_t = eve::element_type_t<T>;
      auto data = produce(type<std::array<e_t,T::size()>>{}, g, args...);

      using v_t = typename decltype(data)::value_type;
      eve::as_wide_t<v_t, eve::cardinal_t<T>> that = eve::load(&data[0], eve::cardinal_t<T>{});

      return poison(that);
    }
  };

  //================================================================================================
  // float16 has to be drawn against its own bounds. Falling through to float evaluates
  // `valmin`/`valmax` against float, so the draw spans +/-3.4e38 and every narrowing to float16
  // lands on infinity.
  //
  // The overload this replaces named randoms in its signature. The trait keys on the type being
  // built, so the branch moves inside the member, and tts::is_randoms_v keeps it a question about
  // the generator's type rather than about the members it happens to carry.
  //================================================================================================
  template<>
  struct generation<eve::float16_t>
  {
    static auto make(auto g, auto... args)
    {
      if constexpr( tts::is_randoms_v<decltype(g)> )
      {
        return static_cast<eve::float16_t>
        ( tts::random_value<float>
          ( static_cast<float>(convert_as(g.mini, type<eve::float16_t>{}))
          , static_cast<float>(convert_as(g.maxi, type<eve::float16_t>{}))
          )
        );
      }
      else
      {
        auto data = produce(type<float>{}, g, args...);
        if constexpr(eve::logical_value<decltype(data)>)
          return static_cast<eve::logical<eve::float16_t>>(data);
        else
          return static_cast<eve::float16_t>(data);
      }
    }
  };

  //================================================================================================
  // More specialized than the simd_value case above, and it has to be: the generic one would draw
  // an array of float16 through the scalar path, which is right, then load it as a wide of the
  // element type the array reports, which is where the two part company.
  //================================================================================================
  template<std::ptrdiff_t N>
  struct generation<eve::wide<eve::float16_t, eve::fixed<N>>>
  {
    static auto make(auto g, auto... args)
    {
      auto arr = produce(type<std::array<eve::float16_t, N>>{}, g, args...);
      return poison(eve::load(arr.data(), eve::fixed<N>{}));
    }
  };


  template<typename Fn, typename Wm, typename... Args>
  auto map(Fn&& f, Wm&& wm, Args&&... args) -> eve::as_wide_t<decltype(f(eve::_::get_at(wm, 0), eve::_::get_at(args, 0)...)), eve::cardinal_t<Wm>>
  {
    using r_t = eve::as_wide_t<decltype(f(eve::_::get_at(wm, 0), eve::_::get_at(args, 0)...)), eve::cardinal_t<Wm>>;
    auto call_f = [&](auto idx) { return f(eve::_::get_at(wm, idx), eve::_::get_at(args, idx)...); };
    return eve::_::apply<eve::cardinal_v<Wm>>([&](auto... I) { return r_t{call_f(I)...}; });
  }

  template<typename L1> struct rewrap;
  template<typename... Ts>
  struct rewrap<kumi::tuple<Ts...>> { using type = tts::types<Ts...>; };

  template<typename L1, typename L2> struct cartesian;

  template<typename... T1s, typename... T2s>
  struct cartesian<tts::types<T1s...>, tts::types<T2s...>>
  {
    using base       = kumi::result::cartesian_product_t<kumi::tuple<T1s...>, kumi::tuple<T2s...>>;
    using types_list = typename rewrap<base>::type;
  };

  template<typename Types> struct cartesian_square;

  template<typename... Types>
  struct cartesian_square<tts::types<Types...>>
  {
    using base       = kumi::result::cartesian_product_t<kumi::tuple<Types...>, kumi::tuple<Types...>>;
    using types_list = typename rewrap<base>::type;
  };
}

//==================================================================================================
// EVE TTS Entrypoint
//==================================================================================================
#include <iostream>

int main(int argc, char const **argv)
{
  ::tts::initialize(argc,argv);
  auto seed = ::tts::random_seed(18102008);
#ifdef NDEBUG
  constexpr auto assert_status = "Disabled";
#else
  constexpr auto assert_status = "Enabled";
#endif

  constexpr auto fp16_status = eve::_::supports_fp16_vector_ops ? "Full" :
                              (eve::_::supports_fp16_vector_conversion ? "Conversion" : "Emulated");

  std::cout << "[EVE] - Target: " << eve::current_api
            << " - Assertions: "  << assert_status
            << " - FP16: "        << fp16_status
            << " - PRNG Seed: "   << seed
            << std::endl;

  eve_entry_point(argc, argv);
  return tts::report(0,0);
}

namespace tts
{

  //==================================================================================================
  // default relative precsion
  //==================================================================================================
  template <typename T> inline double constexpr prec()
  {
    if constexpr( sizeof(eve::element_type_t<T>) == 2)
      return 1.0e-1;
    if constexpr( sizeof(eve::element_type_t<T>) == 4)
      return 1.0e-3;
    else
      return 1.0e-6;
  }

  template <typename T> inline double constexpr prec(double f,  double d)
  {
    if constexpr( sizeof(eve::element_type_t<T>) == 4) return f; else return d;
  }

  template <typename T> inline double constexpr prec(double e, double f,  double d)
  {
    if constexpr( sizeof(eve::element_type_t<T>) == 2)
      return e;
    if constexpr( sizeof(eve::element_type_t<T>) == 4)
      return f;
    else
      return d;
  }
}
