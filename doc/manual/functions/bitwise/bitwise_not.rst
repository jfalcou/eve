.. _function-bitwise_not:

##############
bitwise_not
##############

**Required header:** ``#include <eve/function/bitwise_not.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitwise_not = {};
   }

Function object performing a bitwise COMPLEMENT of a :ref:`Value <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename M, typename N> wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s ) noexcept;

* [1] Performs the bitwise COMPLEMENT of **v**.
* [2] Performs the bitwise COMPLEMENT of **s**.

.. rubric:: Parameters

* **v**, **w**: Instance of :ref:`type-wide` .
* **s**, **t**: Scalar value.

.. rubric:: Return value

* [1,2,3] A value with the same type as the parameter.

.. rubric:: Notes

* There is no type restriction on the parameter  :ref:`Value <concept-value>` type of :ref:`function-bitwise_not`.
  This implies that calls to :ref:`function-bitwise_not` on :ref:`IEEEvalues <concept-IEEEvalue>` are possible.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/bitwise_not.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/bitwise_not.txt
  :literal:
