# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## High-level Code Architecture and Structure

This repository contains a C++ program (`p1.cpp`) that implements an exam registration system for managing student information.

The core of the system is the `ExamRegistrationSystem` class, which uses a hash table with separate chaining to store student records. The hash table size is a prime number to help with distribution.

- **`Student` struct**: Defines the data for a student, including exam ID, name, gender, age, and application category.
- **`Node` struct**: Represents a node in the linked list used for chaining in the hash table. Each node contains a `Student` object.
- **`ExamRegistrationSystem` class**: Encapsulates all the functionality of the system, such as inserting, deleting, searching, modifying, and displaying student information. It manages the hash table and the count of students.
- **Hashing**: A hash function is used to map the student's exam ID to an index in the hash table.

## Common Commands

### Building the code
To compile the C++ code, you can use `g++`. The following command compiles `p1.cpp` and creates an executable named `exam_system`:
```bash
g++ p1.cpp -o output/exam_system
```

### Running the application
After compiling, you can run the program with the following command:
```bash
./output/exam_system
```
The program is interactive and will prompt you for input.
