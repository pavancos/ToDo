# Task Manager

## Abstract

This task manager serves as a project for an Advanced Data Structures course. It functions as a tool to aid users in efficiently organizing their tasks. Users can perform various actions such as adding, viewing, updating, and deleting tasks seamlessly. The program allows users to input task details and deadlines, which are then saved for future reference. Additionally, it calculates and presents the remaining days until each task's deadline, facilitating effective task prioritization. The manager is designed to streamline task management for users across different domains, be it academic, professional, or personal. By demonstrating the practical implementation of advanced data structures, it provides a hands-on learning experience while offering a practical solution for task organization. With its user-friendly interface and straightforward functionalities, the task manager aims to simplify the complexities associated with task management, making it accessible to users of all skill levels. Whether used for educational purposes or day-to-day task tracking, this project showcases the importance and utility of employing advanced data structures in solving real-world challenges.

## Introduction

Task management systems play a good role in aiding individuals and organizations in efficiently organizing and executing tasks. These systems act as digital assistants, allowing users to input, track, and manage tasks seamlessly. By providing features such as deadline tracking, priority setting, and task categorization, task management systems enhance productivity and streamline workflow processes. In today's fast-paced world, where time is of the essence, having an effective task management system is essential for staying organized and meeting deadlines. The project aims to bridge the gap between traditional pen-and-paper methods and modern digital solutions by providing a comprehensive task management system implemented using Advanced Data Structures. By leveraging the power of programming, the system offers advanced features and functionalities designed to enhance productivity and time management skills.

Priority queues are a type of container adaptors, specifically designed such that its first element is always the greatest of the elements it contains, according to some strict weak ordering criterion.[1] Priority queues, built upon the heap data structure, are fundamental to task management systems. In a priority queue, each task is assigned a priority, and the tasks are processed based on their priority level. The heap structure ensures that tasks with the highest priority are executed first, facilitating efficient task management and resource allocation. By leveraging the heap structure, priority queues offer a reliable and efficient means of prioritizing tasks, enabling users to focus on critical tasks and meet deadlines effectively.

Our Task Manger offers features such as task organisation, prioritization according to deadline. Task managers empower users to stay focused, meet deadlines, and achieve their goals with greater efficiency and ease.

## Objectives and Scope of the Project

**Development of User-Friendly Task Management System:** The primary goal of the project is to develop a user-friendly task management system using Advanced Data Structure. This system aims to provide individuals with a convenient platform to organize and prioritize their tasks effectively.

**Implementation of Core Functionalities:** The project focuses on implementing core functionalities essential for task management. These functionalities include:

- Adding tasks with deadlines
- Displaying existing tasks
- Searching for tasks based on deadlines or remaining days
- Deleting tasks by name
- Updating task deadlines

**Scope:**

**Core Functionality Implementation:** The scope of the project involves designing and coding the necessary features to ensure seamless task management. This includes implementing the core functionalities mentioned above to facilitate efficient task organization and tracking.

**User Input Validation:** The project prioritizes user input validation to enhance the reliability and usability of the system. By validating user input, the system can prevent errors and provide clear feedback to users, thereby improving the overall user experience.

**Basic Yet Efficient Solution:** While the system may not include advanced features found in enterprise-level task management software, it aims to provide a basic yet efficient task management solution suitable for personal or small-scale use. The focus is on simplicity and usability, allowing users to streamline their workflow and boost productivity.

**Target Audience:** The project targets individuals seeking a reliable and user-centric task management tool. By addressing the needs of this target audience, the project aims to deliver a solution that meets their requirements for efficient task organization and prioritization.

## Software used

### Programming Language: C++

The project is implemented using C++ as the primary programming language. C++ was chosen for its efficiency, performance, and versatility in handling complex software systems. With features such as memory management, strong typing, and extensive standard libraries, C++ provides a solid foundation for developing robust and scalable applications.

### Development Tools

**Code Editor:** Visual Studio Code (VS Code) serves as the primary code editor for this project. VS Code, a free and open-source editor, offers comprehensive support for various programming languages, including C++. Its features such as syntax highlighting, code completion, and debugging tools facilitate efficient coding and debugging process.

**Version Control System (VCS):** Git is utilized as the Version Control System (VCS) to manage the project's codebase. Git enables tracking of code changes, collaboration among developers, and maintaining a comprehensive history of the project's evolution.

### Libraries:

The project leverages several essential C++ standard libraries to implement various functionalities:

*\<iostream\>:* This library facilitates input/output operations, essential for interacting with the console.[2]
*\<ctime\>:* Offering time-related functions, this library assists in tasks such as setting deadlines and calculating remaining days by providing access to the current date and time.[3]
\<queue\>: Utilized to implement the priority queue data structure, this library aids in storing and prioritizing tasks based on their deadlines.[4]
*\<cstring\>:* This library provides string parsing functions like sscanf, utilized for extracting date information from user input.[5]
*\<fstream\>:* The fstream library facilitates file input/output operations, allowing the task management system to read and write data to external files. It is essential for persistent storage of task information, ensuring that tasks are preserved across sessions and system restarts.[6]

## Proposed Model

![](media/image4.png){width="2.001388888888889in" height="2.3125in"}The proposed model for the task management system utilizes a priority queue data structure as its core mechanism for storing and managing tasks. This data structure was chosen due to its inherent ability to maintain tasks in order of their deadlines, ensuring that the most time-sensitive tasks are always at the forefront. In this model, tasks are organized based on their deadlines, with those having the nearest deadlines being given higher priority in the queue. This prioritization ensures that users can efficiently focus on tasks that require immediate attention, facilitating effective time management and task prioritization.

Each task in the system is represented by a structured data format containing essential information such as a unique task ID, task description, deadline, and the number of remaining days until the deadline. This structured representation enables the system to maintain comprehensive task records and facilitates seamless interaction with users.

Users interact with the task management system through a simple console-based interface. The interface provides intuitive options for users to perform various operations on tasks, including adding new tasks, displaying existing tasks, searching for tasks based on deadlines or remaining days, deleting tasks, and updating task deadlines. This user-friendly interface ensures ease of use and accessibility for users, allowing them to efficiently manage their tasks without the need for complex interactions.

In a max-min heap representation, tasks with the highest priority (such as those with the nearest deadlines or the most critical importance) are placed at the top of the heap, allowing them to be easily accessed and processed first.[7] This prioritization mechanism is essential in a task management system, as it enables users to focus their attention and resources on the most urgent or important tasks. Overall, the max-min heap representation plays a crucial role in the task management model by facilitating efficient prioritization and processing of tasks, ultimately helping users stay organized and productive in managing their workload.

## Conclusion

In conclusion, the task management system developed in this project represents a significant step towards enhancing task organization and productivity for individuals and small teams. By prioritizing tasks based on their deadlines, users can effectively allocate their time and resources, ensuring that urgent tasks receive prompt attention while maintaining visibility over upcoming deadlines.

Looking ahead, future enhancements to the task management system could include the integration of additional features to further enhance its functionality and usability. For instance, incorporating task categorization capabilities could allow users to classify tasks based on different criteria, facilitating more granular organization and prioritization.

Overall, the task management system developed in this project serves as a valuable tool for individuals and small teams seeking to optimize their task management processes and boost overall productivity. By providing a practical and user-centric solution, the system empowers users to efficiently manage their tasks, stay organized, and meet deadlines with confidence. With continued development and refinement, the system holds the potential to become an indispensable asset in the arsenal of tools for effective task management in various contexts.
