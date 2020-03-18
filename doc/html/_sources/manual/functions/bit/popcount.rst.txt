.. _function-popcnt:

########
popcount
########

**Required header:** ``#include <eve/function/popcount.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ popcount = {};
   }

Function object computing the bit count  of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr as_integer_t<T> operator()( T const & x ) noexcept;

*  Computes element-wise the bit count of the :ref:`Value <concept-value>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value of the integral type associated to the parameter.

Example
*******

.. include:: ../../../../test/doc/core/popcount.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/popcount.txt
  :literal:
