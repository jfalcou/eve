.. _function-bit_not:

##############
bit_not
##############

**Required header:** ``#include <eve/function/bit_not.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bit_not = {};
   }

Function object performing a bit COMPLEMENT of a :ref:`Value <concept-value>`.

********
Synopsis
********

.. code-block:: c++

   template<typename T>  U operator()( T const& x) noexcept;


* Returns the bit COMPLEMENT of ``x``.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******


* There is no type restriction on the parameter  :ref:`Value <concept-value>` type of :ref:`function-bit_not`.
  This implies that calls to :ref:`function-bit_not` on :ref:`Ieee values <concept-IEEEvalue>` are possible.


*******
Example
*******

.. include:: ../../../../test/doc/core/bit_not.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bit_not.txt
  :literal:
