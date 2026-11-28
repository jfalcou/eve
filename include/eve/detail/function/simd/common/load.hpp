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
#include <eve/config.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/memory/stack_buffer.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unsafe.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/traits/wide_value_type.hpp>
#include <eve/traits/as_translation.hpp>
#include <eve/concept/ptr_translation.hpp>
#include <eve/wide.hpp>

#include <iterator>

EVE_NAMESPACE::_
{
  //================================================================================================
  // Load helper
  //================================================================================================
  template<typename Wide, typename Iterator>
   auto piecewise_load(Iterator ptr, as<Wide>) noexcept
  {
    auto impl = [&](auto... I)
    {
      std::array<element_type_t<Wide>, Wide::size()> values;

      values[0] = *ptr;
      for(std::size_t i = 1; i < Wide::size(); ++i)
      {
        values[i] = *(ptr = std::next(ptr));
      }

      return Wide(values[I]...);
    };

    return apply<Wide::size()>(impl);
  }

  template<relative_conditional_expr C, typename Wide, typename Iterator>
   auto piecewise_load_cx(C const& cx, Iterator ptr, as<Wide> tgt) noexcept
  {
    if constexpr (C::is_complete)
    {
      if constexpr (C::is_inverted) return piecewise_load(ptr, tgt);
      else                          return _::alternative(cx, Wide {}, tgt);
    }
    else
    {
      std::ptrdiff_t begin = cx.offset(tgt);
      std::ptrdiff_t end = begin + cx.count(tgt);

      Wide res = _::alternative(cx, Wide { }, tgt);

      if (begin != end)
      {
        std::advance(ptr, begin);
        res.set(begin, *ptr);
        for (std::ptrdiff_t i = begin + 1; i < end; ++i)
        {
          ++ptr;
          res.set(i, *ptr);
        }
      }

      return res;
    }
  }

  template<typename Wide, typename Pointer>
   auto aggregate_load(Pointer ptr, as<Wide>) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr p, as<Sub>)
    {
      using type = value_type_t<Ptr>;
      using a_p = eve::aligned_ptr<const type, Sub::size()>;
      if constexpr (std::is_pointer_v<Ptr>) return p;
      else                                  return a_p{p.get()};
    };

    kumi::apply([&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(cast(ptr, as<Sub>{}) + offset), offset += Sub::size()), ...));
      }, that.storage());

    return that;
  }


  template<relative_conditional_expr C, typename Wide, typename To>
  auto bits_alternative(C const& cx, as<Wide> tgt, as<To> to) noexcept
  {
    return map_alternative(cx, [&](auto) { return bit_cast(_::alternative(cx, Wide {}, tgt), to); });
  }

  template<relative_conditional_expr C, typename Wide>
  Wide with_alternative(C const& cx, Wide res) noexcept
  {
    if constexpr (C::has_alternative) return replace_ignored(res, cx, cx.alternative);
    else                              return res;
  }

  struct no_alternative {};

  template<typename Wide>
  constexpr bool has_masked_load() noexcept
  {
    if constexpr (aggregated_abi<Wide>)
    {
      return has_masked_load<std::remove_cvref_t<decltype(std::declval<Wide>().slice(lower_))>>();
    }
    else
    {
      return requires(logical<Wide> m, element_type_t<Wide> const* p) {
        load_masked_impl(current_api, m, no_alternative {}, p, as<Wide> {});
      };
    }
  }

  template<typename Wide, typename Alt>
  Wide load_masked(logical<Wide> m, Alt alt, element_type_t<Wide> const* p) noexcept
  {
    if constexpr (aggregated_abi<Wide>)
    {
      auto [m_lo, m_hi] = m.slice();
      auto const* p_hi  = p + Wide::size() / 2;

      if constexpr (std::same_as<Alt, Wide>)
      {
        auto [a_lo, a_hi] = alt.slice();
        return Wide {load_masked(m_lo, a_lo, p), load_masked(m_hi, a_hi, p_hi)};
      }
      else
      {
        return Wide {load_masked(m_lo, alt, p), load_masked(m_hi, alt, p_hi)};
      }
    }
    else
    {
      return load_masked_impl(current_api, m, alt, p, as<Wide> {});
    }
  }

  // Implementation of load[ignore](ptr): [ptr + offset, ptr + offset + count) is the loaded subpart.
  // Idea from Robert Clausecker (@clausecker).
  template<bool never_empty, std::ptrdiff_t B>
  wide<std::uint8_t, B> load_windowed(std::uint8_t const* ptr,
                                      std::ptrdiff_t offset,
                                      std::ptrdiff_t count,
                                      lanes_t<B>) noexcept
  {
    using bytes = wide<std::uint8_t, B>;
    constexpr as<bytes> tgt {};

    // ptr can be before aligned_f so keeping an extra register of buffer
    stack_buffer<bytes, 3> buf;

    if constexpr (!never_empty) ptr = (count == 0) ? buf.ptr().get() + B : ptr;

    auto const* f = ptr + offset;
    auto const* l = f + count;

    auto aligned_f = previous_aligned_address(f, lanes<B>);
    auto aligned_l = previous_aligned_address(l - 1, lanes<B>);

    // Unconditionally copying to the stack.
    call_store(eve::load[unsafe](aligned_f, tgt), buf.ptr() + B);
    call_store(eve::load[unsafe](aligned_l, tgt), buf.ptr() + 2 * B);
    std::uint8_t const* on_stack = buf.ptr().get() + B + (ptr - aligned_f.get());

    // Loading from the page directly is much cheaper compared to waiting for stores to finish.
    // If the result of stores isn't used, the cost of them seems negligible.
    constexpr auto page = platform::min_page_size;
    auto page_offset = ptr - previous_aligned_address(ptr, lanes<page>).get();
    std::uint8_t const* load_from = (page_offset <= page - B) ? ptr : on_stack;

    return eve::load[unsafe](load_from, tgt);
  }

  template<relative_conditional_expr C, _::data_source DS, typename Wide>
  Wide load_ignore_memcpy(C const& cx, DS src, as<Wide> tgt) noexcept
  {
    using e_t = typename pointer_traits<Wide>::value_type;

    Wide that   = _::alternative(cx, Wide {}, tgt);
    auto offset = cx.offset(tgt);
    auto *dst   = (e_t *)(&that.storage());
    std::memcpy((void *)(dst + offset), unalign(src) + offset, sizeof(e_t) * cx.count(tgt));
    return that;
  }

  template<relative_conditional_expr C, _::data_source DS, typename Wide>
  SPY_DISABLE_SANITIZERS Wide load_unsafe_asan(C const& cx, DS src, as<Wide> tgt) noexcept
  {
    auto res = _::alternative(cx, Wide {}, tgt);

    auto offset = cx.offset(tgt);
    auto count  = cx.count(tgt);

    for (std::ptrdiff_t i = offset; i != count + offset; ++i)
      res.set(i, src[i]);

    return res;
  }

  template<callable_options O, _::data_source DS, typename Wide>
  Wide load_bundle_(O const& opts, DS src, as<Wide>) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    Wide res;

    if constexpr (C::has_alternative)
    {
      kumi::for_each( [=]<typename M>(M& m, auto part_alt, auto p) {
            auto new_c = cx.map_alternative([&](auto) { return part_alt; });
            m = load[opts][new_c](p, as<M>{});
          }
          , res.storage(), cx.alternative, src
          );
    }
    else
    {
      kumi::for_each( [=]<typename M>(M& m, auto p) { m = load[opts](p, as<M>{}); }
                    , res.storage(), src
                    );
    }

    return res;
  }

  template<callable_options O, _::data_source DS, typename Wide, typename To>
  Wide load_bit_cast_(O const& opts, DS src, as<Wide> tgt, as<To> to) noexcept
  {
    auto const new_c = bits_alternative(opts[condition_key], tgt, to);
    return bit_cast(load[opts][new_c](ptr_cast<element_type_t<To> const>(src), to), tgt);
  }

  template<callable_options O, _::data_source DS, typename Wide>
  Wide load_logical_(O const& opts, DS src, as<Wide> tgt) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    using W = as_arithmetic_t<Wide>;

    if constexpr (Wide::abi_type::is_wide_logical)
    {
      return load_bit_cast_(opts, src, tgt, as<W> {});
    }
    else
    {
      auto cx  = opts[condition_key];
      auto res = to_logical(load[opts][drop_alternative(cx)](ptr_cast<element_type_t<W> const>(src), as<W> {}));

      if constexpr (C::has_alternative) return replace_ignored(res, cx, cx.alternative);
      else                              return res;
    }
  }

  template<typename DS, std::ptrdiff_t Bytes>
  constexpr bool is_aligned_on() noexcept
  {
    if constexpr (is_aligned_ptr_v<DS>) return DS::alignment() >= Bytes;
    else                                return false;
  }

  template<relative_conditional_expr C, _::data_source DS, typename Wide>
  Wide load_partial_(C const& cx, DS src, as<Wide> tgt) noexcept
  {
    using T = element_type_t<Wide>;

    constexpr bool          never_empty = _::is_never_empty<C>;
    constexpr std::ptrdiff_t bytes       = sizeof(T) * Wide::size();

    if constexpr (Wide::size() == 1)
    {
      if constexpr (never_empty)
      {
        cx.check_not_empty(tgt);
        return load(src, tgt);
      }
      else
      {
        stack_buffer<Wide> buf;
        T const* ptr = (cx.count(tgt) == 0) ? buf.ptr().get() : unalign(src);
        return with_alternative(cx, load(ptr, tgt));
      }
    }
    else if constexpr (is_aligned_on<DS, bytes>())
    {
      if constexpr (never_empty)
      {
        cx.check_not_empty(tgt);
        return with_alternative(cx, load(src, tgt));
      }
      else
      {
        using a_ptr = aligned_ptr<T const, Wide::size()>;

        stack_buffer<Wide> buf;
        a_ptr ptr = (cx.count(tgt) == 0) ? a_ptr {buf.ptr()} : a_ptr {src};
        return with_alternative(cx, load(ptr, tgt));
      }
    }
    else if constexpr (has_masked_load<Wide>())
    {
      auto m = cx.mask(tgt);

      if constexpr (C::has_alternative) return load_masked(m, _::alternative(cx, Wide {}, tgt), unalign(src));
      else                              return load_masked(m, no_alternative {}, unalign(src));
    }
    else
    {
      auto const* ptr = (std::uint8_t const*)unalign(src);
      auto        res = load_windowed<never_empty>( ptr
                                                  , sizeof(T) * cx.offset(tgt)
                                                  , sizeof(T) * cx.count(tgt)
                                                  , lanes<bytes>
                                                  );
      return with_alternative(cx, bit_cast(res, tgt));
    }
  }

  /*
   * # All the considerations for load distribution.
   *
   * ## Always empty
   * ignore_all
   *
   * ## Custom loads.
   * Calling the custom overloads for a data source.
   *
   * ## non ptr data sources
   * contiguous iterators - becomes ptr
   * non contiguous iterators - piecewise_load
   *
   * ## Translation.
   * The types that have equivalents (like enums or custom types)
   * are translated immediately.
   *
   * ## Bundles.
   * Distributing bundles we consider always optimal.
   * Ofc there are some checks on ignore but we assume the compiler can
   * merge those in an optimal way.
   *
   * ## Logicals.
   * The wide logicals are immediately casted to the relevant bits types.
   * The non wide logicals: do the alternative mapping themselves
   *                        (we believe that's reasonable).
   *                        Then we load the bits without alternatives.
   *
   * ## Type casting
   * Casting signed integers to unsigned numbers. Keeping floats
   * because compilers do not select appropriate instructions.
   *
   * ## Asan with unsafe mode
   * Custom loop with disable sanitizers
   *
   * ## Asan without unsafe mode or emulated
   * memcpy
   *
   * ## Aligned pointer, with ignore
   * for non-empty - just unsafe load.
   * otherwise cmov for pointer + unsafe load
   *
   * ## wide, len = 1, never empty
   * just load
   *
   * ## Aggregate, no ignore
   * split
   *
   * ## wide, len = 1
   * cmov pointer, load
   *
   * ## ignore, mask load supported
   * in the platform specific code - convert ignore to logical.
   * aggregate over the resulting mask if necessary.
   *
   * ## ignore, mask load not supported
   * Do the load windowed.
   *
   * ## no ignore
   * platform load
   */
  template<callable_options O, _::data_source DS, typename Wide>
  Wide load_(EVE_REQUIRES(cpu_), O const& opts, DS src, as<Wide> tgt) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    [[maybe_unused]] auto cx = opts[condition_key];

    if constexpr (C::is_complete && !C::is_inverted)
    {
      return _::alternative(cx, Wide {}, tgt);
    }
    else if constexpr (requires { src.load(opts, tgt); })
    {
      return src.load(opts, tgt);
    }
    else if constexpr (std::contiguous_iterator<DS> && !_::scalar_pointer<DS>)
    {
      return load.behavior(cpu_{}, opts, std::to_address(src), tgt);
    }
    else if constexpr (std::input_iterator<DS> && !_::scalar_pointer<DS>)
    {
      return piecewise_load_cx(cx, src, tgt);
    }
    else if constexpr (translatable_ptr<DS>)
    {
      auto const new_c = map_alternative(cx, [](auto alt) { return translate(alt); });
      return bit_cast(load[opts][new_c](translate_ptr(src), translate(tgt)), tgt);
    }
    else if constexpr (bundle_abi<Wide>)
    {
      return load_bundle_(opts, src, tgt);
    }
    else if constexpr (logical_simd_value<Wide>)
    {
      return load_logical_(opts, src, tgt);
    }
    else if constexpr (match(categorize<Wide>(), category::int_))
    {
      return load_bit_cast_(opts, src, tgt, as<as_uinteger_t<Wide>> {});
    }
    else if constexpr (spy::supports::sanitizers_status && O::contains(unsafe2))
    {
      return load_unsafe_asan(cx, src, tgt);
    }
    else if constexpr (emulated_abi<Wide> || (spy::supports::sanitizers_status && !C::is_complete))
    {
      return load_ignore_memcpy(cx, src, tgt);
    }
    else if constexpr (!C::is_complete)
    {
      return load_partial_(cx, src, tgt);
    }
    else if constexpr (aggregated_abi<Wide>)
    {
      return aggregate_load(src, tgt);
    }
    else
    {
      return load_impl(current_api, src, tgt);
    }
  }
}
