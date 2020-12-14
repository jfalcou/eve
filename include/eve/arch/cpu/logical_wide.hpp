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

#include <eve/arch/cpu/logical.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bitmask.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <cstring>
#include <iosfwd>
#include <type_traits>

namespace eve
{
  template<typename Type, typename N, typename ABI>
  struct EVE_MAY_ALIAS logical<wide<Type, N, ABI>>
  {
    using parent    = wide<logical<Type>, N>;
    using bits_type = wide<detail::as_integer_t<Type, unsigned>, N>;
    using mask_type = wide<Type, N>;

    using storage_type           = typename parent::storage_type;
    using cardinal_type          = typename parent::cardinal_type;
    using abi_type               = typename parent::abi_type;
    using value_type             = typename parent::value_type;
    using size_type              = typename parent::size_type;
    using target_type            = typename parent::target_type;

    static constexpr size_type  static_size       = parent::static_size;
    static constexpr size_type  static_alignment  = parent::static_alignment;

    template<typename T, typename C = expected_cardinal_t<T>>
    using rebind = logical<wide<T,C>>;

    //==============================================================================================
    // Default constructor
    //==============================================================================================
    EVE_FORCEINLINE logical() noexcept {}

    //==============================================================================================
    // Constructs a wide from a native SIMD storage
    //==============================================================================================
    EVE_FORCEINLINE logical(storage_type const &r) noexcept
#if !defined(__aarch64__)
          : data_ ( [&r]()
                    {
                      if constexpr( N::value == 1 && sizeof(Type) == 8 &&
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
        : data_(r)
#endif

    {
    }

    // ---------------------------------------------------------------------------------------------
    // TODO: constructor from bitmap to logical

    //==============================================================================================
    // Constructs a wide from a Range
    //==============================================================================================
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : data_(detail::load(eve::as_<logical>{}, abi_type{}, b, e))
    {
    }

    template<detail::range Range>
    EVE_FORCEINLINE explicit logical(Range &&r) noexcept
          requires( !simd_value<Range> && !std::same_as<storage_type, Range>)
        : logical(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    //==============================================================================================
    // Constructs a wide from a pointer or an aligned pointer
    //==============================================================================================
    template<simd_compatible_ptr<logical> Ptr>
    EVE_FORCEINLINE explicit logical(Ptr ptr) noexcept
    requires( is_logical_v<std::decay_t<decltype(*ptr)>> )
        : data_(detail::load(eve::as_<logical>{}, abi_type{}, ptr))
    {
    }

    //==============================================================================================
    // Constructs a wide  from a single value
    //==============================================================================================
    template<scalar_value T>
    EVE_FORCEINLINE explicit logical(T const &v) noexcept
                    requires( std::convertible_to<T, logical<Type>> )
                  : data_(detail::make(eve::as_<target_type>{}, abi_type{}, v))
    {
    }

    //==============================================================================================
    // Constructs a wide from a sequence of values
    //==============================================================================================
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,logical<Type>> && std::convertible_to<T0,logical<Type>>
                    &&  (... && std::convertible_to<Ts,logical<Type>>)
                    &&  (static_size == 2 + sizeof...(Ts))
                  )
        : data_(detail::make(eve::as_<target_type>{}, abi_type{}, v0, v1, vs...))
    {}

    //==============================================================================================
    // Constructs a wide with a generator function
    //==============================================================================================
    template<typename Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                    requires( std::invocable<Generator,size_type,size_type>)
                  : data_ ( detail::fill( as_<logical>{}, abi_type{},
                            [&](int i, int c)
                            {
                              return static_cast<logical<Type>>(std::forward<Generator>(g)(i,c));
                            }
                          )
            )
    {}

    //==============================================================================================
    // Constructs a wide from a pair of sub-wide
    //==============================================================================================
    template<typename halfSize, typename Other>
    EVE_FORCEINLINE logical ( logical<wide<Type, halfSize, Other>> const &l
                            , logical<wide<Type, halfSize, Other>> const &h
                            ) noexcept
                    requires( static_size == 2 * halfSize::value )
                  : logical(detail::combine(EVE_CURRENT_API{}, l, h))
    {}

    //==============================================================================================
    // Assignment
    //==============================================================================================
    EVE_FORCEINLINE logical &operator=(bool b) { return (*this = logical<Type>{b}); }

    EVE_FORCEINLINE logical &operator=(logical<Type> const &v) noexcept
    {
      data_ = detail::make(eve::as_<target_type>{}, abi_type{}, v);
      return *this;
    }

    //==============================================================================================
    // slice interface
    //==============================================================================================
    template<typename Slice> EVE_FORCEINLINE auto slice(Slice const &s) const
    {
      return detail::slice(EVE_CURRENT_API{},*this, s);
    }

    EVE_FORCEINLINE auto slice() const { return detail::slice(EVE_CURRENT_API{},*this); }

    //==============================================================================================
    // Raw storage access
    //==============================================================================================
    EVE_FORCEINLINE storage_type const& storage() const& noexcept { return data_; }
    EVE_FORCEINLINE storage_type &      storage() &      noexcept { return data_; }
    EVE_FORCEINLINE storage_type        storage() &&     noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type const& () const &  noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type&       () &        noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type        () &&       noexcept { return data_; }


    //==============================================================================================
    // alignment interface
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type alignment() noexcept
    {
      return static_alignment;
    }

    //==============================================================================================
    // array-like interface
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty() noexcept { return false; }

    //==============================================================================================
    // swap
    //==============================================================================================
    EVE_FORCEINLINE void swap(logical &rhs) noexcept { data_.swap(rhs.data_); }

    //==============================================================================================
    // Dynamic index lookup
    //==============================================================================================
    template<typename Index>
    EVE_FORCEINLINE logical operator[](wide<Index,N> const& idx) noexcept
    {
      return bit_cast(lookup(bits(),idx), as(*this));
    }

    //==============================================================================================
    // elementwise access
    //==============================================================================================
    EVE_FORCEINLINE void set(std::size_t i, value_type v) noexcept
    {
      data_.set(i,v);
    }

    EVE_FORCEINLINE value_type operator[](std::size_t i)  const noexcept  { return data_[ i ];    }

    EVE_FORCEINLINE value_type back()                     const noexcept  { return data_.back();  }
    EVE_FORCEINLINE value_type front()                    const noexcept  { return data_.front(); }

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
    /// Stream insertion operator
    //==============================================================================================
    friend std::ostream &operator<<(std::ostream &os, logical const &p)
    {
      auto that = p.bitmap();
      os << '(' << std::boolalpha << that[0];
      for(size_type i = 1; i < p.size(); ++i) os << ", " << that[i];
      return os << std::noboolalpha << ')';
    }

    private:
    wide<logical<Type>, N> data_;
  };
}
