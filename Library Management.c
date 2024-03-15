#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure definitions
typedef struct BOOK {
    int id;
    char title[100];
    char author[50];
    char subject[50];
    int copies;
    struct BOOK* next;
} Book;

typedef struct MEMBER {
    int id;
    char name[50];
    char department[50];
    Book* borrowedBooks;
    struct MEMBER* next;
} Member;

typedef struct User {
    char username[50];
    char password[50];
} User;

// Function decalration
Book* createBook(int id, char title[], char author[], char subject[], int copies);
Member* createMember(int id, char name[], char department[]);
Book* addBook(Book* head, Book* newBook);
Member* addMember(Member* head, Member* newMember);
Book* searchBookById(Book* head, int id);
Member* searchMemberById(Member* head, int id);
void issueBook(Book* book, Member* member);
void returnBook(Book* book, Member* member);
void displayBooks(Book* head);
void displayMembers(Member* head);
void displayIssuedBooksForMember(Member* head, int memberId);
Member* deleteMember(Member* head, int memberId);
Book* deleteBook(Book* head, int bookId);
bool login(User *users, int numUsers);
void addCredentials(User *users, int *numUsers);
void logout(bool *loggedin);

int main() {
    Book* bookList = NULL; //Initialise book list
    Member* memberList = NULL;//Initialise member list
    User users[5];//admins
    int numUsers = 0;
    bool loggedIn=false;//Login status

    //Default admin
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "password");
    numUsers++;
    while(1){
        //it will not enter libraray menu until we put proper login credentials.
        while(!loggedIn){

            if(!loggedIn){
                //for checking credentials
                if (!login(users, numUsers)) {
                    printf("Login failed.\n");
                }
                //for logging in
                else
                    loggedIn=true;    
            }
        }
        int choice, bookID, memberID;
        printf("\nCollege Library System\n");
        printf("1. To Add Book\n");
        printf("2. To Add Member\n");
        printf("3. To Search Book by ID\n");
        printf("4. To Search Member by ID\n");
        printf("5. To Issue Book\n");
        printf("6. To Return Book\n");
        printf("7. To Display all Books\n");
        printf("8. To Display all Members\n");
        printf("9. To Display Issued Books of a Member\n");
        printf("10. To  Delete Member\n");
        printf("11. To Delete Book\n");
        printf("12. To add admin\n");
        printf("13. To logout\n");
        printf("14.To Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Book book;
                //It will take book details as input
                printf("Enter book details:\n");
                printf("ID: ");
                scanf("%d", &bookID);
                getchar(); 
                printf("Title: ");
                gets(book.title);
                printf("Author: ");
                gets(book.author);
                printf("Subject: ");
                gets(book.subject);
                printf("Number of copies: ");
                scanf("%d", &book.copies);
                //This details are used to create a new book
                Book* newBook = createBook(bookID, book.title, book.author, book.subject, book.copies);
                //This book is added to our library
                bookList = addBook(bookList, newBook);
                printf("Book added successfully!\n");
                break;
            }

            case 2: {
                Member member;
                //It will take member details as input
                printf("Enter member details:\n");
                printf("ID: ");
                scanf("%d", &memberID);
                getchar();

                printf("Name: ");
                gets(member.name);  
                printf("Department: ");
                gets(member.department);
                //This details are used to create new member 
                Member* newMember = createMember(memberID, member.name, member.department);
                //This member is added to member list of our library
                memberList = addMember(memberList, newMember);
                printf("Member added successfully!\n");
                break;
            }

            case 3: {
                //Search book by id
                printf("Enter book ID: ");
                scanf("%d", &bookID);
                Book* foundBook = searchBookById(bookList, bookID);
                //It will give details of the book
                if (foundBook != NULL) {
                    printf("Book Found:\n");
                    printf("ID: %d, Title: %s, Author: %s, Subject: %s, Copies: %d\n", foundBook->id, foundBook->title, foundBook->author, foundBook->subject, foundBook->copies);
                } else {
                    printf("Book not found.\n");
                }
                break;
            }

            case 4: {
                //Search member by id
                printf("Enter member ID: ");
                scanf("%d", &memberID);
                Member* foundMember = searchMemberById(memberList, memberID);
                //It will give details of the member
                if (foundMember != NULL) {
                    printf("Member Found:\n");
                    printf("ID: %d, Name: %s, Department: %s\n", foundMember->id, foundMember->name, foundMember->department);
                } else {
                    printf("Member not found.\n");
                }
                break;
            }

            case 5: {
                //Issued book
                //It takes member id and book id as input
                printf("Enter book ID: ");
                scanf("%d", &bookID);
                printf("Enter member ID: ");
                scanf("%d", &memberID);
                //Searching book by its id
                Book* issueB = searchBookById(bookList, bookID);
                //Searching member by its id
                Member* issueM = searchMemberById(memberList, memberID);
                if (issueB != NULL && issueM != NULL) {
                    issueBook(issueB, issueM);
                } else {
                    printf("Invalid book ID or member ID.\n");
                }
                break;
            }

            case 6: {
                //Returning book
                //It takes member id and book id as input
                printf("Enter book ID: ");
                scanf("%d", &bookID);
                printf("Enter member ID: ");
                scanf("%d", &memberID);
                //Searching book by its id
                Book* returnB = searchBookById(bookList, bookID);
                //Searching member by its id
                Member* returnM = searchMemberById(memberList, memberID);
                if (returnB != NULL && returnM != NULL) {
                    returnBook(returnB, returnM);
                } else {
                    printf("Invalid book ID or member ID.\n");
                }
                break;
            }

            case 7:{
                //Displays all book present in our library
                displayBooks(bookList);
                break;
            }
            
            case 8:{
                //Displays all the subscribers to our library
                displayMembers(memberList);
                break;
            }
            case 9: {
                //Displays all issued book for a particular member 
                printf("Enter member ID: ");
                scanf("%d", &memberID);
                displayIssuedBooksForMember(memberList, memberID);
                break;
            }

            case 10: {
                //To unsubscribe the member from library
                printf("Enter member ID to delete: ");
                scanf("%d", &memberID);
                memberList=deleteMember(memberList, memberID);
                break;
            }

            case 11: {
                //To remove a book from library
                printf("Enter book ID to delete: ");
                scanf("%d", &bookID);
                bookList=deleteBook(bookList, bookID);
                break;
            }
            case 12: {
                //To create a new admin
                addCredentials(users, &numUsers);
                break;
            }
            case 13:{
                //For admin to logout
                logout(&loggedIn);
                break;
            }
            case 14:
            //To exit the code
                exit(0);

            default:
            //Default section for invalid choice
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
// Function for authority login 
bool login(User *users, int numUsers) {
    //For admin
    char username[50];
    char password[50];

    printf("Library Authority Login\n");
    printf("Username: ");
    scanf("%s",username);
    printf("Password: ");
    scanf("%s", password);
    //It will check the corresponding user name and password
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return true;
        }
    }

    printf("Invalid username or password.\n");
    return false;
}

