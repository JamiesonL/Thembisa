# Thembisa

This repository contains code and supporting files for the Thembisa HIV/TB model, developed by Prof Leigh Johnson, Prof Rob Dorrington, and Dr Mmamapudi Kubjane. Thembisa is a mathematical model of the South African HIV epidemic, designed to answer policy questions relating to HIV prevention and treatment. Thembisa is also a demographic projection model and a source of demographic statistics. Recently the model has also been extended to include tuberculosis.

This project uses HIV version 4.8 and TB version 2.1 and will be updated as code becomes available from the developers. More details can be found at the official [Thembisa website](https://www.thembisa.org/).

**Note**: If you are a direct collaborator on the project, please follow the instructions set out in the "Collaborators" section below.

## Note to collaborators & users: 
There are two active branches for this repository based on the model you're using:
- **main** contains the code for Thembisa HIV version 5.0
- **Thembisa-TB2.1** contains the code for Thembisa TB version 2.1

If you are working with the HIV model, continue using **main**, if you are using the TB model switch to the TB branch **Thembisa-TB2.1** using:
```{bash, eval=FALSE}
git checkout Thembisa-TB2.1
```

The HIV and TB branches will be merged after the next calibration of the TB model. Collaborators will be updated accordingly.

# Software Requirements

Thembisa is written in C++ and primarily designed for Windows using Microsoft Visual Studio, but it can also be compiled and run on Unix-like systems (Linux/MacOS) with compatibility modifications.

### Windows
- Windows 10 or later
- **Visual Studio**: [Download](https://visualstudio.microsoft.com/downloads/) and select **"Desktop development with C++"** workload.

### Unix-like Systems (Linux/MacOS, WSL, etc.)
- **Visual Studio Code**: [Download](https://code.visualstudio.com/download) and install the **Microsoft C/C++** extension once downloaded.
- GCC or Clang with C++14 support
- Terminal with standard Unix utilities

# Project Directory Structure

```
├── ./ 
│   .gitignore
│   .gitattributes
│   AssemblyInfo.cpp  
│   README.md  
│   StatFunctions.cpp  
│   StatFunctions.h  
│   THEMBISA.cpp  
│   THEMBISA.h  
│   THEMBISA.sln  
│   app.ico  
│   app.rc  
│   mersenne.cpp  
│   randomc.h  
│   stdafx.cpp  
│   stdafx.h
│   THEMBISA.sln
│   THEMBISA.vcxproj
│   THEMBISA.vcxproj.filters
│   ├── calibration-outputs/
│   │   ├── HIV/
│   │   ├── TB/
│   ├── outputs/
│   │   ├── HIV/
│   │   ├── TB/
│   ├── inputs/
│   │   ├── TBinputs/
```

# Running the Model

**1. Setup**

- All text files use Unix-style LF line endings. To avoid automatic conversion by Git, please do **not** modify the `.gitattributes` file.

- Clone the Git repository through either Visual Studio (Windows only) or Visual Studio Code using the built-in Git functionality:
    - **Visual Studio:** [Follow these instructions](https://learn.microsoft.com/en-us/visualstudio/version-control/git-clone-repository?view=visualstudio)
    - **Visual Studio Code:** [Follow these instructions](https://code.visualstudio.com/docs/sourcecontrol/quickstart)
    - **OR** clone the repository through your terminal in a suitable place:
        ```{bash, eval=FALSE}
        git clone https://github.com/leighjohnson/Thembisa.git
        cd Thembisa
        ```

**2. Compatibility**

If you are not using Windows in Visual Studio, please ensure you follow the modifications to the specific files in the table below:

| File                | Lines  | Windows                                                                 | Linux/macOS                                                               |
|---------------------|--------|-------------------------------------------------------------------------|----------------------------------------------------------------------------|
| `Thembisa.cpp`      | 4–6    | `#include "stdafx.h"`<br>`#using <mscorlib.dll>`<br>`using namespace System;` | `using namespace std;`<br>`#include <iostream>`<br>`#include <cstring>`<br>`#include <sstream>`<br>`#include <string>` |
| `Thembisa.cpp`      | 26     | `int _tmain`                                                            | `int main`                                                                |
| `Thembisa.h`        | 7      | `#using <mscorlib.dll>`                                                 | Delete or comment out                                                     |
| `StatFunctions.cpp` | 13–15  | `#include "stdafx.h"`<br>`#using <mscorlib.dll>`                        | Delete or comment out                                                     |
| `StatFunctions.h`   | 8      | `#using <mscorlib.dll>`                                                 | Delete or comment out                                                     |



**3. Compilation**

- **Windows**: Visual Studio
    - Click on Build → Build solution
    - Click on Debug → Start Without Debugging
    
- **Linux/MacOS**: Visual Studio Code
    - Make the compatibility changes in the table above
    - Compile using g++:
        ```cpp
        g++ -std=c++14 THEMBISA.cpp StatFunctions.cpp mersenne.cpp -I. -o THEMBISA
        ```
    - Run THEMBISA.exe:
      ```cpp
        ./THEMBISA
        ```

# National HIV Model

## Simulation

For the national HIV simulation of the model, ensure that in **`THEMBISA.cpp`** , the following lines are commented and uncommented respectively: 

```cpp
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```cpp
int FixedUncertainty = 1;
const int VaryFutureInterventions = 0; 
const int VaryFutureInterventionsTB = 0; 
const int FixedARTinitiation = 0;
const int InputARTinitiationRates = 0; 
```

and: 

```cpp
const int ProvModel = 0; 
string ProvID = "KZ"; // variable selection ignored if ProvModel=0
const int UseBrassLogit = 0;
const int IncludeTB = 0; 
const int IncludeDR_TB = 0; 
```

Ensure that the following calibration settings are enabled (`= 1`):

- `CalibAdultPrev`
- `CalibANCprev`
- `CalibFSWprev`
- `CalibMSMprev`
- `CalibHCT_HH`
- `CalibHCTprev`
- `CalibHCTprevP`
- `CalibDeathsA`
- `CalibDeathsP`
- `CalibARTbyAge`
- `CalibARTcoverage`

All remaining calibration settings should be disabled (`= 0`). Lastly, ensure that the following values are set in `THEMBISA.h`:

```cpp
const int MCMCdim = 51;   ///< Number of parameters in uncertainty analysis
const int MaxPriors = 149; ///< Number of input rows in Priors file (149 for HIV, 63 for TB)
```

# Provincial HIV Model

## Simulation

For the provincial-level HIV simulation, ensure that in the C++ program, **`THEMBISA.cpp`** , the following lines are uncommented and commented respectively: 

```cpp
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```cpp
int FixedUncertainty = 1;
...
const int InputARTinitiationRates = 1; 
```

and: 

```cpp
const int ProvModel = 1; 
string ProvID = "KZ"; // Choose from EC, FS, GT, KZ, LM, MP, NC, NW, WC
const int UseBrassLogit = 0;
const int IncludeTB = 0; 
const int IncludeDR_TB = 0; 
```

Ensure that the following calibration settings are enabled (`= 1`):

- `CalibPaedPrev`
- `CalibAdultPrev`
- `CalibANCprev` (and also `InclANCpre1997` and `InclAS_ANCprov`)
- `CalibDeathsA`
- `CalibARTtotals`
- `CalibARTbyAge`
- `CalibARTbyAgeP2`
- `CalibARTcoverage`

All remaining calibration settings should be disabled (`= 0`). Lastly, ensure that the following values are set in `THEMBISA.h`:

```cpp
const int MCMCdim = 44; ///< Number of parameters in uncertainty analysis
const int MaxPriors = 149; ///< Number of input rows in Priors file (145 for HIV, 63 for TB)
```

# National TB Model

## Simulation

For the simulation of the national-level TB model, ensure that in the C++ program, **`THEMBISA.cpp`** , the following lines are commented and uncommented respectively: 

```cpp
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```cpp

int FixedUncertainty = 1;
const int VaryFutureInterventions = 0; 
const int VaryFutureInterventionsTB = 0; 
const int FixedARTinitiation = 0;
const int InputARTinitiationRates = 0; 

const int PropnalImmART = 1; 
const int ExcludeInterrupters = 1; /
const int UseNumbersTests = 1; 
const int ProvModel = 0; 
string ProvID = "NW"; //will be ignored
const int UseBrassLogit = 0; 
int PrEPorVM = 0; 

const int IncludeTB = 1; 
const int IncludeDR_TB = 0; 
const int FixedTBscreening = 0;
double RRtestingDiagnosed = 1.0; 

```
Please also ensure: 

```cpp
const int MCMCdim = 21; ///< Number of parameters in uncertainty analysis
const int MaxPriors = 65; ///< Number of input rows in Priors file (145 for HIV, 63 for TB)
```

# Variables that should not be changed 

There are some variables specified in the **Thembisa.h** file that should not be changed:

- `StartYear = 1985`
- `VaryFutureInterventions = 0`
- `FixedARTinitiation = 0`
- `ExcludeInterrupters = 1`
- `UseNumbersTests = 1`
- `PrEPorVM = 0`

# Collaborators

This section provides detailed guidance for team members contributing to Thembisa. It is written for people who may be new to GitHub or Git. Following these guidelines ensures consistency, reproducibility, and prevents accidental overwrites of critical files.

Here is a [link to a blog](https://madebymade.medium.com/github-for-dummies-96f753f96a59) that outlines the basics of Git and GitHub.

### Branching basics

Branches allow multiple people to work on the same project **without overwriting each other's work**. The structure we use is the following:

- Main branch: `main` (for stable, tested code)
- Your work: `Feature-branch` (an example name for a copy of the main branch you want to make changes to)

### Creating a branch

```{bash, eval=FALSE}
git checkout -b <your-branch-name>
```
For example, if you're adding compatibility for linux: `git checkout -b linux-compatibility-fix`

### Making changes

1. Edit or add files in your feature branch and ensure the model outputs are the same as on the website outputs.
2. Check what has changed:
   ```{bash, eval=FALSE}
   git status
   ```
3. Stage changes for commit:
   ```{bash, eval=FALSE}
   git add <filename>
   ```
   or **all changes**:
   ```{bash, eval=FALSE}
   git add .
   ```
4. Commit changes with a descriptive message:
   ```{bash, eval=FALSE}
   git commit -m "<descriptive message>"
   ```
   **Example**: "Fix Linux compilation errors in Thembisa.cpp".
   
   **Tip**: Commit small, related changes separately. Avoid committing large outputs or compiled binaries.

6. Push your branch to GitHub
    ```{bash, eval=FALSE}
   git push origin <your-branch-name>
   ```

### Opening a Pull Request (PR)

A PR is a request to merge your branch into main. It allows team members to review your code before it becomes part of the main project.

1. Go to the [GitHub repository](https://github.com/leighjohnson/Thembisa) in your browser.
2. Click **"Compare & pull request"** on your branch.
3. Provide a clear description of your changes.
4. Assign Leigh Johnson as the reviewer, and one additional reviewer if requested.
5. Submit the PR.

The reviewer (Leigh Johnson) checks the code, adds comments, and requests changes if necessary. Address comments by committing updates to your branch and pushing again. Once approved, merge the PR using Squash and Merge (recommended) or Merge Commit. Delete the branch after merging.

### Keeping Your Branch Updated

If others merge changes while you are working, sync your branch:
```{bash, eval=FALSE}
git checkout main
git pull origin main
git checkout <your-branch-name>
```

Resolve any conflicts locally, test the code, then push.

### Handling output files
- **Never** commit files in outputs/ or calibration-outputs/.
- `.gitignore` is configured to prevent this, but double-check before committing.
- If you need to share outputs, compress them and place them in a temporary folder outside the repo or use a shared cloud storage. If outputs are mistakenly pushed in your PR, please let one of the developers know.

### Recommended workflow and additional tips

**Workflow:**
- Clone the repository.
- Create a branch for your work.
- Make small, focused commits.
- Push your branch and open a PR.
- Review, update, and merge.
- Delete old branches to keep the repo clean.

**Tips:**
- **Descriptive commit messages** help reviewers understand your changes.
- Comment your code, especially in complex calculations or compatibility modifications.
- **Test on your platform** (Windows/Linux/MacOS) before requesting a review.
- If unsure about Git commands, visit [**GitHub Docs**](https://docs.github.com/en) or email Lauren Brown (laurenbrown@sun.ac.za) or Georgia Roussos (georgiaroussos@sun.ac.za)
