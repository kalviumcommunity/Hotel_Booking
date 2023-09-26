#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

// base class
class client
{

public:
    // base class data members
    static int clientIdCount;
    int costCount;
    char clientType;

    // base class member functions

    void check()
    {
        fstream clientFile;

        int checkPhn, clientPhn, count = 0, phnLengthFlag = true;
        // Here searching if a client has is registered or not

        clientFile.open("client.csv", ios::in);

        cout << endl
             << "Enter the Phone No. of the Client to Display The Details:- ";
        cin >> checkPhn;
        if (to_string(checkPhn).length() < 10)
        {
            cout
                << endl
                << "Invalid phone number. Please enter a valid phone number with at least 10 digits." << endl;
        }
        cout << endl
             << "Will find your detaild in future, probably in my second milestone!" << endl;

        // Get the user details
        // TODO
        // end of getting user Details

        // if the client isn't registered
        if (count == 0 && !phnLengthFlag)
        {

            cout
                << endl
                << "Record not found" << endl;
            clientFile.close();
        }
    }

    int create()
    {
        fstream clientFile;

        // Getting the client information
        int clientId;
        string clientName;
        string clientPhoneNo;
        string clientAddress;
        string clientAadhar;

        cout << "Enter Client ID:";
        cin >> clientId;
        cout << endl
             << "Enter Client Name:";
        cin.ignore(); // Clear the newline character from the previous input
        getline(cin, clientName);
        cout << endl
             << "Enter Client Phone No:";
        cin >> clientPhoneNo;
        cout << endl
             << "Enter Client Address (Use '_' instead of spaces):";
        cin.ignore(); // Clear the newline character from the previous input
        getline(cin, clientAddress);
        cout << endl
             << "Enter Client Aadhar Number (Use '_' instead of spaces):";
        cin >> clientAadhar;

        clientFile.open("client.csv", ios::out | ios::app);

        if (!clientFile.is_open())
        {
            cout << "Failed to open the file for appending." << endl;
            return -1;
        }

        clientFile << clientId << ","
                   << clientName << ","
                   << clientPhoneNo << ","
                   << clientAddress << ","
                   << clientAadhar << "\n";

        clientFile.close();
        cout << endl
             << "Client Created with ClientID: " << clientId << endl;
        return clientId; // Return the client ID if successful
    }
};

int main()
{
    int userInput; // difining input variable
    int SEARCH_CLIENT = 1;
    int REGISTER_CLIENT = 2;
    int EXIT_PROGRAM = 0;
    // Still needed to make them functional in future, just defining them for now
    int HOTEL_BOOKING = 1;
    int CONVENTION_HALL_BOOKING = 2;
    int RESTAURANT_BOOKING = 3;
    int HOTEL_ROOM_CHECKOUT = 4;
    int RETURN_TO_MAIN_MENU = 0;

    // base class pointer and class objects
    client *cli;
    client newClient;
    // displaying the options
    while (true)
    {

        // options to create and check client id
    A:
        cout << endl
             << "Type 1 to Search for a Client Id" << endl
             << "Type 2 to Register Yourself" << endl
             << "Type 0 Exit" << endl;
        cin >> userInput;
        // base class pointer pointing to a base class object
        cli = &newClient;
        // exception handing if gives unnecessary inputs
        try
        {
            if (userInput == SEARCH_CLIENT)
            {
                cli->check();
            }
            else if (userInput == REGISTER_CLIENT)
            {
                cli->create();
            }
            else if (userInput == EXIT_PROGRAM)
            {
                cout << endl
                     << "Thank you for using our service!" << endl;
                break;
            }
            else
            {
                throw invalid_argument("Invalid input: " + to_string(userInput));
            }
        }
        catch (const invalid_argument &e)
        {
            cout << endl
                 << "Error: " << e.what() << endl
                 << "Please Try Again!" << endl;
            goto A;
        }

    B:
        cout << endl
             << "Type 1 to Book a Hotel Room" << endl
             << "Type 2 to Book Convention Hall" << endl
             << "Type 3 to Reserve Restaurant" << endl
             << "Type 4 to Checkout Hotel Room" << endl
             << "Type 0 to Return to Main Menu" << endl;
        cin >> userInput;
        // exception handing if gives unnecessary inputs
        // needed to be updated/implemented in future
        try
        {
            if (userInput == HOTEL_BOOKING)
            {
                cout << "Hotel Booking Coming soon!" << endl;
                goto B;
            }

            else if (userInput == CONVENTION_HALL_BOOKING)
            {
                cout << "Convention Hall Booking Coming soon!" << endl;
                goto B;
            }
            else if (userInput == RESTAURANT_BOOKING)
            {
                cout << "Restaurant Booking Coming soon!" << endl;
                goto B;
            }
            else if (userInput == HOTEL_ROOM_CHECKOUT)
            {
                cout << "Hotel Room Check out Coming soon!" << endl;
                goto B;
            }
            else if (userInput == RETURN_TO_MAIN_MENU)
            {
                cout << endl
                     << "Thank you! Returning to Main Menu" << endl;
                goto A;
            }
            else
            {
                throw invalid_argument("Invalid input: " + to_string(userInput));
            }
        }
        catch (const invalid_argument &e)
        {
            cout << endl
                 << "Error: " << e.what() << endl
                 << "Please Try Again!" << endl;
            goto B;
        }
    }
}