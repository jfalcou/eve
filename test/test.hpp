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
  template<typename T, typename U>
  double ulp_distance(T const &l, U const &r);

  template<typename T, typename U>
  double relative_distance(T const &l, U const &r);

  template<typename T, typename U>
  double absolute_distance(T const &l, U const &r);

  template<typename T, typename N>
  inline double ulp_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, ulp_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double ulp_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : std::numeric_limits<double>::infinity();
  }

  template<typename T, typename N>
  inline bool is_ieee_equal(eve::wide<T, N> const &a, eve::wide<T, N> const &b)
  {
    for(auto i = 0; i < a.size(); ++i)
    {
      if( (a.get(i) != b.get(i)) && !(eve::is_nan(a.get(i)) && eve::is_nan(b.get(i))))
        return false;
    }
    return true;
  }

  template<typename T>
  inline bool is_ieee_equal(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r);
  }

  template<typename T, typename N>
  inline double relative_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, relative_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double relative_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
  }

  template<typename T, typename N>
  inline double absolute_distance(eve::wide<T, N> const &l, eve::wide<T, N> const &r)
  {
    double max_ulp = 0;
    for(auto i = 0; i < l.size(); ++i)
      max_ulp = std::max(max_ulp, absolute_distance(T(l.get(i)), T(r.get(i))));

    return max_ulp;
  }

  template<typename T>
  inline double absolute_distance(eve::logical<T> const &l, eve::logical<T>const &r)
  {
    return eve::compare_equal(l,r) ? 0. : 1;
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
        case 1024: return {0, 6, 5, 0, 4, 0, 0, 0, 3};
        // Unfortunately, this is too long on simulation
        // case 1024:  return {0,9,8,0,7,0,0,0,6};
        default : return {};
      };
    };

    using type = tts::concatenate_t < to_wide_t < Ts
                                                , std::make_index_sequence<cardinals()[sizeof(Ts)]>
                                                >...
                                    >;
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
  using signed_integers   = ::tts::int_types;
  using signed_types      = ::tts::signed_types;
  using signed_integers   = ::tts::int_types;
  using unsigned_integers = ::tts::uint_types;
  using integers          = ::tts::integral_types;
  using all_types         = ::tts::arithmetic_types;
}

namespace eve::test::simd
{
  using ieee_reals        = eve::test::wides<::tts::real_types>::type;
  using signed_integers   = eve::test::wides<::tts::int_types>::type;
  using signed_types      = eve::test::wides<::tts::signed_types>::type;
  using signed_integers   = eve::test::wides<::tts::int_types>::type;
  using unsigned_integers = eve::test::wides<::tts::uint_types>::type;
  using integers          = eve::test::wides<::tts::integral_types>::type;
  using all_types         = eve::test::wides<::tts::arithmetic_types>::type;
}

//==================================================================================================
// EVE Data generators
//==================================================================================================


