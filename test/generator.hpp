//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include "types.hpp"
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>

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
    using v_t = typename W::value_type;

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
        p_t filler = eve::Constant<p_t, static_cast<p_t>(0xDEADBEEFBABE0000)>() + p_t(i);
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
      if constexpr(eve::floating_ordered_value<T>)
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
