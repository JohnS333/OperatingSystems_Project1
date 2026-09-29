# OperatingSystems_Project1


# Operating Systems Project 1: Division of Labor (After)
Group Number: 9


Team Members:
1. Taylor Vaughn
2. Riley Galpin
3. John Simson

Documentation:
Project Structure: John, 	
Github Maintainer: John ~ Riley and Taylor have Admin

Part 0: Tokenization - [Just use the provided code]


# Part 1: Prompt  [Parsing Phase]
- Riley
- [Done: True ] [Tested: True ]


# Part 2: Environment Variables [Parsing Phase]
- Riley, Taylor
- [Done: True ] [Tested: True ]

# Part 3: Tilde Expansion [Parsing Phase]
- Riley, Taylor
- [Done: True ] [Tested: True ]


# Part 4: $PATH Search  [Parsing Phase]
- John , Riley
- [Done: True ] [Tested: True ]


# Part 5: External Command Execution
- Taylor, Riley
- [Done: True ] [Tested: True ]

# Part 6: I/O Redirection
- Taylor, John 
[Done: True ] [Tested: True]

# Part 7: Piping
- John,  Riley - Testing
- [Done:  True] [Tested: True]


# Part 8: Background Processing
- John, Taylor
- [Done: True ] [Tested: True]


# Part 9: Internal Command Execution
- Taylor, John 
- [Done:  True ] [Tested: True]    

## Github Dev
Dont commit directly into Main,
commit into dev, or better yet, make a branch branching off of dev for your feature or part.
When you are done, make a pull request that merges it back into dev.

For the mnost part, Main branch should only get updated via a pull request from dev.
         
     
                 dev
                  |
                  ├--|
                  |  | feature branch
                  ├--|
         main     |
         ├--------|
         |
         |
         |
         |


[Description]

## File Listing
```
root/
├── include/
│ └── cd.h
│ └── jobs.h
│ └── prompt.h
│ └── path_search.h
│ └── pipe.h
│ └── execution.h
│ └── env_var.h
│ └── output_redirection.h
|
├── src/
│ ├── cd.c
│ ├── jobs.c
│ ├── prompt.c
│ ├── main.c
│ ├── output-redirection.c
│ ├── pipe.c
│ ├── path_search.c
│ ├── execution.c
│ ├── environment.c
│
│
├── README.md
└── Makefile
```
## How to Compile & Execute

### Requirements
- **Compiler**: e.g., `gcc` for C/C++, `rustc` for Rust.
- **Dependencies**: List any libraries or frameworks necessary (rust only).

### Compilation
For a C/C++ example:
```bash
make clean
make
```
This will build the executable in ...


### Execution
```bash
./bin/shell
```
This will run the program ...

## Development Log
Each member records their contributions here.

### John Simson

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-25 | path search implementation, make .h files, and  fix environment.c functions |
| 2026-09-27| IO redirection implementation, piping + enabling background process compatibility  |
| 2026-09-28 | Bug fixes for memory leaks, Finished jobs system. Tested code . Used AI to make a script that piped into our shell 
to test various inputs and expected outputs. That testing harness is not part of our submission. The code segments for printing statements
that include things like %d were made with AI. |

### [Riley Galpin]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-14 | Completed part 1 and testing|
| 2026-09-15 | Completed part 2 and testing|
| 2026-09-16 | Completed part 3 and testing|
| 2026-09-28 |  Completed comprehensive testing for parts 1-8, found output alignment bugs and null errors|



### Taylor Vaughn

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-22 | [Completed part 5 and testing]  |
| 2026-09-22 | [Completed part 6 and testing]  |
| 2026-09-28 | [Completed part 9 and testing for all parts]  |


## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees            | Topics Discussed | Outcomes / Decisions |
|------------|----------------------|------------------|-----------------------|
| 2026-09-13 | Riley Galpin, Taylor Vaugn,  John Simson| Division of Labor   | Discussed and decided how to divide work and began on parts 1-3 and documentation |
| 2026-09-27| Riley Galpin, Taylor Vaugn,  John Simson | Final Product, Testing, Parts 8&9  | Finished up parts 8 & 9 and began testing as a group. Discussed next steps for testing and began completing final documentation|

