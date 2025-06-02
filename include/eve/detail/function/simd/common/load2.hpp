//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/spy.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unsafe.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/traits/wide_value_type.hpp>
#include <eve/wide.hpp>

#include <iterator>

namespace eve::detail
{
  template<typename O>
  concept load_safe_no_cx = match_option<condition_key, O, ignore_none_> && !O::contains(unsafe2);

  template<callable_options O, typename U, loadable<U, O> T>
  EVE_FORCEINLINE auto load_(EVE_REQUIRES(cpu_), O const& opts, T t, as<U> tgt) noexcept
  {
    return t.load(opts, tgt);
  }

  template<callable_options O, loadable_as<O> T>
  EVE_FORCEINLINE auto load_(EVE_REQUIRES(cpu_), O const& opts, T t) noexcept
  {
    return t.load(opts, as<as_wide_t<typename std::iterator_traits<T>::value_type>>{});
  }

  //================================================================================================
  // Load helper
  //================================================================================================
  template<typename Wide, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load(Iterator ptr, as<Wide>) noexcept
  {
    auto impl = [&](auto... I)
    {
      auto deref = [&](auto p, auto const &i) { std::advance(p, i); return *p; };
      return Wide(deref(ptr, static_cast<std::ptrdiff_t>(I))...);
    };

    return apply<Wide::size()>(impl);
  }

