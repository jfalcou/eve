.. _function-iround:

######
iround
######

**Required header:** ``#include <eve/function/iround.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ iround = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  as_integer_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    as_integer_t<T>         operator()( T s ) noexcept;

* [1] Computes the element-wise the round integral values to the value of the :ref:`wide <type-wide>`.
* [2] Computes the round integral value to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``. This function object
    by default implements the ``to_nearest_`` version.

  - the  call to ``iround(a)`` is equivalent to the call ``inearest(a)``

Options
*******

  this object function can be called with an optional tag parameter that change its meaning:

  - ``iround(a, to_nearest_ )`` is equivalent to the call ``inearest(a)``
  - ``iround(a, toward_zero_)`` is equivalent to the call ``itrunc(a)``
  - ``iround(a, upward_ )`` is equivalent to the call ``iceil(a)``
  - ``iround(a, downward_)`` is equivalent to the call ``ifloor(a)``

Example
*******

.. include:: ../../../../test/doc/core/iround.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/iround.txt
  :literal:
