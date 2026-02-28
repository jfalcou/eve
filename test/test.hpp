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

namespace eve
{
  template<typename T, typename N>
  inline bool compare_equal(wide<T, N> const &l, wide<T, N> const &r)
  {
    return eve::all(l == r);
  }

  template<typename T>
  inline bool compare_equal(logical<T> const &l, logical<T> const &r)
  {
    if constexpr(eve::simd_value<T>)  return eve::all(l == r);
    else                              return l == r;
  }
}

namespace tts
{
  // Defined by TTS further down, forward-declared so the element-wise loops below can reach them.
  template<typename T, typename U> inline double ulp_check(T const& a, U const& b);
  template<typename T, typename U> inline double relative_check(T const& a, U const& b);

  //================================================================================================
  // v3 hooks on these by name: `if constexpr(requires { ulp_distance(a,b); })`. Declaring an
  // unconstrained generic here would satisfy that test for every type and hijack the fallback,
  // so only the EVE types are declared, and element-wise recursion goes back through v3's own
  // ulp_check / relative_check / absolute_check.
  //================================================================================================
  template<std::same_as<eve::float16_t> T> inline double ulp_distance(T const &l, T const &r)
  {
    return eve::convert(eve::ulpdist(l, r), eve::as<double> ());
  }

  template<typename T, typename N>
  inline double ulp_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, ulp_check(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double ulp_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : std::numeric_limits<double>::infinity();
  }

  template<typename T, typename N>
  inline bool ieee_equal(eve::wide<T, N> const &a, eve::wide<T, N> const &b)
  {
    for(auto i = 0; i < a.size(); ++i)
    {
      if( (a.get(i) != b.get(i)) && !(eve::is_nan(a.get(i)) && eve::is_nan(b.get(i))))
        return false;
    }
    return true;
  }

  template<typename T>
  inline bool ieee_equal(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r);
  }

  template<typename T, typename N>
  inline double relative_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_dr = 0;
    for(auto i = 0; i < l.size(); ++i)
    {
      if constexpr(eve::integral_value<T>)
      {
        auto dr =  static_cast<double>(relative_check(T(l.get(i)), T(r.get(i))));
        max_dr = (dr > max_dr) ? dr : max_dr;
      }
      else
      {
        auto dr = static_cast<double>(eve::reldist(T(l.get(i)), T(r.get(i))));
        max_dr = (dr > max_dr) ? dr : max_dr;
      }
    }
    return max_dr;
  }

  template<typename T>
  inline double relative_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
  }

  template<typename T, typename N>
  inline double absolute_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_d = 0;
    for(auto i = 0; i < l.size(); ++i)
    {
      auto d = static_cast<double>(eve::dist(T(l.get(i)), T(r.get(i))));
      max_d = (d > max_d) ? d : max_d;
    }
    return max_d;
  }

  template<typename T>
  inline double absolute_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
  }

  template<std::same_as<eve::float16_t> T> inline double absolute_distance(T const &l, T const &r)
  {
    return static_cast<double>(eve::dist(l, r));
  }
}

namespace tts
{

  template<typename T, typename V> auto as_value(V const&);

  template<typename T, typename V>
  auto as_value(V const& v)
  requires( requires { v(eve::as<T>{}); } )
  {
    return v(eve::as<T>{});
  }
}

#include <tts/tts.hpp>

//==================================================================================================
// TTS v2's amalgamated header pulled these in; v3 does not, and the suite has always leant on
// them being there. Kept in one place rather than sprinkled over seven hundred test files.
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
  // v3 renders a streamed value through as_text, which only knows numbers, ranges and its own
  // types. The suite also logs index constants and shuffle patterns; both stream to an ostream.
  //================================================================================================
  template<typename T, T V> auto to_text(std::integral_constant<T,V> const&)
  {
    std::ostringstream os; os << V; return ::tts::text(os.str().c_str());
  }

  template<std::ptrdiff_t... I> auto to_text(eve::pattern_t<I...> const& p)
  {
    std::ostringstream os; os << p; return ::tts::text(os.str().c_str());
  }

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


