.. _function-floor:

#####
floor
#####

**Required header:** ``#include <eve/function/floor.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ floor = {};
   }

Function object computing the greatest integral value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise greatest integral values less or equal to the value of the :ref:`wide <type-wide>`.
* [2] Computes the greatest integral value less or equal to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``up_``, ``down_``, ``to_zero_`` and ``to_nearest_int``. This function object
    implements the ``down_`` version.

  - the  call to ``floor(a)`` is equivalent to the call ``round[down_](a)``

Options
*******

Example
*******

.. include:: ../../../../test/doc/floor.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/floor.txt
  :literal:
