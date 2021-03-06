A ton of life advice from (mainly) the 
[Stampede Supercomputer](https://portal.tacc.utexas.edu/user-guides/stampede2).

# General
* To print a random number between `1` and `X` do:
  ```
  $ echo $[RANDOM%X+1]
  ```

* When you need to match all `.*` files except for the current directory `.` or
  the parent directory `..`, use the `.??*` file globbing pattern. 
  For example: 
  ```
  cp .??* dot.orig
  ```
  copies all the dot files in a directory named `dot.orig`.

* You can get the status of the last command with `$?`. It is 0 for success
  and non-zero for failure:
  ```
  echo "$?"
  ```

* Since bash sources `~/.bashrc` on every sub-shell you want to prevent things
  like path duplication by putting in guard if statements:
  ```
  if [ -z "$__INIT" ]; then
      export __INIT=1
      export PATH=$HOME/bin:$PATH
  fi
  ```

# File System
## Diagnostics
* Use the command `du -h *` to see disk usage for all directories in the current directory.

* The command `ls -F` adds an extra character to mark file type: 
  `/` for directories `*` executables and `@` for symbolic links.

##  Navigating aroud the File system
* If you set `shopt -s autocd` in the bash shell, then you'll be able to change
  directories by just typing the name of the directory.

* You are writing too fast and misspelled the path of your directory while working 
  in an interactive bash session? Try the following command `shopt -s cdspell` 
  and bash will try several minor spelling corrections to see if it can find 
  the actual directory.

* This up shell function can change directory quickly up the directory tree: `up 2` 
  is the same as `cd ../..`. Extra bonus points if you understand how the printf trick works.
  ```
  up() { cd $(eval "printf '../'%.0s {1..$1}") && pwd }
  ```

* When running a for loop in multiple directories, it may be helpful to use     
  parentheses to create a sub-shell:                                            
  ```                                                                           
  for d in d1 d2 d3 ; do ( cd $d; do_some_command_here; ); done                 
  ``` 

# Building
* If your build process is failing and you know that you need some extra library
  directories. Try setting `LIBRARY_PATH` to be colon separated list of directories.
  Both the intel and gcc compilers will use the list as library directories (`-L/foo/bar`).

## Building Scientific Stuff
* To see `MVAPICH2`'s process mapping, `export MV2_SHOW_CPU_BINDING=1` inside
  your script or before launching your job.

# Running
* Does rank 0 need more memory than your other `MPI` tasks?
  If you have 64 tasks, for example, allocate 5 nodes and launch with:
  ```
  ibrun -n 64 -o 15 # puts rank 0 on a node by itself.
  ```

# TACC
* You can find all installed bio codes by executing
  ```
  module keyword bio
  ```

## Software Building
* Add the following include statements in your Makefile to compile PETSc code:
  ```
  include ${PETSC_DIR}/conf/variables
  include ${PETSC_DIR}/conf/rules
  ```

* Linking to TACC packages? You don't have to remember their locations. 
  Just use `$TACC_THATPACKAGE_DIR`, `$TACC_THATPACKAGE_INC`, and `$TACC_THATPACKAGE_LIB`. 
  These variables will be defined after you load the module.

* Want to install your own python modules? Do `module help python`.

## Software Running
* If you have an MPI application with threads, don't forget to use 
  `tacc_affinity`. See the system user guide for more details.

## Diagnostics
* Did you know that job resource utilization reports are available via TACC's 
  [remora](https://github.com/TACC/remora) tool? Try it:
  ```
  module load remora
  module help remora
  ```

* Curious about the network topology in your job? Try TACC's 
  [remora](https://github.com/TACC/remora) tool:
  ```
  module load remora
  module help remora
  ```

# Cool Command-line Utilities
* [Reshaping JSON with jq](https://programminghistorian.org/en/lessons/json-and-jq)
