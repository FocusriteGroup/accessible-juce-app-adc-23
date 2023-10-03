# Building an accessible app in JUCE

Welcome! This repository contains the materials for the "Building an accessible app in JUCE" ADC23 talk. 

## Table of contents

- [Repository contents](#repository-contents)
- [About the commit history](#about-the-commit-history)
- [Building the demo app](#building-the-demo-app)
  - [Prerequisites](#prerequisites)
  - [Setting up the build environment](#setting-up-the-build-environment)

## Repository contents

- Source code for the demo app
- Accompanying presentation slides written in markdown, which can be found in the `docs/` directory.
  - Pre-rendered versions of the presentation can be found next to the markdown source, in PDF and HTML formats.
  - N.B. Screen reader users, I'd recommend the HTML version in a web browser, using `spacebar` and `shift+space` to navigate the presentation. Unfortunately Marp's PDF rendering doesn't seem as accessible.

## About the commit history

The commits of this repository are marked stages of the app's development, as referred to in the slides. The initial commit presents the app in a not-very-accessible state, and the commits which follow contain tweaks which improve the screen reader accessibility.

To jump between the git history on the command line, run:

`git checkout ':/Commit message'`

With the message of the commit you want to go to, as indicated in the slides.

Alternatively, use a graphical git client such as [Fork](https://git-fork.com/) to move between commits.

After checking out a commit, you can build and run the app and experience that particular stage of development using a screen reader.

## Building the demo app

### Prerequisites

- git
- CMake
- C++ IDE (e.g. Xcode, Visual Studio, VS Code, CLion)

### Setting up the build environment

1. Clone the repo

   `git clone git@github.com:FocusriteGroup/accessible-juce-app-adc-23.git`

2. Change to the repo directory

   `cd accessible-juce-app-adc-23`

3. Generate project files in a `build/` directory

   `cmake -B build -G <generator_name>`

   Recommended generators:

   - Ninja for cross-platform
   - Visual Studio for Windows
   - Xcode for MacOS

   For a full list of available generators, run:

   `cmake --help`

4. Open the project in your IDE

   Open the generated project file within `build/` for VS or Xcode, or the entire directory in CLion / VS Code.

   Note: If you wish to use VS Code, you may need to install the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) and the C++ build tools for your OS (e.g. Xcode command line tools, or Visual C++ build tools, which come with the respective IDEs).
