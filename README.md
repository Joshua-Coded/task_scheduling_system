# Task Scheduling System

A C-based task management system designed for small companies to manage and prioritize tasks efficiently.

## Features

- Priority-based task management (1-5 priority levels)
- Task creation and assignment
- Due date tracking
- Task completion tracking
- Display of pending and completed tasks
- Priority-based task ordering

## Structure

### Task Properties
- Title (up to 50 characters)
- Description (up to 200 characters)
- Assigned employee
- Due date
- Priority level (1 highest - 5 lowest)
- Completion status
- Creation timestamp

## Installation

```bash
# Clone the repository
git clone https://github.com/Joshua-Coded/task_scheduling_system.git

# Navigate to directory
cd task_scheduling_system

# Compile the program
gcc task_scheduling_system.c -o task_scheduling_system

# Run the program
./task_scheduling_system
```

## Usage

```c
// Initialize the system
TaskSystem system;
init_system(&system);

// Add a new task
add_task(&system, 
    "Website Update",              // Title
    "Update company website",      // Description
    "John Doe",                    // Employee
    create_date(27, 10, 2024),    // Due date
    1                             // Priority
);

// Complete a task
complete_task(&system, 0);  // Complete first task

// View all tasks
display_all_tasks(&system);

// Get next priority task
Task* next = get_next_task(&system);
```

## Functions

| Function | Description |
|----------|-------------|
| `init_system()` | Initialize the task system |
| `add_task()` | Add a new task with details |
| `complete_task()` | Mark a task as completed |
| `get_next_task()` | Get highest priority pending task |
| `display_task()` | Display single task details |
| `display_all_tasks()` | Show all pending and completed tasks |

## Limitations

- Maximum 100 tasks (configurable in MAX_TASKS)
- Fixed string lengths for task properties
- In-memory storage (no persistence)
- Basic date validation

## Future Improvements

- [ ] Task editing functionality
- [ ] Data persistence (file storage)
- [ ] Task search and filtering
- [ ] Employee workload tracking
- [ ] Task dependencies
- [ ] Due date reminders
- [ ] Multi-user support

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author

Your Name
- GitHub: [@Joshua-Coded]
- Email: j.alana@alustudent.com