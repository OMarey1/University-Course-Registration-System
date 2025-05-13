# University Course Registration System (UCRS)

## Project Description
UCRS is a desktop application built with Qt and C++ for managing university course registrations. It allows students to register and drop courses, instructors to view their assigned courses, and administrators to manage users and courses. The system supports features such as course capacity, waiting lists, schedule conflict detection, and detailed reporting.

## Features
- Student, Instructor, and Admin roles
- Course registration and dropping for students
- Waiting list management for full courses
- Schedule conflict detection
- Course and user management for admins
- Instructor workload and student schedule views
- Modern, user-friendly Qt interface

## Setup Instructions
1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd UCRS
   ```
2. **Open the project in Qt Creator:**
   - Open `UCRS.pro` in Qt Creator.
3. **Build the project:**
   - Click the build button or use `Ctrl+B`.
4. **Run the application:**
   - Click the run button or use `Ctrl+R`.

### Dependencies
- Qt 6.x (Tested with Qt 6.8.2)
- C++17 or later

## Usage Examples
### Student Registration
- Log in as a student.
- View available courses, register for a course, or drop a registered course.
- The system will prevent registration if there is a schedule conflict or if the course is full (in which case you are added to the waiting list).

### Admin Management
- Log in as an admin.
- Add, edit, or delete users and courses.
- View reports on course enrollments and student schedules.

### Instructor View
- Log in as an instructor.
- View assigned courses and enrolled students.

## Screenshots
Add screenshots of the main windows and typical outputs here:

- **Login Screen:**
  ![Login Screen](screenshots/login.png)
- **Student Course Registration:**
  ![Student Registration](screenshots/student_registration.png)
- **Admin Dashboard:**
  ![Admin Dashboard](screenshots/admin_dashboard.png)
- **Reports:**
  ![Reports](screenshots/reports.png)

> _To add your own screenshots, place images in a `screenshots/` folder and update the paths above._
 
