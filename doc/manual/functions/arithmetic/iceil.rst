.. _function-iceil:

#####
iceil
#####

**Required header:** ``#include <eve/function/iceil.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ iceil = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  as_integer_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    as_integer_t<T>         operator()( T s ) noexcept;

* [1] Computes the element-wise least integral values greater or equal to the value of the :ref:`wide <type-wide>`.
* [2] Computes the least integral value greater or equal to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value of the integral type associated to the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``upward_`` version.

  - the call to ``iceil(a)`` is equivalent to the call ``iround[upward_](a)``

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/iceil.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/iceil.txt
  :literal:
