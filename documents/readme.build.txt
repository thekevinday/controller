# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
# version 2024/07/02
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.build.txt +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#
# To read the "Build Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.build.txt +Q -cn "Build Readme Documentation" | iki_read +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#

Build Readme Documentation:
  The bold:"Featureless Make", or code:"fake", is a build system opposing the bold:"GNU Make" build (and install) system.

  The bold:"GNU Make" system is powerful, but introduces too much unecessary functionality.
  In opposition to parts of how bold:"GNU Make" works but also in honor of the success of the bold:"GNU Make" system, the bold:"Featureless Make" system follows the following concepts\:
  - A build system is just that, a build system. Do not attempt to install, leave that to the distributor or individual installer.
  - A build system should not be trying to guess what is or is not on the system, instead, allow the distributor or individual installer to just specify what they want.
  - Provide a simple configuration design by using the bold:"Featureless Settings Specification".
  - Provide advanced functionality to provide flexibility with different system designs.
  - Userspace execution calling is expensive, attempt to avoid such overhead by providing built-in functionality where reasonably possible.
  - There should never need to be a code:"configure" script, like bold:"GNU Autoconf".

  The code:"fake" is designed to specifically build the FLL:"Featureless Linux Library" and encourages the use of code:"fake" to build FLL:"Featureless Linux Library".

  The code:"fake" provides two main build operations\:
  - code:"build": a lean purely FSS:"Featureless Settings Specification" based build process, designed around specific but simple project designs (explicitly used by FLL:"Featureless Linux Library").
  - code:"make": a more powerful build process design to be more akin to bold:"GNU Make".

  The code:"fake" supports custom development environments using the file:"work" directory concept, such as code:"fake build -w /tmp/work".
  The file:"work" directory structure is identical to the build directory structure.

  Build Example, Using code:"build"\:
    code:"fake build"

  Build Example, Using code:"make"\:
    code:"fake"

  Build Example, Explicitly Using code:"make"\:
    code:"fake make"

  Build Tree Structure Example (using the FLL:"Featureless Linux Library" code:"status_code-0.7.0" project)\:
    block:"
      build/
      ├── documents
      ├── includes
      │   └── program
      │       └── status_code
      │           ├── fss
      │           │   ├── common.h
      │           │   └── status_code.h
      │           └── main
      │               ├── common.h
      │               ├── common-print.h
      │               ├── print.h
      │               └── status_code.h
      ├── libraries
      │   ├── script
      │   ├── shared
      │   │   ├── libstatus_code.so -> libstatus_code.so.0
      │   │   ├── libstatus_code.so.0 -> libstatus_code.so.0.7
      │   │   ├── libstatus_code.so.0.7 -> libstatus_code.so.0.7.0
      │   │   └── libstatus_code.so.0.7.0
      │   └── static
      │       └── libstatus_code.a
      ├── objects
      │   ├── config.o
      │   ├── fss
      │   │   ├── common.o
      │   │   └── status_code.o
      │   ├── main
      │   │   ├── common.o
      │   │   ├── common-print.o
      │   │   ├── print.o
      │   │   ├── private-status_code.o
      │   │   └── status_code.o
      │   ├── script
      │   ├── shared
      │   └── static
      ├── programs
      │   ├── script
      │   ├── shared
      │   │   ├── fss_status_code
      │   │   └── status_code
      │   └── static
      │       ├── fss_status_code
      │       └── status_code
      ├── settings
      └── stage
          ├── library_shared-settings.built
          ├── library_static-settings.built
          ├── objects_static-settings.built
          ├── program_shared-settings.fss.built
          ├── program_shared-settings.main.built
          ├── skeleton-settings.built
          ├── skeleton-settings.fss.built
          ├── skeleton-settings.main.built
          ├── sources_headers-settings.built
          ├── sources_script-settings.built
          ├── sources_script-settings.fss.built
          ├── sources_script-settings.main.built
          ├── sources_settings-settings.built
          ├── sources_settings-settings.fss.built
          └── sources_settings-settings.main.built
    "

  See: FLL:"Featureless Linux Library" code:"fake" project documents for further details on how to use the bold:"Featureless Make" system.
  See: FLL:"Featureless Linux Library" code:"fake" project specifications for how to configure the build FSS:"Featureless Settings Specification" files and make FSS:"Featureless Settings Specification" files.
  See: file:"readme.bootstrap.txt" for notes on installing.
