.. _function-bitwise_shr:

##############
bitwise_shr
##############

**Required header:** ``#include <eve/function/bitwise_shr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitwise_shr = {};
   }

Function object performing a bitwise shift  to the right of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>` with the same number of elements and same element size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( T                s, wide<U,M> const& w ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s, U t ) noexcept;

* [1] Performs a bitwise shift of each element of **v** by each element of **w**.
* [2] Performs a bitwise shift of each element of **v** by **s**.
* [3] Performs a bitwise shift of **s** by each element of **w**.
* [4] Performs a bitwise shift of **s** by **t**.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` satisfying  the :ref:`IntegralValue <concept-integralvalue>` concept.
* **s**, **t**: Integer values.

.. rubric:: Return value

* [1,2,4] A value with the same type as the first parameter.
* [3] A value of type **wide<T,N>**.

.. rubric:: Notes

* ``bitwise_shr`` is a 'logical' shift that does not preserve the sign of the input : zeros are pushed at the left as the shift process to the right.
* All shift are to be greater or equal to zero and not greater or equal to the size in bit of the element shifted or an assert is issued.

*******
Options
*******

.. seealso::  :ref:`bitwise_shr <function-bitwise_shr>`

*******
Example
*******

.. include:: ../../../../test/doc/core/bitwise_shr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bitwise_shr.txt
  :literal:
