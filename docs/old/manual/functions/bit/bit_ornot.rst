.. _function-bit_ornot:

##############
bit_ornot
##############

**Required header:** ``#include <eve/function/bit_ornot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_ornot = {};
   }

Function object performing a bit OR between a :ref:`Value <concept-value>` and the COMPLEMENT of
another :ref:`Value <concept-value>` of the same bit size.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const& y ) noexcept;

* Performs a bit OR between ``x`` and the bitwise COMPLEMENT of ``y`` .

Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of :ref:`Value <concept-value>`.
* All parameters must share the same global size.

Return value
************

*  A value with the same type as the first parameter.

Notes
*****

* There is no type restriction between operands of :ref:`function-bit_ornot` as long as the number
  of bits between them are equals. This implies that calls to :ref:`function-bit_and` on
  :ref:`Ieee Values <concept-ieeevalue>` are possible as long as they are performed with a
  second parameters of proper size.

* There is no cardinal restriction on the :ref:`concept-vectorized` operands of :ref:`function-bit_ornot`
  as long as the number of bits between them are equals.  This implies that calls to :ref:`function-bit_and`
  on :ref:`concept-vectorized` values of different cardinals are allowed as long as their total size
  in bits are equal.

Example
*******

.. include:: ../../../../test/doc/core/bit_ornot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_ornot.txt
  :literal:
