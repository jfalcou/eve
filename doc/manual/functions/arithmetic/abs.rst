.. _function-abs:

###
abs
###

**Required header:** ``#include <eve/function/abs.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ abs = {};
   }

Function object computing the absolute value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise absolute value of the :ref:`Value <concept-value>`.

.. rubric:: Parameter

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - Be aware that for signed integers the absolute value of :ref:`Valmin <constant-valmin>` is
    not representable  in the input type and the result is undefined. Use the :ref:`saturated_ <feature-decorator>` decorator to avoid
    this problem: if ``iT`` is a signed integer type, ``saturated_(abs(Valmin<iT>())`` returns ``Valmax<iT>()``.

  - With the :ref:`saturated_ <feature-decorator>` decorator the result is guaranted to be positive or 0.

  - Be also aware that ``abs`` is a also a standard library function name and there possibly exists
    a C macro version which may be called instead of the boost simd version.
    To avoid this you may prefix ``abs`` using ``eve::abs`` notation.


Example
*******

.. include:: ../../../../test/doc/core/abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/abs.txt
  :literal:
