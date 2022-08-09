//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/cpu/logical.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/conditional.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/bitmask.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>
#include <eve/traits/as_integer.hpp>

#include <cstring>
#include <concepts>
#include <type_traits>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD registers holding logical types with compile-time size
  //!
  //! **Required header:** `#include <eve/logical.hpp>`
  //!
  //! This specialization of eve::logical is an architecture-agnostic representation of a low-level
  //! SIMD register mask and provides standardized API to access informations, compute values and
  //! manipulate such register.
  //!
  //! @tparam Type      Type of value to store in the register
  //! @tparam Cardinal  Cardinal of the register. By default, the best cardinal for current
  //!                   architecture is selected.
  //================================================================================================
  template<arithmetic_scalar_value Type, typename Cardinal>
  struct  EVE_MAY_ALIAS  logical<wide<Type,Cardinal>>
        : detail::wide_storage<as_logical_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>
  {
    using storage_base  = detail::wide_storage<as_logical_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>;

    public:
    //! The type stored in the register.
    using value_type    = logical<Type>;

    //! The ABI tag for this register.
    using abi_type      = abi_t<Type, Cardinal>;

    //! The type used for this register storage
    using storage_type  = typename storage_base::storage_type;

    //! Type describing the number of lanes of current wide
    using cardinal_type = Cardinal;

    //! Type representing the size of the current wide
    using size_type     = std::ptrdiff_t;

    //! Type representing the bits of the logical value
    using bits_type = wide<as_integer_t<Type, unsigned>, Cardinal>;

    //! Type representing the numerical value associated to the mask
    using mask_type = wide<Type, Cardinal>;

    //! @brief Generates a eve::wide from a different type `T` and cardinal `N`.
    //! If unspecified, `N` is computed as `expected_cardinal_t<T>`.
    template<typename T, typename N = expected_cardinal_t<T>> using rebind = logical<wide<T,N>>;

    //! Generates a eve::wide type from a different cardinal `N`.
    template<typename N> using rescale = logical<wide<Type,N>>;

    //! Returns the alignment expected to be used to store a eve::logical
    static EVE_FORCEINLINE constexpr auto alignment() noexcept { return sizeof(Type)*Cardinal::value; }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! Default constructor
    EVE_FORCEINLINE logical() = default;

    //! Constructs from ABI-specific storage
    EVE_FORCEINLINE logical(storage_type const &r) noexcept
      : storage_base( r )
    {}

    //! @brief Constructs a eve::logical from a pair of @iterator.
    //! Construction is done piecewise unless the @iterator{s} are @raiterator{s}.
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : storage_base(load(as<logical>{}, b, e))
    {}

    //! @brief Constructs a eve::logical from a @container.
    //! Construction is done piecewise unless the @iterator{s} extracted from `r` are @raiterator{s}.
    template<detail::range Range>
    EVE_FORCEINLINE explicit logical(Range &&r) noexcept requires(!std::same_as<storage_type, Range>)
                  : logical(std::begin(EVE_FWD(r)), std::end(EVE_FWD(r)))
    {}

    //! Constructs a eve::logical from a SIMD compatible pointer
    template<simd_compatible_ptr<logical> Ptr>
    EVE_FORCEINLINE explicit logical(Ptr ptr) noexcept
                  : storage_base(load(ptr, Cardinal{}))
    {
    }

    //! Constructs a eve::logical by splatting a scalar value in all lanes
    template<scalar_value S>
    EVE_FORCEINLINE explicit logical(S v) noexcept
                  : storage_base(detail::make(eve::as<logical>{}, v)) {}

    //! Constructs a eve::logical from a sequence of scalar values of proper size
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,logical<Type>> && std::convertible_to<T0,logical<Type>>
                    &&  (... && std::convertible_to<Ts,logical<Type>>)
                    &&  (Cardinal::value == 2 + sizeof...(Ts))
                  )
        : storage_base(detail::make(eve::as<logical>{}, v0, v1, vs...))
    {}

    //==============================================================================================
    //! @brief Constructs a eve::logical from a @callable.
    //!
    //! The @callable must satisfy the following prototype:
    //!
    //! @code
    //! T generator(std::ptrdiff_t index, std::ptrdiff_t cardinal);
    //! @endcode
    //! <br/>
    //!
    //! and is supposed to return the value computed from the current index and the cardinal to
    //! store at said index.
    //!
    //! @param g  The @callable to use as a value generator
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/aWa385hKb)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
    //!   std::cout << r << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    template<eve::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                  : storage_base(detail::fill(as<logical>{}, EVE_FWD(g)))
    {}

    //! @brief Constructs a eve::logical by combining two eve::logical of half the current cardinal.
    //! Does not participate in overload resolution if `Cardinal::value != 2 * Half::value`.
    template<typename Half>
    EVE_FORCEINLINE logical ( logical<wide<Type, Half>> const &l
                            , logical<wide<Type, Half>> const &h
                            ) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( Cardinal::value == 2 * Half::value )
