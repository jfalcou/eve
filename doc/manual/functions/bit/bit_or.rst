.. _function-bit_or:

###########
bit_or
###########

**Required header:** ``#include <eve/function/bit_or.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_or = {};
   }

Function object performing a bit OR between two :ref:`Values <concept-value>` of same size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U>             wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename U> constexpr               T         operator()( T s, U t ) noexcept;

* [1] Performs a bit OR between both :ref:`wide <type-wide>`.
* [2] Performs a bit OR between the scalar and each elements of the :ref:`type-wide` instance.
* [3] Performs a bit OR between both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying ``sizeof(v) == sizeof(w)``.
* **s**, **t**: Scalar values of type **U** satisfying ``sizeof(T) == sizeof(U)``.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.

.. rubric:: Notes

* There is no type restriction between operands of :ref:`function-bit_or` as long as the number
  of bits between them are equals. This implies that calls to :ref:`function-bit_or` on
  :ref:`concept-ieeevalue` are possible as long as they are performed with a
  second parameters of proper size.

* There is no cardinal restriction on the :ref:`concept-vectorized` operands of :ref:`function-bit_or`
  as long as the number of bits between them are equals.  This implies that calls to :ref:`function-bit_or`
  on :ref:`concept-vectorized` values of different cardinals are allowed as long as their total size
  in bits are equal.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_or.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_or.txt
  :literal:
