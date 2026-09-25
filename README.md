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
│ ├── tokenization.c
│ ├── execution.c
│ ├── environment.c
│
├── include/
│ └── prompt.h
│ └── env_var.h
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

### [Member 1]

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |

### [Member 2]

| Date       | Work Completed / Notes |
|------------|------------------------|
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |
| YYYY-MM-DD | [Description of task]  |


### [Member 3]

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
