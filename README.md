# Thembisa

This repository contains code and supporting files for the Thembisa HIV/TB model, developed by Prof Leigh Johnson, Prof Rob Dorrington, and Dr Mmamapudi Kubjane. Thembisa is a mathematical model of the South African HIV epidemic, designed to answer policy questions relating to HIV prevention and treatment. Thembisa is also a demographic projection model and a source of demographic statistics. Recently the model has also been extended to include tuberculosis.

This project uses HIV version 4.8 and TB version 2.1 and will be updated as code becomes available from the developers. More details can be found at the official [Thembisa website](https://www.thembisa.org/)

**Note**: If you are a direct collaborator on the project, please follow the instructions set out in the "Collaborators" section below.

# Software Requirements

Thembisa is written in C++ and primarily designed for Windows using Microsoft Visual Studio, but it can also be compiled and run on Unix-like systems (Linux/MacOS) with compatibility modifications.

### Git installation
- Windows: [Download](https://git-scm.com/install/windows)
- MacOS: [Download](https://git-scm.com/install/mac)
- Linux: [Download](https://git-scm.com/install/linux)

- Configure Git in your terminal (first time only)
```{bash, eval=FALSE}
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

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
│   .DS_Store  
│   .gitignore  
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
│   ├── calibration-outputs/
│   ├── outputs/
│   │   ├── Backup/
│   │   ├── Debug/
│   │   ├── Release/
│   │   ├── Template/
│   │   ├── ipch/
│   ├── inputs/
│   │   ├── TBinputs/
```

# Running the Model

**1. Setup**

- All text files use Unix-style LF line endings. To avoid automatic conversion by Git, run the following in your terminal:
    ```{bash, eval=FALSE}
    git config --global core.autocrlf false
    ```
    Do **not** modify the `.gitattributes` file.

- Clone the full directory structure, including inputs, outputs, and calibration-outputs in a suitable place:
    ```{bash, eval=FALSE}
    git clone https://github.com/leighjohnson/Thembisa.git
    cd Thembisa
    ```

**2. Compatibility**

If you are not using Windows and Visual Studio, please ensure you follow the modifications to the specific files in the table below:

| File               | Lines    | Windows                                                                       | Linux/MacOS                                                                  |
|--------------------|----------|-------------------------------------------------------------------------------|------------------------------------------------------------------------------|
| `Thembisa.cpp`     | 4–6      | `#include "stdafx.h"`<br>`#using <mscorlib.dll>`<br>`using namespace System;` | `using namespace std;`<br>`#include <iostream>`<br>`#include <cstring>`<br>`#include <sstream>`<br>`#include <string>` |
| `Thembisa.h`       | 7        | `#using <mscorlib.dll>`                                                       | _Delete_ or comment out                                                      |
| `StatFunctions.cpp`| 13–15    | `#include "stdafx.h"`<br>`#using <mscorlib.dll>`                              | _Delete_ or comment out                                                      |
| `StatFunctions.h`  | 8        | `#using <mscorlib.dll>`                                                       | _Delete_ or comment out                                                      |
| `mersenne.cpp`     | 8        | `#include "stdafx.h`                                                          | _Delete_ or comment out                                                      |

**3. Compilation**

- Windows: Open `THEMBISA.sln` in Visual Studio and build the solution.
    
- Linux/MacOS: Compile using g++
    ```{bash, eval=FALSE}
    g++ -std=c++14 THEMBISA.cpp StatFunctions.cpp mersenne.cpp -I. -o THEMBISA
    ```

# National HIV Model

## Simulation

For the national HIV simulation of the model, ensure that in **`THEMBISA.cpp`** , the following lines are commented and uncommented respectively: 

```{bash, eval=FALSE}
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```{bash, eval=FALSE}
int FixedUncertainty = 1;
const int VaryFutureInterventions = 0; 
const int VaryFutureInterventionsTB = 0; 
const int FixedARTinitiation = 0;
const int InputARTinitiationRates = 0; 
```

and: 

```{bash, eval=FALSE}
const int ProvModel = 0; 
string ProvID = "KZ"; // variable selection ignored if ProvModel=0
const int UseBrassLogit = 0;
const int IncludeTB = 0; 
const int IncludeDR_TB = 0; 
```

Please also ensure: 

```{bash, eval=FALSE}
const int MCMCdim = 49; ///< Number of parameters in uncertainty analysis
const int MaxPriors = 145; ///< Number of input rows in Priors file (145 for HIV, 63 for TB)
```

# Provincial HIV Model

## Simulation

For the provincial-level HIV simulation, ensure that in the C++ program, **`THEMBISA.cpp`** , the following lines are uncommented and commented respectively: 

```{bash, eval=FALSE}
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```{bash, eval=FALSE}
int FixedUncertainty = 1;
```

and: 

```{bash, eval=FALSE}
const int ProvModel = 1; 
string ProvID = "KZ"; // Choose from EC, FS, GT, KZ, LM, MP, NC, NW, WC
const int UseBrassLogit = 0;
const int IncludeTB = 0; 
const int IncludeDR_TB = 0; 
```

Please also ensure: 

```{bash, eval=FALSE}
const int MCMCdim = 40; ///< Number of parameters in uncertainty analysis
const int MaxPriors = 145; ///< Number of input rows in Priors file (145 for HIV, 63 for TB)
```

# National TB Model

## Simulation

For the simulation of the national-level TB model, ensure that in the C++ program, **`THEMBISA.cpp`** , the following lines are commented and uncommented respectively: 

```{bash, eval=FALSE}
RunSample();	
//runIMIS(0.0);
```

In the header file, **`THEMBISA.h`**, ensure

```{bash, eval=FALSE}

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

```{bash, eval=FALSE}
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

### 1. Branching basics

Branches allow multiple people to work on the same project **without overwriting each other's work**.

- Main branch: `main` (stable, tested code)
- "Feature branch": for your work

### 2. Creating a branch

```{bash, eval=FALSE}
git checkout -b <your-branch-name>
```
For example, if you're adding compatibility for linux: `git checkout -b linux-compatibility-fix`

### 3. Making changes

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

### 4. Opening a Pull Request (PR)

A PR is a request to merge your branch into main. It allows team members to review your code before it becomes part of the main project.

1. Go to the [GitHub repository](https://github.com/leighjohnson/Thembisa) in your browser.
2. Click **"Compare & pull request"** on your branch.
3. Provide a clear description of your changes.
4. Assign Leigh Johnson as the reviewer, and one additional reviewer if requested.
5. Submit the PR.

The reviewer checks the code, adds comments, and requests changes if necessary. Address comments by committing updates to your branch and pushing again. Once approved, merge the PR using Squash and Merge (recommended) or Merge Commit. Delete the branch after merging.

### 5. Keeping Your Branch Updated

If others merge changes while you are working, sync your branch:
```{bash, eval=FALSE}
git checkout main
git pull origin main
git checkout <your-branch-name>
git merge main
```

Resolve any conflicts locally, test the code, then push.

### 6. Handling output files
- **Never** commit files in outputs/ or calibration-outputs/.
- `.gitignore` is configured to prevent this, but double-check before committing.
- If you need to share outputs, compress them and place them in a temporary folder outside the repo or use a shared cloud storage. If outputs are mistakenly pushed in your PR, please let one of the developers know.

### 7. Recommended workflow and additional tips

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
- If unsure about Git commands, visit [**GitHub Docs**](https://docs.github.com/en)
