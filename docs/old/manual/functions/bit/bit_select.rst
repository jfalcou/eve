.. _function-bit_select:

##############
bit_select
##############

**Required header:** ``#include <eve/function/bit_select.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_select = {};
   }

Function object performing a bit selection between two :ref:`Values <concept-value>` of same bit size according to a
mask.

********
Synopsis
********

.. code-block:: c++

.. code-block:: c++

   template<typename T, typename U> U operator()( T const& x, U const& y, U const& z ) noexcept;

* Selects bits between ``y`` and ``z`` based on the value of ``x``. This computation is equivalent to ``bit_or(bit_and(y, x), eve::bit_andnot(z, x))``.

Parameters
***********

* Each parameter  ``x``, ``y`` and ``z`` must be an instance of :ref:`Value <concept-value>`.
* All parameters must share the same global size.


Return value
************

* A value of the type shared by the second and third parameters.

*******
Example
*******

.. include:: ../../../../test/doc/core/bit_select.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_select.txt
  :literal:
