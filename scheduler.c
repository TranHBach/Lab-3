/*
 * scheduler.c
 *
 *  Created on: Apr 1, 2024
 *      Author: TRAN HUU BACH
 */

#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;
typedef struct node
{
    sTasks task;
    struct node *next;
} node;

node SCH_tasksNode[SCH_MAX_TASKS];
node *head;

void SCH_Init(void)
{
    current_index_task = 0;
}

void handle_allocating_linked_list(node *newTaskNode)
{
    node *test = head;
    if (head == 0)
    {
        head = newTaskNode;
    }
    else
    {
        node *currentTaskNode;
        node *prevNode;
        currentTaskNode = head;
        // Exit condition is 1 when the newNodeTask find the location in the linkedlist by comparing with other tasks
        // Exit condition is 2 when the currentNodeTask reach end of linked list and cannot reevaluate any task afterward
        int exitCondition = 0;
        while (currentTaskNode->task.Delay <= newTaskNode->task.Delay)
        {
            newTaskNode->task.Delay -= currentTaskNode->task.Delay;
            if (currentTaskNode->next == 0)
            {
                exitCondition = 2;
                break;
            }
            prevNode = currentTaskNode;
            currentTaskNode = currentTaskNode->next;
            exitCondition = 1;
        }

        if (currentTaskNode == head && exitCondition == 1)
        {
            head = newTaskNode;
        }

        if (exitCondition == 1)
        {
            newTaskNode->next = currentTaskNode;
            prevNode->next = newTaskNode;
            currentTaskNode->task.Delay -= newTaskNode->task.Delay;
        }
        else
        {
            currentTaskNode->next = newTaskNode;
        }
    }
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
    if (current_index_task < SCH_MAX_TASKS)
    {
        SCH_tasksNode[current_index_task].task.pTask = pFunction;
        SCH_tasksNode[current_index_task].task.Delay = DELAY / 10;
        SCH_tasksNode[current_index_task].task.Period = PERIOD / 10;
        SCH_tasksNode[current_index_task].task.RunMe = 0;

        SCH_tasksNode[current_index_task].task.TaskID = current_index_task;

        struct node *newTaskNodePointer = &SCH_tasksNode[current_index_task];
        handle_allocating_linked_list(newTaskNodePointer);
        current_index_task++;
    }
}

void SCH_Update(void)
{
    node *test = head;
    if (head->task.Delay > 0)
    {
        head->task.Delay--;
    }
    else
    {
        head->task.Delay = head->task.Period;
        head->task.RunMe = 1;
    }
}

void SCH_Add_And_Delete_Tasks(void)
{
    node *readdedTaskNode = head;
    head = head->next;
    readdedTaskNode->next = 0;
    handle_allocating_linked_list(readdedTaskNode);
}

void SCH_Dispatch_Tasks(void)
{
    node *currentNode = head;
    while(currentNode != 0 && (currentNode->task.Delay == 0 || currentNode->task.RunMe > 0)) {
        if (currentNode->task.Delay == 0)
        {
            currentNode->task.Delay = currentNode->task.Period;
            currentNode->task.RunMe = 1;
        }

        if (currentNode->task.RunMe > 0)
        {
            currentNode->task.RunMe--;
            (*currentNode->task.pTask)();
            SCH_Add_And_Delete_Tasks();
        }
        currentNode = currentNode->next;
    }
}
void test1() {}
void test2() {}
void test3() {}
int main()
{
    SCH_Add_Task(test1, 30, 30);
    SCH_Add_Task(test2, 50, 50);
    SCH_Add_Task(test3, 70, 70);
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);

    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);
    SCH_Update();
    SCH_Dispatch_Tasks();
    printf("%i %i %i\n", head->task.Delay, head->next->task.Delay, head->next->next->task.Delay);


}

/*
 * scheduler.c
 *
 *  Created on: Apr 1, 2024
 *      Author: TRAN HUU BACH
 */

// #include "scheduler.h"
// #include <stdlib.h>
// sTasks SCH_tasks_G[SCH_MAX_TASKS];
// uint8_t current_index_task = 0;
// typedef struct node
// {
//     sTasks task;
//     struct node *next;
// } node;

// node SCH_tasksNode[SCH_MAX_TASKS];
// node *head;

// void SCH_Init(void)
// {
//     current_index_task = 0;
// }

// void handle_allocating_linked_list(node *newTaskNode)
// {
//     if (head == 0)
//     {
//         head = newTaskNode;
//     }
//     else
//     {
//         node *currentTaskNode;
//         node *prevNode;
//         currentTaskNode = head;
//         // Exit condition is 1 when the newNodeTask find the location in the linkedlist by comparing with other tasks
//         // Exit condition is 2 when the currentNodeTask reach end of linked list and cannot reevaluate any task afterward
//         int exitCondition = 0;
//         while (currentTaskNode->task.Delay <= newTaskNode->task.Delay)
//         {
//             newTaskNode->task.Delay -= currentTaskNode->task.Delay;
//             if (currentTaskNode->next == 0)
//             {
//                 exitCondition = 2;
//                 break;
//             }
//             prevNode = currentTaskNode;
//             currentTaskNode = currentTaskNode->next;
//             exitCondition = 1;
//         }

//         if (currentTaskNode == head && exitCondition == 1)
//         {
//             head = newTaskNode;
//         }

//         if (exitCondition == 1)
//         {
//             newTaskNode->next = currentTaskNode;
//             prevNode->next = newTaskNode;
//             currentTaskNode->task.Delay -= newTaskNode->task.Delay;
//         }
//         else
//         {
//             currentTaskNode->next = newTaskNode;
//         }
//     }
// }

// void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
// {
//     if (current_index_task < SCH_MAX_TASKS)
//     {
//         SCH_tasksNode[current_index_task].task.pTask = pFunction;
//         SCH_tasksNode[current_index_task].task.Delay = DELAY / 10;
//         SCH_tasksNode[current_index_task].task.Period = PERIOD / 10;
//         SCH_tasksNode[current_index_task].task.RunMe = 0;

//         SCH_tasksNode[current_index_task].task.TaskID = current_index_task;

//         struct node *newTaskNodePointer = &SCH_tasksNode[current_index_task];
//         handle_allocating_linked_list(newTaskNodePointer);
//         current_index_task++;
//     }
// }

// void SCH_Update(void)
// {
//     if (head->task.Delay > 0)
//     {
//         head->task.Delay--;
//     }
//     else
//     {
//         head->task.Delay = head->task.Period;
//         head->task.RunMe += 1;
//         node *taskWithSameDelay = head->next;
//         while(taskWithSameDelay != 0 && taskWithSameDelay->task.Delay == 0) {
//             taskWithSameDelay->task.Delay = taskWithSameDelay->task.Period;
//             taskWithSameDelay->task.RunMe += 1;
//             taskWithSameDelay = taskWithSameDelay->next;
//         }
//     }
// }

// void SCH_Add_And_Delete_Tasks(void)
// {
//     node *readdedTaskNode = head;
//     head = head->next;
//     readdedTaskNode->next = 0;
//     handle_allocating_linked_list(readdedTaskNode);
// }

// void SCH_Dispatch_Tasks(void)
// {
//     for (int i = 0; i < current_index_task; i++)
//     {
//         if (SCH_tasksNode[i].task.RunMe > 0)
//         {
//             SCH_tasksNode[i].task.RunMe--;
//             (*SCH_tasksNode[i].task.pTask)();
//             SCH_Add_And_Delete_Tasks();
//         }
//     }
// }
