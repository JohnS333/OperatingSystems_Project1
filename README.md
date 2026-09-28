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
│ └── shell.c
│
├── include/
│ └── shell.h
│
├── README.md
└── Makefile
```
## How to Compile & Execute

### Requirements
- **Compiler**: e.g., `gcc` for C/C++.


### Compilation

```bash
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

### [Riley Galpin]

| Date       | Work Completed / Notes |
|------------|------------------------|
| 2026-09-14 | Completed part 1 and testing|
| 2026-09-15 | Completed part 2 and testing|
| 2026-09-16 | Completed part 3 and testing|
| 2026-09-28 |  Completed comprehensive testing for parts 1-8, found output alignment bugs and null errors|


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
Document in-person meetings, their purpose, and what was discussed. -> N/A

| Date       | Attendees            | Topics Discussed | Outcomes / Decisions |
|------------|----------------------|------------------|-----------------------|
| YYYY-MM-DD | [Names]              | [Agenda items]   | [Actions/Next steps]  |
| YYYY-MM-DD | [Names]              | [Agenda items]   | [Actions/Next steps]  |



## Bugs
- **Bug 1**: Errors running on Linprog due to differences in environment specifically in using getline()
- **Bug 2**: Errors with piping when executing (ls -la | grep shell)
- **Bug 3**: Output missalignments when executing tests with background processing and piping.

## Extra Credit
- **Extra Credit 1**: [Extra Credit Option]
- **Extra Credit 2**: [Extra Credit Option]
- **Extra Credit 3**: [Extra Credit Option]

## Considerations
[Description]
