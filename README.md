# Testable project from scratch

Instructions to start a project from scratch

## Requirement

* C++ compiler
* CMake
* CMake Tool (VS code plugin)
* git

## Instructions

1. Create a new folder for the project
2. Create a README.md to log the status of the project. Check a cheatsheet to use markdown language. Some references: [r1](https://www.markdownguide.org/cheat-sheet/), [r2](https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)

3. Clone googletest repository

``` shell
git clone https://github.com/google/googletest.git
```

4. Init a repository. Check a git cheatsheet or install a GUI/VS Code plugin

``` shell
git init
git status
git add .
git status
git commit -m "Initial commit"
```

5. Create a basic setup: inc, src, test. The main program is provided by googletest: gtest_main. Check CMakeLists.txt (root and test folder)