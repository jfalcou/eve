.. _function-round:

#####
round
#####

**Required header:** ``#include <eve/function/round.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ round = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise the round integral values to the value of the :ref:`wide <type-wide>`.
* [2] Computes the round integral value to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``up_``, ``down_``, ``to_zero_`` and ``to_nearest_int_``. This function object
    by default implements the ``to_nearest_int_`` version.

  - the  call to ``round(a)`` is equivalent to the call ``nearest(a)``

  - half-integral values are rounded to the round even integral

Options
*******

  this object function can be called with an optional tag parameter that change its meaning:
 
  - ``round[to_nearest_int_](a)`` is equivalent to the call ``nearest(a)``
  - ``round[to_zero_](a)`` is equivalent to the call ``trunc(a)``
  - ``round[up_](a)`` is equivalent to the call ``ceil(a)``     
  - ``round[down_](a)`` is equivalent to the call ``floor(a)``

Example
*******

.. include:: ../../../../test/doc/round.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/round.txt
  :literal:
