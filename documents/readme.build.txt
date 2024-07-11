# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
# version 2024/07/10
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.build.txt +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#
# To read the "Build Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.build.txt +Q -cn "Build Readme Documentation" | iki_read +Q -w -rr FLL FLL FSS FSS -WW character "'" "'" code '"' '"'
#

Build Readme Documentation:
  The bold:"Featureless Make", or code:"fake", is a build system opposing the bold:"GNU Make" build (and install) system.
  See the code:"fake" project for further details regarding that build system.

  Use the code:"make" operation from the code:"fake" program to build this project\:
    code:"fake"

  If the project has already been built before, alternative consider performing both a code:"clean" and an explicit code:"make" operation\:
    code:"fake clean make"

  After building, either run the helper file:"install.sh" script or manually install the build files.

  Install Example\:
    code:"./install.sh"

  Manual Install Example\:
    code:"cp -vR build/documentation/* /usr/share/"
    code:"cp -vR build/includes/* /usr/include/"
    code:"cp -vR build/libaries/shared/* /usr/lib/"
    code:"cp -vR build/programs/shared/* /usr/bin/"
    code:"cp -vR build/settings/* /etc/"

  Build Tree Structure Example (using an early code:"controller-0.7.0" project structure)\:
    block:"
      build/
      ├── documentation
      │   └── man
      │       ├── man1
      │       │   └── controller.1
      │       └── man5
      │           ├── controller-actions.5
      │           ├── controller-entry.5
      │           ├── controller-exit.5
      │           ├── controller-packet.5
      │           └── controller-rule.5
      ├── documents
      ├── includes
      │   └── program
      │       └── controller
      │           ├── controller
      │           │   ├── controller.h
      │           │   └── string.h
      │           ├── init
      │           │   ├── init.h
      │           │   └── string.h
      │           └── main
      │               ├── common
      │               │   ├── define
      │               │   │   ├── control.h
      │               │   │   ├── entry.h
      │               │   │   ├── rule.h
      │               │   │   └── thread.h
      │               │   ├── define.h
      │               │   ├── enumeration
      │               │   │   ├── control.h
      │               │   │   ├── entry.h
      │               │   │   ├── instance.h
      │               │   │   ├── process.h
      │               │   │   ├── rule.h
      │               │   │   └── thread.h
      │               │   ├── enumeration.h
      │               │   ├── print.h
      │               │   ├── string
      │               │   │   ├── general.h
      │               │   │   └── rule.h
      │               │   ├── string.h
      │               │   ├── type
      │               │   │   ├── cache.h
      │               │   │   ├── control.h
      │               │   │   ├── defs.h
      │               │   │   ├── entry.h
      │               │   │   ├── execute.h
      │               │   │   ├── instance.h
      │               │   │   ├── interrupt.h
      │               │   │   ├── lock.h
      │               │   │   ├── process.h
      │               │   │   ├── rule.h
      │               │   │   └── thread.h
      │               │   └── type.h
      │               ├── common.h
      │               ├── controller.h
      │               ├── convert.h
      │               ├── entry
      │               │   ├── action.h
      │               │   ├── preprocess.h
      │               │   ├── process.h
      │               │   └── setting.h
      │               ├── entry.h
      │               ├── file.h
      │               ├── instance
      │               │   ├── prepare.h
      │               │   └── wait.h
      │               ├── instance.h
      │               ├── lock.h
      │               ├── path.h
      │               ├── perform.h
      │               ├── print
      │               │   ├── data.h
      │               │   ├── debug
      │               │   │   ├── perform
      │               │   │   │   ├── control.h
      │               │   │   │   └── pid.h
      │               │   │   └── rule
      │               │   │       ├── action.h
      │               │   │       └── execute.h
      │               │   ├── debug.h
      │               │   ├── error
      │               │   │   ├── entry
      │               │   │   │   ├── action.h
      │               │   │   │   ├── item.h
      │               │   │   │   └── setting.h
      │               │   │   ├── entry.h
      │               │   │   ├── lock.h
      │               │   │   ├── perform
      │               │   │   │   └── pid.h
      │               │   │   ├── rule
      │               │   │   │   ├── action.h
      │               │   │   │   ├── item.h
      │               │   │   │   └── setting.h
      │               │   │   └── rule.h
      │               │   ├── error.h
      │               │   ├── lock.h
      │               │   ├── message
      │               │   │   ├── entry
      │               │   │   │   ├── action.h
      │               │   │   │   └── item.h
      │               │   │   └── entry.h
      │               │   ├── message.h
      │               │   ├── output
      │               │   │   ├── entry
      │               │   │   │   └── setting.h
      │               │   │   └── rule
      │               │   │       ├── execute.h
      │               │   │       ├── setting.h
      │               │   │       └── validate.h
      │               │   ├── verbose.h
      │               │   ├── warning
      │               │   │   ├── entry
      │               │   │   │   ├── action.h
      │               │   │   │   ├── item.h
      │               │   │   │   └── setting.h
      │               │   │   └── rule
      │               │   │       ├── action.h
      │               │   │       ├── item.h
      │               │   │       └── setting.h
      │               │   └── warning.h
      │               ├── process.h
      │               ├── rule
      │               │   ├── action.h
      │               │   ├── execute.h
      │               │   ├── expand.h
      │               │   ├── instance.h
      │               │   ├── is.h
      │               │   ├── item.h
      │               │   ├── parameter.h
      │               │   ├── read.h
      │               │   ├── setting.h
      │               │   └── wait.h
      │               ├── rule.h
      │               ├── signal.h
      │               ├── status.h
      │               ├── thread
      │               │   ├── cleanup.h
      │               │   ├── control.h
      │               │   ├── entry.h
      │               │   ├── instance.h
      │               │   ├── is.h
      │               │   ├── rule.h
      │               │   └── signal.h
      │               ├── thread.h
      │               ├── time.h
      │               └── validate.h
      ├── libraries
      │   ├── script
      │   ├── shared
      │   │   ├── libcontroller.so -> libcontroller.so.0
      │   │   ├── libcontroller.so.0 -> libcontroller.so.0.7
      │   │   ├── libcontroller.so.0.7 -> libcontroller.so.0.7.0
      │   │   └── libcontroller.so.0.7.0
      │   └── static
      ├── objects
      │   ├── script
      │   ├── shared
      │   └── static
      ├── programs
      │   ├── script
      │   ├── shared
      │   │   ├── controller
      │   │   └── init
      │   └── static
      ├── settings
      │   └── controller
      │       ├── entries
      │       │   ├── default.entry
      │       │   └── maintenance.entry
      │       ├── example
      │       │   ├── cgroup_example
      │       │   │   ├── entries
      │       │   │   │   ├── chromium.entry
      │       │   │   │   ├── eclipse.entry
      │       │   │   │   ├── firefox.entry
      │       │   │   │   └── setup_cgroups.entry
      │       │   │   └── rules
      │       │   │       ├── program
      │       │   │       │   ├── chromium.rule
      │       │   │       │   ├── eclipse.rule
      │       │   │       │   └── firefox.rule
      │       │   │       └── setup
      │       │   │           └── cgroups.rule
      │       │   ├── entries
      │       │   │   ├── asynchronous.entry
      │       │   │   ├── asynchronous-serial.entry
      │       │   │   ├── delay-program.entry
      │       │   │   ├── delay-service.entry
      │       │   │   ├── environment.entry
      │       │   │   ├── htop-alternate.entry
      │       │   │   ├── htop-command.entry
      │       │   │   ├── htop.entry
      │       │   │   ├── iki.entry
      │       │   │   ├── serial-alternate.entry
      │       │   │   ├── serial.entry
      │       │   │   ├── sshd.entry
      │       │   │   ├── test.entry
      │       │   │   ├── up.entry
      │       │   │   └── utility.entry
      │       │   ├── exits
      │       │   │   ├── htop-alternate.exit
      │       │   │   ├── serial.exit
      │       │   │   └── sshd.exit
      │       │   └── rules
      │       │       ├── asynchronous
      │       │       │   ├── sleep_10.rule
      │       │       │   ├── sleep_1.rule
      │       │       │   ├── sleep_2.rule
      │       │       │   ├── sleep_3.rule
      │       │       │   ├── sleep_5.rule
      │       │       │   └── sleep_8.rule
      │       │       ├── command
      │       │       │   ├── htop.rule
      │       │       │   └── multiple.rule
      │       │       ├── delay
      │       │       │   ├── long.rule
      │       │       │   └── short.rule
      │       │       ├── environment
      │       │       │   ├── default.rule
      │       │       │   ├── empty.rule
      │       │       │   ├── exported.rule
      │       │       │   ├── exporting.rule
      │       │       │   ├── fake-nothing.rule
      │       │       │   └── fake-something.rule
      │       │       ├── maintenance
      │       │       │   └── boom.rule
      │       │       ├── print
      │       │       │   └── newline.rule
      │       │       ├── script
      │       │       │   ├── create_socket_path.rule
      │       │       │   ├── fail.rule
      │       │       │   ├── iki.rule
      │       │       │   ├── php.rule
      │       │       │   ├── python.rule
      │       │       │   ├── require_me.rule
      │       │       │   └── succeed.rule
      │       │       ├── serial
      │       │       │   ├── s_1.rule
      │       │       │   ├── s_2.rule
      │       │       │   ├── s_3.rule
      │       │       │   ├── s_4.rule
      │       │       │   ├── s_5.rule
      │       │       │   └── s_6.rule
      │       │       ├── service
      │       │       │   └── sshd.rule
      │       │       └── utility
      │       │           ├── sleeper_1.rule
      │       │           ├── sleeper_2.rule
      │       │           └── sleeper_3.rule
      │       └── rules
      │           ├── boot
      │           │   ├── devices.rule
      │           │   ├── file_system.rule
      │           │   ├── modules.rule
      │           │   ├── proc.rule
      │           │   └── root.rule
      │           ├── maintenance
      │           │   └── console.rule
      │           ├── net
      │           │   ├── all.rule
      │           │   └── loopback.rule
      │           ├── service
      │           │   ├── dbus.rule
      │           │   ├── logger.rule
      │           │   └── mouse.rule
      │           ├── task
      │           │   ├── clock.rule
      │           │   ├── keyboard.rule
      │           │   └── ntpdate.rule
      │           └── terminal
      │               ├── four.rule
      │               ├── one.rule
      │               ├── three.rule
      │               └── two.rule
      └── stage
          ├── library_shared-settings.built
          ├── program_shared-settings.controller.built
          ├── program_shared-settings.init.built
          ├── skeleton-settings.built
          ├── skeleton-settings.controller.built
          ├── skeleton-settings.init.built
          ├── sources_documentation-settings.built
          ├── sources_documentation-settings.controller.built
          ├── sources_documentation-settings.init.built
          ├── sources_headers-settings.built
          ├── sources_headers-settings.controller.built
          ├── sources_headers-settings.init.built
          ├── sources_script-settings.built
          ├── sources_script-settings.controller.built
          ├── sources_script-settings.init.built
          ├── sources_settings-settings.built
          ├── sources_settings-settings.controller.built
          └── sources_settings-settings.init.built
    "

  See: FLL:"Featureless Linux Library" code:"fake" project documents and specifications for further details on how to use the bold:"Featureless Make" system.
  See: FLL:"Featureless Linux Library" project documentation and specifications for how to configure the bold:"Featureless Make" FSS:"Featureless Settings Specification" files.
