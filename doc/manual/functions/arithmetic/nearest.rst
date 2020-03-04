.. _function-nearest:

#######
nearest
#######

**Required header:** ``#include <eve/function/nearest.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nearest = {};
   }

Function object computing the rounding of the  value of a :ref:`Value <concept-value>`.
If a value is an half-integer it is rounded to the nearest even value.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise the nearest integral values to the value of the :ref:`wide <type-wide>`.
* [2] Computes the nearest integral value to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``to_nearest_`` version.

  - the  call to ``nearest(a)`` is equivalent to the call ``round(a, to_nearest_)``

  - half-integral values are rounded to the nearest even integral

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/nearest.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/nearest.txt
  :literal:
