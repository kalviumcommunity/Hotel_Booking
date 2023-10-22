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
    fstream clientFile;
    string phn;

public:
    ClientFileManager(const string &fileName)
    {
        this->fileName = fileName;
    };

    virtual string checkClient(const string &targetPhn)
    {

        // opening the file
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
    int costCnt;
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

class Conventionhall : virtual public Client

{
private:
    string day;
    string time;
    string BookedBy;
    string targetDay;
    string targetTime;
    string res;
    int clientId;

public:
    Conventionhall() : Client("client.csv"){};

    ~Conventionhall(){};

    // check function to check if the hall is empty in the required time

    string checkConvention()
    {
        res = "Not booked";
        // opening the text file and taking necessary informations
        ifstream convntionalHallFile("conventionhall.txt");
        if (!convntionalHallFile)
            cout << endl
                 << "Unable to open conventionhall file" << endl;

        cout << endl
             << "Please enter the date(Ex: 22/10/2023):";
        cin >> targetDay;
        // If the required time exists then the result(res) will be changed to booked
        while (!convntionalHallFile.eof())
        {
            convntionalHallFile >> day >> time >> BookedBy;
            if (day == targetDay)
                res = "Booked";
        }

        convntionalHallFile.close();
        return res;
    };
    // updating the booking of the convention hall
    int bookConvention()
    {
        // taking necessary infos to book a time

        cout << "Please again enter the required date(Ex: 22/10/2023): ";
        cin >> targetDay;
        cout << endl
             << "Please enter the required time(Ex: 07:00 / 11:00): ";
        cin >> targetTime;
        cout << endl
             << "Please enter the client id: ";
        cin >> clientId;
        // calculating the cost
        costCnt += 20000;
        // opening the text file to append and returning the cost
        ofstream outf("conventionhall.txt", ios::app);
        outf << endl
             << targetDay << " " << targetTime << " " << clientId;
        outf.close();
        return costCnt;
    }
};

class cost : public Conventionhall
{
private:
    int paid;

public:
    cost() : Client("client.csv"), Conventionhall(){};
    void displayCost(int cost)
    {
        cout << endl
             << "Total cost:" << cost << endl;
        cout << endl
             << "How much amount you want to pay: ";
        cin >> paid;
        cout << endl
             << "Due Amount: " << cost - paid << endl;
    }
    // !need to implement this in future
    //  operator overloading to compute the cost
    //  cost operator-(cost c)
    //  {
    //      cost cost;
    //      cost.cost_cnt = c.cost_cnt - this->cost_cnt;
    //      return cost;
    //  }
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
    Conventionhall hall;
    cost c2;
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
                client = &hall;
                client->costCnt = 0;
                string res = hall.checkConvention();
                if (res == "Booked")
                {
                    cout << endl
                         << "Already Booked on this Date, Sorry!" << endl;
                    goto B;
                }
                cout << endl
                     << "Type 1 to book , Type 0 to not" << endl;
                cin >> userInput;
                if (userInput == 1)
                {
                    c2.displayCost(hall.bookConvention());
                    cout << endl
                         << "Convention Hall is successfully booked, Thank You!" << endl;
                }
                else if (userInput == 0)
                {
                    cout << "Thank you!" << endl;
                    goto B;
                }
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