  template<typename Wide, typename Pointer>
  EVE_FORCEINLINE auto aggregate_load(Pointer ptr, as<Wide>) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr p, as<Sub>)
    {
      using type = element_type_t<Wide>;
      using a_p = eve::aligned_ptr<const type, cardinal_t<Sub>>;
      if constexpr (std::is_pointer_v<Ptr>) return p;
      else                                  return a_p{p.get()};
    };

    that.storage().apply
    (
      [&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(cast(ptr, as<Sub>{}) + offset), offset += Sub::size()), ...));
      }
    );

    return that;
  }

  //================================================================================================
  // Load from a range [b, e(
  //================================================================================================
  template<callable_options O, std::input_iterator Iterator, typename Wide>
  EVE_FORCEINLINE Wide load_(EVE_REQUIRES(cpu_), O const&, Iterator b, [[maybe_unused]] Iterator, as<Wide> tgt) noexcept
  {
    return piecewise_load(b, tgt);
  }

  //================================================================================================
  // Load from pointer - Emulation
  //================================================================================================
  template<callable_options O, typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_(EVE_REQUIRES(cpu_), O const&, Ptr ptr, as<wide<T, N>> tgt) noexcept
    requires (simd_compatible_ptr<Ptr, wide<T, N>> && std::same_as<abi_t<T, N>, emulated_> && load_safe_no_cx<O>)
  {
    return piecewise_load(unalign(ptr), tgt);
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<callable_options O, typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_(EVE_REQUIRES(cpu_), O const&, Ptr ptr, as<wide<T, N>> tgt) noexcept
    requires (simd_compatible_ptr<Ptr, wide<T, N>> && std::same_as<abi_t<T, N>, aggregated_> && load_safe_no_cx<O>)
  {
    return aggregate_load(ptr, tgt);
  }

  //================================================================================================
  // Bundle
  //================================================================================================
  template<callable_options O, typename N, typename ... Ptrs>
  EVE_FORCEINLINE wide<value_type_t<soa_ptr<Ptrs...>>, N>
  load_(EVE_REQUIRES(cpu_), O const& opts, soa_ptr<Ptrs...> ptr, as<wide<value_type_t<soa_ptr<Ptrs...>>, N>>) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto c = opts[condition_key];

    wide<value_type_t<soa_ptr<Ptrs...>>, N> that;
    if constexpr ( C::has_alternative )
    {
      kumi::for_each( [=]<typename M>(M& m, auto part_alt, auto p) {
            auto new_c = c.map_alternative([&](auto) { return part_alt; });
            m = load[opts][new_c](p, as<M>{});
          }
          , that.storage(), c.alternative, ptr
          );
    }
    else
    {
      kumi::for_each( [=]<typename M>(M& m, auto p) { m = load[opts](p, as<M>{}); }
                     , that.storage(), ptr
                     );
    }

    return that;
  }

  //================================================================================================
  // Basic logical support
  //================================================================================================
  template<callable_options O, typename T, typename N, data_source Pointer>
  EVE_FORCEINLINE logical<wide<T, N>> load_(EVE_REQUIRES(cpu_), O const&, Pointer ptr, as<logical<wide<T, N>>> tgt) noexcept
    requires (dereference_as<logical<T>, Pointer>::value && !x86_abi<abi_t<T, N>> && load_safe_no_cx<O>)
  {
    if constexpr ( std::same_as<abi_t<T, N>, aggregated_> ) return aggregate_load(ptr, tgt);
    else return
      bit_cast
            ( [&]() -> wide<T, N>
              {
                return load(ptr_cast<T>(ptr), as<wide<T, N>>{});
              }()
            , tgt
            );
  }

  // ================================================================================================
  // Load from pointer - Conditional load
  // ================================================================================================
  template<callable_options O, scalar_pointer Ptr, typename Wide>
  EVE_FORCEINLINE auto load_(EVE_REQUIRES(cpu_), O const& opts, Ptr ptr, as<Wide> tgt) noexcept
    requires (simd_compatible_ptr<Ptr, Wide> && !O::contains(unsafe2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cond = opts[condition_key];

    using e_t = typename pointer_traits<Wide>::value_type;
    using r_t = Wide;
    using c_t = cardinal_t<Wide>;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      static constexpr bool is_aligned_enough = c_t() * sizeof(e_t) >= Ptr::alignment();

      if constexpr( !spy::supports::sanitizers_status && is_aligned_enough )
      {
        auto that = eve::load[unsafe2](ptr, tgt);
        if constexpr( C::has_alternative ) return replace_ignored(that, cond, cond.alternative);
        else return that;
      }
      else { return eve::load[cond](ptr.get(), tgt); }
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( C::is_complete )
      {
        if constexpr( C::is_inverted ) { return eve::load(ptr, tgt); }
        else
        {
          if constexpr( C::has_alternative ) return r_t {cond.alternative};
          else return r_t {};
        }
      }
      else
      {
        auto offset = cond.offset(as<r_t> {});
        if constexpr( C::has_alternative )
        {
          [[maybe_unused]] r_t that(cond.alternative);
          auto                *dst = (e_t *)(&that.storage());
          std::memcpy((void *)(dst + offset), ptr + offset, sizeof(e_t) * cond.count(as<r_t> {}));
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that = {};
          auto                *dst = (e_t *)(&that.storage());
          std::memcpy((void *)(dst + offset), ptr + offset, sizeof(e_t) * cond.count(as<r_t> {}));
          return that;
        }
      }
    }
  }

  // making unsafe(load) call intrinsics requires a lot of work and is not very portable
  // due to what called functions it will affect.
  // Since the unsafe is mostly used in corner cases, will do it scalar in asan mode.
  template<callable_options O, typename Ptr, typename Wide>
  SPY_DISABLE_SANITIZERS Wide load_(EVE_REQUIRES(cpu_), O const& opts, Ptr ptr, as<Wide> tgt) noexcept
    requires (!has_bundle_abi_v<Wide> && O::contains(unsafe2))
  {
    if constexpr( spy::supports::sanitizers_status )
    {
      auto cond = opts[condition_key];

      Wide that;

      auto offset = cond.offset(tgt);
      auto count  = cond.count(tgt);

      for( std::ptrdiff_t i = offset; i != count + offset; ++i ) that.set(i, ptr[i]);

      return that;
    }
    else { return eve::load[opts.drop(unsafe2)](ptr, tgt); }
  }
}
