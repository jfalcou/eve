//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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

#include <cstring>
#include <type_traits>
#include <iosfwd>

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
    using card_base = detail::wide_cardinal<Size>;
    using storage_base  = detail::wide_storage<as_logical_register_t<Type, Size, ABI>>;

    public:
    using abi_type      = ABI;
    using value_type    = logical<Type>;
    using storage_type  = typename storage_base::storage_type;
    using size_type     = typename card_base::size_type;

    using bits_type = wide<detail::as_integer_t<Type, unsigned>, Size>;
    using mask_type = wide<Type, Size>;

    template<typename T, typename N = expected_cardinal_t<T>>
    using rebind = logical<wide<T,N>>;

    static constexpr size_type  static_alignment  = std::min( sizeof(Type)*Size::value
                                                            , alignof(storage_type)
                                                            );

    //==============================================================================================
    // Default constructor
    //==============================================================================================
    EVE_FORCEINLINE logical() noexcept {}

    //==============================================================================================
    // Constructs a logical<wide> from a native SIMD storage
    //==============================================================================================
    EVE_FORCEINLINE logical(storage_type const &r) noexcept
#if !defined(__aarch64__)
          : storage_base( [&r]()
                          {
                            if constexpr( Size::value == 1 && sizeof(Type) == 8 &&
                                          std::is_same_v<ABI, neon64_>
                                        )
                            {
                              return logical<Type>(r);
                            }
                            else
                            {
                            return r;
                            }
                          }()
                        )
#else
        : storage_base(r)
#endif
    {
    }

    //==============================================================================================
    // Constructs a logical<wide> from a Range
    //==============================================================================================
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : storage_base(detail::load(eve::as_<logical>{}, b, e))
    {
    }

    template<detail::range Range>
    EVE_FORCEINLINE explicit logical(Range &&r) noexcept
          requires( !std::same_as<storage_type, Range> )
        : logical(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    //==============================================================================================
    // Constructs a logical<wide> from a pointer or an aligned pointer
    //==============================================================================================
    template<simd_compatible_ptr<logical> Ptr>
    EVE_FORCEINLINE explicit logical(Ptr ptr) noexcept
        : storage_base(detail::load(eve::as_<logical>{}, ptr))
    {
    }

    //==============================================================================================
    // Constructs a logical<wide>  from a single value
    //==============================================================================================
    EVE_FORCEINLINE explicit logical(scalar_value auto v) noexcept
                  : storage_base(detail::make(eve::as_<logical>{}, v))
    {
    }

    //==============================================================================================
    // Constructs a logical<wide> from a sequence of values
    //==============================================================================================
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,logical<Type>> && std::convertible_to<T0,logical<Type>>
                    &&  (... && std::convertible_to<Ts,logical<Type>>)
                    &&  (card_base::static_size == 2 + sizeof...(Ts))
                  )
        : storage_base(detail::make(eve::as_<logical>{}, v0, v1, vs...))
    {}

    //==============================================================================================
    // Constructs a logical<wide> with a generator function
    //==============================================================================================
    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                  : storage_base(detail::fill(as_<logical>{}, std::forward<Generator>(g)))
    {}

    //==============================================================================================
    // Constructs a logical<wide> from a pair of sub-wide
    //==============================================================================================
    template<typename halfSize>
    EVE_FORCEINLINE logical ( logical<wide<Type, halfSize>> const &l
                            , logical<wide<Type, halfSize>> const &h
                            ) noexcept
                    requires( card_base::static_size == 2 * halfSize::value )
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    using detail::wide_ops<logical>::operator=;
    using detail::wide_ops<logical>::operator[];

    //==============================================================================================
    // Convert a logical to a bit value
    //==============================================================================================
    EVE_FORCEINLINE constexpr bits_type bits() const noexcept
    {
      return detail::to_bits(EVE_CURRENT_API{},*this);
    }

    //==============================================================================================
    // Convert a logical to a typed mask value
    //==============================================================================================
    EVE_FORCEINLINE constexpr mask_type mask() const noexcept
    {
      return detail::to_mask(EVE_CURRENT_API{},*this);
    }

    //==============================================================================================
    // Convert a logical to a bitmap of its truth values
    //==============================================================================================
    EVE_FORCEINLINE constexpr auto bitmap() const noexcept
    {
      return detail::to_bitmap(EVE_CURRENT_API{},*this);
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
