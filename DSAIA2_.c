#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Movie {
    int movieID;
    char title[100];
    int availableSeats;                 // Define a structure for a movie
    struct Movie* next;
} Movie;


typedef struct Booking {
    int bookingID;
    int movieID;
    int numTickets;                  // Define a structure for a booking
    struct Booking* next;
} Booking;


typedef struct StackNode {
    Booking* booking;
    struct StackNode* next;           // Define a stack data structure for managing bookings
} StackNode;

StackNode* top = NULL;  // Initialize an empty stack for bookings
Movie* movieList = NULL;  // Initialize an empty linked list for movies


void push(Booking* booking) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->booking = booking;
    newNode->next = top;                       // Function to push a booking onto the stack
    top = newNode;
}


Booking* pop() {
    if (top == NULL) {
        return NULL;  // Stack is empty
    }
    StackNode* temp = top;                                   // Function to pop a booking from the stack
    top = top->next;
    Booking* poppedBooking = temp->booking;
    free(temp);
    return poppedBooking;
}


Movie* createMovieNode(const char* title, int seats) {
    Movie* newMovie = (Movie*)malloc(sizeof(Movie));
    static int movieIDCounter = 1;
    newMovie->movieID = movieIDCounter++;                                      // Function to create a new movie node
    strncpy(newMovie->title, title, sizeof(newMovie->title));
    newMovie->availableSeats = seats;
    newMovie->next = NULL;
    return newMovie;
}


void displayMovies() {
    Movie* current = movieList;
    printf("Available Movies:\n");                                   // Function to display the list of available movies
    while (current != NULL) {
        printf("Movie ID: %d, Title: %s, Available Seats: %d\n", current->movieID, current->title, current->availableSeats);
        current = current->next;
    }
}


Booking* createBooking(int movieID, int numTickets) {
    Booking* newBooking = (Booking*)malloc(sizeof(Booking));
    static int bookingIDCounter = 1;
    newBooking->bookingID = bookingIDCounter++;                       // Function to create a new booking
    newBooking->movieID = movieID;
    newBooking->numTickets = numTickets;
    newBooking->next = NULL;
    return newBooking;
}


void displayBookings() {
    StackNode* current = top;
    printf("Booked Tickets:\n");
    while (current != NULL) {                                      // Function to display the list of bookings
        Booking* booking = current->booking;
        printf("Booking ID: %d, Movie ID: %d, Num Tickets: %d\n", booking->bookingID, booking->movieID, booking->numTickets);
        current = current->next;
    }
}

int main() {
    movieList = createMovieNode("Avengers: Endgame", 100);
    movieList->next = createMovieNode("Fast and Furious 49", 150);
    movieList->next->next = createMovieNode("The Founder", 75);

    int choice;
    int movieID, numTickets;

    while (1) {
        printf("Movie Ticket Booking System\n");
        printf("1. Display Available Movies\n");
        printf("2. Book Tickets\n");
        printf("3. Display Booked Tickets\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMovies();
                break;
            case 2:
                displayMovies();
                printf("Enter Movie ID: ");
                scanf("%d", &movieID);
                printf("Enter the number of tickets: ");
                scanf("%d", &numTickets);
                Movie* selectedMovie = movieList;
                while (selectedMovie != NULL && selectedMovie->movieID != movieID) {
                    selectedMovie = selectedMovie->next;
                }
                if (selectedMovie == NULL) {
                    printf("Movie not found with the specified ID.\n");
                } else if (selectedMovie->availableSeats >= numTickets) {
                    Booking* newBooking = createBooking(movieID, numTickets);
                    push(newBooking);
                    selectedMovie->availableSeats -= numTickets;
                    printf("Tickets booked successfully!\n");
                } else {
                    printf("Not enough available seats for this movie.\n");
                }
                break;
            case 3:
                displayBookings();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
