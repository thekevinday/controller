#!/bin/bash
# license: lgpl-2.1-or-later
# programmer: Kevin Day
#
# The purpose of this script is to provide a simple bootstrap tool to compile any part of the FLL project.
#
# The dependencies of this script are: bash, basename, cp, dirname, grep, ln, mkdir, rm, sed, and touch.
#
# This script is only designed specifically for bootstrap compiling the FLL project and does not necessarily fully follow the fake (featureless make) build process.
#
# This script can also be run under zsh rather than bash by setting the environment variable SHELL_ENGINE to "zsh", such as:
#   SHELL_ENGINE="zsh" zsh ./bootstrap.sh --help
#

bootstrap_main() {

  if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
    emulate ksh
  fi

  local public_name="Simple FLL Bootstrap Script"
  local system_name=bootstrap
  local called_name=$(basename ${0})
  local version=0.7.0

  local grab_next=
  local do_color=dark
  local do_help=
  local do_copyright=
  local i=0
  local m=
  local p=
  local t=0

  local c_reset="\\033[0m"
  local c_title="\\033[1;33m"
  local c_error="\\033[1;31m"
  local c_warning="\\033[0;33m"
  local c_highlight="\\033[1;32m"
  local c_notice="\\033[0;01m"
  local c_important="\\033[0;32m"
  local c_subtle="\\033[1;30m"
  local c_prefix="\\"

  local key=
  local -A variables=()
  local failure=0
  local settings_name=settings
  local settings_file=
  local settings_defines=
  local mode=
  local modes=
  local modes_available=
  local operation=
  local operation_failure=
  local path_build=build/
  local path_build_stage=build/stage/
  local path_data=data/
  local path_documentation=${path_data}documentation/
  local path_settings=${path_data}settings/
  local path_sources=sources/
  local path_language=c/
  local path_work=
  local print_line_first="yes"
  local print_line_last="yes"
  local project_built=
  local project_built_shared=
  local project_built_static=
  local project_label=
  local override_path_build=
  local override_path_data=
  local override_path_sources=
  local override_path_work=
  local define_extra=
  local process=
  local verbosity=normal
  local verbose=
  local verbose_common=

  local enable_documentation=
  local enable_shared=
  local enable_static=

  if [[ $# -gt 0 ]] ; then
    t=$#

    while [[ ${i} -lt ${t} ]] ; do
      let i=${i}+1

      if [[ ${SHELL_ENGINE} == "zsh" ]] ; then
        p=${(P)i}
      else
        p=${!i}
      fi

      if [[ ${grab_next} == "" ]] ; then
        if [[ ${p} == "-h" || ${p} == "--help" ]] ; then
          do_help=yes
        elif [[ ${p} == "+C" || ${p} == "++copyright" ]] ; then
          do_copyright="yes"
        elif [[ ${p} == "+d" || ${p} == "++dark" ]] ; then
          do_color=dark
          context="+d"
        elif [[ ${p} == "+l" || ${p} == "++light" ]] ; then
          do_color=light
          context="+l"
        elif [[ ${p} == "+n" || ${p} == "++no_color" ]] ; then
          do_color=none
          context="+n"
        elif [[ ${p} == "+Q" || ${p} == "++quiet" ]] ; then
          verbosity="quiet"
          verbose="+Q"
          verbose_common=
        elif [[ ${p} == "+E" || ${p} == "++error" ]] ; then
          verbosity="error"
          verbose="+E"
          verbose_common=
        elif [[ ${p} == "+N" || ${p} == "++normal" ]] ; then
          verbosity=
          verbose="+N"
          verbose_common=
        elif [[ ${p} == "+V" || ${p} == "++verbose" ]] ; then
          verbosity="verbose"
          verbose="+V"
          verbose_common="-v"
        elif [[ ${p} == "+D" || ${p} == "++debug" ]] ; then
          verbosity="debug"
          verbose="+D"
          verbose_common="-v"
        elif [[ ${p} == "+F" || ${p} == "++line_first_no" ]] ; then
          print_line_first="no"
        elif [[ ${p} == "+L" || ${p} == "++line_last_no" ]] ; then
          print_line_last="no"
        elif [[ ${p} == "+v" || ${p} == "++version" ]] ; then
          echo ${version}
          return 0
        elif [[ ${p} == "-d" || ${p} == "--define" ]] ; then
          grab_next=define_extra
        elif [[ ${p} == "-m" || ${p} == "--mode" ]] ; then
          grab_next="mode"
        elif [[ ${p} == "-p" || ${p} == "--process" ]] ; then
          grab_next="process"
        elif [[ ${p} == "-s" || ${p} == "--settings" ]] ; then
          grab_next=settings_name
        elif [[ ${p} == "-b" || ${p} == "--build" ]] ; then
          grab_next=path_build
        elif [[ ${p} == "-d" || ${p} == "--data" ]] ; then
          grab_next=path_data
        elif [[ ${p} == "-S" || ${p} == "--sources" ]] ; then
          grab_next=path_sources
        elif [[ ${p} == "-w" || ${p} == "--work" ]] ; then
          grab_next=path_work
        elif [[ ${p} == "--enable-doc" ]] ; then
          enable_documentation="yes"
        elif [[ ${p} == "--disable-doc" ]] ; then
          enable_documentation="no"
        elif [[ ${p} == "--enable-shared" ]] ; then
          enable_shared="yes"
        elif [[ ${p} == "--disable-shared" ]] ; then
          enable_shared="no"
        elif [[ ${p} == "--enable-static" ]] ; then
          enable_static="yes"
        elif [[ ${p} == "--disable-static" ]] ; then
          enable_static="no"
        elif [[ ${operation} == "" ]] ; then
          operation="${p}"
        elif [[ ${operation_failure} == "" ]] ; then
          operation_failure=fail-multiple
        fi
      else
        if [[ ${grab_next} == "define_extra" ]] ; then
          define_extra="${define_extra}${p} "
        elif [[ ${grab_next} == "mode" ]] ; then
          modes="${modes}${p} "
        elif [[ ${grab_next} == "process" ]] ; then
          process="${p}"
        elif [[ ${grab_next} == "settings_name" ]] ; then
          settings_name="${p}"
        elif [[ ${grab_next} == "path_build" ]] ; then
          path_build=$(echo ${p} | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_build="y"
        elif [[ ${grab_next} == "path_data" ]] ; then
          path_data=$(echo ${p} | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_data="y"
        elif [[ ${grab_next} == "path_sources" ]] ; then
          path_sources=$(echo ${p} | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_sources="y"
        elif [[ ${grab_next} == "path_work" ]] ; then
          path_work=$(echo ${p} | sed -e 's|//*|/|g' -e 's|/*$|/|')
          override_path_work="y"
        fi

        grab_next=
      fi
    done

    p=
  fi

  if [[ ${verbosity} == "quiet" ]] ; then
    print_line_first="no"
    print_line_last="no"
  fi

  # If the settings_name has a directory separator, then assume it is a path to the settings file.
  if [[ $(echo ${settings_name} | grep -s -o '/') == "" ]] ; then
    settings_file="${path_data}build/${settings_name}"
  else
    settings_file="${settings_name}"

    # Extract the settings name from the path.
    settings_name=$(basename ${settings_name})
  fi

  settings_defines="${path_data}build/defines"
  path_documentation="${path_data}documentation/"
  path_settings="${path_data}settings/"
  path_build_stage="${path_build}stage/"

  bootstrap_handle_colors

  if [[ ${do_help} == "yes" ]] ; then
    bootstrap_help
    bootstrap_cleanup

    return 0
  fi

  if [[ ${do_copyright} == "yes" ]] ; then
    bootstrap_copyright
    bootstrap_cleanup

    return 0
  fi

  bootstrap_load_settings

  # FSS and Featurless Make supports more flexible mode names, but for the purpose of this bootstrap script and avoiding potential problems, keep it simple.
  if [[ ${modes} != "" ]] ; then
    for mode in ${modes} ; do
      if [[ $(echo "${mode}" | grep -s -o "[^_[:alnum:]+-]") != "" ]] ; then
        if [[ ${verbosity} != "quiet" ]] ; then
          bootstrap_print_first

          echo -e "${c_error}ERROR: The mode ${c_notice}${mode}${c_error} includes invalid characters, only alphanumeric, underscore, minus, and plus are allowed.${c_reset}"

          bootstrap_print_last
        fi

        bootstrap_cleanup

        return 1
      fi
    done
  fi

  if [[ ${?} -ne 0 ]] ; then
    bootstrap_cleanup

    return 1
  fi

  bootstrap_load_settings_mode

  if [[ ${?} -ne 0 ]] ; then
    bootstrap_cleanup

    return 1
  fi

  bootstrap_id "build_name"
  project_built="${path_build_stage}${variables[${key}]}"
  if [[ ${process} != "" ]] ; then
    project_built="${project_built}-${process}"
  fi

  project_built_shared="${project_built}.shared"
  project_built_static="${project_built}.static"

  if [[ ${modes_available} == "" ]] ; then
    if [[ ${modes} != "" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: The mode(s) ${c_notice}${modes}${c_error} are not a valid modes, there are no available modes.${c_error}${c_reset}"

        bootstrap_print_last
      fi

      bootstrap_cleanup

      return 1
    fi
  else
    let i=0
    for m in ${modes_available} ; do

      for mode in ${modes} ; do

        if [[ "${mode}" == "${m}" ]] ; then
          let i=1

          break
        fi
      done

      if [[ ${i} -eq 1 ]] ; then break ; fi
    done

    if [[ ${i} -eq 0 ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: The mode(s) ${c_notice}${modes}${c_error} are not valid modes, they must be one of: ${c_notice}${modes_available}${c_error}.${c_reset}"

        bootstrap_print_last
      fi

      bootstrap_cleanup

      return 1
    fi
  fi

  bootstrap_id "build_name"
  if [[ ${variables[${key}]} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The required setting '${c_notice}build_name${c_error}' is not specified in the build settings file '${c_notice}${settings_file}${c_error}'.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  bootstrap_id "version_major"
  if [[ ${variables[${key}]} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The required setting '${c_notice}version_major${c_error}' is not specified in the build settings file '${c_notice}${settings_file}${c_error}'.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  bootstrap_id "version_minor"
  if [[ ${variables[${key}]} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The required setting '${c_notice}version_minor${c_error}' is not specified in the build settings file '${c_notice}${settings_file}${c_error}'.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  bootstrap_id "version_micro"
  if [[ ${variables[${key}]} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The required setting '${c_notice}version_micro${c_error}' is not specified in the build settings file '${c_notice}${settings_file}${c_error}'.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${path_data} == "" || ! -d ${path_data} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The data directory ${c_notice}${path_data}${c_error} is not a valid directory.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${path_sources} == "" || ! -d ${path_sources} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The sources directory ${c_notice}${path_sources}${c_error} is not a valid directory.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${path_work} != "" && ! -d ${path_work} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The work directory ${c_notice}${path_work}${c_error} is not a valid directory.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  bootstrap_id "build_name"
  project_label="${variables[${key}]}"

  bootstrap_id "version_major"
  if [[ "${variables[${key}]}" != "" ]] ; then
    project_label="${project_label}-${variables[${key}]}"

    bootstrap_id "version_minor"
    if [[ "${variables[${key}]}" != "" ]] ; then
      project_label="${project_label}.${variables[${key}]}"

      bootstrap_id "version_micro"
      if [[ "${variables[${key}]}" != "" ]] ; then
        project_label="${project_label}.${variables[${key}]}"
      fi
    fi
  fi

  if [[ ${operation_failure} == "fail-multiple" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Only one operation may be specified at a time.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  elif [[ ${operation} == "build" ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      bootstrap_print_first

      echo -e "${c_highlight}Building:${c_reset} ${c_notice}${project_label}${c_highlight} with modes: ${c_notice}${modes}${c_highlight}.${c_reset}"
    fi

    if [[ ! -f ${project_built}.prepared ]] ; then
      bootstrap_prepare_build

      if [[ ${?} -ne 0 ]] ; then
        bootstrap_cleanup

        return 1
      fi
    fi

    bootstrap_operation_build

    if [[ ${?} -ne 0 ]] ; then
      bootstrap_cleanup

      return 1
    fi
  elif [[ ${operation} == "clean" ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      bootstrap_print_first

      echo -e "${c_highlight}Cleaning Project:${c_reset} ${c_notice}${project_label}${c_highlight}.${c_reset}"
    fi

    bootstrap_operation_clean
  elif [[ ${operation} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: No operation was given.${c_reset}"
    fi

    bootstrap_cleanup

    return 1
  else
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The operation ${c_notice}${operation}${c_error} was not recognized.${c_reset}"

      bootstrap_print_last
    fi

    bootstrap_cleanup

    return 1
  fi

  if [[ ${verbosity} != "quiet" ]] ; then
    if [[ ${failure} -eq 1 || ${verbosity} != "error" ]] ; then
      bootstrap_print_last
    fi
  fi

  bootstrap_cleanup

  return 0
}

bootstrap_handle_colors() {

  if [[ ${do_color} == "light" ]] ; then
    c_error="\\033[1;31m"
    c_warning="\\033[0;31m"
    c_title="\\033[1;34m"
    c_highlight="\\033[0;34m"
    c_notice="\\033[0;01m"
    c_important="\\033[0;35m"
  elif [[ ${do_color} == "none" ]] ; then
    c_reset=
    c_title=
    c_error=
    c_warning=
    c_highlight=
    c_notice=
    c_important=
    c_subtle=
    c_prefix=
  fi
}

bootstrap_help() {

  bootstrap_print_first

  echo -e "${c_title}${public_name}${c_reset}"
  echo -e " ${c_notice}Version ${version}${c_reset}"
  echo
  echo -e "${c_highlight}${system_name}${c_reset} ${c_notice}[${c_reset} options ${c_notice}]${c_reset} ${c_notice}[${c_reset} operation ${c_notice}]${c_reset}"
  echo -e " ${c_important}build${c_reset}  Build or compile the code based on build settings file."
  echo -e " ${c_important}clean${c_reset}  Delete all build files."
  echo
  echo -e "${c_highlight}Options:${c_reset}"
  echo -e " -${c_important}h${c_reset}, --${c_important}help${c_reset}           Print this help message."
  echo -e " +${c_important}C${c_reset}, ++${c_important}copyright${c_reset}      Print the copyright."
  echo -e " +${c_important}d${c_reset}, ++${c_important}dark${c_reset}           Output using colors that show up better on dark backgrounds."
  echo -e " +${c_important}l${c_reset}, ++${c_important}light${c_reset}          Output using colors that show up better on light backgrounds."
  echo -e " +${c_important}n${c_reset}, ++${c_important}no_color${c_reset}       Do not print using color."
  echo -e " +${c_important}Q${c_reset}, ++${c_important}quiet${c_reset}          Decrease verbosity, silencing most print.to."
  echo -e " +${c_important}E${c_reset}, ++${c_important}error${c_reset}          Decrease verbosity, using only error print.to."
  echo -e " +${c_important}N${c_reset}, ++${c_important}normal${c_reset}         Set verbosity to normal."
  echo -e " +${c_important}V${c_reset}, ++${c_important}verbose${c_reset}        Increase verbosity beyond normal print.to."
  echo -e " +${c_important}D${c_reset}, ++${c_important}debug${c_reset}          Enable debugging, significantly increasing verbosity beyond normal print.to."
  echo -e " +${c_important}v${c_reset}, ++${c_important}version${c_reset}        Print only the version number."
  echo -e " +${c_important}F${c_reset}, ++${c_important}line_first_no${c_reset}  Disable printing of first line."
  echo -e " +${c_important}L${c_reset}, ++${c_important}line_last_no${c_reset}   Disable printing of last line."
  echo
  echo -e "${c_highlight}Bootstrap Options:${c_reset}"
  echo -e " -${c_important}d${c_reset}, --${c_important}define${c_reset}     Append an additional define after defines from settings file."
  echo -e " -${c_important}m${c_reset}, --${c_important}mode${c_reset}       Use this mode when processing the build settings."
  echo -e " -${c_important}p${c_reset}, --${c_important}process${c_reset}    Process name for storing build states."
  echo -e " -${c_important}s${c_reset}, --${c_important}settings${c_reset}   Use this settings file, from within the source settings directory."
  echo
  echo -e " -${c_important}b${c_reset}, --${c_important}build${c_reset}      Specify a custom build directory."
  echo -e " -${c_important}D${c_reset}, --${c_important}data${c_reset}       Specify a custom path to the data files."
  echo -e " -${c_important}S${c_reset}, --${c_important}sources${c_reset}    Specify a custom path to the source files."
  echo -e " -${c_important}w${c_reset}, --${c_important}work${c_reset}       Use includes/libraries/programs from this directory instead of system."
  echo
  echo -e "${c_highlight}Special Options:${c_reset}"
  echo -e " --${c_important}enable-doc${c_reset}      Forcibly do build documentation files."
  echo -e " --${c_important}disable-doc${c_reset}     Forcibly do not build documentation files."
  echo -e " --${c_important}enable-shared${c_reset}   Forcibly do build shared files."
  echo -e " --${c_important}disable-shared${c_reset}  Forcibly do not build shared files."
  echo -e " --${c_important}enable-static${c_reset}   Forcibly do build static files."
  echo -e " --${c_important}disable-static${c_reset}  Forcibly do not build static files."

  bootstrap_print_last
}

bootstrap_copyright() {

  bootstrap_print_first

  echo "Copyright © 2007-2023 Kevin Day."
  echo
  echo "Source code license lgpl-2.1-or-later."
  echo "Standard and specification license open-standard-license-1.0."
  echo "Documentation license cc-by-sa-4.0."

  bootstrap_print_last
}

bootstrap_id() {

  case ${1} in
    "build_compiler") let key=0;;
    "build_indexer") let key=1;;
    "build_indexer_arguments") let key=2;;
    "build_language") let key=3;;
    "build_libraries") let key=4;;
    "build_libraries_shared") let key=5;;
    "build_libraries_static") let key=6;;
    "build_name") let key=7;;
    "build_objects_library") let key=8;;
    "build_objects_library_shared") let key=9;;
    "build_objects_library_static") let key=10;;
    "build_objects_program") let key=11;;
    "build_objects_program_shared") let key=12;;
    "build_objects_program_static") let key=13;;
    "build_script") let key=14;;
    "build_shared") let key=15;;
    "build_sources_documentation") let key=16;;
    "build_sources_headers") let key=17;;
    "build_sources_headers_shared") let key=18;;
    "build_sources_headers_static") let key=19;;
    "build_sources_library") let key=20;;
    "build_sources_library_shared") let key=21;;
    "build_sources_library_static") let key=22;;
    "build_sources_object") let key=23;;
    "build_sources_object_shared") let key=24;;
    "build_sources_object_static") let key=25;;
    "build_sources_program") let key=26;;
    "build_sources_program_shared") let key=27;;
    "build_sources_program_static") let key=28;;
    "build_sources_script") let key=29;;
    "build_sources_setting") let key=30;;
    "build_static") let key=31;;
    "defines") let key=32;;
    "defines_library") let key=33;;
    "defines_library_shared") let key=34;;
    "defines_library_static") let key=35;;
    "defines_object") let key=36;;
    "defines_object_shared") let key=37;;
    "defines_object_static") let key=38;;
    "defines_program") let key=39;;
    "defines_program_shared") let key=40;;
    "defines_program_static") let key=41;;
    "defines_shared") let key=42;;
    "defines_static") let key=43;;
    "environment") let key=44;;
    "flags") let key=45;;
    "flags_library") let key=46;;
    "flags_library_shared") let key=47;;
    "flags_library_static") let key=48;;
    "flags_object") let key=49;;
    "flags_object_shared") let key=50;;
    "flags_object_static") let key=51;;
    "flags_program") let key=52;;
    "flags_program_shared") let key=53;;
    "flags_program_static") let key=54;;
    "flags_shared") let key=55;;
    "flags_static") let key=56;;
    "has_path_standard") let key=57;;
    "modes") let key=58;;
    "modes_default") let key=59;;
    "path_headers") let key=60;;
    "path_language") let key=61;;
    "path_library_script") let key=62;;
    "path_library_shared") let key=63;;
    "path_library_static") let key=64;;
    "path_object_script") let key=65;;
    "path_object_shared") let key=66;;
    "path_object_static") let key=67;;
    "path_program_script") let key=68;;
    "path_program_shared") let key=69;;
    "path_program_static") let key=70;;
    "path_sources") let key=71;;
    "path_sources_object") let key=72;;
    "preserve_path_headers") let key=73;;
    "process_post") let key=74;;
    "process_pre") let key=75;;
    "search_exclusive") let key=76;;
    "search_shared") let key=77;;
    "search_static") let key=78;;
    "version_file") let key=79;;
    "version_major") let key=80;;
    "version_major_prefix") let key=81;;
    "version_micro") let key=82;;
    "version_micro_prefix") let key=83;;
    "version_minor") let key=84;;
    "version_minor_prefix") let key=85;;
    "version_nano") let key=86;;
    "version_nano_prefix") let key=87;;
    "version_target") let key=88;;

    "build_compiler-mode") let key=89;;
    "build_indexer-mode") let key=90;;
    "build_indexer_arguments-mode") let key=91;;
    "build_language-mode") let key=92;;
    "build_libraries-mode") let key=93;;
    "build_libraries_shared-mode") let key=94;;
    "build_libraries_static-mode") let key=95;;
    "build_name-mode") let key=96;;
    "build_objects_library-mode") let key=97;;
    "build_objects_library_shared-mode") let key=98;;
    "build_objects_library_static-mode") let key=99;;
    "build_objects_program-mode") let key=100;;
    "build_objects_program_shared-mode") let key=101;;
    "build_objects_program_static-mode") let key=102;;
    "build_script-mode") let key=103;;
    "build_shared-mode") let key=104;;
    "build_sources_documentation-mode") let key=105;;
    "build_sources_headers-mode") let key=106;;
    "build_sources_headers_shared-mode") let key=107;;
    "build_sources_headers_static-mode") let key=108;;
    "build_sources_library-mode") let key=109;;
    "build_sources_library_shared-mode") let key=110;;
    "build_sources_library_static-mode") let key=111;;
    "build_sources_object-mode") let key=112;;
    "build_sources_object_shared-mode") let key=113;;
    "build_sources_object_static-mode") let key=114;;
    "build_sources_program-mode") let key=115;;
    "build_sources_program_shared-mode") let key=116;;
    "build_sources_program_static-mode") let key=117;;
    "build_sources_script-mode") let key=118;;
    "build_sources_setting-mode") let key=119;;
    "build_static-mode") let key=120;;
    "defines-mode") let key=121;;
    "defines_library-mode") let key=122;;
    "defines_library_shared-mode") let key=123;;
    "defines_library_static-mode") let key=124;;
    "defines_object-mode") let key=125;;
    "defines_object_shared-mode") let key=126;;
    "defines_object_static-mode") let key=127;;
    "defines_program-mode") let key=128;;
    "defines_program_shared-mode") let key=129;;
    "defines_program_static-mode") let key=130;;
    "defines_shared-mode") let key=131;;
    "defines_static-mode") let key=132;;
    "environment-mode") let key=133;;
    "flags-mode") let key=134;;
    "flags_library-mode") let key=135;;
    "flags_library_shared-mode") let key=136;;
    "flags_library_static-mode") let key=137;;
    "flags_object-mode") let key=138;;
    "flags_object_shared-mode") let key=139;;
    "flags_object_static-mode") let key=140;;
    "flags_program-mode") let key=141;;
    "flags_program_shared-mode") let key=142;;
    "flags_program_static-mode") let key=143;;
    "flags_shared-mode") let key=144;;
    "flags_static-mode") let key=145;;
    "has_path_standard-mode") let key=146;;
    "path_headers-mode") let key=147;;
    "path_language-mode") let key=148;;
    "path_library_script-mode") let key=149;;
    "path_library_shared-mode") let key=150;;
    "path_library_static-mode") let key=151;;
    "path_object_script-mode") let key=152;;
    "path_object_shared-mode") let key=153;;
    "path_object_static-mode") let key=154;;
    "path_program_script-mode") let key=155;;
    "path_program_shared-mode") let key=156;;
    "path_program_static-mode") let key=157;;
    "path_sources-mode") let key=158;;
    "path_sources_object-mode") let key=159;;
    "preserve_path_headers-mode") let key=160;;
    "process_post-mode") let key=161;;
    "process_pre-mode") let key=162;;
    "search_exclusive-mode") let key=163;;
    "search_shared-mode") let key=164;;
    "search_static-mode") let key=165;;
    "version_file-mode") let key=166;;
    "version_major-mode") let key=167;;
    "version_major_prefix-mode") let key=168;;
    "version_micro-mode") let key=169;;
    "version_micro_prefix-mode") let key=170;;
    "version_minor-mode") let key=171;;
    "version_minor_prefix-mode") let key=172;;
    "version_nano-mode") let key=173;;
    "version_nano_prefix-mode") let key=174;;
    "version_target-mode") let key=175;;

    "has-build_compiler") let key=176;;
    "has-build_indexer") let key=177;;
    "has-build_indexer_arguments") let key=178;;
    "has-build_name") let key=179;;
    "has-has_path_standard") let key=180;;
    "has-path_library_script") let key=181;;
    "has-path_library_shared") let key=182;;
    "has-path_library_static") let key=183;;
    "has-path_object_script") let key=184;;
    "has-path_object_shared") let key=185;;
    "has-path_object_static") let key=186;;
    "has-path_program_script") let key=187;;
    "has-path_program_shared") let key=188;;
    "has-path_program_static") let key=189;;
    "has-path_sources") let key=190;;
    "has-path_sources_object") let key=191;;
    "has-search_exclusive") let key=192;;
    "has-search_shared") let key=193;;
    "has-search_static") let key=194;;
    "has-version_major_prefix") let key=195;;
    "has-version_micro_prefix") let key=196;;
    "has-version_minor_prefix") let key=197;;
    "has-version_nano_prefix") let key=198;;

    "has-build_compiler-mode") let key=199;;
    "has-build_indexer-mode") let key=200;;
    "has-build_indexer_arguments-mode") let key=201;;
    "has-build_name-mode") let key=202;;
    "has-has_path_standard-mode") let key=203;;
    "has-path_library_script-mode") let key=204;;
    "has-path_library_shared-mode") let key=205;;
    "has-path_library_static-mode") let key=206;;
    "has-path_object_script-mode") let key=207;;
    "has-path_object_shared-mode") let key=208;;
    "has-path_object_static-mode") let key=209;;
    "has-path_program_script-mode") let key=210;;
    "has-path_program_shared-mode") let key=211;;
    "has-path_program_static-mode") let key=212;;
    "has-path_sources-mode") let key=213;;
    "has-path_sources_object-mode") let key=214;;
    "has-search_exclusive-mode") let key=215;;
    "has-search_shared-mode") let key=216;;
    "has-search_static-mode") let key=217;;
    "has-version_major_prefix-mode") let key=218;;
    "has-version_micro_prefix-mode") let key=219;;
    "has-version_minor_prefix-mode") let key=220;;
    "has-version_nano_prefix-mode") let key=221;;
  esac
}

bootstrap_load_settings() {
  local i=
  local key=
  local value=

  if [[ ! -d ${path_data}build/ ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: No build settings directory '${c_notice}${path_data}build/${c_error}' could not be found or is not a valid directory.${c_reset}"
    fi

    let failure=1
  elif [[ ! -f ${settings_file} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: No settings file ${c_notice}${settings_file}${c_error} could not be found or is not a valid file.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  # Get available modes.
  if [[ ${modes_available} == "" ]] ; then
    modes_available=$(grep -s -o "^[[:space:]]*modes[[:space:]].*\$" ${settings_file} | sed -e "s|^[[:space:]]*modes\>||" -e 's|^[[:space:]]*||')
  fi

  # Get default modes.
  modes_default=$(grep -s -o "^[[:space:]]*modes_default[[:space:]].*\$" ${settings_file} | sed -e "s|^[[:space:]]*modes_default\>||" -e 's|^[[:space:]]*||')

  # Use default modes if no mode is explicitly provided.
  if [[ ${modes} == "" ]] ; then
    modes=${modes_default}
  fi

  # Single value Objects.
  for i in build_compiler build_indexer build_language build_name build_script build_shared build_sources_object build_sources_object_shared build_sources_object_static build_static has_path_standard path_headers path_language path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object preserve_path_headers process_post process_pre search_exclusive search_shared search_static version_file version_major version_major_prefix version_micro version_micro_prefix version_minor version_minor_prefix version_nano version_nano_prefix version_target ; do

    bootstrap_id "${i}"

    if [[ ${key} == "" ]] ; then
      if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
        echo -e "${c_warning}WARNING: Failed to find index for '${c_notice}${i}${c_warning}' when calling ${c_notice}bootstrap_id()${c_warning}.${c_reset}"
      fi

      key=
      bootstrap_id "has-${i}"
      if [[ ${key} != "" ]] ; then
        variables[${key}]="no"
      fi
    else
      if [[ $(grep -s -o "^[[:space:]]*${i}[[:space:]].*\$" ${settings_file}) != "" ]] ; then
        value=$(grep -s -o "^[[:space:]]*${i}[[:space:]].*\$" ${settings_file} | sed -e "s|^[[:space:]]*${i}\>||" -e 's|^[[:space:]]*||')
        variables[${key}]="${value}"

        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="yes"
        fi
      elif [[ $(grep -s -o "^[[:space:]]*${i}\$" ${settings_file}) != "" ]] ; then
        variables[${key}]=""

        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="yes"
        fi
      else
        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="no"
        fi
      fi
    fi
  done

  # Multi value Objects.
  for i in build_indexer_arguments build_libraries build_libraries_shared build_libraries_static build_objects_library build_objects_library_shared build_objects_library_static build_objects_program build_objects_program_shared build_objects_program_static build_sources_documentation build_sources_headers build_sources_headers_shared build_sources_headers_static build_sources_library build_sources_library_shared build_sources_library_static build_sources_program build_sources_program_shared build_sources_program_static build_sources_script build_sources_setting defines defines_library defines_library_shared defines_library_static defines_object defines_object_shared defines_object_static defines_program defines_program_shared defines_program_static defines_shared defines_static environment flags flags_library flags_library_shared flags_library_static flags_object flags_object_shared flags_object_static flags_program flags_program_shared flags_program_static flags_shared flags_static ; do

    bootstrap_id "${i}"

    if [[ ${key} == "" ]] ; then
      if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
        echo -e "${c_warning}WARNING: Failed to find index for '${c_notice}${i}${c_warning}' when calling ${c_notice}bootstrap_id()${c_warning}.${c_reset}"
      fi

      key=
      bootstrap_id "has-${i}"
      if [[ ${key} != "" ]] ; then
        variables[${key}]="no"
      fi
    else
      if [[ $(grep -s -o "^[[:space:]]*${i}[[:space:]].*\$" ${settings_file}) != "" ]] ; then
        value=$(grep -s -o "^[[:space:]]*${i}[[:space:]].*\$" ${settings_file} | sed -e "s|^[[:space:]]*${i}\>||" -e 's|^[[:space:]]*||')
        variables[${key}]="${variables[${key}]}${value} "

        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="yes"
        fi
      elif [[ $(grep -s -o "^[[:space:]]*${i}\$" ${settings_file}) != "" ]] ; then
        variables[${key}]=""

        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="yes"
        fi
      else
        key=
        bootstrap_id "has-${i}"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="no"
        fi
      fi
    fi
  done
}

bootstrap_load_settings_mode() {
  local i=
  local key=
  local m=
  local value=

  for m in ${modes} ; do

    # Single value Objects.
    for i in build_compiler build_indexer build_language build_name build_script build_shared build_sources_object build_sources_object_shared build_sources_object_static build_static has_path_standard path_headers path_language path_library_script path_library_shared path_library_static path_object_script path_object_shared path_object_static path_program_script path_program_shared path_program_static path_sources path_sources_object preserve_path_headers process_post process_pre search_exclusive search_shared search_static version_file version_major version_major_prefix version_micro version_micro_prefix version_minor version_minor_prefix version_nano version_nano_prefix version_target ; do

      bootstrap_id "${i}-mode"

      if [[ ${key} == "" ]] ; then
        if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
          echo -e "${c_warning}WARNING: Failed to find index for '${c_notice}${i}-${m}${c_warning}' when calling ${c_notice}bootstrap_id()${c_warning}.${c_reset}"
        fi

        key=
        bootstrap_id "has-${i}-mode"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="no"
        fi
      else

        if [[ $(grep -s -o "^[[:space:]]*${i}-${m}[[:space:]].*\$" ${settings_file}) != "" ]] ; then
          value=$(grep -s -o "^[[:space:]]*${i}-${m}[[:space:]].*\$" ${settings_file} | sed -e "H;/${i}-${m}/h;\$!d;x" | sed -e "s|^[[:space:]]*${i}-${m}\>||" -e 's|^[[:space:]]*||')
          variables[${key}]="${value}"

          key=
          bootstrap_id "has-${i}-mode"
          if [[ ${key} != "" ]] ; then
            variables[${key}]="yes"
          fi
        elif [[ $(grep -s -o "^[[:space:]]*${i}-${m}\$" ${settings_file}) != "" ]] ; then
          variables[${key}]=""

          key=
          bootstrap_id "has-${i}-mode"
          if [[ ${key} != "" ]] ; then
            variables[${key}]="yes"
          fi
        else
          key=
          bootstrap_id "has-${i}-mode"
          if [[ ${key} != "" ]] ; then
            variables[${key}]="no"
          fi
        fi
      fi
    done

    # Multi value Objects.
    for i in build_indexer_arguments build_libraries build_libraries_shared build_libraries_static build_objects_library build_objects_library_shared build_objects_library_static build_objects_program build_objects_program_shared build_objects_program_static build_sources_documentation build_sources_headers build_sources_headers_shared build_sources_headers_static build_sources_library build_sources_library_shared build_sources_library_static build_sources_object_shared build_sources_object_static build_sources_program build_sources_program_shared build_sources_program_static build_sources_script build_sources_setting build_static defines defines_library defines_library_shared defines_library_static defines_object defines_object_shared defines_object_static defines_program defines_program_shared defines_program_static defines_shared defines_static environment flags flags_library flags_library_shared flags_library_static flags_object flags_object_shared flags_object_static flags_program flags_program_shared flags_program_static flags_shared flags_static ; do

      bootstrap_id "${i}-mode"

      if [[ ${key} == "" ]] ; then
        if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
          echo -e "${c_warning}WARNING: Failed to find index for '${c_notice}${i}-${m}${c_warning}' when calling ${c_notice}bootstrap_id()${c_warning}.${c_reset}"
        fi

        key=
        bootstrap_id "has-${i}-mode"
        if [[ ${key} != "" ]] ; then
          variables[${key}]="no"
        fi
      else
        if [[ $(grep -s -o "^[[:space:]]*${i}-${m}[[:space:]].*\$" ${settings_file}) != "" ]] ; then
          value=$(grep -s -o "^[[:space:]]*${i}-${m}[[:space:]].*\$" ${settings_file} | sed -e "s|^[[:space:]]*${i}-${m}\>||" -e 's|^[[:space:]]*||')
          variables[${key}]="${variables[${key}]}${value} "

          key=
          bootstrap_id "has-${i}"
          if [[ ${key} != "" ]] ; then
            variables[${key}]="yes"
          fi
        elif [[ $(grep -s -o "^[[:space:]]*${i}-${m}\$" ${settings_file}) != "" ]] ; then
          variables[${key}]=""

          key=
          bootstrap_id "has-${i}"
          if [[ ${key} != "" ]] ; then
            variables[${key}]="yes"
          fi
        else
          key=
          bootstrap_id "has-${i}-mode"
          if [[ ${key} != "" && ${variables[${key}]} != "yes" ]] ; then
            variables[${key}]="no"
          fi
        fi
      fi
    done
  done
}

bootstrap_prepare_build() {
  local alt=${1}
  local i=

  mkdir ${verbose_common} -p ${path_build}{documents,documentation,includes,libraries/{script,shared,static},objects/{script,shared,static},programs/{script,shared,static},settings,stage} || failure=1

  if [[ ${failure} -eq 1 ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      echo -e "${c_warning}WARNING: Failed to create build directories in '${c_notice}${path_build}${c_error}'.${c_reset}"
    fi

    return 1
  fi

  bootstrap_id "path_headers-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    mkdir ${verbose_common} -p ${path_build}includes/${variables[${key}]} || failure=1
  else
    bootstrap_id "path_headers"

    if [[ ${variables[${key}]} != "" ]] ; then
      mkdir ${verbose_common} -p ${path_build}includes/${variables[${key}]} || failure=1
    fi
  fi

  if [[ ${failure} -eq 1 ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      echo -e "${c_warning}WARNING: Failed to create ${c_notice}path_heades${c_error} build directories in '${c_notice}${path_build}${c_error}'.${c_reset}"
    fi

    return 1
  fi

  touch ${project_built}-${settings_name}.prepared

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build() {
  local i=
  local n=
  local version_file=
  local version_target=
  local alt=${1}
  local directory=
  local key=

  bootstrap_id "build_compiler"
  local build_compiler=${variables[${key}]}

  bootstrap_id "build_indexer"
  local build_indexer=${variables[${key}]}

  bootstrap_id "build_indexer_arguments"
  local build_indexer_arguments=${variables[${key}]}

  bootstrap_id "build_name"
  local build_name=${variables[${key}]}

  bootstrap_id "build_shared"
  local build_shared=${variables[${key}]}

  bootstrap_id "build_static"
  local build_static=${variables[${key}]}

  bootstrap_id "defines"
  local defines=${variables[${key}]}

  bootstrap_id "defines_library"
  local defines_library=${variables[${key}]}

  bootstrap_id "defines_library_shared"
  local defines_library_shared=${variables[${key}]}

  bootstrap_id "defines_library_static"
  local defines_library_static=${variables[${key}]}

  bootstrap_id "defines_object"
  local defines_object=${variables[${key}]}

  bootstrap_id "defines_object_shared"
  local defines_object_shared=${variables[${key}]}

  bootstrap_id "defines_object_static"
  local defines_object_static=${variables[${key}]}

  bootstrap_id "defines_program"
  local defines_program=${variables[${key}]}

  bootstrap_id "defines_program_shared"
  local defines_program_shared=${variables[${key}]}

  bootstrap_id "defines_program_static"
  local defines_program_static=${variables[${key}]}

  bootstrap_id "defines_shared"
  local defines_shared=${variables[${key}]}

  bootstrap_id "defines_static"
  local defines_static=${variables[${key}]}

  bootstrap_id "flags"
  local flags=${variables[${key}]}

  bootstrap_id "flags_library"
  local flags_library=${variables[${key}]}

  bootstrap_id "flags_library_shared"
  local flags_library_shared=${variables[${key}]}

  bootstrap_id "flags_library_static"
  local flags_library_static=${variables[${key}]}

  bootstrap_id "flags_object"
  local flags_object=${variables[${key}]}

  bootstrap_id "flags_object_shared"
  local flags_object_shared=${variables[${key}]}

  bootstrap_id "flags_object_static"
  local flags_object_static=${variables[${key}]}

  bootstrap_id "flags_program"
  local flags_program=${variables[${key}]}

  bootstrap_id "flags_program_shared"
  local flags_program_shared=${variables[${key}]}

  bootstrap_id "flags_program_static"
  local flags_program_static=${variables[${key}]}

  bootstrap_id "flags_shared"
  local flags_shared=${variables[${key}]}

  bootstrap_id "flags_static"
  local flags_static=${variables[${key}]}

  bootstrap_id "build_libraries"
  local libraries=${variables[${key}]}

  bootstrap_id "build_libraries_shared"
  local libraries_shared=${variables[${key}]}

  bootstrap_id "build_libraries_static"
  local libraries_static=${variables[${key}]}

  bootstrap_id "build_objects_library"
  local objects_library=${variables[${key}]}

  bootstrap_id "build_objects_library_shared"
  local objects_library_shared=${variables[${key}]}

  bootstrap_id "build_objects_library_static"
  local objects_library_static=${variables[${key}]}

  bootstrap_id "build_objects_program"
  local objects_program=${variables[${key}]}

  bootstrap_id "build_objects_program_shared"
  local objects_program_shared=${variables[${key}]}

  bootstrap_id "build_objects_program_static"
  local objects_program_static=${variables[${key}]}

  bootstrap_id "path_headers"
  local path_headers=${variables[${key}]}

  bootstrap_id "preserve_path_headers"
  local preserve_path_headers=${variables[${key}]}

  bootstrap_id "path_library_script"
  local path_library_script=${variables[${key}]}

  bootstrap_id "path_library_shared"
  local path_library_shared=${variables[${key}]}

  bootstrap_id "path_library_static"
  local path_library_static=${variables[${key}]}

  bootstrap_id "path_object_script"
  local path_object_script=${variables[${key}]}

  bootstrap_id "path_object_shared"
  local path_object_shared=${variables[${key}]}

  bootstrap_id "path_object_static"
  local path_object_static=${variables[${key}]}

  bootstrap_id "path_program_script"
  local path_program_script=${variables[${key}]}

  bootstrap_id "path_program_shared"
  local path_program_shared=${variables[${key}]}

  bootstrap_id "path_program_static"
  local path_program_static=${variables[${key}]}

  bootstrap_id "has_path_standard"
  local has_path_standard=${variables[${key}]}

  bootstrap_id "search_exclusive"
  local search_exclusive=${variables[${key}]}

  bootstrap_id "search_shared"
  local search_shared=${variables[${key}]}

  bootstrap_id "search_static"
  local search_static=${variables[${key}]}

  bootstrap_id "build_sources_documentation"
  local sources_documentation=${variables[${key}]}

  bootstrap_id "build_sources_headers"
  local sources_headers=${variables[${key}]}

  bootstrap_id "build_sources_library"
  local sources_library=${variables[${key}]}

  bootstrap_id "build_sources_library_shared"
  local sources_library_shared=${variables[${key}]}

  bootstrap_id "build_sources_library_static"
  local sources_library_static=${variables[${key}]}

  bootstrap_id "build_sources_object"
  local sources_object=${variables[${key}]}

  bootstrap_id "build_sources_object_shared"
  local sources_object_shared=${variables[${key}]}

  bootstrap_id "build_sources_object_static"
  local sources_object_static=${variables[${key}]}

  bootstrap_id "build_sources_program"
  local sources_program=${variables[${key}]}

  bootstrap_id "build_sources_program_shared"
  local sources_program_shared=${variables[${key}]}

  bootstrap_id "build_sources_program_static"
  local sources_program_static=${variables[${key}]}

  bootstrap_id "build_sources_script"
  local sources_script=${variables[${key}]}

  bootstrap_id "build_sources_setting"
  local sources_setting=${variables[${key}]}

  bootstrap_id "version_file"
  local version_file_value=${variables[${key}]}

  bootstrap_id "version_major"
  local version_major=${variables[${key}]}

  bootstrap_id "version_major_prefix"
  local version_major_prefix=${variables[${key}]}

  bootstrap_id "version_minor"
  local version_minor=${variables[${key}]}

  bootstrap_id "version_minor_prefix"
  local version_minor_prefix=${variables[${key}]}

  bootstrap_id "version_micro"
  local version_micro=${variables[${key}]}

  bootstrap_id "version_micro_prefix"
  local version_micro_prefix=${variables[${key}]}

  bootstrap_id "version_nano"
  local version_nano=${variables[${key}]}

  bootstrap_id "version_nano_prefix"
  local version_nano_prefix=${variables[${key}]}

  bootstrap_id "version_target"
  local version_target_value=${variables[${key}]}

  local links=
  local sources=

  bootstrap_operation_build_prepare_defaults

  bootstrap_operation_build_prepare_versions

  bootstrap_operation_build_prepare_shared_static

  bootstrap_operation_build_prepare_paths

  bootstrap_operation_build_prepare_flags

  bootstrap_operation_build_prepare_defines

  bootstrap_operation_build_prepare_libraries

  bootstrap_operation_build_prepare_objects

  bootstrap_operation_build_prepare_programs

  bootstrap_operation_build_prepare_settings

  bootstrap_operation_build_prepare_documentation

  bootstrap_operation_build_prepare_headers

  bootstrap_operation_build_prepare_remaining

  if [[ ${build_shared} == "yes" && -f ${project_built_shared}.built || ${build_static} == "yes" && -f ${project_built_static}.built ]] ; then
    if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
      echo -e "${c_warning}WARNING: This project has already been built.${c_reset}"
    fi

    return 0
  fi

  local arguments_include="-I${path_build}includes/"
  local arguments_shared="-L${path_build}libraries/${path_library_shared}"
  local arguments_static="-L${path_build}libraries/${path_library_static}"

  if [[ ${path_work} != "" ]] ; then
    arguments_include="${arguments_include} -I${path_work}includes/"
    arguments_shared="${arguments_shared} -L${path_work}libraries/${path_library_shared}"
    arguments_static="${arguments_static} -L${path_work}libraries/${path_library_static}"
  fi

  bootstrap_operation_build_validate_paths

  bootstrap_operation_build_validate_shared_static

  bootstrap_operation_build_validate_sources

  bootstrap_operation_build_validate_search

  bootstrap_operation_build_validate_build

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  if [[ ${sources_documentation} != "" ]] ; then
    for i in ${sources_documentation} ; do
      directory=$(dirname ${i})

      if [[ ! -e ${path_documentation}${i} ]] ; then
        if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
          echo
          echo -e "${c_warning}WARNING: Documentation path '${c_notice}${path_documentation}${i}${c_warning}' is not found.${c_reset}"
        fi

        continue;
      fi

      if [[ ${directory} == "." ]] ; then
        cp ${verbose_common} -R ${path_documentation}${i} ${path_build}documentation/ || failure=1
      else
        mkdir ${verbose_common} -p ${path_build}documentation/${directory} || failure=1

        if [[ ${failure} -eq 0 ]] ; then
          cp ${verbose_common} -R ${path_documentation}${i} ${path_build}documentation/${directory}/ || failure=1
        fi
      fi
    done
  fi

  if [[ ${sources_setting} != "" ]] ; then
    for i in ${sources_setting} ; do
      directory=$(dirname ${i})

      if [[ ${directory} == "." ]] ; then
        cp ${verbose_common} -R ${path_settings}${i} ${path_build}settings/ || failure=1
      else
        mkdir ${verbose_common} -p ${path_build}settings/${directory} || failure=1

        if [[ ${failure} -eq 0 ]] ; then
          cp ${verbose_common} -R ${path_settings}${i} ${path_build}settings/${directory}/ || failure=1
        fi
      fi
    done
  fi

  if [[ ${failure} -eq 0 && ${sources_headers} != "" ]] ; then
    if [[ ${preserve_path_headers} == "yes" ]] ; then
      for i in ${sources_headers} ; do
        directory=$(dirname ${i})

        if [[ ${directory} == "." ]] ; then
          cp ${verbose_common} -f ${path_sources}${path_language}${i} ${path_build}includes/${path_headers} || failure=1
        else
          if [[ ! -d ${path_build}includes/${path_headers}${directory} ]] ; then
            mkdir ${verbose_common} -p ${path_build}includes/${path_headers}${directory} || failure=1
          fi

          if [[ ${failure} -eq 0 ]] ; then
            cp ${verbose_common} -f ${path_sources}${path_language}${i} ${path_build}includes/${path_headers}${i} || failure=1
          fi
        fi
      done
    else
      for i in ${sources_headers} ; do
        cp ${verbose_common} -f ${path_sources}${path_language}${i} ${path_build}includes/${path_headers} || failure=1
      done
    fi
  fi

  if [[ ${failure} -eq 0 && ${build_shared} == "yes" && ! -f ${project_built_shared}.built ]] ; then
    if [[ ${sources_object} != "" || ${sources_object_shared} != "" ]] ; then
      sources=
      let count=0

      # Sources object only allows for a single value.
      if [[ ${sources_object_shared} != "" ]] ; then
        for i in ${sources_object_shared} ; do
          let count++
        done

        if [[ ${count} -gt 1 ]] ; then
          if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object_shared${c_warning}' found, only using the first one found is going to be used.${c_reset}"
          fi
        fi

        for i in ${sources_object_shared} ; do
          sources="${path_sources_object}${path_language}${i} "

          break
        done
      else
        for i in ${sources_object} ; do
          let count++
        done

        if [[ ${count} -gt 1 ]] ; then
          if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object${c_warning}' found, only using the first one found is going to be used.${c_reset}"
          fi
        fi

        for i in ${sources_object} ; do
          sources="${path_sources_object}${path_language}${i} "

          break
        done
      fi

      if [[ ${verbosity} == "verbose" ]] ; then
        echo ${build_compiler} ${sources} -c -o ${path_build}objects/${path_object_shared}${build_name}.o ${arguments_shared} ${arguments_include} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_object} ${flags_object_shared} ${defines} ${defines_shared} ${defines_object} ${defines_object_shared} ${define_extra}
      fi

      ${build_compiler} ${sources} -c -o ${path_build}objects/${path_object_shared}${build_name}.o ${arguments_shared} ${arguments_include} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_object} ${flags_object_shared} ${defines} ${defines_shared} ${defines_object} ${defines_object_shared} ${define_extra} || failure=1
    fi

    if [[ ${sources_library} != "" || ${sources_library_shared} != "" ]] ; then
      sources=

      if [[ ${objects_library} != "" || ${objects_library_shared} != "" ]] ; then
        for i in ${objects_library} ${objects_library_shared} ; do
          sources="${sources}${path_build}objects/${path_object_shared}${i} "
        done
      fi

      for i in ${sources_library} ${sources_library_shared} ; do
        sources="${sources}${path_sources}${path_language}${i} "
      done

      if [[ ${verbosity} == "verbose" ]] ; then
        echo ${build_compiler} ${sources} -shared -Wl,-soname,lib${build_name}.so${version_target} -o ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_file} ${arguments_shared} ${arguments_include} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_library} ${flags_library_shared} ${defines} ${defines_shared} ${defines_library} ${defines_library_shared} ${define_extra}
      fi

      ${build_compiler} ${sources} -shared -Wl,-soname,lib${build_name}.so${version_target} -o ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_file} ${arguments_shared} ${arguments_include} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_library} ${flags_library_shared} ${defines} ${defines_shared} ${defines_library} ${defines_library_shared} ${define_extra} || failure=1

      if [[ ${failure} -eq 0 ]] ; then
        if [[ ${version_file_value} != "major" ]] ; then
          if [[ ${version_file_value} == "minor" ]] ; then
            ln ${verbose_common} -sf lib${build_name}.so${version_file} ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_major_prefix}${version_major} || failure=1
          else
            ln ${verbose_common} -sf lib${build_name}.so${version_major_prefix}${version_major}${version_minor_prefix}${version_minor} ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_major_prefix}${version_major} || failure=1

            if [[ ${failure} -eq 0 ]] ; then
              if [[ ${version_file_value} == "micro" ]] ; then
                ln ${verbose_common} -sf lib${build_name}.so${version_file} ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_major_prefix}${version_major}${version_minor_prefix}${version_minor} || failure=1
              else
                ln ${verbose_common} -sf lib${build_name}.so${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro} ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_major_prefix}${version_major}${version_minor_prefix}${version_minor} || failure=1

                if [[ ${failure} -eq 0 ]] ; then
                  ln ${verbose_common} -sf lib${build_name}.so${version_file} ${path_build}libraries/${path_library_shared}lib${build_name}.so${version_major_prefix}${version_major}${version_minor_prefix}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro} || failure=1
                fi
              fi
            fi
          fi
        fi

        if [[ ${failure} -eq 0 ]] ; then
          ln ${verbose_common} -sf lib${build_name}.so${version_major_prefix}${version_major} ${path_build}libraries/${path_library_shared}lib${build_name}.so || failure=1
        fi
      fi
    fi

    if [[ ${failure} -eq 0 && ${sources_program} != "" ]] ; then
      sources=
      links=

      if [[ ${sources_library} != "" || ${sources_library_shared} != "" ]] ; then
        links="-l${build_name} "
      fi

      if [[ ${objects_program} != "" || ${objects_program_shared} != "" ]] ; then
        for i in ${objects_program} ${objects_program_shared} ; do
          sources="${sources}${path_build}objects/${path_object_shared}${i} "
        done
      fi

      for i in ${sources_program} ${sources_program_shared} ; do
        sources="${sources}${path_sources}${path_language}${i} "
      done

      if [[ ${verbosity} == "verbose" ]] ; then
        echo ${build_compiler} ${sources} -o ${path_build}programs/${path_program_shared}${build_name} ${arguments_shared} ${arguments_include} ${links} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_program} ${flags_program_shared} ${defines} ${defines_shared} ${defines_program} ${defines_program_shared} ${define_extra}
      fi

      ${build_compiler} ${sources} -o ${path_build}programs/${path_program_shared}${build_name} ${arguments_shared} ${arguments_include} ${links} ${libraries} ${libraries_shared} ${flags} ${flags_shared} ${flags_program} ${flags_program_shared} ${defines} ${defines_shared} ${defines_program} ${defines_program_shared} ${define_extra} || failure=1
    fi

    if [[ ${failure} -eq 0 ]] ; then
      touch ${project_built_shared}-${settings_name}.built
    fi
  fi

  if [[ ${failure} -eq 0 && ${build_static} == "yes" && ! -f ${project_built_static}.built ]] ; then
    if [[ ${sources_object} != "" || ${sources_object_static} != "" ]] ; then
      let count=0

      # Sources object only allows for a single value.
      if [[ ${sources_object_static} != "" ]] ; then
        for i in ${sources_object_static} ; do
          let count++
        done

        if [[ ${count} -gt 1 ]] ; then
          if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object_static${c_warning}' found, only using the first one found is going to be used.${c_reset}"
          fi
        fi

        for i in ${sources_object_static} ; do
          sources="${path_sources_object}${path_language}${i} "

          break
        done
      else
        for i in ${sources_object} ; do
          let count++
        done

        if [[ ${count} -gt 1 ]] ; then
          if [[ ${verbosity} != "quiet" && ${verbosity} != "error" ]] ; then
            echo -e "${c_warning}WARNING: Multiple '${c_notice}sources_object${c_warning}' found, only using the first one found is going to be used.${c_reset}"
          fi
        fi

        for i in ${sources_object} ; do
          sources="${path_sources_object}${path_language}${i} "

          break
        done
      fi

      if [[ ${verbosity} == "verbose" ]] ; then
        echo ${build_compiler} ${sources} -c -o ${path_build}objects/${path_object_static}${build_name}.o ${arguments_static} ${arguments_include} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_object} ${flags_object_static} ${defines} ${defines_static} ${defines_object} ${defines_object_static} ${define_extra}
      fi

      ${build_compiler} ${sources} -c -o ${path_build}objects/${path_object_static}${build_name}.o ${arguments_static} ${arguments_include} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_object} ${flags_object_static} ${defines} ${defines_static} ${defines_object} ${defines_object_static} ${define_extra} || failure=1
    fi

    if [[ ${sources_library} != "" || ${sources_library_static} != "" ]] ; then
      sources=

      if [[ ${objects_library} != "" || ${objects_library_static} != "" ]] ; then
        for i in ${objects_library} ${objects_library_static} ; do
          sources="${sources}${path_build}objects/${path_object_static}${i} "
        done
      fi

      for i in ${sources_library} ${sources_library_static} ; do
        directory=$(dirname ${i})
        n=$(basename ${i} | sed -e 's|\.c$||')

        if [[ ${directory} != "." && ! -d ${path_build}objects/${directory} ]] ; then
          mkdir ${verbose_common} -p ${path_build}objects/${directory}

          if [[ ${?} -ne 0 ]] ; then
            let failure=1

            break;
          fi
        fi

        # These are objects created by the static build step rather than objects created by the object build step.
        sources="${sources}${path_build}objects/${directory}/${n}.o "

        if [[ ${verbosity} == "verbose" ]] ; then
          echo ${build_compiler} ${path_sources}${path_language}${i} -c -static -o ${path_build}objects/${directory}/${n}.o ${arguments_static} ${arguments_include} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_library} ${flags_library_static} ${defines} ${defines_static} ${defines_library} ${defines_library_static} ${define_extra}
        fi

        ${build_compiler} ${path_sources}${path_language}${i} -c -static -o ${path_build}objects/${directory}/${n}.o ${arguments_static} ${arguments_include} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_library} ${flags_library_static} ${defines} ${defines_static} ${defines_library} ${defines_library_static} ${define_extra} || failure=1

        if [[ ${failure} -eq 1 ]] ; then
          break;
        fi
      done

      if [[ ${failure} -eq 0 && ( ${sources_library} != "" || ${sources_library_static} != "" ) ]] ; then

        if [[ ${verbosity} == "verbose" ]] ; then
          echo ${build_indexer} ${build_indexer_arguments} ${path_build}libraries/${path_library_static}lib${build_name}.a ${sources}
        fi

        ${build_indexer} ${build_indexer_arguments} ${path_build}libraries/${path_library_static}lib${build_name}.a ${sources} || failure=1
      fi
    fi

    if [[ ${failure} -eq 0 && ${sources_program} != "" ]] ; then
      sources=
      links=

      if [[ ${sources_library} != "" || ${sources_library_static} != "" ]] ; then
        links="-l${build_name} "
      fi

      if [[ ${objects_program} != "" || ${objects_program_static} != "" ]] ; then
        for i in ${objects_program} ${objects_program_static} ; do
          sources="${sources}${path_build}objects/${path_object_static}${i} "
        done
      fi

      for i in ${sources_program} ${sources_program_static} ; do
        sources="${sources}${path_sources}${path_language}${i} "
      done

      if [[ ${verbosity} == "verbose" ]] ; then
        echo ${build_compiler} ${sources} -static -o ${path_build}programs/${path_program_static}${build_name} ${arguments_static} ${arguments_include} ${links} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_program} ${flags_program_static} ${defines} ${defines_static} ${defines_program} ${defines_program_static} ${define_extra}
      fi

      ${build_compiler} ${sources} -static -o ${path_build}programs/${path_program_static}${build_name} ${arguments_static} ${arguments_include} ${links} ${libraries} ${libraries_static} ${flags} ${flags_static} ${flags_program} ${flags_program_static} ${defines} ${defines_static} ${defines_program} ${defines_program_static} ${define_extra} || failure=1
    fi

    if [[ ${failure} -eq 0 ]] ; then
      touch ${project_built_static}-${settings_name}.built
    fi
  fi

  if [[ ${failure} -eq 1 ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Failed to build.${c_reset}"
    fi

    let failure=1

    return 1
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build_prepare_defaults() {
  local key=

  bootstrap_id "has-version_major_prefix-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-version_major_prefix"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      version_major_prefix="."
    fi
  fi

  bootstrap_id "has-version_minor_prefix-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-version_minor_prefix"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      version_minor_prefix="."
    fi
  fi

  bootstrap_id "has-version_micro_prefix-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-version_micro_prefix"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      version_micro_prefix="."
    fi
  fi

  bootstrap_id "has-version_nano_prefix-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-version_nano_prefix"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      version_nano_prefix="."
    fi
  fi

  bootstrap_id "has-build_compiler-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-build_compiler"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      build_compiler="gcc"
    fi
  fi

  bootstrap_id "has-build_indexer-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-build_indexer"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      build_indexer="ar"
    fi
  fi

  bootstrap_id "has-path_library_script-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_library_script"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_library_script="script/"
    fi
  fi

  bootstrap_id "has-path_library_shared-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_library_shared"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_library_shared="shared/"
    fi
  fi

  bootstrap_id "has-path_library_static-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_library_static"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_library_static="static/"
    fi
  fi

  bootstrap_id "has-path_object_script-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_object_script"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_object_script="script/"
    fi
  fi

  bootstrap_id "has-path_object_shared-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_object_shared"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_object_shared="shared/"
    fi
  fi

  bootstrap_id "has-path_object_static-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_object_static"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_object_static="static/"
    fi
  fi

  bootstrap_id "has-path_program_script-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_program_script"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_program_script="script/"
    fi
  fi

  bootstrap_id "has-path_program_shared-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_program_shared"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_program_shared="shared/"
    fi
  fi

  bootstrap_id "has-path_program_static-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_program_static"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_program_static="static/"
    fi
  fi

  bootstrap_id "has-path_sources-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_sources"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_sources="sources/"
    fi
  fi

  bootstrap_id "has-path_sources_object-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-path_sources_object"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      path_sources_object="sources/"
    fi
  fi

  bootstrap_id "has-has_path_standard-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-has_path_standard"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      has_path_standard="yes"
    fi
  fi

  bootstrap_id "has-search_shared-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-search_shared"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      search_shared="yes"
    fi
  fi

  bootstrap_id "has-build_shared-mode"
  if [[ ${variables[${key}]} != "yes" ]] ; then

    bootstrap_id "has-build_shared"
    if [[ ${variables[${key}]} != "yes" ]] ; then
      build_shared="yes"
    fi
  fi
}

bootstrap_operation_build_prepare_defines() {
  local key=

  bootstrap_id "defines-mode"
  if [[ ${defines} == "" ]] ; then
    defines=${variables[${key}]}
  else
    defines="${defines} ${variables[${key}]}"
  fi

  bootstrap_id "defines_library-mode"
  if [[ ${defines_library} == "" ]] ; then
    defines_library=${variables[${key}]}
  else
    defines_library="${defines_library} ${variables[${key}]}"
  fi

  bootstrap_id "defines_library_shared-mode"
  if [[ ${defines_library_shared} == "" ]] ; then
    defines_library_shared=${variables[${key}]}
  else
    defines_library_shared="${defines_library_shared} ${variables[${key}]}"
  fi

  bootstrap_id "defines_library_static-mode"
  if [[ ${defines_library_static} == "" ]] ; then
    defines_library_static=${variables[${key}]}
  else
    defines_library_static="${defines_library_static} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_library-mode"
  if [[ ${defines_object_library} == "" ]] ; then
    defines_object_library=${variables[${key}]}
  else
    defines_object_library="${defines_object_library} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_library_shared-mode"
  if [[ ${defines_object_library_shared} == "" ]] ; then
    defines_object_library_shared=${variables[${key}]}
  else
    defines_object_library_shared="${defines_object_library_shared} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_library_static-mode"
  if [[ ${defines_object_library_static} == "" ]] ; then
    defines_object_library_static=${variables[${key}]}
  else
    defines_object_library_static="${defines_object_library_static} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_program-mode"
  if [[ ${defines_object_program} == "" ]] ; then
    defines_object_program=${variables[${key}]}
  else
    defines_object_program="${defines_object_program} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_program_shared-mode"
  if [[ ${defines_object_program_shared} == "" ]] ; then
    defines_object_program_shared=${variables[${key}]}
  else
    defines_object_program_shared="${defines_object_program_shared} ${variables[${key}]}"
  fi

  bootstrap_id "defines_object_program_static-mode"
  if [[ ${defines_object_program_static} == "" ]] ; then
    defines_object_program_static=${variables[${key}]}
  else
    defines_object_program_static="${defines_object_program_static} ${variables[${key}]}"
  fi

  bootstrap_id "defines_program-mode"
  if [[ ${defines_program} == "" ]] ; then
    defines_program=${variables[${key}]}
  else
    defines_program="${defines_program} ${variables[${key}]}"
  fi

  bootstrap_id "defines_program_shared-mode"
  if [[ ${defines_program_shared} == "" ]] ; then
    defines_program_shared=${variables[${key}]}
  else
    defines_program_shared="${defines_program_shared} ${variables[${key}]}"
  fi

  bootstrap_id "defines_program_static-mode"
  if [[ ${defines_program_static} == "" ]] ; then
    defines_program_static=${variables[${key}]}
  else
    defines_program_static="${defines_program_static} ${variables[${key}]}"
  fi

  bootstrap_id "defines_shared-mode"
  if [[ ${defines_shared} == "" ]] ; then
    defines_shared=${variables[${key}]}
  else
    defines_shared="${defines_shared} ${variables[${key}]}"
  fi

  bootstrap_id "defines_static-mode"
  if [[ ${defines_static} == "" ]] ; then
    defines_static=${variables[${key}]}
  else
    defines_static="${defines_static} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_documentation() {
  local key=

  bootstrap_id "build_sources_documentation-mode"
  if [[ ${sources_documentation} == "" ]] ; then
    sources_documentation=${variables[${key}]}
  else
    sources_documentation="${sources_documentation} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_flags() {
  local key=

  bootstrap_id "flags-mode"
  if [[ ${flags} == "" ]] ; then
    flags=${variables[${key}]}
  else
    flags="${flags} ${variables[${key}]}"
  fi

  bootstrap_id "flags_library-mode"
  if [[ ${flags_library} == "" ]] ; then
    flags_library=${variables[${key}]}
  else
    flags_library="${flags_library} ${variables[${key}]}"
  fi

  bootstrap_id "flags_library_shared-mode"
  if [[ ${flags_library_shared} == "" ]] ; then
    flags_library_shared=${variables[${key}]}
  else
    flags_library_shared="${flags_library_shared} ${variables[${key}]}"
  fi

  bootstrap_id "flags_library_static-mode"
  if [[ ${flags_library_static} == "" ]] ; then
    flags_library_static=${variables[${key}]}
  else
    flags_library_static="${flags_library_static} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_library-mode"
  if [[ ${flags_object_library} == "" ]] ; then
    flags_object_library=${variables[${key}]}
  else
    flags_object_library="${flags_object_library} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_library_shared-mode"
  if [[ ${flags_object_library_shared} == "" ]] ; then
    flags_object_library_shared=${variables[${key}]}
  else
    flags_object_library_shared="${flags_object_library_shared} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_library_static-mode"
  if [[ ${flags_object_library_static} == "" ]] ; then
    flags_object_library_static=${variables[${key}]}
  else
    flags_object_library_static="${flags_object_library_static} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_program-mode"
  if [[ ${flags_object_program} == "" ]] ; then
    flags_object_program=${variables[${key}]}
  else
    flags_object_program="${flags_object_program} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_program_shared-mode"
  if [[ ${flags_object_program_shared} == "" ]] ; then
    flags_object_program_shared=${variables[${key}]}
  else
    flags_object_program_shared="${flags_object_program_shared} ${variables[${key}]}"
  fi

  bootstrap_id "flags_object_program_static-mode"
  if [[ ${flags_object_program_static} == "" ]] ; then
    flags_object_program_static=${variables[${key}]}
  else
    flags_object_program_static="${flags_object_program_static} ${variables[${key}]}"
  fi

  bootstrap_id "flags_program-mode"
  if [[ ${flags_program} == "" ]] ; then
    flags_program=${variables[${key}]}
  else
    flags_program="${flags_program} ${variables[${key}]}"
  fi

  bootstrap_id "flags_program_shared-mode"
  if [[ ${flags_program_shared} == "" ]] ; then
    flags_program_shared=${variables[${key}]}
  else
    flags_program_shared="${flags_program_shared} ${variables[${key}]}"
  fi

  bootstrap_id "flags_program_static-mode"
  if [[ ${flags_program_static} == "" ]] ; then
    flags_program_static=${variables[${key}]}
  else
    flags_program_static="${flags_program_static} ${variables[${key}]}"
  fi

  bootstrap_id "flags_shared-mode"
  if [[ ${flags_shared} == "" ]] ; then
    flags_shared=${variables[${key}]}
  else
    flags_shared="${flags_shared} ${variables[${key}]}"
  fi

  bootstrap_id "flags_static-mode"
  if [[ ${flags_static} == "" ]] ; then
    flags_static=${variables[${key}]}
  else
    flags_static="${flags_static} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_headers() {
  local key=

  bootstrap_id "build_sources_headers-mode"
  if [[ ${sources_headers} == "" ]] ; then
    sources_headers=${variables[${key}]}
  else
    sources_headers="${sources_headers} ${variables[${key}]}"
  fi

  if [[ ${build_shared} == "yes" ]] ; then
    bootstrap_id "build_sources_headers_shared"
    if [[ ${sources_headers} == "" ]] ; then
      sources_headers=${variables[${key}]}
    else
      sources_headers="${sources_headers} ${variables[${key}]}"
    fi

    bootstrap_id "build_sources_headers_static"
    if [[ ${sources_headers} == "" ]] ; then
      sources_headers=${variables[${key}]}
    else
      sources_headers="${sources_headers} ${variables[${key}]}"
    fi
  fi

  if [[ ${build_static} == "yes" ]] ; then
    bootstrap_id "build_sources_headers_shared-mode"
    if [[ ${sources_headers} == "" ]] ; then
      sources_headers=${variables[${key}]}
    else
      sources_headers="${sources_headers} ${variables[${key}]}"
    fi

    bootstrap_id "build_sources_headers_static-mode"
    if [[ ${sources_headers} == "" ]] ; then
      sources_headers=${variables[${key}]}
    else
      sources_headers="${sources_headers} ${variables[${key}]}"
    fi
  fi

  bootstrap_id "path_headers-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_headers=${variables[${key}]}
  else
    bootstrap_id "path_headers"
    if [[ ${variables[${key}]} != "" ]] ; then
      path_headers=${variables[${key}]}
    fi
  fi

  if [[ ${path_headers} != "" ]] ; then
    path_headers=$(echo ${path_headers} | sed -e 's|/*$|/|')
  fi
}

bootstrap_operation_build_prepare_libraries() {
  local key=

  bootstrap_id "build_libraries-mode"
  if [[ ${libraries} == "" ]] ; then
    libraries=${variables[${key}]}
  else
    libraries="${variables[${key}]} ${libraries}"
  fi

  bootstrap_id "build_libraries_shared-mode"
  if [[ ${libraries_shared} == "" ]] ; then
    libraries_shared=${variables[${key}]}
  else
    libraries_shared="${variables[${key}]} ${libraries_shared}"
  fi

  bootstrap_id "build_libraries_static-mode"
  if [[ ${libraries_static} == "" ]] ; then
    libraries_static=${variables[${key}]}
  else
    libraries_static="${variables[${key}]} ${libraries_static}"
  fi

  bootstrap_id "build_sources_library-mode"
  if [[ ${sources_library} == "" ]] ; then
    sources_library=${variables[${key}]}
  else
    sources_library="${sources_library} ${variables[${key}]}"
  fi

  bootstrap_id "build_sources_library_shared-mode"
  if [[ ${sources_library_shared} == "" ]] ; then
    sources_library_shared=${variables[${key}]}
  else
    sources_library_shared="${build_sources_library_shared} ${variables[${key}]}"
  fi

  bootstrap_id "build_sources_library_static-mode"
  if [[ ${sources_library_static} == "" ]] ; then
    sources_library_static=${variables[${key}]}
  else
    sources_library_static="${build_sources_library_static} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_objects() {
  local key=

  bootstrap_id "build_objects_library-mode"
  if [[ ${objects_library} == "" ]] ; then
    objects_library=${variables[${key}]}
  else
    objects_library="${variables[${key}]} ${objects_library}"
  fi

  bootstrap_id "build_objects_library_shared-mode"
  if [[ ${objects_library_shared} == "" ]] ; then
    objects_library_shared=${variables[${key}]}
  else
    objects_library_shared="${variables[${key}]} ${objects_library_shared}"
  fi

  bootstrap_id "build_objects_library_static-mode"
  if [[ ${objects_library_static} == "" ]] ; then
    objects_library_static=${variables[${key}]}
  else
    objects_library_static="${variables[${key}]} ${objects_library_static}"
  fi

  bootstrap_id "build_objects_program-mode"
  if [[ ${objects_program} == "" ]] ; then
    objects_program=${variables[${key}]}
  else
    objects_program="${variables[${key}]} ${objects_program}"
  fi

  bootstrap_id "build_objects_program_shared-mode"
  if [[ ${objects_program_shared} == "" ]] ; then
    objects_program_shared=${variables[${key}]}
  else
    objects_program_shared="${variables[${key}]} ${objects_program_shared}"
  fi

  bootstrap_id "build_objects_program_static-mode"
  if [[ ${objects_program_static} == "" ]] ; then
    objects_program_static=${variables[${key}]}
  else
    objects_program_static="${variables[${key}]} ${objects_program_static}"
  fi

  if [[ ${sources_object} == "" ]] ; then
    bootstrap_id "build_sources_object-mode"
    sources_object=${variables[${key}]}
  fi

  if [[ ${sources_object_shared} == "" ]] ; then
    bootstrap_id "build_sources_object_shared-mode"
    sources_object_shared=${variables[${key}]}
  fi

  if [[ ${sources_object_static} == "" ]] ; then
    bootstrap_id "build_sources_object_static-mode"
    sources_object_static=${variables[${key}]}
  fi
}

bootstrap_operation_build_prepare_paths() {
  local key=

  if [[ ${override_path_sources} == "" ]] ; then
    bootstrap_id "path_sources-mode"
    if [[ ${variables[${key}]} != "" ]] ; then
      path_sources=${variables[${key}]}
    else
      bootstrap_id "path_sources"
      if [[ ${variables[${key}]} != "" ]] ; then
        path_sources=${variables[${key}]}
      fi
    fi
  fi

  if [[ ${path_sources} != "" ]] ; then
    path_sources=$(echo ${path_sources} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_sources_object-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_sources_object=${variables[${key}]}
  else
    bootstrap_id "path_sources_object"
    if [[ ${variables[${key}]} != "" ]] ; then
      path_sources_object=${variables[${key}]}
    fi
  fi

  if [[ ${path_sources_object} != "" ]] ; then
    path_sources_object=$(echo ${path_sources_object} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_headers-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_headers=${variables[${key}]}
  fi

  if [[ ${path_headers} != "" ]] ; then
    path_headers=$(echo ${path_headers} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "has_path_standard-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    has_path_standard=${variables[${key}]}
  fi

  if [[ ${has_path_standard} == "no" ]] ; then
    path_language=
  else
    bootstrap_id "path_language-mode"
    if [[ ${variables[${key}]} != "" ]] ; then
      path_language=${variables[${key}]}
    else
      bootstrap_id "path_language"
      if [[ ${variables[${key}]} != "" ]] ; then
        path_language=${variables[${key}]}
      fi
    fi

    if [[ ${path_language} != "" ]] ; then
      path_language=$(echo ${path_language} | sed -e 's|//*|/|g' -e 's|/*$|/|')
    fi
  fi

  bootstrap_id "path_object_library-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_library=${variables[${key}]}
  fi

  if [[ ${path_object_library} != "" ]] ; then
    path_object_library=$(echo ${path_object_library} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_program-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_program=${variables[${key}]}
  fi

  if [[ ${path_object_program} != "" ]] ; then
    path_object_program=$(echo ${path_object_program} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_library_script-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_library_script=${variables[${key}]}
  fi

  if [[ ${path_library_script} != "" ]] ; then
    path_library_script=$(echo ${path_library_script} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_library_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_library_shared=${variables[${key}]}
  fi

  if [[ ${path_library_shared} != "" ]] ; then
    path_library_shared=$(echo ${path_library_shared} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_library_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_library_static=${variables[${key}]}
  fi

  if [[ ${path_library_static} != "" ]] ; then
    path_library_static=$(echo ${path_library_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_library_script-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_library_script=${variables[${key}]}
  fi

  if [[ ${path_object_library_script} != "" ]] ; then
    path_object_library_script=$(echo ${path_object_library_script} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_library_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_library_shared=${variables[${key}]}
  fi

  if [[ ${path_object_library_shared} != "" ]] ; then
    path_object_library_shared=$(echo ${path_object_library_shared} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_library_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_library_static=${variables[${key}]}
  fi

  if [[ ${path_object_library_static} != "" ]] ; then
    path_object_library_static=$(echo ${path_object_library_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_program_script-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_program_script=${variables[${key}]}
  fi

  if [[ ${path_object_program_script} != "" ]] ; then
    path_object_program_script=$(echo ${path_object_program_script} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_program_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_program_shared=${variables[${key}]}
  fi

  if [[ ${path_object_program_shared} != "" ]] ; then
    path_object_program_shared=$(echo ${path_object_program_shared} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_program_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_program_static=${variables[${key}]}
  fi

  if [[ ${path_object_program_static} != "" ]] ; then
    path_object_program_static=$(echo ${path_object_program_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_script-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_script=${variables[${key}]}
  fi

  if [[ ${path_object_script} != "" ]] ; then
    path_object_script=$(echo ${path_object_script} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_shared=${variables[${key}]}
  fi

  if [[ ${path_object_shared} != "" ]] ; then
    path_object_shared=$(echo ${path_object_shared} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_object_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_object_static=${variables[${key}]}
  fi

  if [[ ${path_object_static} != "" ]] ; then
    path_object_static=$(echo ${path_object_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${path_object_static} != "" ]] ; then
    path_object_static=$(echo ${path_object_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_program_script-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_program_script=${variables[${key}]}
  fi

  if [[ ${path_program_script} != "" ]] ; then
    path_program_script=$(echo ${path_program_script} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_program_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_program_shared=${variables[${key}]}
  fi

  if [[ ${path_program_shared} != "" ]] ; then
    path_program_shared=$(echo ${path_program_shared} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  bootstrap_id "path_program_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    path_program_static=${variables[${key}]}
  fi

  if [[ ${path_program_static} != "" ]] ; then
    path_program_static=$(echo ${path_program_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi

  if [[ ${path_program_static} != "" ]] ; then
    path_program_static=$(echo ${path_program_static} | sed -e 's|//*|/|g' -e 's|/*$|/|')
  fi
}

bootstrap_operation_build_prepare_programs() {
  local key=

  bootstrap_id "build_sources_program-mode"
  if [[ ${sources_program} == "" ]] ; then
    sources_program=${variables[${key}]}
  else
    sources_program="${sources_program} ${variables[${key}]}"
  fi

  bootstrap_id "build_sources_program_shared-mode"
  if [[ ${sources_program_shared} == "" ]] ; then
    sources_program_shared=${variables[${key}]}
  else
    sources_program_shared="${sources_program_shared} ${variables[${key}]}"
  fi

  bootstrap_id "build_sources_program_static-mode"
  if [[ ${sources_program_static} == "" ]] ; then
    sources_program_static=${variables[${key}]}
  else
    sources_program_static="${sources_program_static} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_remaining() {
  local key=

  bootstrap_id "has-build_compiler-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "build_compiler-mode"
    build_compiler=${variables[${key}]}
  fi

  bootstrap_id "has-build_indexer-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "build_indexer-mode"
    build_indexer=${variables[${key}]}
  fi

  bootstrap_id "has-build_indexer_arguments-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "build_indexer_arguments-mode"
    build_indexer_arguments=${variables[${key}]}
  fi

  bootstrap_id "has-build_name-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "build_name-mode"
    build_name=${variables[${key}]}
  fi

  bootstrap_id "has-version_major-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_major-mode"
    version_major=${variables[${key}]}
  fi

  bootstrap_id "has-version_major_prefix-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_major_prefix-mode"
    version_major_prefix=${variables[${key}]}
  fi

  bootstrap_id "has-version_minor-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_minor-mode"
    version_minor=${variables[${key}]}
  fi

  bootstrap_id "has-version_minor_prefix-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_minor_prefix-mode"
    version_minor_prefix=${variables[${key}]}
  fi

  bootstrap_id "has-version_micro-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_micro-mode"
    version_micro=${variables[${key}]}
  fi

  bootstrap_id "has-version_micro_prefix-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_micro_prefix-mode"
    version_micro_prefix=${variables[${key}]}
  fi

  bootstrap_id "has-version_nano-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_nano-mode"
    version_nano=${variables[${key}]}
  fi

  bootstrap_id "has-version_nano_prefix-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "version_nano_prefix-mode"
    version_nano_prefix=${variables[${key}]}
  fi

  bootstrap_id "has-path_headers-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_headers-mode"
    path_headers=${variables[${key}]}
  fi

  bootstrap_id "has-preserve_path_headers-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "preserve_path_headers-mode"
    preserve_path_headers=${variables[${key}]}
  fi

  bootstrap_id "has-path_library_script-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_library_script-mode"
    path_library_script=${variables[${key}]}
  fi

  bootstrap_id "has-path_library_shared-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_library_shared-mode"
    path_library_shared=${variables[${key}]}
  fi

  bootstrap_id "has-path_library_static-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_library_static-mode"
    path_library_static=${variables[${key}]}
  fi

  bootstrap_id "has-path_object_script-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_object_script-mode"
    path_object_script=${variables[${key}]}
  fi

  bootstrap_id "has-path_object_shared-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_object_shared-mode"
    path_object_shared=${variables[${key}]}
  fi

  bootstrap_id "has-path_object_static-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_object_static-mode"
    path_object_static=${variables[${key}]}
  fi

  bootstrap_id "has-path_program_script-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_program_script-mode"
    path_program_script=${variables[${key}]}
  fi

  bootstrap_id "has-path_program_shared-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_program_shared-mode"
    path_program_shared=${variables[${key}]}
  fi

  bootstrap_id "has-path_program_static-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "path_program_static-mode"
    path_program_static=${variables[${key}]}
  fi

  bootstrap_id "has-has_path_standard-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "has_path_standard-mode"
    has_path_standard=${variables[${key}]}
  fi

  bootstrap_id "has-search_exclusive-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "search_exclusive-mode"
    search_exclusive=${variables[${key}]}
  fi

  bootstrap_id "has-search_shared-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "search_shared-mode"
    search_shared=${variables[${key}]}
  fi

  bootstrap_id "has-search_static-mode"
  if [[ ${variables[${key}]} == "yes" ]] ; then
    bootstrap_id "search_static-mode"
    search_static=${variables[${key}]}
  fi
}

bootstrap_operation_build_prepare_settings() {
  local key=

  bootstrap_id "build_sources_setting-mode"
  if [[ ${sources_setting} == "" ]] ; then
    sources_setting=${variables[${key}]}
  else
    sources_setting="${sources_setting} ${variables[${key}]}"
  fi
}

bootstrap_operation_build_prepare_shared_static() {
  local key=

  bootstrap_id "build_shared-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    build_shared=${variables[${key}]}
  fi

  bootstrap_id "build_static-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    build_static=${variables[${key}]}
  fi

  if [[ ${enable_shared} == "yes" ]] ; then
    build_shared="yes"
    search_shared="yes"
  elif [[ ${enable_shared} == "no" ]] ; then
    build_shared="no"
    search_shared="no"
  fi

  if [[ ${enable_static} == "yes" ]] ; then
    build_static="yes"
    search_static="yes"
  elif [[ ${enable_static} == "no" ]] ; then
    build_static="no"
    search_static="no"
  fi

  if [[ ${search_shared} == "no" ]] ; then
    arguments_shared=
  fi

  if [[ ${search_static} == "no" ]] ; then
    arguments_static=
  fi
}

bootstrap_operation_build_validate_build() {

  if [[ ${build_compiler} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Cannot Build, no '${c_notice}build_compiler${c_error}' specified, such as '${c_notice}gcc${c_error}'.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${build_indexer} == "" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Cannot Build, no '${c_notice}build_indexer${c_error}' specified, such as '${c_notice}ar${c_error}'.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build_validate_paths() {

  if [[ ${path_sources} == "" || ! -d ${path_sources} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The sources directory ${c_notice}${path_sources}${c_error} is not a valid directory.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 0 && ${path_sources_object} != "" && ! -d ${path_sources_object} ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: The sources object directory ${c_notice}${path_sources_object}${c_error} is not a valid directory.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build_validate_search() {

  # When not in search exclusive mode, allow static libraries to be linked into shared libraries if the shared library is not found first.
  if [[ ${search_exclusive} == "no" ]] ; then
    arguments_shared="${arguments_shared} ${arguments_static}"
  fi
}

bootstrap_operation_build_validate_shared_static() {

  if [[ ${build_shared} != "yes" && ${build_static} != "yes" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Cannot Build, either build_shared or build_static must be set to 'yes'.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${search_shared} != "yes" && ${search_static} != "yes" ]] ; then
    if [[ ${verbosity} != "quiet" ]] ; then
      bootstrap_print_first

      echo -e "${c_error}ERROR: Cannot Build, either search_shared or search_static must be set to 'yes'.${c_reset}"
    fi

    let failure=1
  fi

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build_validate_sources() {

  for i in ${sources_script} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_script path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_headers} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_headers path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_library} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_library path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_library_object} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_library_object path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_program_object} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_program_object path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_program} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_program path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_documentation} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_documentation path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  for i in ${sources_setting} ; do
    if [[ ${i} != "$(echo ${i} | sed -e 's|^//*||' -e 's|^\.\.//*||' -e 's|/*$||')" ]] ; then
      if [[ ${verbosity} != "quiet" ]] ; then
        bootstrap_print_first

        echo -e "${c_error}ERROR: Cannot Build, invalid build_sources_setting path provided: '${i}'.${c_reset}"
      fi

      let failure=1
    fi
  done

  if [[ ${failure} -eq 1 ]] ; then
    return 1
  fi

  return 0
}

bootstrap_operation_build_prepare_versions() {
  local key=

  bootstrap_id "version_file-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    version_file_value=${variables[${key}]}
  fi

  bootstrap_id "version_target-mode"
  if [[ ${variables[${key}]} != "" ]] ; then
    version_target_value=${variables[${key}]}
  fi

  if [[ ${version_file_value} == "" ]] ; then
    version_file_value="micro"
  fi

  if [[ ${version_target_value} == "" ]] ; then
    version_target_value="major"
  fi

  if [[ ${version_major} == "" ]] ; then
    version_major_prefix=
  fi

  if [[ ${version_minor} == "" ]] ; then
    version_minor_prefix=
  fi

  if [[ ${version_micro} == "" ]] ; then
    version_micro_prefix=
  fi

  if [[ ${version_nano} == "" ]] ; then
    version_nano_prefix=
  fi

  if [[ ${version_file_value} == "major" ]] ; then
    version_file="${version_major_prefix}${version_major}"
  elif [[ ${version_file_value} == "minor" ]] ; then
    version_file="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}"
  elif [[ ${version_file_value} == "micro" ]] ; then
    version_file="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro}"
  elif [[ ${version_file_value} == "nano" ]] ; then
    version_file="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro}${version_nano_prefix}${version_nano}"
  fi

  if [[ ${version_target_value} == "major" ]] ; then
    version_target="${version_major_prefix}${version_major}"
  elif [[ ${version_target_value} == "minor" ]] ; then
    version_target="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}"
  elif [[ ${version_target_value} == "micro" ]] ; then
    version_target="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro}"
  elif [[ ${version_target_value} == "nano" ]] ; then
    version_target="${version_major_prefix}${version_major}${version_minor_prefix}${version_minor}${version_micro_prefix}${version_micro}${version_nano_prefix}${version_nano}"
  fi
}

bootstrap_operation_clean() {

  local i=

  for i in ${path_build}{documents,documentation,includes,libraries,objects,programs,settings,stage} ; do
    if [[ -e ${i} ]] ; then
      rm ${verbose_common} -Rf ${i}
    fi
  done

  if [[ -f ${project_built}.prepared ]] ; then
    rm ${verbose_common} -f ${project_built}-${settings_name}.prepared
  fi

  if [[ -f ${project_built_shared}-${settings_name}.built ]] ; then
    rm ${verbose_common} -f ${project_built_shared}-${settings_name}.built
  fi

  if [[ -f ${project_built_static}-${settings_name}.built ]] ; then
    rm ${verbose_common} -f ${project_built_static}-${settings_name}.built
  fi
}

bootstrap_print_first() {

  if [[ ${print_line_first} == "yes" ]] ; then
    echo

    print_line_first=
  fi
}

bootstrap_print_last() {

  if [[ ${print_line_last} == "yes" ]] ; then
    echo
  fi
}

bootstrap_cleanup() {

  unset bootstrap_copyright
  unset bootstrap_main
  unset bootstrap_handle_colors
  unset bootstrap_help
  unset bootstrap_id
  unset bootstrap_load_settings
  unset bootstrap_load_settings_mode
  unset bootstrap_prepare_build
  unset bootstrap_operation_build
  unset bootstrap_operation_build_prepare_defaults
  unset bootstrap_operation_build_prepare_defines
  unset bootstrap_operation_build_prepare_documentation
  unset bootstrap_operation_build_prepare_flags
  unset bootstrap_operation_build_prepare_headers
  unset bootstrap_operation_build_prepare_libraries
  unset bootstrap_operation_build_prepare_objects
  unset bootstrap_operation_build_prepare_paths
  unset bootstrap_operation_build_prepare_programs
  unset bootstrap_operation_build_prepare_remaining
  unset bootstrap_operation_build_prepare_settings
  unset bootstrap_operation_build_prepare_shared_static
  unset bootstrap_operation_build_prepare_versions
  unset bootstrap_operation_build_validate_build
  unset bootstrap_operation_build_validate_paths
  unset bootstrap_operation_build_validate_search
  unset bootstrap_operation_build_validate_shared_static
  unset bootstrap_operation_build_validate_sources
  unset bootstrap_operation_clean
  unset bootstrap_print_first
  unset bootstrap_print_last
  unset bootstrap_cleanup
}

bootstrap_main $*
