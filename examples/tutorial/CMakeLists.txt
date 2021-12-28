##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Introductory Tutorial
##==================================================================================================
make_unit( "examples.tutorial" intro-01.cpp )
make_unit( "examples.tutorial" intro-02.cpp )
make_unit( "examples.tutorial" intro-03.cpp )
make_unit( "examples.tutorial" intro-04.cpp )

##==================================================================================================
## Loop Tutorial
##==================================================================================================
make_unit( "examples.tutorial" process.cpp  )

##==================================================================================================
## Conditionals Tutorial
##==================================================================================================
make_unit( "examples.tutorial" safe_sqrt_between.cpp      )
make_unit( "examples.tutorial" safe_sqrt_else.cpp         )
make_unit( "examples.tutorial" safe_sqrt_ignore.cpp       )
make_unit( "examples.tutorial" safe_sqrt_ignore_both.cpp  )
make_unit( "examples.tutorial" safe_sqrt_op.cpp           )
make_unit( "examples.tutorial" safe_sqrt.cpp              )
make_unit( "examples.tutorial" square_or_diff.cpp         )
