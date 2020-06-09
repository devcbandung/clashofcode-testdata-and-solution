# DevC Clash of Code 2020

This repository contains solutions and test cases generation files for DevC Clash of Code 2020 by DevC Bandung and Semarang. We use [tcframe](https://tcframe.toki.id/) as test case generator framework.

## Geting Started

This are only tested inside WSL2 Ubuntu 18.04, but should run as well in other unix-based environments. Here are the steps needed before running:

- Install necessary executables:
    ```bash
    sudo apt-get install g++ zip
    ```
- Export necessary env and aliases:
    ```bash
    source .env
    ```
    Note that if you use [zsh plugin for .env](https://github.com/johnhamelink/env-zsh), this step is automatically done.

### Adding Problems

Suppose you want to build test cases for problem `devc-problem`. Here are the steps you need to do.

- Create `devc-problem` folder.
    ```bash
    mkdir devc-problem
    ```
- Create the solution file named `solution.cpp`.
- Create `spec.cpp` file containing the problem and test case spec file. Read [tcframe guide](https://tcframe.toki.id/en/stable/getting-started/getting-started.html#writing-spec-file) or consult existing `spec.cpp` files on other problems for guides on creating spec file.
- Run the following command from inside the `devc-problem` folder:
    ```bash
    build
    ```
    (or alternatively, `build devc-problem` from anywhere inside the repository).
    
    This will compile your solution and spec files, and automatically generate test cases files to `tc/*`, and zip them into `devc-problem/tc-devc-problem.zip`, which conforms to Hackerrank test case format.

    You should get output similar to this:
    ```
    Building test cases for problem devc-problem...
    Compiling solution and spec...
    Generating test cases...

    [ SAMPLE TEST CASES ]

    [ OFFICIAL TEST CASES ]
      devc-problem_1: OK
      devc-problem_2: OK
      devc-problem_3: OK
      devc-problem_4: OK
      devc-problem_5: OK
      devc-problem_6: OK
      devc-problem_7: OK
      devc-problem_8: OK

    Generation finished. All test cases OK.
    Packing test cases...
      adding: input/input1.txt (stored 0%)
      adding: input/input2.txt (stored 0%)
      adding: input/input3.txt (stored 0%)
      adding: input/input4.txt (stored 0%)
      adding: input/input5.txt (stored 0%)
      adding: input/input6.txt (stored 0%)
      adding: input/input7.txt (stored 0%)
      adding: input/input8.txt (stored 0%)
      adding: output/output1.txt (stored 0%)
      adding: output/output2.txt (stored 0%)
      adding: output/output3.txt (stored 0%)
      adding: output/output4.txt (stored 0%)
      adding: output/output5.txt (stored 0%)
      adding: output/output6.txt (stored 0%)
      adding: output/output7.txt (stored 0%)
      adding: output/output8.txt (stored 0%)
    Packing done. File tc-devc-problem.zip ready to upload!
    ```

Few notes:
- Hackerrank is unable to distinguish file names between real and sample cases. Hence, do not create sample test cases using tcframe! Treat all test cases as normal test cases, and mark sample cases manually in Hackerrank challenge dashboard. Use few first test cases as sample, like [this](https://github.com/devcbandung/devc-clash-of-code-2020/blob/master/devc-member-growth/spec.cpp#L31-L33).

### Creating Alternate Solutions

Ideally, a problem needs at least two solutions to make sure that the main solution is correct.

- Create alternate solution, with `solution_` prefix and if possible, descriptive suffix, e.g. `solution_brute.cpp`.
- Compile the alternate solution:
    ```bash
    g++ -std=c++11 solution_brute.cpp -o solution_brute
    ```
- Make sure that you have `runner` executable already. You should have it if you already ran `build` command. If you want to do it manually, run this:
    ```bash
    tcframe build
    ```
- Run the grader
    ```bash
    ./runner grade --solution=./solution_brute
    ```
    You should get the following output:
    ```
    Local grading with solution command: './solution_brute'...

    [ SAMPLE TEST CASES ]

    [ OFFICIAL TEST CASES ]
      devc-problem_1: Accepted
      devc-problem_2: Accepted
      devc-problem_3: Accepted
      devc-problem_4: Accepted
      devc-problem_5: Accepted
      devc-problem_6: Accepted
      devc-problem_7: Accepted
      devc-problem_8: Accepted

    [ VERDICT ]
      Accepted [100]
    ```
