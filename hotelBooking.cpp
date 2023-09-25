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
    static int c_id_count;
    int cost_cnt;
    char c_type;
    // base class member functions

    void check()
    {
        int check_phn, c_phn, count = 0, phn_length_flag = true;
        // Here searching if a client has is registered or not
        fstream client_file;
        client_file.open("client.csv", ios::in);

        cout << endl
             << "Enter the Phone No. of the Client to Display The Details:- ";
        cin >> check_phn;
        if (to_string(check_phn).length() < 10)
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
        if (count == 0 && !phn_length_flag)
        {

            cout
                << endl
                << "Record not found" << endl;
        }
    }

    int create()
    {
        fstream client_file;

        // Getting the client information
        int c_id;
        string c_name;
        string c_phone_no;
        string c_address;
        string c_aadhar;

        cout << "Enter Client ID:";
        cin >> c_id;
        cout << endl
             << "Enter Client Name:";
        cin.ignore(); // Clear the newline character from the previous input
        getline(cin, c_name);
        cout << endl
             << "Enter Client Phone No:";
        cin >> c_phone_no;
        cout << endl
             << "Enter Client Address (Use '_' instead of spaces):";
        cin.ignore(); // Clear the newline character from the previous input
        getline(cin, c_address);
        cout << endl
             << "Enter Client Aadhar Number (Use '_' instead of spaces):";
        cin >> c_aadhar;

        client_file.open("client.csv", ios::out | ios::app);

        if (!client_file.is_open())
        {
            cout << "Failed to open the file for appending." << endl;
            return -1;
        }

        client_file << c_id << ","
                    << c_name << ","
                    << c_phone_no << ","
                    << c_address << ","
                    << c_aadhar << "\n";

        client_file.close();
        cout << endl
             << "Client Created with ClientID: " << c_id << endl;
        return c_id; // Return the client ID if successful
    }
};

int main()
{
    int userInput; // difining input variable

    // base class pointer and other class objects
    client *cli = new client;
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

        // exception handing if gives unnecessary inputs
        try
        {
            if (userInput == 1)
            {
                cli->check();
            }
            else if (userInput == 2)
            {
                cli->create();
            }
            else if (userInput == 0)
            {

                cout << endl
                     << "Thank you for using our service" << endl;
                delete cli;
                break;
            }
            else
                throw(userInput);
        }
        catch (...)
        {
            cout << endl
                 << "Typed Undisired Input!" << endl
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

        try
        {
            if (userInput == 1)
            {
                cout << "Hotel Booking Coming soon!" << endl;
                goto B;
            }

            else if (userInput == 2)
            {
                cout << "Convention Hall Booking Coming soon!" << endl;
                goto B;
            }
            else if (userInput == 3)
            {
                cout << "Restaurant Booking Coming soon!" << endl;
                goto B;
            }
            else if (userInput == 4)
            {
                cout << "Hotel Room Check out Coming soon!" << endl;
                goto B;
            }
            else if (userInput == 0)
            {
                cout << endl
                     << "Thank you! Returning to Main Menu" << endl;
                goto A;
            }
            else
                throw(userInput);
        }
        catch (...)
        {
            cout << endl
                 << "Typed Undisired Input!" << endl
                 << "Please Try Again!" << endl;
            goto B;
        }
    }
}