namespace eve::detail
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
  template<typename F> struct constant : F
  {
    constant(F f) : F(f) {}
    using F::operator();
  };

  template<typename T, typename V> auto as_value(constant<V> const& v)
  {
    return v(eve::as<T>{});
  }

  //================================================================================================
  // Poison wide data when using sub-sized types
  //================================================================================================
  template<eve::simd_value W> auto poison(W data)
  {
    using v_t = eve::element_type_t<W>;

    // Add garbage at the end of sub-native registers
    // For emulated type, there is no such gap so we don't do anything
    if constexpr( (W::size() < eve::fundamental_cardinal_v<v_t>)&&!eve::has_emulated_abi_v<W>
                  && eve::current_api != eve::rvv )
    {
      using p_t   = eve::as_arithmetic_t<eve::as_integer_t<v_t, unsigned>>;
      using ftype = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;

      ftype these(data.storage());

      // Compute a recognizable filler
      for(std::ptrdiff_t i=data.size();i<these.size();++i)
      {
        p_t filler = eve::Constant<p_t, static_cast<p_t>(0xDEADBEEFBABE0000)>() + p_t(i);
        these.set(i, eve::bit_cast(filler,eve::as<v_t>()) );
      }

      return W(these.storage());
    }
    else if constexpr( (W::size() < eve::fundamental_cardinal_v<v_t>)&&!eve::has_emulated_abi_v<W>
                       && eve::current_api == eve::rvv )
    {
      // for riscv we can not just cast ftypes from storage type, so use bitcast.
      using p_t   = eve::as_arithmetic_t<eve::as_integer_t<v_t, unsigned>>;
      using ftype = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;

      ftype these = eve::bit_cast(data, eve::as<ftype> {});

      // Compute a recognizable filler
      for( std::ptrdiff_t i = data.size(); i < these.size(); ++i )
      {
        p_t filler = eve::Constant<p_t, static_cast<p_t>(0xDEADBEEFBABE0000)>() + p_t(i);
        these.set(i, eve::bit_cast(filler, eve::as<v_t>()));
      }

      return eve::bit_cast(these, eve::as<W> {});
    }
    else
    {
      return data;
    }
  }

  //================================================================================================
  // Customization point for argument building
  //================================================================================================
  template<eve::simd_value T>
  auto produce(type<T> const&, auto g, auto& rng, auto... args)
  {
    using e_t = eve::element_type_t<T>;
    auto data = produce(type<std::array<e_t,T::size()>>{},g,rng, args...);

    using v_t = typename decltype(data)::value_type;
    eve::as_wide_t<v_t, eve::cardinal_t<T>> that = eve::load(&data[0], eve::cardinal_t<T>{});

    return poison(that);
  }

  //================================================================================================
  // logical ramp - generate (v+1) % k == 0, (v+2) % k ==  0, ... (v+N) % k == 0
  //================================================================================================
  template<typename T, typename U = T> struct logicals
  {
    logicals(T v, U k) : start(v), range(k)  {}

    template<typename D> auto operator()(tts::type<D>, auto&) const
    {
      using type = eve::as_logical_t<D>;
      return as_value<type>(false);
    }

    template<typename D> auto operator()(tts::type<D>, auto&, auto idx, auto...) const
    {
      using type = eve::as_logical_t<D>;
      return as_value<type>(((start+idx)%range) == 0);
    }

    T start;
    U range;
  };

  //================================================================================================
  // generate random bits
  //================================================================================================
  struct random_bits
  {
    template<typename D> auto operator()(tts::type<D>, auto& rng, auto...)
    {
      using i_t = eve::as_integer_t<eve::element_type_t<D>>;
      tts::realistic_distribution<i_t> dist(0,8*sizeof(i_t)-1);
      return dist(rng);
    }
  };

  //================================================================================================
  // Convert generated data to integral values
  //================================================================================================
  template<typename G>
  struct as_integer
  {
    as_integer(G g) : generator_(g) {}
    template<typename D> auto operator()(tts::type<D>, auto& rng, auto... args)
    {
      using i_t = eve::as_integer_t<eve::element_type_t<D>>;
      return generator_(tts::type<i_t>{},rng, args...);
    }

    G generator_;
  };

  template<typename G>
  struct as_signed_integer
  {
    as_signed_integer(G g) : generator_(g) {}
    template<typename D> auto operator()(tts::type<D>, auto& rng, auto... args)
    {
      using i_t = eve::as_integer_t<eve::element_type_t<D>, signed>;
      return generator_(tts::type<i_t>{},rng, args...);
    }

    G generator_;
  };

  //================================================================================================
  // IEEE Special Constant value
  //================================================================================================
  template<typename T>
  inline auto limits(tts::type<T>)
  {
    return []()
    {
      if constexpr(eve::floating_value<T>)
      {
        struct values
        {
          using type  = T;
          type nan         = eve::nan     (eve::as<type>{});
          type inf         = eve::inf     (eve::as<type>{});
          type minf        = eve::minf    (eve::as<type>{});
          type mzero       = eve::mzero   (eve::as<type>{});
          type zero        = eve::zero   (eve::as<type>{});
          type maxflint    = eve::maxflint(eve::as<type>{});
          type valmax      = eve::valmax(eve::as<type>{});
          type valmin      = eve::valmin(eve::as<type>{});
          type mindenormal = eve::mindenormal(eve::as<type>{});
          type smallestposval = eve::smallestposval(eve::as<type>{});
          type mone       = eve::mone   (eve::as<type>{});
          type one        = eve::one   (eve::as<type>{});
        };

        return values{};
      }
      else
      {
        struct values
        {
          using type  = T;
          type valmax    = eve::valmax(eve::as<type>{});
          type valmin    = eve::valmin(eve::as<type>{});
        };

        return values{};
      }
    }();
  }
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

  std::cout << "[EVE] - Target: " << eve::current_api
            << " - Assertions: "  << assert_status
            << " - PRNG Seed: "   << seed
            << std::endl;

  eve_entry_point(argc, argv);
  return tts::report(0,0);
}
