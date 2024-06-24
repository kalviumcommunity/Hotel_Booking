#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

class IClientManager {
public:
    virtual string checkClient(const string &targetPhn) = 0;
    virtual string registerClient(int clientId, const string &clientName, const string &clientPhoneNo, const string &clientAddress, const string &clientAadhar) = 0;
};

class ClientFileManager : public IClientManager
{
private:
    string fileName;
    int count;
    fstream clientFile;
    string phn;

public:
    ClientFileManager(const string &fileName)
    {
        this->fileName = fileName;
    };

    virtual string checkClient(const string &targetPhn) override
    {
        count = 0;
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

    string registerClient(int clientId, const string &clientName, const string &clientPhoneNo, const string &clientAddress, const string &clientAadhar) override
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
    static const int ARRAY_SIZE = 5;
    ClientFileManager *clientFileManager[ARRAY_SIZE];

public:
    int costCnt;
    Client(const string &fileName)
    {
        clientFileManager[0] = new ClientFileManager(fileName); // Initialize the first element
        for (int i = 1; i < ARRAY_SIZE; ++i)
        {
            clientFileManager[i] = nullptr; // Initialize other array elements to null
        }
    }
    // Function to save client data to a file and return the details as a string

    void setTargetPhn(const string &targetPhn)
    {
        this->targetPhn = targetPhn;
    }

    virtual string isClientRegistered()
    {

        string result = clientFileManager[0]->checkClient(targetPhn);
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
            string savedClient = clientFileManager[0]->registerClient(clientId, clientName, clientPhoneNo, clientAddress, clientAadhar);
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
        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            delete clientFileManager[i]; // Release memory for each object
        }
    }
};

class Hotelroom : virtual public Client
{
private:
    int roomId;
    string roomType;
    string roomBooked;
    int targetRoomId;
    int cId;
    string clientId;

public:
    Hotelroom() : Client("client.csv"){};

    ~Hotelroom(){};
    // extented check function to check if a hotel room is vacant
    void checkHotelRooms()
    {
        // opening txt file to read
        ifstream hotelRoomFile("hotelroom.txt");

        // if the text file is not available
        if (!hotelRoomFile)
        {
            cout << endl
                 << "Unable to open hotelroom file" << endl;
            return;
        }

        cout << endl
             << "hotelrooms to book:" << endl;

        // reading the whole file to print available hotel rooms
        while (hotelRoomFile >> roomId >> roomType >> roomBooked)
        {
            if (roomBooked == "NULL")
                cout << roomId << " " << roomType << endl;
        }

        // Check if the last read was successful (optional)
        if (!hotelRoomFile.eof() && roomBooked == "NULL")
        {
            cout << roomId << " " << roomType << endl;
        }

        // closing the file
        hotelRoomFile.close();
    }
    // extented update funtion to book a hotel room
    int bookHotelRoom()
    {
        // taking the information to book a definite room
        cout << "Please enter the required room id: ";
        cin >> targetRoomId;
        cout << "Please enter the client id: ";
        cin >> cId;

        // changing the int c_id to string client_id to compare
        stringstream ss;
        ss << cId;
        clientId = ss.str();

        // opening the text file to read and append
        ifstream hotelRoomFile1("hotelroom.txt");
        ofstream hotelRoomFile2("hotelroom1.txt");

        if (!hotelRoomFile1)
        {
            cout << endl
                 << "Unable to open hotelroom file" << endl;
            return 0; // or another appropriate value indicating an error
        }

        int roomId;
        string roomType;
        string roomBooked;

        // taking all the data to book the required room
        while (hotelRoomFile1 >> roomId >> roomType >> roomBooked)
        {
            if (roomId == targetRoomId)
            {
                // using the base class data member to calculate client's cost
                costCnt += 1000;
                cout << roomId << " " << roomType << endl;
                // updating the room id with client_id to make it booked
                hotelRoomFile2 << roomId << " " << roomType << " " << clientId << endl;
            }
            else
            {
                // if it isn't the required room then simply rewriting it
                hotelRoomFile2 << roomId << " " << roomType << " " << roomBooked << endl;
            }
        }

        // closing the two files to save update
        hotelRoomFile2.close();
        hotelRoomFile1.close();

        // deleting previous text file then renaming the updated text file to replace the previous one
        remove("hotelroom.txt");
        rename("hotelroom1.txt", "hotelroom.txt");

        // return the cost of the client
        return costCnt;
    }
    // checkout a booked room to make it available again
    void checkout()
    {
        // getting necessary infos and changing to string
        cout << "Please enter the client id:";
        cin >> cId;

        string clientId;
        stringstream ss;
        ss << cId;
        clientId = ss.str();

        // read & write the text file
        ifstream hotelRoomFile1("hotelroom.txt");
        ofstream hotelRoomFile2("hotelroom1.txt");

        if (!hotelRoomFile1 || !hotelRoomFile2)
        {
            cout << endl
                 << "Unable to open hotelroom file" << endl;
            return;
        }

        int roomId;
        string roomType;
        string roomBooked;

        // updating the rooms which the client holds to make them available
        while (hotelRoomFile1 >> roomId >> roomType >> roomBooked)
        {
            if (roomBooked == clientId)
            {
                cout << endl
                     << "Checking Out all Rooms Booked By you!" << endl
                     << roomId << " " << roomType << endl;
                hotelRoomFile2 << roomId << " " << roomType << " "
                               << "NULL" << endl;
            }
            else
            {
                hotelRoomFile2 << roomId << " " << roomType << " " << roomBooked << endl;
            }
        }

        // closing the file
        hotelRoomFile1.close();
        hotelRoomFile2.close();

        // replacing the previous file
        remove("hotelroom.txt");
        rename("hotelroom1.txt", "hotelroom.txt");
    }
};

class Restaurant : virtual public Client
{
private:
    string day;
    string time;
    string resBook;
    string targetDay;
    string targetTime;
    string res;
    string clientId;

public:
    Restaurant() : Client("client.csv"){};

    ~Restaurant(){};
    // check if the restaurant is booked or not
    string checkRestaraunt()
    {
        res = "Not booked";
        // input the necessary infos
        ifstream restarauntFile("restaurant.txt");
        if (!restarauntFile)
        {
            cout << endl
                 << "Unable to open Restaurant file" << endl;
        }
        cout << endl
             << "Please enter the date(Ex: 01/11/2023):";
        cin >> targetDay;
        cout << endl
             << "Please enter the time(Ex: 07:00):";
        cin >> targetTime;
        // comparing with the required time and giving result
        while (!restarauntFile.eof())
        {
            restarauntFile >> day >> time;
            if (day == targetDay && time == targetTime)
                res = "Booked";
        }

        restarauntFile.close();
        return res;
    }
    // booking the restaurant
    int bookRestaraunt()
    {
        // taking necessary data
        cout << "Please again enter the required date(Ex: 22/10/2023): ";
        cin >> targetDay;
        cout << "Please enter the required time(Ex: 07:00 / 11:00): ";
        cin >> targetTime;
        cout << "Please enter the Client id: ";
        cin >> clientId;
        // cost count
        costCnt += 200;
        // write the text file and returning cost
        ofstream restarauntFile("restaurant.txt", ios::app);
        restarauntFile << endl
                       << targetDay << " " << targetTime << " " << clientId;
        restarauntFile.close();
        return costCnt;
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
             << "Please enter the Client id: ";
        cin >> clientId;
        // calculating the cost
        costCnt += 20000;
        // opening the text file to append and returning the cost
        ofstream convntionalHallFile("conventionhall.txt", ios::app);
        convntionalHallFile << endl
                            << targetDay << " " << targetTime << " " << clientId;
        convntionalHallFile.close();
        return costCnt;
    }
};

class cost : public Conventionhall, public Restaurant
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
    //      cost.costCnt = c.costCnt - this->costCnt;
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
    Hotelroom h1;
    Conventionhall hall;
    Restaurant restaurant;
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
                {
                    client = &h1;
                    client->costCnt = 0;
                    h1.checkHotelRooms();
                    cout << endl
                         << "Type 1 to checkin , Type 0 to not" << endl;
                    cin >> userInput;
                    if (userInput)
                    {
                        int i, d;
                        cout << endl
                             << "How many rooms do you need?" << endl;
                        cin >> i;
                        while (i--)
                            d = h1.bookHotelRoom();
                        c2.displayCost(d);
                    }
                }
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
                client = &restaurant;
                client->costCnt = 0;
                string res = restaurant.checkRestaraunt();
                if (res == "Booked")
                {
                    cout << endl
                         << "Already Booked on this Date and Time, Sorry!" << endl;
                    goto B;
                }
                cout << endl
                     << "Type 1 to book , Type 0 to not" << endl;
                cin >> userInput;
                if (userInput == 1)
                {
                    c2.displayCost(restaurant.bookRestaraunt());
                    cout << endl
                         << "Restraunt is successfully reserved, Thank You!" << endl;
                }
                else if (userInput == 0)
                {
                    cout << "Thank you!" << endl;
                    goto B;
                }
            }
            else if (userInput == HOTEL_ROOM_CHECKOUT)
            {
                h1.checkout();
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