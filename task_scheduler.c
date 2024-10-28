/**
 * @file task_scheduler.c
 * @author Joshua Alana (https://joshua-alana.vercel.app/)
 * @brief A scheduler implementation
 * @version 0.1
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// some macro definitions

#define MAX_TASKS 100
#define MAX_TITLE 50
#define MAX_DESC 200
#define MAX_EMPLOYEE 50

// structure for date

typedef struct
{
    int day;
    int month;
    int year;
} Date;

// structure for task

typedef struct
{
    char title[MAX_TITLE];
    char description[MAX_DESC];
    char assigned_to[MAX_EMPLOYEE];
    Date due_date;
    int priority;
    int is_completed;
    time_t created_at;
} Task;

// structure for task management

typedef struct
{
    Task tasks[MAX_TASKS];
    int task_count;
    Task completed_tasks[MAX_TASKS];
    int completed_count;
} TaskSystem;

// function to initialize task system

void init_system(TaskSystem *sys)
{
    sys->task_count = 0;
    sys->completed_count = 0;
}

// function to create a date

Date create_date(int day, int month, int year)
{
    Date date = {day, month, year};
    return date;
}

// function to check if date is valid

int is_valid_date(Date date)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.year < 2024 || date.month < 1 || date.month > 12)
        return 0;

    if (date.month == 2 && date.year % 4 == 0) // leap year
        return date.day <= 29;

    return date.day <= days_in_month[date.month - 1];
}

// function to add task

int add_task(TaskSystem *sys, const char *title, const char *desc, const char *employee, Date due_date, int priority)
{
    if (sys->task_count >= MAX_TASKS || priority < 1 || priority > 5 || !is_valid_date(due_date))
        return 0;

    Task new_task;
    strncpy(new_task.title, title, MAX_TITLE - 1);
    strncpy(new_task.description, desc, MAX_DESC - 1);
    strncpy(new_task.assigned_to, employee, MAX_EMPLOYEE - 1);
    new_task.due_date = due_date;
    new_task.priority = priority;
    new_task.is_completed = 0;
    new_task.created_at = time(NULL);

    // find position to insert (maintain sorted order by priority)
    int pos = sys->task_count;
    while (pos > 0 && sys->tasks[pos - 1].priority > priority)
    {
        sys->tasks[pos] = sys->tasks[pos - 1];
        pos--;
    }

    sys->tasks[pos] = new_task;
    sys->task_count++;
    return 1;
}

// function to complete a task

int complete_task(TaskSystem *sys, int task_index)
{
    if (task_index < 0 || task_index >= sys->task_count)
        return 0;

    // move task to completed array
    sys->completed_tasks[sys->completed_count++] = sys->tasks[task_index];
    sys->completed_tasks[sys->completed_count - 1].is_completed = 1;

    // shift remaining tasks
    for (int i = task_index; i < sys->task_count - 1; i++)
    {
        sys->tasks[i] = sys->tasks[i + 1];
    }
    sys->task_count--;
    return 1;
}

// function to view next task

Task *get_next_task(TaskSystem *sys)
{
    if (sys->task_count == 0)
        return NULL;
    return &sys->tasks[0];
}

// function to display a task

void display_task(Task *task)
{
    printf("\nTask: %s", task->title);
    printf("\nPriority: %d", task->priority);
    printf("\nAssigned to: %s", task->assigned_to);
    printf("\nDue Date: %02d/%02d/%2d", task->due_date.day, task->due_date.month, task->due_date.year);
    printf("\nDescription: %s", task->description);
    printf("\nStatus: %s", task->is_completed ? "Completed" : "Pending");
    printf("\n--------------------\n");
}

// function to display all tasks

void display_all_tasks(TaskSystem *sys)
{
    printf("\nPending Tasks (%d):\n", sys->task_count);
    for (int i = 0; i < sys->task_count; i++)
    {
        printf("\n%d. ", i + 1);
        display_task(&sys->tasks[i]);
    }
    printf("\nCompleted Tasks (%d):\n", sys->completed_count);
    for (int i = 0; i < sys->completed_count; i++)
    {
        printf("\n%d. ", i + 1);
        display_task(&sys->completed_tasks[i]);
    }
}

int main()
{
    TaskSystem system;
    init_system(&system);

    // Example usage
    Date today = create_date(27, 10, 2024);
    Date next_week = create_date(3, 11, 2024);

    // Add some tasks
    add_task(&system, "Website Update", "Update company website content",
             "John Doe", today, 1);
    add_task(&system, "Client Meeting", "Prepare presentation for client",
             "Jane Smith", next_week, 2);
    add_task(&system, "Code Review", "Review new feature implementation",
             "Bob Johnson", today, 1);

    // Display all tasks
    printf("Initial Task List:");
    display_all_tasks(&system);

    // Complete a task
    complete_task(&system, 0);

    // Display updated list
    printf("\nAfter completing one task:");
    display_all_tasks(&system);

    // View next task
    Task *next = get_next_task(&system);
    if (next)
    {
        printf("\nNext task to handle:");
        display_task(next);
    }

    return 0;
}