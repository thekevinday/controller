# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
# version 2024/07/10
#
# This file (assumed to be named readme.build.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.txt +Q -w -r FLL FLL
#
# To read the "Readme Documentation" section of this file, use this command sequence:
#   fss_basic_list_read readme.txt +Q -cn "Readme Documentation" | iki_read +Q -w -r FLL FLL
#

Readme Documentation:
  The Controller program utilizes the FLL:"Featureless Linux Library" and is designed to be used for bold:"Linux" systems.

  This project follows many of the FLL:"Featureless Linux Library" project practices and the documentation provided by that project should be consulted for further details in this regard.

  The purpose of this project is to provide a tool to help facilitate controlled execution of processes.
  This behavior is strongly correlated with how a basic system initializer works, alsa called an bold:"init" program.
  An bold:"init" program is therefore provided as another alternative to the different bold:"init" programs out there.

  This project follows bold:"Specification Driven Development" and details of the configuration files are defined in the directory:"specifications/" and in the directory:"documents/".

  To facilitate building of this project, these build systems are provided\:
  - The bold:"Featureless Make", which is a level 3 project provided by FLL:"Featureless Linux Library".

  See: file:"data/build/dependencies" for specific dependencies of this project.
  See: file:"documents/readme.build.txt" for bold:"Featureless Make" compiling and notes on installing.
