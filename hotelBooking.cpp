#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

class ClientFileManager
{
private:
    string fileName;
    int count = 0;
    string phn;
    fstream clientFile;

public:
    ClientFileManager(const string &fileName)
    {
        this->fileName = fileName;
    };

    virtual string checkClient(const string &targetPhn)
    {
        clientFile.open(fileName, ios::in);
        if (!clientFile.is_open())
        {
            cout << "Failed to open the Client File" << endl;
            return "Failed to open the Client File";
        }

        // using vector to get a line at a time
        vector<string> row;
        string line;

        while (getline(clientFile, line)) // Read line by line
        {
            row.clear();
            stringstream s(line);

            // get the data splitting by comma from the line
            string word;
            while (getline(s, word, ','))
            {
                row.push_back(word);
            }

            // Check if the phone number matches
            if (row.size() > 2 && targetPhn == row[2])
            {
                // printing the client data
                count = 1;
                clientFile.close(); // Close the file before returning
                return "Client Id: " + row[0] + "\n" +
                       "Client Name: " + row[1] + "\n" +
                       "Client Phone No: " + row[2] + "\n" +
                       "Client Address: " + row[3] + "\n" +
                       "Client Aadhar Number: " + row[4] + "\n";
            }
        }

        // if the client isn't registered
        if (count == 0)
        {
            clientFile.close(); // Close the file
            return "Client not registered!\n";
        }

        clientFile.close(); // Close the file
    }

    string registerClient(int clientId, const string &clientName, const string &clientPhoneNo, const string &clientAddress, const string &clientAadhar)
    {
        clientFile.open(fileName, ios::app | ios::out);
        if (!clientFile.is_open())
        {
            cout << "Failed to open the Client File" << endl;
        }

        clientFile << clientId << ","
                   << clientName << ","
                   << clientPhoneNo << ","
                   << clientAddress << ","
                   << clientAadhar << "\n";

        clientFile.close();

        // Return the client details as a string
        return "Client ID: " + to_string(clientId) + "\n" +
               "Client Name: " + clientName + "\n" +
               "Client Phone No: " + clientPhoneNo + "\n" +
               "Client Address: " + clientAddress + "\n" +
               "Client Aadhar Number: " + clientAadhar + "\n";
    }

    ~ClientFileManager()
    {
        if (clientFile.is_open())
        {
            clientFile.close();
        };
    }
};
class Client
{
private:
    int clientId;
    string clientName;
    string clientPhoneNo;
    string clientAddress;
    string clientAadhar;
    string targetPhn;
    ClientFileManager *clientFileManager;

public:
    Client(const string &fileName)
    {
        clientFileManager = new ClientFileManager(fileName);
    }
    // Function to save client data to a file and return the details as a string

    void setTargetPhn(const string &targetPhn)
    {
        this->targetPhn = targetPhn;
    }

    virtual string isClientRegistered()
    {

        string result = clientFileManager->checkClient(targetPhn);
        cout << endl
             << result << endl;
        return result;
    }

    string save()
    {

        cout << "Enter Client ID: ";
        cin >> clientId;
        cout << "Enter Client Name: ";
        cin.ignore();
        getline(cin, clientName);
        cout << "Enter Client Phone No: ";
        cin >> clientPhoneNo;
        cout << "Enter Client Address: ";
        cin.ignore();
        getline(cin, clientAddress);
        cout << "Enter Client Aadhar Number: ";
        cin >> clientAadhar;

        if (ClientFileManager("client.csv").checkClient(clientPhoneNo) == "Client not registered!\n")
        {
            string savedClient = clientFileManager->registerClient(clientId, clientName, clientPhoneNo, clientAddress, clientAadhar);
            cout << endl
                 << "Client Registered Successfully!" << endl
                 << savedClient << endl;
        }
        else
        {
            cout << endl
                 << "Client Already Registered!" << endl;
        }
    }
    ~Client()
    {
        delete clientFileManager;
    }
};

class client_hotelroom : virtual public Client
{
};

int main()
{
    string targetPhn;
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
    Client *client;
    Client client1("client.csv");
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
        client = &client1;
        // exception handing if gives unnecessary inputs
        try
        {
            if (userInput == SEARCH_CLIENT)
            {
                cout << "Enter the phone number of the client to display details: ";
                cin >> targetPhn;
                client->setTargetPhn(targetPhn);
                string res = client->isClientRegistered();
                if (res == "Client not registered!\n")
                {
                    cout << "Please register yourself first!" << endl;
                    goto A;
                }
            }
            else if (userInput == REGISTER_CLIENT)
            {
                client->save();
            }
            else if (userInput == EXIT_PROGRAM)
            {
                cout << "Thank you for using our service!" << endl;
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
};