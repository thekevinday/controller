# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
# version 2024/07/02
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.txt +Q -w -rrrr API API FLL FLL FSS FSS KISS KISS -WW character "'" "'" code '"' '"'
#
# To read the "Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.txt +Q -cn "Readme Documentation" | iki_read +Q -w -rrrr API API FLL FLL FSS FSS KISS KISS -WW character "'" "'" code '"' '"'
#

Readme Documentation:
  The FLL:"Featureless Linux Library" is a set of projects designed to be used for bold:"Linux" programming.

  The FLL:"Featureless Linux Library" is design around the following concepts\:
  - API:"Application Programming Interface" designed around communicating to the programmer and maintaining unchanging consistency.
  - Hacker friendly, promote changing the project via its designed methodologies, implementations, standards, practices, and licenses.
  - Add freedom back to computing, via the bold:"LGPL" license, because a library is a library.
  - A standard is not a true standard if it is not freely available and cannot be freely used or followed.
  - Avoid the bold:"feature" trap where projects keep adding things.
  - Provide an explicit versioning system that is more than a number, it communicates the status in a very simple manner.
  - Continue mantaining major versions, a project should be able to last 20, 30, or even 60 years without breaking changes.
  - Follow the KISS:"Keep It Simple Stupid", principles.
  - Can be broken up into individual projects, and then further fine-tuned via custom define macros, so that only what is needed for specific situations need be used.

  The FLL:"Featureless Linux Library" versioning system has three parts: code:"major.minor.micro".
  - The bold:"Major" is the primary API:"Application Programming Interface" specification, changes to this number represent massive breaking changes and for all intents and purposes is a different project.
  - The bold:"Minor" represents potential breaking changes, where odd numbers represent bold:"development status" and even numbers represent bold:"stable status".
  - The bold:"Micro" represents bug fixes and security fixes, these should never introduce neither API:"Application Programming Interface" breaking changes nor new functionality.

  Development releases (as specified by bold:"Minor" version part) may introduce breaking changes and new functionality.
  Stable releases (as specified by the bold:"Minor" version part) may not introduce breaking change, unless forced by some security or other difficult situation, and must not add new functionality.

  The FLL:"Featureless Linux Library" project is broken up into 3 different levels: code:"level_0", code:"level_1", and code:"level_2".
  A third pseudo-level also exists for common programs built using this project, called code:"level_3".

  With an exception of a few projects within code:"level_0", each level should only depend on a project from a lower level.
  Therefore, a code:"level_1" project can only depend on code:"level_0" projects and a code:"level_2" project can depend on only code:"level_0" and code:"level_1" projects.
  This does not technically apply to the pseudo-level, code:"level_3", projects, but the pattern is generally followed.

  A few projects in code:"level_0" are essentially required by everything and are depended on by virtually all projects, regardless of the level.
  These code:"level_0" projects are\:
  - code:"f_type": Provides core type definitions, code:"#define", and similar structures for the entire set of FLL:"Featureless Linux Library" projects.
  - code:"f_status": provides status codes and other status codes to be used by the entire set of FLL:"Featureless Linux Library" projects.
  - code:"f_memory": provides common memory allocation or deallocation to be used by the entire set of FLL:"Featureless Linux Library" projects.
  - code:"f_type_array": provides an extension on code:"f_type" that requires linking to code:"f_memory" to be used by the entire set of FLL:"Featureless Linux Library" projects.
  - code:"f_string": provides common string management to be used by the entire set of the FLL:"Featureless Linux Library" projects.
  - code:"f_utf": provides common UTF-8 related string management to be used by the entire set of the FLL:"Featureless Linux Library" projects.

  The above projects should be installed first, and in the provided order (code:"f_type", then code:"f_status", then code:"f_memory", then code:"f_type_array", then code:"f_string", and finally code:"f_utf").
  No other code:"level_0" project should depend on another and can be installed in any order.

  To facilitate building of this project, two different build systems are provided\:
  - The bootstrap, via the file:"bootstrap.sh" script.
  - The bold:"Featureless Make", which is a level_3 project provided by FLL:"Featureless Linux Library".

  An example bootstrap script is provided (file:"build/scripts/bootstrap-example.sh") is provided for to show how to build the FLL:"Featureless Linux Library" directly from source.
  Use it as an example or explicitly call it (such as: code:"bash build/scripts/bootstrap-example.sh monolithic 0.7.0").

  See: file:"dependencies" for specific dependencies of this project.
  See: file:"readme.bootstrap.txt" for bootstrap compiling (or just regular compiling) any part of the FLL:"Featureless Linux Library" and notes on installing.
  See: file:"readme.build.txt" for bold:"Featureless Make" compiling and notes on installing.
