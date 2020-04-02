.. _function-hypot:

#####
hypot
#####

**Required header:** ``#include <eve/function/hypot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ hypot = {};
   }

Function object Computing the square root of the sum of the squares of:ref:`IEEEValue <ieeeconcept-value>`  x and y.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  std::pair<wide<T,N>, wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    std::pair<T, T>                 operator()( T s ) noexcept;

* [1] Computes a pair : a normalized fraction and an flint exponent of two.
* [2] Computes a pair : a normalized fraction and an flint exponent of two.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A pair of values with the same type as the parameters. 

Notes
*****

  With the pedantic_ decorator
  -  hypot(x, y), hypot(y, x), and hypot(x, -y) are equivalent
  -  if one of the arguments is :math:``\pm0`, hypot(x,y) is equivalent to  :ref:`abs <function-abs` called with the non-zero argument
  -  if one of the arguments is :math:``\pm\infty` hypot(x,y) returns math:``\infty` even if the other argument is NaN
  -  otherwise, if any of the arguments is NaN, NaN is returned 


Options
*******
 withh the pedantic_ option the computation is made without undue overflow or underflow at intermediate stages of the computation

.. seealso::  :ref:`abs <function-abs>`

Example
*******

.. include:: ../../../../test/doc/core/hypot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/hypot.txt
  :literal:
