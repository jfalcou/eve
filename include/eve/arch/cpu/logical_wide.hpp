//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/cpu/logical.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bitmask.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/traits/as_integer.hpp>

#include <cstring>
#include <type_traits>
#include <ostream>

namespace eve
{
  //================================================================================================
  // Wrapper for SIMD registers holding logical types with compile-time size
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct  EVE_MAY_ALIAS  logical<wide<Type,Size,ABI>>
        : detail::wide_cardinal<Size>
        , detail::wide_ops<logical<wide<Type,Size,ABI>>>
        , detail::wide_storage<as_logical_register_t<Type, Size, ABI>>
  {
    using card_base     = detail::wide_cardinal<Size>;
    using storage_base  = detail::wide_storage<as_logical_register_t<Type, Size, ABI>>;

    public:
    using abi_type      = ABI;
    using value_type    = logical<Type>;
    using storage_type  = typename storage_base::storage_type;
    using size_type     = typename card_base::size_type;

    using bits_type = wide<as_integer_t<Type, unsigned>, Size>;
    using mask_type = wide<Type, Size>;

    template<typename N> using rescale = logical<wide<Type,N>>;
    template<typename T, typename N = expected_cardinal_t<T>>
    using rebind = logical<wide<T,N>>;

    static constexpr size_type  static_alignment = sizeof(Type)*Size::value;

    //==============================================================================================
    // Constructors
    //==============================================================================================
    EVE_FORCEINLINE logical() noexcept {}
    EVE_FORCEINLINE logical(logical const& w) noexcept : storage_base(w.storage()) {}

    EVE_FORCEINLINE logical(storage_type const &r) noexcept
      : storage_base( [&]()
                      { constexpr auto  c =   Size::value == 1 && sizeof(Type) == 8
                                          &&  std::is_same_v<ABI, arm_64_>
                                          && current_api != asimd;
                        if constexpr(c) return value_type(r); else  return r;
                      }()
                    )
    {}

    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : storage_base(detail::load(eve::as_<logical>{}, b, e))
    {}

    template<detail::range Range>
    EVE_FORCEINLINE explicit logical(Range &&r) noexcept requires(!std::same_as<storage_type, Range>)
                  : logical(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {}

    template<simd_compatible_ptr<logical> Ptr>
    EVE_FORCEINLINE explicit logical(Ptr ptr) noexcept
                  : storage_base(detail::load(eve::as_<logical>{}, ptr)) {}

    EVE_FORCEINLINE explicit logical(scalar_value auto const& v) noexcept
                  : storage_base(detail::make(eve::as_<logical>{}, v)) {}

    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,logical<Type>> && std::convertible_to<T0,logical<Type>>
                    &&  (... && std::convertible_to<Ts,logical<Type>>)
                    &&  (card_base::static_size == 2 + sizeof...(Ts))
                  )
        : storage_base(detail::make(eve::as_<logical>{}, v0, v1, vs...))
    {}

    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                  : storage_base(detail::fill(as_<logical>{}, std::forward<Generator>(g)))
    {}

    template<typename HalfSize>
    EVE_FORCEINLINE logical ( logical<wide<Type, HalfSize>> const &l
                            , logical<wide<Type, HalfSize>> const &h
                            ) noexcept
                    requires( card_base::static_size == 2 * HalfSize::value )
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {}

    //==============================================================================================
    // Assignments
    //==============================================================================================
    logical& operator=(logical const&) & = default;
    using detail::wide_ops<logical>::operator=;

    //==============================================================================================
    // Convertion from logical to other formats (mask, bits, bitmap)
    //==============================================================================================
    EVE_FORCEINLINE auto bits()   const noexcept { return detail::to_bits(EVE_CURRENT_API{},*this); }
    EVE_FORCEINLINE auto mask()   const noexcept { return detail::to_mask(EVE_CURRENT_API{},*this); }
    EVE_FORCEINLINE auto bitmap() const noexcept { return detail::to_bitmap(EVE_CURRENT_API{},*this); }

    //==============================================================================================
    // Logical operations
    //==============================================================================================
    template<typename U, typename A2>
    friend EVE_FORCEINLINE auto operator&&(logical const& v, logical<wide<U,Size,A2>> const& w) noexcept
    {
      return detail::self_logand(v,w);
    }

    friend EVE_FORCEINLINE auto operator&&(logical const& v, scalar_value auto w) noexcept
    {
      return v && logical{w};
    }

    friend EVE_FORCEINLINE auto operator&&(scalar_value auto v, logical const& w) noexcept
    {
      return w && v;
    }

    template<typename U, typename A2>
    friend EVE_FORCEINLINE auto operator||(logical const& v, logical<wide<U,Size,A2>> const& w) noexcept
    {
      return detail::self_logor(v,w);
    }

    friend EVE_FORCEINLINE auto operator||(logical const& v, scalar_value auto w) noexcept
    {
      return v || logical{w};
    }

    friend EVE_FORCEINLINE auto operator||(scalar_value auto v, logical const& w) noexcept
    {
      return w || v;
    }

    //==============================================================================================
    // Inserting a logical<wide> into a stream
    //==============================================================================================
    friend std::ostream &operator<<(std::ostream &os, logical const &p)
    {
      auto that = p.bitmap();
      os << '(' << (that[0] ? "true" : "false");
      for(size_type i = 1; i < p.size(); ++i) os << ", " << (that[i] ? "true" : "false");
      return os << ')';
    }
  };
}
