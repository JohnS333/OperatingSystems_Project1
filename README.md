# OperatingSystems_Project1

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
shell/
│
├── src/
│ ├── main.c
│ ├── background.c
│ ├── output-redirection.c
│ ├── pipe.c
│ ├── signals.c
│ ├── path_search.c
│ ├── tokenization.c
│ ├── execution.c
│ ├── environment.c
│
├── include/
│ └── prompt.h
│ └── path_search.h
│ └── execution.h
│ └── env_var.h
│ └── output_redirection.h
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
make
```
This will build the executable in ...


### Execution
```bash
make run
```
This will run the program ...

## Development Log
Each member records their contributions here.

### John Simson

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-25 | path search implementation, make .h files, and  fix environment.c functions |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |

### Riley Galpin

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |


### Taylor Vaughn

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |


## Meetings
Document in-person meetings, their purpose, and what was discussed.

| Date       | Attendees            | Topics Discussed | Outcomes / Decisions |
|------------|----------------------|------------------|-----------------------|
| YYYY-MM-DD | [Names]              | [Agenda items]   | [Actions/Next steps]  |
| YYYY-MM-DD | [Names]              | [Agenda items]   | [Actions/Next steps]  |



## Bugs
- **Bug 1**: This is bug 1.
- **Bug 2**: This is bug 2.
- **Bug 3**: This is bug 3.

## Extra Credit
- **Extra Credit 1**: [Extra Credit Option]
- **Extra Credit 2**: [Extra Credit Option]
- **Extra Credit 3**: [Extra Credit Option]

## Considerations
[Description]


# Operating Systems Project 1: Division of Labor
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
- Riley, John 
- [Done: True ] [Tested: ? ]


# Part 2: Environment Variables [Parsing Phase]
- Riley, Taylor
- [Done: True ] [Tested: ? ]

# Part 3: Tilde Expansion [Parsing Phase]
- Riley, Taylor
- [Done: True ] [Tested: ? ]


# Part 4: $PATH Search  [Parsing Phase]
- John , Riley
- [Done: True ] [Tested: ? ]


# Part 5: External Command Execution
- Taylor, Riley
- [Done: Yes ] [Tested: Yes ]

# Part 6: I/O Redirection
- Taylor, John 
[Done: Yes ] [Tested: ]

# Part 7: Piping
- John,  Riley
- [Done:  Yes] [Tested: ]


# Part 8: Background Processing
- John, Taylor
- [Done: Yes ] [Tested: ]


# Part 9: Internal Command Execution
- Taylor, John 
- [Done:  Yes ] [Tested: ]    
