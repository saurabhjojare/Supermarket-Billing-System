#include<iostream>
#include<fstream>

using namespace std;

class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
m:
    int choice;
    string email;
    string password;

    cout << "Supermarket Main Menu\n";
    cout << "1) Administrator \n";
    cout << "2) Buyer         \n";
    cout << "3) Exit          \n";
    cout << "Please Select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\nPlease Login\n";
        cout << "Enter Email: ";
        cin >> email;
        cout << "Password: ";
        cin >> password;

        if (email == "saurabh@gmail.com" && password == "saurabh@123")
        {
            administrator();
        }
        else
        {
            cout << "Invalid email/password";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
        cout << "Please Select From The Given Options";
    }

    goto m;
}

void shopping::administrator()
{
m:
    int choice;
    cout << "\nAdministrator Menu\n";
    cout << "1) Add the product\n";
    cout << "2) Modify the product\n";
    cout << "3) Delete the product\n";
    cout << "4) Back to the Menu\n";
	cout << "5) Exit\n";
	
    cout << "\nPlease Enter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;
        
    case 5:
        exit(0);
        break;

    default:
        cout << "Invalid Choice";
    }

    goto m;
}

void shopping::buyer()
{
m:
    int choice;
    cout << "\nBuyer Menu\n";
    cout << "1) Buy product\n";
    cout << "2) Back to the Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Invalid Choice";
    }

    goto m;
}

void shopping::add()
{
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\nAdd new product\n";
    cout << "Enter the product code: ";
    cin >> pcode;

    cout << "Name of the product: ";
    cin >> pname;
    cout << "Price of the product: ";
    cin >> price;
    cout << "Discount on product: ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data)
    {
        // If the file doesn't exist, create and insert the record
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
        cout << "Record Inserted\n";
    }
    else
    {
        // Check if the product code already exists
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (c == pcode)
            {
                cout << "Product code already exists. Record not inserted.\n";
                data.close();
                return; // Exit the function if the product code exists
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        // If product code doesn't exist, insert the record
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
        cout << "Record Inserted\n";
    }
}


void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\nModify the record\n";
    cout << "Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File Doesn't Exist\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "New Code: ";
                cin >> c;
                cout << "New Name: ";
                cin >> pname;  // Update the variable with the new name
                cout << "Price: ";
                cin >> p;
                cout << "Discount: ";
                cin >> d;
                data1 << " " << c << " " << pname << " " << p << " " << d << "\n";  // Use the updated variable
                cout << "Record Edited\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "Record not found\n";
        }
    }
}


void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\nDelete product\n";
    cout << "Enter the product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist\n";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "Product deleted successfully\n";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "Record not found\n";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\nProduct No\tName\t\tPrice\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float total = 0;

    cout << "\nReceipt\n";
    data.open("database.txt", ios::in);

    if (!data)
    {
        cout << "Empty Database\n";
    }
    else
    {
        data.close();
        list();

        cout << "\nPlace the order\n";

        do
        {
        m:
            cout << "\nEnter Product Code: ";
            cin >> arrc[c];
            cout << "Enter the quantity: ";
            cin >> arrq[c];

            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\nDuplicate product code.\n";
                    goto m;
                }
            }

            c++;
            cout << "\nDo you want to buy another product or not?\nIf yes then press y else n: ";
            cin >> choice;

        } while (choice == 'y');

        cout << "\nReceipt\n";
        cout << "Product No\tProduct Name\tQuantity\tPrice\t\tDiscount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;

            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    float productDiscount = amount * dis / 100; // Calculate discount for each product
                    total += (amount - productDiscount);

                    cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << productDiscount << "\n";
                }

                data >> pcode >> pname >> price >> dis;
            }

            data.close();
        }
    }

    cout << "\nTotal Amount: " << total << "\n";
}


int main()
{
    shopping s;
    s.menu();
}

