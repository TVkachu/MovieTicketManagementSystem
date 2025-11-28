#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

typedef enum {Economy, Premium, Luxury} seatType;

typedef struct {

    bool isBooked;
    float price;
    char whoBooked[64];
    char password[16];
    seatType type;


} movieSeat;

void welcomeScreenPrinter();
void mainMenuPrinter();
void seatMapPrinter(movieSeat theatre[][10]);

int main() {

    int choice, i, j;
    movieSeat theatre[10][10] = {};
    FILE *fp;

    fp = fopen("seatMovie.dat", "rb");

    if (fp) {
        fread(theatre, sizeof(movieSeat), 10*10, fp);
        fclose(fp);
    }

    else {

        for (i = 0; i < 10; i++) {

            for (j = 0; j < 10; j++) {

                if (i < 4) {

                    theatre[i][j].price = 1000.0;

                }

                else if (i >= 4 && i < 7) {

                    theatre[i][j].price = 2500.0;
                    theatre[i][j].type = Premium;

                }

                else {

                    theatre[i][j].price = 5000.0;
                    theatre[i][j].type = Luxury;

                }


            }

        }

    }

    welcomeScreenPrinter();

    do {

        mainMenuPrinter();
        printf("Enter the corresponding serial number here: ");
        scanf("%d", &choice);
        printf("\n");

        if (choice == 1) {

            seatMapPrinter(theatre);

        }

        else if (choice == 2) {

            do {

                int row;
                char col;

                seatMapPrinter(theatre);

                printf("Please enter the seat to book (eg. 'C2') or Q0 to cancel: ");
                scanf(" %c%d", &col, &row);

                if (col == 'Q') {

                    break;

                }

                if (row < 0 || row > 9 || col < 'A' || col > 'J') {

                    printf("Please enter valid seat ID.\n");
                    continue;

                }

                else if (theatre[row][(int)col-65].isBooked) {

                    printf("Sorry! That seat has already been booked by %s. Please choose a different seat!\n", theatre[row][col-65].whoBooked);
                    continue;
                }

                else {

                    printf("Please provide your name to proceed with the booking: ");
                    getchar();
                    fgets(theatre[row][col-65].whoBooked, sizeof(theatre[row][col-65].whoBooked), stdin);
                    theatre[row][col-65].whoBooked[strlen(theatre[row][col-65].whoBooked)-1] = '\0';
                    printf("\n");

                    printf("To confirm the booking, a password is required.\n");
                    printf("This password is required in case of cancellation of booking.\n");
                    printf("Please enter the password (MAX 15 CHARACTERS): ");
                    fgets(theatre[row][col-65].password, sizeof(theatre[row][col-65].password), stdin);
                    theatre[row][col-65].password[strlen(theatre[row][col-65].password)-1] = '\0';
                    printf("\n");

                    theatre[row][col-65].isBooked = 1;
                    printf("Booking successful! Please pay %.2f at the premises.\n", theatre[row][col-65].price);
                    break;

                }

            } while (1);
        }

        else if (choice == 3) {

            do {

                int row;
                char col, name[64], inputPassword[16];

                seatMapPrinter(theatre);

                printf("Please enter the seat to cancel (eg. 'C2') or Q0 to go back: ");
                scanf(" %c%d", &col, &row);
                getchar();

                if (col == 'Q') {

                    break;

                }

                if (row < 0 || row > 9 || col < 'A' || col > 'J') {

                    printf("Please enter valid seat ID.\n");
                    continue;

                }

                else if (theatre[row][(int)col-65].isBooked) {

                    do {
                        printf("For security reasons, please provide your name as entered during booking: ");
                        fgets(name, sizeof(name), stdin);
                        name[strlen(name)-1] = '\0';
                        printf("\n");

                        if (strcmp(name, theatre[row][(int)col-65].whoBooked)) {

                            printf("Entered name does NOT match. Please try again.\n");
                            continue;

                        }

                        else {

                            break;

                        }
                    } while (1);

                    do {
                        printf("Please enter the password for this booking: ");
                        fgets(inputPassword, sizeof(inputPassword), stdin);
                        inputPassword[strlen(inputPassword)-1] = '\0';
                        printf("\n");

                        if (strcmp(inputPassword, theatre[row][(int)col-65].password)) {

                            printf("Entered password does NOT match, cancellation request DENIED.\n");
                            break;

                        }

                        else {

                            strcpy(theatre[row][(int)col-65].whoBooked,"\0");
                            theatre[row][(int)col-65].isBooked = 0;
                            strcpy(theatre[row][(int)col-65].password, "\0");
                            printf("Your booking has been cancelled.\n");

                            break;

                        }


                    } while (1);


                }

                else {

                    printf("No booking found for this seat...\n");
                    continue;

                }



            } while(1);

        }

        else if (choice == 4) {

            break;

        }

        else {

            printf("Invalid choice! Please try again.\n");

        }

    } while(choice != 4);

    fp = fopen("seatMovie.dat", "wb");
    fwrite(theatre, sizeof(movieSeat), 10*10, fp);
    fclose(fp);


    printf("Thank you for using this program. Goodbye!\n");
    return 0;
}

void welcomeScreenPrinter() {

    int i;

    printf("\n==================================================\n");
    for (i = 0; i < 15; i++) {
        printf(" ");
    }
    printf("Movie Ticket Manager\n");
    printf("==================================================\n\n");


}

void mainMenuPrinter() {

    int i;

    printf("\n\n==================================================\n");
    for (i = 0; i < 20; i++) {
        printf(" ");
    }
    printf("Main Menu!\n");
    printf("1. View available seats...\n");
    printf("2. Book a Seat...\n");
    printf("3. Cancel a Booking...\n");
    printf("4. Save and Exit...\n");
    printf("==================================================\n\n");



}

void seatMapPrinter(movieSeat theatre[][10]) {

    int i, j;
    char ch;

    printf("\n");
    for (i = 0; i < 35; i++) {

        printf(" ");

    }

    printf("! THE SCREEN IS THIS WAY !\n\n");

    for (i = 0; i < 10; i++) {

        for (j = 0; j < 10; j++) {

            if (j == 5) {

                printf("\t");

            }

            if (theatre[i][j].isBooked) {

                printf("\tx");

            }

            else {

                printf("\t.");

            }

            if (j == 9) {

                printf("\t%d", i);

            }

        }

        printf("\n\n");

    }

    printf("\n");

    for (ch = 'A'; ch < 'K'; ch++) {

        if (ch == 'F') {

            printf("\t");

        }

        printf("\t%c", ch);

    }

    printf("\n");



}