#endif
                  : storage_base(detail::combine(eve::current_api, l, h))
    {}

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================

    //! @brief Assignment of a logical value by splatting it in all lanes
    EVE_FORCEINLINE logical& operator=(logical<Type> v) noexcept
    {
      logical that(v);
      swap(that);
      return *this;
    }

    //! @brief Assignment of a boolean value by splatting it in all lanes
    EVE_FORCEINLINE logical& operator=(bool v) noexcept
    {
      logical that( value_type{v} );
      swap(that);
      return *this;
    }

    //! @brief Assignment of an architecture-specific SIMD register
    logical& operator=(storage_type const &r) { storage_base::data_ = r; return *this; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Indexing and reordering
    //! @{
    //==============================================================================================

    //! @brief Size of the wide in number of lanes
    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return Cardinal::value; }

    //! @brief Maximal number of lanes for a given wide
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return Cardinal::value; }

    //! @brief Check if a wide contains 0 lanes
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Conversion from logical to other formats (mask, bits, bitmap)
    //==============================================================================================
    //! @brief Computes a eve::wide containing the bit pattern of current logical.
    //! This bit patterns is contained in a eve::wide of unsigned integral.
    EVE_FORCEINLINE auto bits()   const noexcept { return detail::to_bits(eve::current_api,*this); }

    //! @brief Computes a eve::wide containing the bit pattern of current logical.
    //! This bit patterns is contained in a eve::wide of `Type`.
    EVE_FORCEINLINE auto mask()   const noexcept { return detail::to_mask(eve::current_api,*this); }

    //! Returns a bitset corresponding to the current logical values.
    EVE_FORCEINLINE auto bitmap() const noexcept { return detail::to_bitmap(eve::current_api,*this); }

    //==============================================================================================
    // Logical operations
    //==============================================================================================
    //! Perform a logical and operation between two eve::logical
    template<typename U>
    friend EVE_FORCEINLINE auto operator&&(logical const& v, logical<wide<U, Cardinal>> const& w) noexcept
    {
      return detail::self_logand(eve::current_api,v,w);
    }

    //! Perform a logical and operation between a eve::logical and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&&(logical const& v, S w) noexcept
    {
      return v && logical{w};
    }

    //! Perform a logical and operation between a scalar and a eve::logical
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&&(S v, logical const& w) noexcept
    {
      return w && v;
    }

    //! Perform a logical or operation between two eve::logical
    template<typename U>
    friend EVE_FORCEINLINE auto operator||(logical const& v, logical<wide<U, Cardinal>> const& w) noexcept
    {
      return detail::self_logor(eve::current_api,v,w);
    }

    //! Perform a logical or operation between a eve::logical and a scalar
    friend EVE_FORCEINLINE auto operator||(logical const& v, scalar_value auto w) noexcept
    {
      return v || logical{w};
    }

    //! Perform a logical or operation between a scalar and a eve::logical
    friend EVE_FORCEINLINE auto operator||(scalar_value auto v, logical const& w) noexcept
    {
      return w || v;
    }

    //! Computes the logical complement of its parameter
    friend EVE_FORCEINLINE auto operator!(logical const& v) noexcept
    {
      return detail::self_lognot(v);
    }

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    //! Exchange this value with another eve::logical
    void swap( logical& other ) { std::swap(this->storage(), other.storage()); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //! @brief Swaps the contents of `lhs` and `rhs` by calling `lhs.swap(rhs)`.
    friend EVE_FORCEINLINE void swap(logical &lhs, logical &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    //==============================================================================================
    //! @name Sequence interface
    //! @{
    //==============================================================================================
    //! Set the value of a given lane
    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(*this, i, v);
    }

    //! Retrieve the value from a given lane
    EVE_FORCEINLINE auto get(std::size_t i) const noexcept
    {
      return detail::extract(*this, i);
    }

    //! Retrieve the value of the first lanes
    EVE_FORCEINLINE auto back()  const noexcept { return get(Cardinal::value-1); }

    //! Retrieve the value of the first lane
    EVE_FORCEINLINE auto front() const noexcept { return get(0); }

    //==============================================================================================
    //! @brief Slice a eve::logical into two eve::logical of half cardinal.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/P8W3K7T7q)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the logical<wide> [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
    //!   std::cout << r << "\n";
    //!
    //!   auto[lo,hi] = r.slice();
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    EVE_FORCEINLINE auto slice() const
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Cardinal::value > 1)
#endif
    {
      return detail::slice(*this);
    }

    //==============================================================================================
    //! @brief Return the upper or lower half-sized slice of a eve::logical.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! @see eve::upper_
    //! @see eve::lower_
    //!
    //! @param s A tag indicating which slice is required
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/WjWxP4jqW)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the logical<wide> [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
    //!   std::cout << r << "\n";
    //!
    //!   auto lo = r.slice(eve::lower_);
    //!   auto hi = r.slice(eve::upper_);
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //
    //==============================================================================================
    template<std::size_t Slice>
    EVE_FORCEINLINE auto slice(slice_t<Slice> s) const
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Cardinal::value > 1)
#endif
    {
      return detail::slice(*this, s);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================
    //! @brief Element-wise equality comparison of two eve::logical
    friend EVE_FORCEINLINE logical operator==(logical v, logical w) noexcept
    {
      return detail::self_eq(v,w);
    }

    //! @brief Element-wise equality comparison of a eve::logical and a scalar value
    template<scalar_value S>
    requires requires(S s) { logical{s}; }
    friend EVE_FORCEINLINE logical operator==(logical v, S w) noexcept
    {
      return v == logical{w};
    }

    //! @brief Element-wise equality comparison of a scalar value and a eve::logical
    template<scalar_value S>
    requires requires(S s) { logical{s}; }
    friend EVE_FORCEINLINE logical operator==(S v, logical w) noexcept
    {
      return w == v;
    }

    //! @brief Element-wise inequality comparison of two eve::logical
    friend EVE_FORCEINLINE logical operator!=(logical v, logical w) noexcept
    {
      return detail::self_neq(v,w);
    }

    //! @brief Element-wise inequality comparison of a eve::logical and a scalar value
    template<scalar_value S>
    requires requires(S s) { logical{s}; }
    friend EVE_FORCEINLINE logical operator!=(logical v, S w) noexcept
    {
      return v != logical{w};
    }

    //! @brief Element-wise inequality comparison of a scalar value and a eve::logical
    template<scalar_value S>
    requires requires(S s) { logical{s}; }
    friend EVE_FORCEINLINE logical operator!=(S v, logical w) noexcept
    {
      return w != v;
    }

    //! Inserts a eve::wide into a output stream
    friend std::ostream &operator<<(std::ostream &os, logical const &p)
    {
      auto that = p.bitmap();
      os << '(' << (that[0] ? "true" : "false");
      for(size_type i = 1; i < p.size(); ++i) os << ", " << (that[i] ? "true" : "false");
      return os << ')';
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}
