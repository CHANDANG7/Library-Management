Data Structures Used
The above code primarily uses linked lists to manage data structures:
Book and Member Structures:
Each book and member are represented using a structure Book and Member
respectively.
These structures hold information such as book ID, title, author, subject, copies
available, member ID, name, and department.
Both structures contain pointers (next) to the next element in the linked list.
User Structure:
The User structure represents admin users of the library system.
It is the array of Structures.
It stores the username and password of each user.
Linked Lists:
The program maintains Multiple linked lists of books and members.
Each node in the linked list corresponds to a book or a member.
The next pointer in each node points to the next node in the list and other List
also.
Node Member also points to the Node book.
Linked lists are used to dynamically manage and store multiple books and
members in memory.
These linked lists allow for efficient insertion, deletion, and traversal of books
and members within the library management system. Additionally, the use of
linked lists allows for flexibility in managing variable numbers of books and
members without requiring fixed-size arrays.
