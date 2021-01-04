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
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bitmask.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/compounds.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>

#include <cstring>
#include <type_traits>
#include <iosfwd>

namespace eve
{
  //================================================================================================
  // Wrapper for SIMD registers holding logical types with compile-time size
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct EVE_MAY_ALIAS logical<wide<Type,Size,ABI>>
  {
    private:
    //==============================================================================================
    // INTERNAL - Compute the type used as target for detail implementation
    //==============================================================================================
    template<typename P, typename A> struct tgt_      { using type = typename P::value_type;    };
    template<typename P> struct tgt_<P, emulated_>    { using type = typename P::storage_type;  };
    template<typename P> struct tgt_<P, aggregated_>  { using type = P;                         };

    public:
    using storage_type  = as_logical_register_t<Type, Size, ABI>;
    using cardinal_type = Size;
    using abi_type      = ABI;
    using value_type    = logical<Type>;
    using size_type     = std::ptrdiff_t;
    using target_type   = typename tgt_<logical, abi_type>::type;

    using bits_type = wide<detail::as_integer_t<Type, unsigned>, Size>;
    using mask_type = wide<Type, Size>;

    template<typename T, typename N = expected_cardinal_t<T>>
    using rebind = logical<wide<T,N>>;

    static constexpr size_type  static_size       = Size::value;
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
          : data_ ( [&r]()
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
        : data_(r)
#endif
    {
    }

    //==============================================================================================
    // Constructs a logical<wide> from a Range
    //==============================================================================================
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : data_(detail::load(eve::as_<logical>{}, abi_type{}, b, e))
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
        : data_(detail::load(eve::as_<logical>{}, abi_type{}, ptr))
    {
    }

    //==============================================================================================
    // Constructs a logical<wide>  from a single value
    //==============================================================================================
    template<scalar_value T>
    EVE_FORCEINLINE explicit logical(T const &v) noexcept
                    requires( std::convertible_to<T, logical<Type>> )
                  : data_(detail::make(eve::as_<target_type>{}, abi_type{}, v))
    {
    }

    //==============================================================================================
    // Constructs a logical<wide> from a sequence of values
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
    // Constructs a logical<wide> with a generator function
    //==============================================================================================
    template<typename Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                    requires( std::invocable<Generator,size_type,size_type>)
                  : data_ ( detail::fill( as_<logical>{}, abi_type{},
                            [&](auto i, auto c)
                            {
                              return static_cast<logical<Type>>(std::forward<Generator>(g)(i,c));
                            }
                          )
            )
    {}

    //==============================================================================================
    // Constructs a logical<wide> from a pair of sub-wide
    //==============================================================================================
    template<typename halfSize>
    EVE_FORCEINLINE logical ( logical<wide<Type, halfSize>> const &l
                            , logical<wide<Type, halfSize>> const &h
                            ) noexcept
                    requires( static_size == 2 * halfSize::value )
                  : data_(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    //==============================================================================================
    // Assign a single value to a logical<wide>
    //==============================================================================================
    EVE_FORCEINLINE logical &operator=(bool b) { return (*this = logical<Type>{b}); }

    EVE_FORCEINLINE logical &operator=(logical<Type> const &v) noexcept
    {
      data_ = detail::make(eve::as_<target_type>{}, abi_type{}, v);
      return *this;
    }

    //==============================================================================================
    // Raw storage access
    //==============================================================================================
    EVE_FORCEINLINE storage_type const& storage() const & noexcept { return data_; }
    EVE_FORCEINLINE storage_type &      storage() &       noexcept { return data_; }
    EVE_FORCEINLINE storage_type        storage() &&      noexcept { return data_; }

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
    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }

    //==============================================================================================
    // slice interface
    //==============================================================================================
    EVE_FORCEINLINE auto slice() const { return detail::slice(EVE_CURRENT_API{},*this); }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const &s) const
    {
      return detail::slice(EVE_CURRENT_API{},*this, s);
    }

    //==============================================================================================
    // swap
    //==============================================================================================
    EVE_FORCEINLINE void swap(logical &rhs) noexcept
    {
      std::swap(data_, rhs.data_);
    }

    //==============================================================================================
    // Dynamic index lookup
    //==============================================================================================
    template<typename Index>
    EVE_FORCEINLINE logical operator[](wide<Index,Size> const& idx) noexcept
    {
      return bit_cast(lookup(bits(),idx), as(*this));
    }

    //==============================================================================================
    // elementwise access
    //==============================================================================================
    EVE_FORCEINLINE void set(std::size_t i, value_type v) noexcept
    {
      detail::insert(*this, i, v);
    }

    EVE_FORCEINLINE value_type operator[](std::size_t i) const noexcept
    {
      return detail::extract(*this, i);
    }

    EVE_FORCEINLINE value_type back()  const noexcept { return this->operator[](static_size-1); }
    EVE_FORCEINLINE value_type front() const noexcept { return this->operator[](0);             }

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

    //==============================================================================================
    // SIMD register storage
    //==============================================================================================
    private:
    storage_type data_;
  };
}
