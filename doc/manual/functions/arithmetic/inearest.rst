.. _function-inearest:

########
inearest
########

**Required header:** ``#include <eve/function/inearest.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ inearest = {};
   }

Function object computing the rounding of the  value of a :ref:`Value <concept-value>`.
If a value is an half-integer it is rounded to the nearest even value.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  as_integer_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    as_integer_t<T>         operator()( T s ) noexcept;

* [1] Computes the element-wise the inearest integral values to the value of the :ref:`wide <type-wide>`.
* [2] Computes the inearest integral value to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_inearest``. This function object
    implements the ``to_inearest_`` version.

  - the  call to ``inearest(a)`` is equivalent to the call ``iround[to_inearest_](a)``

  - half-integral values are rounded to the inearest even integral

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/inearest.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/inearest.txt
  :literal:
