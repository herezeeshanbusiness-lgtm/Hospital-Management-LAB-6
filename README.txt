Hospital Management System — Lab 06 Part B

Problem:
A hospital waiting list can cycle through patients for repeated review/display.
After the last patient, traversal returns to the first instead of ending at nullptr.

Why circular linked list:
Each PatientNode points to the next patient, and the last node links back to the
first. The class uses pivot as the last node and pivot->next as the first node.

Files:
- main.cpp: menu and validated input.
- CircularLinkedList.h: node structure and class declarations.
- CircularLinkedList.cpp: circular-list implementation.

Lab 06 Part B methods:
InsertAt, RemoveAt, Swap, Sort, Reverse, Print, Insert and Remove at pivot->next,
IsEmpty, IsNotEmpty, and circular traversal with MoveToNext.

Priority: 1=Urgent, 2=Regular, 3=Low. Sort() sorts by priority.
Indexes are zero-based; circular indexes wrap around the list.

Compile in VS Code terminal:
g++ -std=c++17 main.cpp CircularLinkedList.cpp -o hospital

Run on Windows PowerShell:
.\hospital.exe

Run on Linux/macOS:
./hospital
