.. _function-ldexp:

#####
ldexp
#####

**Required header:** ``#include <eve/function/ldexp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ldexp = {};
   }

Function object. If no errors occur, ``ldexp(x,exp)`` returns ``x`` multiplied by 2 to the power of`` exp`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, wide<U,N> const& m) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, U  n)
   template<typename T,typename U> constexpr    T          operator()( T s,U n ) noexcept;

* [1] Computes the element-wise :math:x2^m`.
* [2] Computes the element-wise :math:x2^n`. 
* [2] Computes :math:s2^n`. 

.. rubric:: Parameters

* **v**, **m**: Instance of :ref:`type-wide`.
* **s**, **n**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.

Notes
******

  -   If the first parameteris of an integral value type the second must be too.

  -   If the second paramter is not of integral value type it is truncated:
     `ldexp(x,n)` is similar to: `x*pow(2, trunc(n))`


Options
*******

     - pedantic_ By default ``ldexp` does not take care of denormal or limiting values.
       Use the  pedantic_ decorator if these are to be properly computed.
     
       - If x is ±0, it is returned, unmodified
       - If x is ±$B!g(B, it is returned, unmodified
       - If exp is 0, then x is returned, unmodified
       - If x is NaN, NaN is returned 

Example
*******

.. include:: ../../../../test/doc/ldexp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/ldexp.txt
  :literal:



 