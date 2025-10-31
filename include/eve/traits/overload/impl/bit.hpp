//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/tuple.hpp>
#include <eve/detail/function/inner_bit_cast.hpp>
#include <eve/traits/bit_value.hpp>
#include <eve/conditional.hpp>

namespace eve
{
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct bit_callable : strict_tuple_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_tuple_callable<Func, OptionsValues, Options...>;

    template<typename T, typename Tgt>
    constexpr static EVE_FORCEINLINE auto process_input(T v, as<Tgt>) noexcept
    {
      using expected_t = as_wide_as_t<element_type_t<T>, Tgt>;
      if constexpr (has_emulated_abi_v<expected_t>) return detail::inner_bit_cast(v, as<as_uinteger_t<T>>{});
      else                                          return v;
    }

    template<typename T, typename Tgt>
    constexpr static EVE_FORCEINLINE auto process_alternative(T v, as<Tgt>) noexcept
    {
      using utgt_t = as_uinteger_t<Tgt>;
      using inner_tgt_t = std::conditional_t<has_emulated_abi_v<Tgt>, utgt_t, Tgt>;

      if constexpr (scalar_value<T>)
      {
        using utgt_et      = element_type_t<utgt_t>;
        using inner_tgt_et = element_type_t<inner_tgt_t>;
        using ut_t         = as_uinteger_t<T>;

        const auto uv = std::bit_cast<ut_t>(v);

        if constexpr (sizeof(ut_t) > sizeof(utgt_et))
        {
          EVE_ASSERT((uv >> (sizeof(utgt_et) * 8)) == ut_t{ 0 }, "[eve::bit_callable] Alternative value has non-zero truncated bits");
        }

        return std::bit_cast<inner_tgt_et>(static_cast<utgt_et>(uv));
      }
      else
      {
        return inner_bit_cast(v, as<inner_tgt_t>{});
      }
    }

    template<callable_options O, typename... Ts>
    constexpr EVE_FORCEINLINE bit_value_t<Ts...> execute(auto arch, O const& opts, Ts... xs) const
    {
      using r_t = bit_value_t<Ts...>;
      return detail::inner_bit_cast(base_t::behavior(arch, opts, process_input(xs, as<r_t>{})...), as<bit_value_t<Ts...>>{});
    }

    template<callable_options O, kumi::product_type Tup>
    constexpr EVE_FORCEINLINE kumi::apply_traits_t<bit_value, Tup> behavior(auto arch, O const& opts, Tup x) const
    {
      return kumi::apply([&](auto... xs) { return behavior(arch, opts, xs...); }, x);
    }

    template<callable_options O, typename... Ts>
    constexpr EVE_FORCEINLINE bit_value_t<Ts...> behavior(auto arch, O const& opts, Ts... xs) const
    {
      using C = rbr::result::fetch_t<condition_key, O>;

      if constexpr (conditional_expr<C>)
      {
        if constexpr (C::has_alternative)
        {
          using tgt_t = bit_value_t<Ts...>;
          const auto new_cx = opts[condition_key].rebase(process_alternative(opts[condition_key].alternative, as<tgt_t>{}));
          const auto new_cl = (*this)[new_cx];
          return new_cl.execute(arch, new_cl.options(), xs...);
        }
        else return execute(arch, opts, xs...);
      }
      else return execute(arch, opts, xs...);
    }
  };
}
