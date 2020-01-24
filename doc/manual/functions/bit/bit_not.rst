.. _function-bit_not:

##############
bit_not
##############

**Required header:** ``#include <eve/function/bit_not.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_not = {};
   }

Function object performing a bit COMPLEMENT of a :ref:`Value <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename N> wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s ) noexcept;

* [1] Performs the bit COMPLEMENT of **v**.
* [2] Performs the bit COMPLEMENT of **s**.

.. rubric:: Parameters

* **v**, **w**: Instance of :ref:`type-wide` .
* **s**, **t**: Scalar value.

.. rubric:: Return value

* [1,2,3] A value with the same type as the parameter.

.. rubric:: Notes

* There is no type restriction on the parameter  :ref:`Value <concept-value>` type of :ref:`function-bit_not`.
  This implies that calls to :ref:`function-bit_not` on :ref:`IEEEvalues <concept-IEEEvalue>` are possible.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_not.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_not.txt
  :literal:
