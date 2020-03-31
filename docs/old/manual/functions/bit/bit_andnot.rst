.. _function-bit_andnot:

##############
bit_andnot
##############

**Required header:** ``#include <eve/function/bit_andnot.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_andnot = {};
   }

Function object performing a bit AND between a :ref:`Value <concept-value>` and the COMPLEMENT of
another :ref:`Value <concept-value>` of the same bit size.

Synopsis
********

.. code-block:: c++

   template<typename T, typename U> auto operator()( T const& x, U const& y ) noexcept;

* Performs a bit AND between ``x`` and the bitwise COMPLEMENT of ``y`` .

Parameters
**********

* Each parameter ``x`` and ``y`` must be an instance of :ref:`Value <concept-value>`.
* All parameters must share the same global size.

Return value
************

*  A value with the same type as the first parameter.

Notes
*****

* There is no type restriction between operands of :ref:`function-bit_andnot` as long as the number
  of bits between them are equals. This implies that calls to :ref:`function-bit_and` on
  :ref:`Ieee Values <concept-ieeevalue>` are possible as long as they are performed with a
  second parameters of proper size.

* There is no cardinal restriction on the :ref:`concept-vectorized` operands of :ref:`function-bit_andnot`
  as long as the number of bits between them are equals.  This implies that calls to :ref:`function-bit_and`
  on :ref:`concept-vectorized` values of different cardinals are allowed as long as their total size
  in bits are equal.

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_andnot.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_andnot.txt
  :literal:
