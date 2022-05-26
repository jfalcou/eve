//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/polynom.hpp>
#include <algorithm>
#include <map>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //===============================================================================================
  //! @brief representation of sparse polynoms
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! eve::polynom and monom are templates structure representing respactivly polynomials with real
  //! or complex floating coefficients (resp polynomials with only one non zero coefficient).
  //! polynomials are internally based on std:vectors of coefficients on the fundamental basis and in
  //! decreasing powers order, but:
  //!
  //!  \f$ \displaystyle p(x) = \sum_0^n p[i]x^{i]\f$
  //!
  //!
  //! @tparam Type  Underlying scalar floating point type
  //!
  //! provided operators and functions are :
  //!
  //! - constructors
  //!    - trivial constructor provides the null polynomial (of degree -1) with no coefficients
  //!    - a constructor from a range of coefficients in decreasing power order
  //!    - a constructor from an initializer list of coefficients in decreasing power order
  //!    - a constructor from a range of elements in increasing power order (with second parameter eve::upward);
  //!
  //! - operators :
  //!     - +,  -, *, /, %, +=, -=, *=, /=, %=, <<, >>
  //!
  //!       binary operators accept mix of polynom, momom, value_type in any order.
  //!       monomial multiplication can be replaced by shift operators
  //!       division and remainder with null second parameter are UB.
  //!
  //!    - operator(): p(x) evaluates the polynomial p at x. x can be a scalar, an simd value or a range of scalar
  //!                  of the underlying type
  //!                  Take care that if a non const range is evaluted,  it is evaluated in place
  //!    - operator[]: p[i] return the coefficient of order i of the polynomial (i.e. of the monomial \f$x^i\f$.
  //!                  In particular 0 if i is not in the range \f$[0, degree(p)]\f$. (This operator is const).
  //!    - operator==: Two polynomials are equal if and only if they have the same degree and the same coefficients.
  //!    - operator!=: Two polynomials are not equal if and only if they do not have the same degree or two coefficients differ.
  //!
  //!@warning : this is a simple polynomial class not fit for big or sparse polynomials,  but for monomials or
  //!           dense polynomials of small degrees (in particular fft is not used for implementing *
  //!           (i.e. polynomial multiplication which could be written as a convolution)
  //!
  //! - friend functions
  //!     - degree returns the polynomial degree, i.e. the greatest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - valuation returns the polynomial valuation i.e. the lest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - remquo computes both the quotient and remainder of euclidian division
  //!     - young(n, p0) suppress all coefficients of degree greater than n,  thus giving the regular part
  //!       of the Taylor-Young devlopment of the polynom
  //!     - young_remainder(n, p0) zeroes all the lower n coefficients of p0 : one have
  //!       young(n, p0)+young_remainder(n, p0) == p0.
  //!       concat(p1, p0) if n is the degree of p0, return the polynom \f$x^{n+1}p1+p0\f$.
  //!     - is_null returns true if and only if the polynomial is of degree -1
  //!     - is_constant returns true if and only if the polynomial is of degree less than 1
  //!     - is_monomial returns true if and only if the polynomial has only one non null coef
  //!     - derivative(p, n) computes the nth derivative of p
  //!     - primive(p, n)    computes a primitive of order n of p (the one with valuation greater or equal to n)
  //!
  //================================================================================================


  template<floating_scalar_value Type>
  struct sparse_polynom
  {
    /// Underlying type
    using value_type = Type;
    using sparse_polynom_t  = sparse_polynom<value_type>;
    using data_t     = std::map<int, value_type, std::greater<int>>;
    using pair_t     = typename data_t::value_type;
    using monom_t    = monom<value_type>;
    using polynom_t  = polynom<value_type>;

    // constructors
    sparse_polynom() {}

    sparse_polynom(value_type const & v) : data{{0, v}}{};
    sparse_polynom(std::initializer_list<pair_t> const & c) : data(c) { normalize();}

    template <detail::range R>
    sparse_polynom(R const & r) : data(r.begin(), r.end()) { normalize();}

    sparse_polynom(monom_t const & m) : data{{degree(m), m[0]}} {};
    sparse_polynom(polynom_t const & p) {
      for(int i=0; i <= degree(p); ++i) data[i] = p[i];
      normalize();
    }

    //==============================================================================================
    //== degree and valuation
    //==============================================================================================
    friend inline int degree(sparse_polynom_t const & p) noexcept
    {
      return p.data.empty() ? -1 : p.data.begin()->first;
    }

    friend inline int valuation(sparse_polynom_t const & p) noexcept
    {
      return p.data.empty() ? -1 :p.data.rbegin()->first;
    }

    //==============================================================================================
    //== coefficients but only for reading.
    //== Out of range returns 0
    //==============================================================================================
    auto operator[](int const & i) const noexcept
    {
      auto search = data.find(i);
      return (search != data.end()) ? search->second : zero(as<value_type>());
    }

    //==============================================================================================
    //== evaluation
    //==============================================================================================
    template <floating_value T>
    auto operator()(T const & x) noexcept
    {
      auto s = T(0);
      for (const auto& [i, value] : data) { s+= pow(x, i)*value; }
      return s;
    }

    template <detail::range R>
    friend void tagged_dispatch( eve::tag::polyval_, inplace_type const&
                               , sparse_polynom_t const & p, R & x)  noexcept
    {
      auto eval = [ p ](auto e){
        auto s = zero(as(e));
        for (const auto& [i, value] : p.data) { s+= eve::pow(e, i)*value; }
        return s;
      };
      eve::algo::transform_inplace(x, eval);
    }

    template <detail::range R>
    friend  R tagged_dispatch( eve::tag::polyval_, sparse_polynom_t const & p, const R & x)  noexcept
    {
      return p(x);
    }

    template <detail::range R> [[nodiscard]] R operator()(R const & x) const noexcept
    {
      auto px(x);
      auto eval = [ this ](auto e){
        auto s = zero(as(e));
        for (const auto& [i, value] : data) { s+= pow(e, i)*value; }
        return s;
      };
      eve::algo::transform_inplace(px, eval);
      return px;
    }

    //==============================================================================================
    //== derivatives
    //==============================================================================================

    [[nodiscard]] friend sparse_polynom_t & tagged_dispatch( eve::tag::derivative_, sparse_polynom_t & p) noexcept
    {
      value_type n = degree(p);
      sparse_polynom_t der(p); 
      if(n < 1) return sparse_polynom_t();
      else
      {
        for (const auto& [i, value] : p.data) { der[i-1] = i*e; }
        return der.normalize(); 
      }
    }


    friend sparse_polynom_t tagged_dispatch( eve::tag::derivative_
                                   ,  sparse_polynom_t & p, size_t m) noexcept
    {
      int n = degree(p);
      if (int(m) > n)  { return sparse_polynom_t() }
      else if (int(m) == n) { return sparse_polynom_t{value_type(factorial(m)), 0};}
      else if (m == 0) return p;
      else if (m == 1) return derivative(p);
      else
      {
        std::vector<value_type> f(p.size()); 
        std::transform(p.data.begin(), p.data.end(), f.begin(), [](auto pair){return pair.first});
        auto factors(f);                       
        auto mult = [](auto pair){
          auto [x, y] = pair; 
          return x *= y;
        };
        for(size_t i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, dec);
          eve::algo::transform_to(eve::algo::views::zip(factors, f), factors, mult);
        }
        sparse_polynom_t der; 
        for (const auto& [i, v] : p.data) { if(i >= m) der[i-m] = f[i]*v;} }       
        return der.normalize();
      }
    }



//     [[nodiscard]] friend auto tagged_dispatch( eve::tag::derivative_, sparse_polynom_t const & p
//                                              , size_t m, eve::callable_all_) noexcept
//     {
//       int n = degree(p);
//       std::vector<sparse_polynom_t> ders(m+1);
//       ders[0] = p;
//       if (m == 0 || n <= 0) return ders;
//       ders[1] = derivative(p);
//       if (m == 1) return ders;
//       value_type nvt = n;
//       auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), nvt+1);
//       data_t f(n+1);
//       data_t datad(n+1);
//       eve::algo::copy(factors, datad);
//       eve::algo::copy(factors, f);
//       auto mult = [](auto pair) {
//         auto [x, y] = pair;
//         return x *= y;
//       };
//       eve::algo::transform_to(eve::algo::views::zip(datad, p.data), datad, mult);

//       for(size_t i=2; i <= eve::min(size_t(n), m); ++i)
//       {
//         eve::algo::transform_inplace(f, dec);
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, mult);
//         datad.resize(n-i+1);
//         f.resize(n-i+1);
//         ders[i] = sparse_polynom_t(datad);
//       }
//       return ders;
//     }

//     //==============================================================================================
//     //== primitives
//     //==============================================================================================
//     friend sparse_polynom_t & tagged_dispatch( eve::tag::primitive_
//                                       , inplace_type const &, sparse_polynom_t & p) noexcept
//     {
//       int n = degree(p);
//       if(n < 0) return p;
//       else if(n <= 1){ p.data.resize(n); return p;}
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//         auto divi = [](auto pair){
//           auto [x, y] = pair;
//           return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, factors), p.data, divi);
//         p.data.resize(n+2);
//         return p;
//       }
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_
//                                                   , sparse_polynom_t const & p) noexcept
//     {
//       int n = degree(p);
//       if(n < 0) return sparse_polynom_t();
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//         data_t datad(n+1);
//         eve::algo::copy(p.data, datad);
//         auto divi = [](auto pair){
//             auto [x, y] = pair;
//             return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(datad, factors), datad, divi);
//         datad.resize(n+2);
//         sparse_polynom_t prim(datad);
//         return prim;
//       }
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_, sparse_polynom_t & p
//                                     , size_t m) noexcept
//     {
//       int n = degree(p);
//       if (m == 0 || n < 0) return p;
//       else if (m == 1u) return primitive(p);
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
//         data_t f(n+1);
//         data_t datad(n+1);
//         eve::algo::copy(p.data, datad);
//         eve::algo::copy(factors, f);
//         auto divi = [](auto pair)
//           {
//             auto [x, y] = pair;
//             return x /= y;
//           };
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         for(size_t i=2; i <= m; ++i)
//         {
//           eve::algo::transform_inplace(f, inc);
//           eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         }
//         datad.resize(n+m+1);
//         sparse_polynom_t integ(datad);
//         return integ;
//       }
//     }

//     friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_, inplace_type const &
//                                     , sparse_polynom_t & p, size_t m) noexcept
//     {
//       int n = degree(p);
//       if (m == 0 || n < 0) return p;
//       else if (m == 1u) return inplace(primitive)(p);
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
//         data_t f(n+1);
//         eve::algo::copy(factors, f);
//         auto divi = [](auto pair) {
//           auto [x, y] = pair;
//           return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
//         for(size_t i=2; i <= m; ++i)
//         {
//           eve::algo::transform_inplace(f, inc);
//           eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
//         }
//         p.data.resize(n+m+1);
//         return p;
//       }
//     }

//     [[nodiscard]] friend auto tagged_dispatch( eve::tag::primitive_
//                                              , sparse_polynom_t const & p, size_t m
//                                              , eve::callable_all_) noexcept
//     {
//       int n = degree(p);
//       std::vector<sparse_polynom_t> prims(m+1);
//       prims[0] = p;
//       if (m == 0 || n <= 0) return prims;
//       prims[1] = primitive(p);
//       if (m == 1) return prims;
//       value_type nvt = n+1;
//       auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//       data_t f(n+1);
//       data_t datad(n+1);
//       eve::algo::copy(p.data, datad);
//       eve::algo::copy(factors, f);
//       auto divi = [](auto pair) {
//         auto [x, y] = pair;
//         return x /= y;
//       };
//       eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);

//       for(size_t i=2; i <= m; ++i)
//       {
//         eve::algo::transform_inplace(f, inc);
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         prims[i] = sparse_polynom_t(datad);
//         prims[i].data.resize(n+i+1);
//       }
//       return prims;
//     }

    //==============================================================================================
    //=== operators
    //==============================================================================================

    //==============================================================================================
    //=== operator+ family
    //==============================================================================================
    friend sparse_polynom_t operator+(sparse_polynom_t const & p0)
    {
      return p0;
    }

    template < typename Other>
    friend sparse_polynom_t operator+(sparse_polynom_t const & p0, Other const & v)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      sparse_polynom_t r(p0);
      return r += v;
    }

    template < typename Other>
    friend sparse_polynom_t operator+(Other const & v, sparse_polynom_t const & p0)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t> {}))
    {
      return p0+v;
    }

    template < typename Other>
    sparse_polynom_t & operator+= (Other const & other)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      if constexpr(std::same_as<Other, value_type>)
      {
        data[0]+= other;
      }
      else if constexpr(std::same_as<Other, monom_t>)
      {
        data[degree(other)]+= coef(other);
      }
      else if  constexpr(std::same_as<Other, sparse_polynom_t>)
      {
        for (const auto& [i, value] : other.data)
        {
          data[i] += value;
        }
      }
      else if  constexpr(std::same_as<Other, polynom_t>)
      {
        auto d = degree(other);
        for (int i = 0; i <= d;  ++i) data[i] += other[i];
      }
      return normalize();
    }

    //==============================================================================================
    //=== leading term
    //==============================================================================================
    friend monom_t lead(sparse_polynom_t const & p0)
    {
      if (is_null(p0)) return monom_t();
      else
      {
        monom_t m(p0.data.begin()->second, p0.data.begin()->first);
        return m;
      }
    }


    //==============================================================================================
    //=== operator- family
    //==============================================================================================
    friend sparse_polynom_t operator-(sparse_polynom_t const & p0)
    {
      sparse_polynom_t r(p0);
      for (const auto& [i, value] : r.data) r.data[i] = -value;
      return r;
    }

    template < typename Other>
    sparse_polynom_t & operator-= (Other const & other)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      if constexpr(std::same_as<Other, value_type>)
      {
        data[0]-= other;
      }
      else if constexpr(std::same_as<Other, monom_t>)
      {
        data[degree(other)]-= coef(other);
      }
      else if  constexpr(std::same_as<Other, sparse_polynom_t>)
      {
        for (const auto& [i, v] : other.data)
        {
         data[i] -= v;
        }
      }
      else if  constexpr(std::same_as<Other, polynom_t>)
      {
        auto d = degree(other);
        for (int i = 0; i <= d;  ++i) data[i] -= other[i];
      }
      return normalize();
    }

    template < typename Other>
    friend sparse_polynom_t operator-(sparse_polynom_t const & p0, Other const & v)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      sparse_polynom_t r(p0);
      return r -= v;
    }

    template < typename Other>
    friend sparse_polynom_t operator-(Other const & v, sparse_polynom_t const & p0)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t> {}))
    {
      return -(p0-v);
    }

    //=== operator* family
    template < typename Other>
    friend sparse_polynom_t operator*(sparse_polynom_t const & p0, Other const &  p1)
      requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      sparse_polynom_t r(p0);
      return r*= p1;
    }

    template < typename Other>
    friend sparse_polynom_t operator*(Other const &  p0, sparse_polynom_t const & p1)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t> {}))
    {
      sparse_polynom_t r(p1);
      return r*= p0;
    }

    template < typename Other>
    sparse_polynom_t & operator*= (Other const & other)
    requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t, sparse_polynom_t> {}))
    {
      if constexpr(std::same_as<Other, value_type>)
      {
        for (auto cur = data.begin(); cur != data.end();  ++cur) cur->second *= other;
      }
      else if constexpr(std::same_as<Other, monom_t>)
      {
        sparse_polynom_t r;
        int d = degree(other);
        value_type c = coef(other);
        for (const auto& [i, v] : data) r.data[i+d] = v*c;
        *this = r;
      }
      else if  constexpr(std::same_as<Other, sparse_polynom_t>)
      {
        sparse_polynom_t r;
        for (const auto& [i, v] : other.data )
        {
          auto z = monom_t(v, i);
          r += (*this)*z;
        }
        *this = r;
      }
      else if  constexpr(std::same_as<Other, polynom_t>)
      {
        sparse_polynom_t r;
        for (const auto& [j, v] : data )
        {
          auto z = monom_t(v, j);
          r+= other*z;
        }
        *this = r;
      }
      return normalize();
    }

    //==============================================================================================
    //=== operator/ family and remquo
    //==============================================================================================
    friend kumi::tuple<sparse_polynom_t, sparse_polynom_t> remquo(sparse_polynom_t const & num, sparse_polynom_t const & den)
    {
      int const dnum = degree(num);
      int const dden = degree(den);
      if (dden == -1) return {den, sparse_polynom_t()};
      if (dnum == 0) {
        if (is_null(den)) return  {den, sparse_polynom_t()};
        else return {sparse_polynom_t(), num*rec(den.data.begin()->second)};
      }
      if (dnum < dden) return {num, sparse_polynom_t()};
      else
      {
        sparse_polynom_t r(num);
        sparse_polynom_t q;
        monom_t md = lead(den);
        while (degree(r) >= 0 && degree(r) >= dden)
        {
          auto t = lead(r)/md;
          q += t;
          r -= t*den;
        }
        return {r, q};
      }
    }

    template < typename Other>
    friend kumi::tuple<sparse_polynom_t, sparse_polynom_t> remquo(sparse_polynom_t const & p0, Other const & other)
      requires(is_one_of<Other>(detail::types<monom_t, value_type, polynom_t> {}))
    {
      if constexpr(std::same_as<Other, value_type>)
      {
        return {sparse_polynom_t(), p0*rec(other)};
      }
      else if constexpr(std::same_as<Other, monom_t>)
      {
        int const dnum = degree(p0);
        int const dden = degree(other);
        if (dden == -1) return {sparse_polynom_t(), sparse_polynom_t()};
        if (dnum == 0) {
          return {sparse_polynom_t(), p0*rec(other.coef())};
        }
        if (dnum < dden)
          return {p0, sparse_polynom_t()};
        else
        {
          sparse_polynom_t r(p0);
          sparse_polynom_t q;
          while (degree(r) >= 0 && degree(r) >= dden)
          {
            auto t = lead(r)/other;
            q += t;
            r -= t*other;
          }
          return {r, q};
        }
      }
      else if  constexpr(std::same_as<Other, sparse_polynom_t>)
      {
        int const dden = degree(p0);
       if (dden == -1) return {other, sparse_polynom_t()};
        int const dnum = degree(other);
        if (dnum == 0) {
          if (is_null(other)) return  {other, sparse_polynom_t()};
          else return {sparse_polynom_t(), p0*rec(coef(lead(other)))};
        }
        if (dnum < dden) return {p0, sparse_polynom_t()};
        else
        {
          sparse_polynom_t r(p0);
          sparse_polynom_t q;
          monom_t md = lead(other);
          while (degree(r) >= 0 && degree(r) >= dden)
          {
            auto t = lead(r)/md;
            q += t;
            r -= t*other;
          }
          return {r, q};
        }
      }
      else if  constexpr(std::same_as<Other, polynom_t>)
      {
        sparse_polynom_t sp1(other);
        return remquo(p0, sp1);  // TODO
      }
   }

//     template < typename O>
//     friend sparse_polynom_t operator/(sparse_polynom_t const & p0, O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       if constexpr(std::same_as<O, value_type>)
//       {
//         auto fac =  rec(p1);
//         return (is_not_finite(fac) || is_eqz(fac)) ? sparse_polynom_t() : p0*fac;
//       }
//       else
//       {
//         auto [_, q] = remquo(p0, p1);
//         return q;
//       }
//     }

//     template < typename O>
//     auto operator/= (O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       return *this = *this/p1;
//     }

//     template < typename O>
//     friend sparse_polynom_t operator%(sparse_polynom_t const & p0, O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       if constexpr(std::same_as<O, value_type>)
//       {
//         return sparse_polynom_t();
//       }
//       else
//       {
//         auto [r, _] = remquo(p0, p1);
//         return r;
//       }
//     }

//     template < typename O>
//     auto operator%= (O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       return *this = *this%p1;
//     }

//     //==============================================================================================
//     //=== young and young_remainder
//     //==============================================================================================

//     friend sparse_polynom_t young(int n, sparse_polynom_t const & p0)
//     {
//       auto d = degree(p0);
//       if (n >= d)
//         return p0;
//       else if (n == -1)
//         return sparse_polynom_t();
//       else
//         return sparse_polynom_t(eve::algo::as_range(p0.data.begin()+d-n, p0.data.end()));
//     }

//     friend sparse_polynom_t young_remainder(int n, sparse_polynom_t const & p0)
//     {
//       auto d = degree(p0);
//       if (n > d)
//         return sparse_polynom_t();
//       else if (n == -1)
//         return p0;
//       else
//       {
//         sparse_polynom_t yr(p0);
//         eve::algo::fill(eve::algo::as_range(yr.data.begin()+d-n, yr.data.end()), value_type(0));
//         return yr;
//       }
//     }

//     //==============================================================================================
//     //=== concat
//     //==============================================================================================
//     friend sparse_polynom_t concat(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
//     {
//       auto d = degree(p0);
//       if (d == -1) return p1;
//       else return p0+monom_t(value_type(1), d+1)*p1;
//     }


    //==============================================================================================
    //=== operator ==  and !=
    //==============================================================================================
    friend bool operator==(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
    {
      return p0.data.size() == p1.data.size()
        && std::equal(p0.data.begin(), p0.data.end(), p1.data.begin());
    }

    friend bool operator!=(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
    {
      return p0.data.size() != p1.data.size()
        || !std::equal(p0.data.begin(), p0.data.end(), p1.data.begin());
    }

    friend bool operator==( monom_t const & p0, sparse_polynom_t const & p1)
    {
      return p1 == p0;
    }

    friend bool operator==(sparse_polynom_t const & p0, monom_t const & p1)
    {
      return is_monomial(p0) && (lead(p0) == p1);
    }

    friend bool operator!=( monom_t const & p0, sparse_polynom_t const & p1)
    {
      return p1 != p0;
    }

    friend bool operator!=(sparse_polynom_t const & p0, monom_t const & p1)
    {
      return !is_monomial(p0) || (lead(p0) != p1);
    }

    //==============================================================================================
    //=== predicates
    //==============================================================================================

    friend bool is_null(sparse_polynom_t const & p0)
    {
      return p0.data.empty();
    }

    friend bool is_constant(sparse_polynom_t const & p0)
    {
      return degree(p0) <=  0;
    }

    friend bool is_monomial(sparse_polynom_t const & p0)
    {
      return degree(p0) == valuation(p0);
    }

    //==============================================================================================
    //=== ostream
    //==============================================================================================
    template <class charT, class traits> friend
    inline std::basic_ostream<charT, traits>&
    operator << (std::basic_ostream<charT, traits>& os, const sparse_polynom<value_type>& poly)
    {
      os << std::noshowpos;
      if (poly.data.empty())
        return os << value_type(0);
      else
      {
        for (const auto& [i, value] : poly.data) {
          auto show = false;
          auto neg = is_ltz(value);
          auto z = eve::abs(value);
          if(eve::abs(z) == one(as(z)) && (i!= 0))
          {
            os << (neg ? "-" : (show ? "+" : ""));
            show = true;
          }
          else
          {
            if (show) os << std::showpos;
            os << value;
            show = true;
          }
          if (i!=  0) os << "x";
          if (i > 1 ) os << "^" <<  std::noshowpos << i << std::showpos;
        }
      }
      return os << std::noshowpos;
    }

    sparse_polynom_t & normalize()
    {
      std::erase_if (data, [](const auto& item){ auto const & [i, v] = item; return is_eqz(v); });
      return *this;
    }

  private :
    data_t data;
  };
}
