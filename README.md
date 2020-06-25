# DevC Clash of Code 2020

This repository contains solutions and test cases generation files for [DevC Clash of Code 2020](https://devcbandung.github.io/clashofcode) by [DevC Bandung](https://www.facebook.com/groups/DevCBandung) and [DevC Semarang](https://www.facebook.com/groups/DevCSemarang) on June 13 - June 25 2020.

## Generating Test Cases

We use [tcframe](https://tcframe.toki.id/) as test case generator framework.

### Initializing

Before you can start generating test cases, you should run these commands. These are only tested on [Ubuntu 18.04 on WSL2](https://wiki.ubuntu.com/WSL), but it should run as well on other UNIX-based environments.

- Install necessary executables (`g++` and `zip`):
    ```bash
    sudo apt-get install g++ zip
    # on other OS, you may use different package managers
    ```
- Export necessary env and aliases:
    ```bash
    source .env
    ```
    Note that if you use [zsh plugin for .env](https://github.com/johnhamelink/env-zsh), this step is automatically done.

### Generating Test Cases

Suppose you want to generate test cases for problems `devc-member-growth`. You just need to run this:

```bash
build devc-member-growth
```

If everything went correctly, you should get output similar to this:

```
Building test cases for problem devc-member-growth...
Compiling solution and spec...
Generating test cases...

[ SAMPLE TEST CASES ]

[ OFFICIAL TEST CASES ]
  devc-member-growth_1: OK
  devc-member-growth_2: OK
  devc-member-growth_3: OK
  devc-member-growth_4: OK
  devc-member-growth_5: OK
  devc-member-growth_6: OK
  devc-member-growth_7: OK
  devc-member-growth_8: OK

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
Packing done. File tc-devc-member-growth.zip ready to upload!
```

Now you will see new folder `devc-member-growth/tc` containing all test cases (file `.in` for input and `.out` for the expected output), and a zip file `devc-member-growth/tc-devc-member-growth.zip` as well. The structure of the zip file is different from the `/tc` folder, because we need to conform with the Hackerrank input/output format.

## Testing Your Own Solution Locally

Tcframe has a nice feature to test your own solution locally.

- Follow steps on the previous section to generate test cases.
- Create your own solution inside the problem folder. Let's say it's named `solution_mine.cpp`. Don't forget to compile it:
    ```bash
    g++ solution_mine.cpp -o solution_mine.cpp
    ```
- Then run this to test your solution:
    ```bash
    ./runner grade --solution=./solution_mine
    ```

    You would get output similar to this:
    ```
    Local grading with solution command: './solution_mine'...

    [ SAMPLE TEST CASES ]

    [ OFFICIAL TEST CASES ]
      devc-member-growth_1: Accepted
      devc-member-growth_2: Accepted
      devc-member-growth_3: Accepted
      devc-member-growth_4: Accepted
      devc-member-growth_5: Accepted
      devc-member-growth_6: Accepted
      devc-member-growth_7: Accepted
      devc-member-growth_8: Accepted

    [ VERDICT ]
      Accepted [100]
    ```

## Adding New Problems

Suppose you want to build test cases for problem `devc-problem`. Here are the steps you need to do.

- Create `devc-problem` folder.
    ```bash
    mkdir devc-problem
    ```
- Create the solution file named `solution.cpp`.
- Create `spec.cpp` file containing the problem and test case spec file. Read [tcframe guide](https://tcframe.toki.id/en/stable/getting-started/getting-started.html#writing-spec-file) or consult existing `spec.cpp` files on other problems for guides on creating spec file.
- Then, generate test case just like explained on the previous section.
    ```bash
    build devc-problem
    ```
    (or alternatively, just `build` from inside the problem folder).

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

## License

The codes inside this repository is licensed under [MIT](https://github.com/devcbandung/clashofcode-testdata/blob/master/LICENSE.txt).

We include a copy of [tcframe](https://tcframe.toki.id/) inside this repository, which is licensed under [MIT](https://github.com/devcbandung/clashofcode-testdata/blob/master/tcframe/LICENSE.txt) as well.