namespace eve::_
{
  template<typename T, typename V> auto as_value(callable_object<V> const& v)
  {
    return v(eve::as<T>{});
  }
}



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
  //================================================================================================
  //================================================================================================
  // v3 passes generators as non-type template parameters, which requires a structural type.
  // Deriving from the closure is not: the type carries the lambda, the object stores nothing.
  //================================================================================================
  template<typename F> struct constant
  {
    constexpr constant(F) {}
    template<typename D> constexpr auto operator()(D d) const { return F{}(d); }
  };

  template<typename T, typename V> auto as_value(constant<V> const& v)
  {
    return v(eve::as<T>{});
  }

  //================================================================================================
  // v3 funnels a generator bound through convert_as, which static_casts it to the tested type.
  // A constant is a per-type recipe, not a value: it has to be evaluated against T instead.
  //================================================================================================
  template<typename T, typename V> auto convert_as(V const& v, type<T> const&)
  requires( requires { v(eve::as<T>{}); } )
  {
    auto r = v(eve::as<T>{});
    // A recipe is free to answer in whatever type it finds natural - `-128 : 0` is an int even
    // when T is double. Both bounds of a generator must land on T or v3 cannot deduce it.
    if constexpr(std::convertible_to<decltype(r), T>) return static_cast<T>(r);
    else                                             return r;
  }

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
  // v3 unwraps a generated type through tts::base_type before sizing its integer counterpart.
  // Left unspecialized it would size against sizeof(wide<T,N>) rather than sizeof(T).
  //================================================================================================
  template<typename T, typename N> struct base_type<eve::wide<T,N>>    { using type = T; };
  template<typename T, typename N> struct boolean_type<eve::wide<T,N>>  { using type = eve::logical<eve::wide<T,N>>; };
  template<typename T>             struct boolean_type<eve::logical<T>> { using type = eve::logical<T>; };
  template<typename T> requires(std::is_arithmetic_v<T> && !std::is_same_v<T,bool>)
  struct boolean_type<T> { using type = eve::logical<T>; };
  template<typename T>             struct base_type<eve::logical<T>>   { using type = base_type_t<T>; };

  //================================================================================================
  // v3 owns the name `random_bits` and gives it the other meaning: a full-width bit pattern.
  // What the shift tests need is a valid shift count, which is what EVE's generator always was.
  //================================================================================================
  struct random_shift
  {
    template<typename D> auto operator()(tts::type<D>, auto...) const
    {
      using i_t = eve::as_integer_t<eve::element_type_t<D>>;
      return tts::random_value<i_t>(0, 8*sizeof(i_t)-1);
    }
  };

  //================================================================================================
  // v3 ships its own limits(), but it is built on std::numeric_limits, which knows nothing of
  // eve::wide. Constrained on EVE values so it wins over v3's for those and only those.
  //================================================================================================
  template<eve::value T>
  inline auto limits(tts::type<T>)
  {
    if constexpr(eve::floating_value<T>)
    {
      struct values
      {
        using type  = T;
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

      return values{};
    }
    else
    {
      struct values
      {
        using type  = T;
        type valmax = eve::valmax(eve::as<type>{});
        type valmin = eve::valmin(eve::as<type>{});
      };

      return values{};
    }
  }

  //================================================================================================
  // Customization point for argument building
  //================================================================================================
  template<eve::simd_value T>
  auto produce(type<T> const&, auto g, auto... args)
  {
    using e_t = eve::element_type_t<T>;
    auto data = produce(type<std::array<e_t,T::size()>>{},g, args...);

    using v_t = typename decltype(data)::value_type;
    eve::as_wide_t<v_t, eve::cardinal_t<T>> that = eve::load(&data[0], eve::cardinal_t<T>{});

    return poison(that);
  }

  auto produce(type<eve::float16_t> const&, auto g, auto... args)
  {
    auto data = produce(type<float>{}, g, args...);
    if constexpr (eve::logical_value<decltype(data)>)
    {
      return static_cast<eve::logical<eve::float16_t>>(data);
    }
    else
    {
      return static_cast<eve::float16_t>(data);
    }
  }

  template<std::ptrdiff_t N>
  auto produce(type<eve::wide<eve::float16_t, eve::fixed<N>>> const&, auto g, auto... args)
  {
    auto arr = produce(type<std::array<eve::float16_t, N>>{}, g, args...);
    return poison(eve::load(arr.data(), eve::fixed<N>{}));
  }


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
