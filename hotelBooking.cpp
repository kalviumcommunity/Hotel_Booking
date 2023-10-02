#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Client
{
private:
    int clientId;
    string clientName;
    string clientPhoneNo;
    string clientAddress;
    string clientAadhar;

public:
    // Constructor to initialize client data
    Client(int clientId, string clientName, string clientPhoneNo, string clientAddress, string clientAadhar)
    {
        this->clientId = clientId;
        this->clientName = clientName;
        this->clientPhoneNo = clientPhoneNo;
        this->clientAddress = clientAddress;
        this->clientAadhar = clientAadhar;
    }

    // Function to save client data to a file and return the details as a string
    string save(const string &fileName)
    {
        ofstream clientFile(fileName, ios::out | ios::app); // Open the file in append mode

        if (!clientFile.is_open())
        {
            return "Failed to open the file for appending.";
        }

        clientFile << clientId << ","
                   << clientName << ","
                   << clientPhoneNo << ","
                   << clientAddress << ","
                   << clientAadhar << "\n";

        clientFile.close();

        // Return the client details as a string
        return "Client data saved to " + fileName + "\n" + "\n" +
               "Client ID: " + to_string(this->clientId) + "\n" +
               "Client Name: " + this->clientName + "\n" +
               "Client Phone No: " + this->clientPhoneNo + "\n" +
               "Client Address: " + this->clientAddress + "\n" +
               "Client Aadhar Number: " + this->clientAadhar + "\n";
    }
};

int main()
{
    int clientId;
    string clientName;
    string clientPhoneNo;
    string clientAddress;
    string clientAadhar;

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

    // Create a Client object
    Client newClient(clientId, clientName, clientPhoneNo, clientAddress, clientAadhar);

    // Save client data to a file and get the details as a string
    string result = newClient.save("client.csv");

    // Display the result
    cout << result << endl;

    return 0;
}
