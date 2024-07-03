# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
# version 2024/07/02
#
# This file (assumed to be named readme.bootstrap.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.bootstrap.txt +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#
# To read the "Bootstrap Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.bootstrap.txt +Q -cn "Bootstrap Readme Documentation" | iki_read +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#

Bootstrap Readme Documentation:
  The FLL:"Featureless Linux Library" provides a special bootstrap script in case the bold:"Featureless Make" is not currently installed.

  The bold:"GNU Bash" scripts, called file:"bootstrap.sh" and file:"install.sh", are provided to perform this bootstrap process.

  The syntax for file:"bootstrap.sh" is\:
    code:"bootstrap.sh <operation> [options]"
    - where operation is one of the following: code:"build" or code:"clean".
    - No code:"install" command is provided, all of the files to install may be found in the file:"build/" directory after the build command is executed.
    - To install, either copy the files in the build directory to their appropriate destination or use the file:"install.sh" bold:"GNU Bash" script.
    - For all operations and options, get help from the bootstrap script by appending the code:"--help" to the script, such as: code:"./bootstrap.sh --help".
    - The monolithic build process is the simplest, which can be generated like the following: code:"./bootstrap.sh build -m monolithic".
    - When during development, consider using a work directory, such as: code:"./bootstrap.sh --work /tmp/work".

  The syntax for file:"install.sh" is\:
    code:"install.sh [options]"
    - This defaults to code:"/usr/local/" paths commonly found in bold:"GNU Linux" systems.
    - Accepts options for specifying specific install directory paths, such as a custom bin directory: code:"./install.sh --bindir /custom/program".
    - This is a simple installer and is not intended to be an all-solution.
    - For more powerful installation: manually install, use custom scripts, or use an appropriate build/install system.
    - When during development, consider using a work directory, such as: code:"./install.sh --work /tmp/work".
    - The code:"--work" parameter in file:"install.sh" is similar to the code:"--prefix" parameter, except that it is used for easier development scripting and also for communicating intent and has a different directory structure.
    - The bold:"Featureless Make" is a build system only and not an install system, the file:"install.sh" script may still be needed to install when using the bold:"Featureless Make".

  Build Example\:
    code:"./bootstrap.sh build"

  Install Example\:
    code:"./install.sh"

  Manual Install Example\:
    code:"cp -vR build/includes/* /usr/include/"
    code:"cp -vR build/libaries/shared/* /usr/lib/"
    code:"cp -vR build/programs/shared/* /usr/bin/"
    code:"cp -vR build/settings/* /etc/"

  If one of the build sub-directories, such as includes, libraries, programs, and settings, is empty or missing after a successful build, then there are no files of that type to install.

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

  Work Tree Sructure Example at file:"/tmp/work" (using the FLL:"Featureless Linux Library" code:"status_code-0.7.0" project)\:
    block:"
      /tmp/work/
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
      └── libraries
          ├── shared
          │   ├── libstatus_code.so -> libstatus_code.so.0
          │   ├── libstatus_code.so.0 -> libstatus_code.so.0.7
          │   ├── libstatus_code.so.0.7 -> libstatus_code.so.0.7.0
          │   └── libstatus_code.so.0.7.0
          └── static
              └── libstatus_code.a
    "
