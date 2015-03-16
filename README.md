# Eugenics-System
A system designed to generate a visualize a circuit generation algorithm.
Consists of the engine server and visualization client.

[Christopher Findeisen](mailto:cfindeisen7@email.tamu.edu) & [Sam Gwydir](mailto:gwydir8@gmail.com) & [Jerego Orlino](mailto:jjo498@email.tamu.edu) & [Vincent Valenti](mailto:vincentv18@email.tamu.edu)

----------
# Development Notes
## Directories

- src := source code for project. this is the *need to know*
- sys := environment and a lot of details regarding some of the frameworks and
  configs that we're using. feel free to ask about it at any point for more
  info. a more detailed README can be found here

## Branches

The most salient point of our branching structure is to stay on the 'develop'
branch when working. This is the default, so unless there's a reason to, don't checkout a different branch.
If you want more info, see [this article](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)

#Production Notes
## Building
### Dependencies
- gflags 2.1.1
- cmake
- FLTK (not yet)

#### Linux
Use your package manager to install cmake.

If building on Linux, `share/scripts/install-gflags.sh` will install gflags into `$PROJECT_ROOT/local`.

```bash
cd $PROJECT_ROOT;
./share/scripts/install-gflags.sh
```

#### OS X
If you have [homebrew](https://github.com/Homebrew/homebrew) installed:
```bash
brew install cmake
brew install https://raw.githubusercontent.com/Gwydir8/Eugenics/develop/share/scripts/gflags.rb
```

If you don't have [homebrew](https://github.com/Homebrew/homebrew) installed:
```bash
echo "Come back when you do!"
```

### Manual Build
- note this builds the release build by default.
- run `cmake -DCMAKE_BUILD_TYPE=Debug ..` in build to build debug build
- run `cmake -DCMAKE_BUILD_TYPE=Release ..` in build to build release build explicitly

```bash
mkdir build
cd build
cmake ..
```

### Automated Build
- PROJECT_ROOT is where you cloned the repository.
```bash
cd $PROJECT_ROOT;
./build.sh
# release binary will be build/eugenics-system/{eugenics, lookingglass}
# debug binary will be debug/eugenics-system/{eugenics, lookingglass}
```

## Help
```bash
man $PROJECT_ROOT/share/man/eugenics.1
man $PROJECT_ROOT/share/man/lookingglass.1
```