Book* createBook(int id, char title[], char author[], char subject[], int copies) {
    //New book is created and returned
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->subject, subject);
    newBook->copies = copies;
    newBook->next = NULL;
    return newBook;
}

Member* createMember(int id, char name[], char department[]) {
    //New member is created and returned
    Member* newMember = (Member*)malloc(sizeof(Member));
    newMember->id = id;
    strcpy(newMember->name, name);
    strcpy(newMember->department, department);
    newMember->borrowedBooks = NULL;
    newMember->next = NULL;
    return newMember;
}

Book* addBook(Book* head, Book* newBook) {
    // Check if the book with the same ID already exists
    Book* existingBook = searchBookById(head, newBook->id);
    if (existingBook != NULL) {
        printf("Book with ID %d already exists.\n", newBook->id);
        //If exists copies will be incremented
        existingBook->copies++;
        // Free memory allocated for the new book
        free(newBook); 
        return head;
    }
    // If the book doesn't exist, add it to the list
    if (head == NULL) {
        //For first book
        head = newBook;
    }
    else {
        Book* temp = head;
        //Traversed till end and then added
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
    printf("Book with ID %d added successfully!\n", newBook->id);
    return head;
}


Member* addMember(Member* head, Member* newMember) {
    // Check if a member with the same ID already exists
    Member* existingMember = searchMemberById(head, newMember->id);
    if (existingMember != NULL) {
        printf("Member with ID %d already exists.\n", newMember->id);
        free(newMember); // Free memory allocated for the new member
        return head;
    }
    // If the member doesn't exist, add them to the list
    if (head == NULL) {
        //For first member
        head = newMember;
    } else {
        Member* temp = head;
        //Traversed till end and then added
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMember;
    }
    printf("Member with ID %d added successfully!\n", newMember->id);
    return head;
}

Book* searchBookById(Book* head, int id) {
    Book* temp = head;
    //Traverse
    while (temp != NULL) {
        if (temp->id == id) {
            //Returning the book 
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Member* searchMemberById(Member* head, int id) {
    Member* temp = head;
    //Traverse
    while (temp != NULL) {
        if (temp->id == id) {
            //Returning member 
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void issueBook(Book* book, Member* member) {
    if (book->copies > 0) {
        // Create a new borrowed book node
        Book* newBorrowedBook = createBook(book->id, book->title, book->author, book->subject, 1);
        book->copies--;

        // Add the new borrowed book to the member's list of borrowed books
        if (member->borrowedBooks == NULL) {
            //First time borrowing
            member->borrowedBooks = newBorrowedBook;
        } else {
            Book* temp = member->borrowedBooks;
            while (temp->next != NULL) {
                //Traversing till end and then added to borrow book list
                temp = temp->next;
            }
            temp->next = newBorrowedBook;
        }
        printf("Book issued successfully!\n");
    } else {
        printf("No copies available for issuing.\n");
    }
}

void returnBook(Book* book, Member* member) {
   
    Book* prev = NULL;
    Book* temp = member->borrowedBooks;

    while (temp != NULL) {
        if (temp->id == book->id) {
            // Remove the returned book from the member's list of borrowed books
            if (prev == NULL) {
                //For first book returning
                member->borrowedBooks = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            //That book is added back to library
            book->copies++;
            printf("Book returned successfully!\n");
            return;
        }
        //For traversing we use this
        prev = temp;
        temp = temp->next;
    }

    printf("This book has not been issued to this member.\n");
}


void displayBooks(Book* head) {
    Book* temp = head;
    if (temp == NULL) {
        printf("No books found.\n");
        return;
    }
    printf("List of Books:\n");
    //Displaying all the books present in library 
    while (temp != NULL) {
        printf("ID: %d, Title: %s, Author: %s, Subject: %s, Copies Available: %d\n", temp->id, temp->title, temp->author, temp->subject, temp->copies);
        temp = temp->next;
    }
}

void displayMembers(Member* head) {
    Member* temp = head;
    if (temp == NULL) {
        printf("No members found.\n");
        return;
    }
    printf("List of Members:\n");
    //Displaying all subscribers
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Department: %s\n", temp->id, temp->name, temp->department);
        temp = temp->next;
    }
}

void displayIssuedBooksForMember(Member* head, int memberId) {
    //Searching member with id
    Member* member = searchMemberById(head, memberId);
    if (member == NULL) {
        printf("Member not found.\n");
        return;
    }
    Book* borrowedBooks = member->borrowedBooks;
    //For no previous borrowing books
    if (borrowedBooks == NULL) {
        printf("No books issued to this member.\n");
        return;
    }
    printf("Books issued to Member ID: %d:\n", member->id);
    //For displaying all the books barrowed by that member 
    while (borrowedBooks != NULL) {
        printf("ID: %d, Title: %s, Author: %s, Subject: %s\n", borrowedBooks->id, borrowedBooks->title, borrowedBooks->author, borrowedBooks->subject);
        borrowedBooks = borrowedBooks->next;
    }
}

Member* deleteMember(Member* head, int memberId) {
    Member* current = head;
    Member* prev = NULL;

    // Find the member to be deleted
    while (current != NULL && current->id != memberId) {
        prev = current;
        current = current->next;
    }

    // If the member was found, delete it
    if (current != NULL) {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("Member with ID %d deleted successfully!\n", memberId);
    } else {
        printf("Member with ID %d not found.\n", memberId);
    }
    return head;
}

Book* deleteBook(Book* head, int bookId) {
    Book* current = head;
    Book* prev = NULL;

    // Find the book to be deleted
    while (current != NULL && current->id != bookId) {
        prev = current;
        current = current->next;
    }

    // If the book was found, delete it
    if (current != NULL) {
        if (prev == NULL) {
            head = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("Book with ID %d deleted successfully!\n", bookId);
    } else {
        printf("Book with ID %d not found.\n", bookId);
    }
    return head;
}
void addCredentials(User *users, int *numUsers) {
    if (*numUsers >= 5) {
        printf("Maximum number of users reached.\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%s", users[*numUsers].username);
    printf("Enter new password: ");
    scanf("%s", users[*numUsers].password);
    
    (*numUsers)++;
    printf("User added successfully!\n");
}
void logout(bool *loggedIn){
    *loggedIn=false;
    printf("logged out successfully...\n\n");
}