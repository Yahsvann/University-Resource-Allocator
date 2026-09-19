# University-Resource-Allocator / Student Management System

A C++ object-oriented program that manages university students and faculty members with project assignments and supervision tracking.

## Overview

This system simulates a comprehensive university student-faculty management system that handles academic relationships, project assignments, and teaching responsibilities. The system manages two distinct student categories with different academic requirements and supervision needs. In this program we randomly generate unique named students, faculty, hostels.

### Key Components

**Input format:** <No.of students> <No.of faculty> <No.of hostels>

**Student Types:**
- **BTech Students**: Undergraduate students requiring faculty advisors and project guides for their final year projects
- **DualDegree Students**: Graduate students who need both project supervision for their research work and can serve as Teaching Assistants (TAs)

**Faculty Management:**
- **Permanent Faculty**: Full-time faculty members who can supervise projects and teach courses
- **Adjunct Faculty**: Part-time faculty who can teach and supervise TAs but cannot guide projects

**Hostel System:**
- Students are assigned to different hostels (residential halls) 
- Hostel assignments influence project guide allocation for DualDegree students

**Unique Identification:**
- Each student has a unique roll number for identification
- Each faculty member has a unique name identifier

**Random Generation Engine:**
- Automated creation of student and faculty profiles with random attributes
- Random assignment of faculty advisors to students
- Random TA supervisor assignments with constraint checking
- CGPA-based intelligent assignment for BTech project guides

## Features

### Core Functionality
- **Student Management**: Handle BTech and DualDegree students with comprehensive profile tracking including roll numbers, hostel assignments, CGPA, and faculty relationships
- **Faculty Management**: Track permanent and adjunct faculty members with their teaching loads and supervision capacities
- **Random Data Generation**: Automatically generate realistic student and faculty populations for testing and simulation purposes

### Intelligent Assignment Systems
- **Faculty Advisor Assignment**: Random allocation of faculty advisors to all students
- **BTech Project Guide Assignment**: 
  - Merit-based assignment using CGPA ranking (highest CGPA gets first choice)
  - Only permanent faculty eligible as project guides
  - Strict capacity limit of 2 projectees per guide
- **DualDegree Project Guide Assignment**:
  - Hostel-based allocation (students from same hostel grouped together)
  - Only permanent faculty eligible as project guides
  - Maximum 2 projectees per guide
- **TA Supervisor Assignment**:
  - Random assignment to DualDegree students
  - Both permanent and adjunct faculty can supervise TAs
  - Capacity limit of 5 TAs per supervisor

### Advanced Query and Analysis Functions
- **Constraint Validation**: Verify all assignment rules are properly followed
- **Overlap Analysis**: Calculate percentage of DualDegree students whose project guide and TA supervisor are the same person
- **Multi-criteria Sorting**: Sort students by roll number, guide name, or hostel assignment
- **Unassigned Student Tracking**: Identify students who couldn't be assigned guides due to capacity constraints
- **Cross-referencing**: Find all DualDegree students from specific hostels working under particular faculty members
- **Workload Distribution Analysis**: Identify faculty members supervising students across the maximum number of different hostels

## Class Structure

### Core Classes
- **BTech**: Represents BTech students with project guide functionality
- **DualDegree**: Represents dual degree students with both project and TA supervision
- **Faculty**: Represents faculty members (permanent/adjunct status)
- **University**: Main container class managing students and faculty

### Key Constraints
- **Project Guide Eligibility**: Only permanent faculty can supervise student projects (adjunct faculty excluded)
- **BTech Project Capacity**: Maximum 2 BTech students per permanent faculty guide
- **DualDegree Project Capacity**: Maximum 2 DualDegree students per permanent faculty guide  
- **TA Supervision Capacity**: Maximum 5 Teaching Assistants per faculty supervisor (both permanent and adjunct eligible)
- **Unique Faculty Courses**: Each faculty member teaches exactly one course

Check out the code to see the implementation details and discover how it all works under the hood!
