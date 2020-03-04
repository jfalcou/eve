.. _function-rshl:

####
rshl
####

**Required header:** ``#include <eve/function/rshl.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rshl = {};
   }

Function object performing a relative shift to the left or the right of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>`  with the same number of elements and same element size. The shift direction is left
(resp. right) if the shift is positive (resp. negative)

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( T                s, wide<U,M> const& w ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s, U t ) noexcept;

* [1] Performs a bitwise left or right shift of each element of **v** by each element of **w**.
* [2] Performs a bitwise left or right shift of each element of **v** by **s**.
* [3] Performs a bitwise left or right shift of **s** by each element of **w**.
* [4] Performs a bitwise left or right shift of **s** by **t**.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying  the :ref:`IntegralValue <concept-integralvalue>` concept.
* **s**, **t**: Integer values.

.. rubric:: Return value

* [1,2,4] A value with the same type as the first parameter.
* [3] A value of type **wide<T,N>**.

.. rubric:: Notes

*  shifts  greater or equal to zero are to the left, less or equal to zero to the right.
*  shifts absolute values must not be greater or equal to the size in bit of the element shifted or an assert is issued.

*******
Options
*******

.. seealso::  :ref:`rshr <function-rshl>`,  :ref:`shl <function-rshl>`,  :ref:`shr <function-rshl>`,  
         :ref:`bit_shl <function-bit_shl>`,  :ref:`bit_shr <function-bit_shr>`

*******
Example
*******

.. include:: ../../../../test/doc/core/rshl.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rshl.txt
  :literal:
