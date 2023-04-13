#include<iostream>
#include<fstream>
#include<sstream>
#include<string>


using namespace std;

void ViewProduct();
void AddOrder();
int main();

// BOOLEAN METHODS 

bool islogged(string CustomerName,string CustomerPassword)
{
      ifstream file;
      file.open("login.txt");
      string s1=CustomerName+","+CustomerPassword;
      string s2;
      while(getline(file,s2))
      {
          if(s2==s1)
          {
              return true;
          }
      }
      return false;
}

bool CheckWord(string filename, string search)
{
    int offset; 
    string line;
    ifstream Myfile;
    Myfile.open (filename);

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
                cout << "Aleady exists, try again later."<<endl;
                Myfile.close();
                exit(1);
            }
        }
        Myfile.close();
    }

    return false;
}


// CLASSES // 

class Admin;
class Customer;


class Customer {

public:

    void CustomerMenu()
    {
    int choice;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter Choice: ";

        cin>>choice;
        cout<<endl;

        switch(choice)
        {
                case 1:
                    CustomerLogin();
                    break;
                case 2:
                    AddCustomer();
                    break;
                case 3:
                    exit(1);
                    break;
                default:
                    system("cls");
                    cout<<"Invalid input, try again!\n"<<endl; 
                    main();
        }
    }

    void AddCustomer()
    {   
        ofstream input, info;

        // OPENING FILES IN APPEND MODE
        input.open("login.txt",ios::app);
        info.open("info.txt",ios::app);

            if (!input.is_open()) 
            {cout<<"File Empty!";}

            while ((getchar()) != '\n');

            cout<<"Customer Name: ";
            getline(cin, CustomerName); 

            cout<<"Customer Password: ";
            getline(cin, CustomerPassword); 

            cout<<"Customer ID: ";
            getline(cin, CustomerID);
            CheckWord("info.txt", CustomerID);
            
            cout<<"Customer Address: ";
            getline(cin, CustomerAddress);

            cout << "Customer Number: ";
            getline(cin, CustomerNumber);


            //  STORING IN INFO.TXT 
            info<<CustomerName; 
            info<<',';           
            info<<CustomerID;
            info<<',';    
            info<<CustomerAddress;
            info<<',';    
            info<<CustomerNumber;
            info<<'\n';

            // STORING IN LOGIN.TXT
            input<<CustomerName; 
            input<<','; 
            input<<CustomerPassword;
            input<<'\n';             

            // CLOSING FILES
            input.close(); 
            info.close();
    }

    void ViewCustomer()
    {
        string line;
        fstream myFileStream("info.txt");
        while(getline(myFileStream, line))
        {
            stringstream ss(line);
            getline(ss,CustomerName, ',');
            getline(ss,CustomerID,',');
            getline(ss,CustomerAddress,',');
            getline(ss,CustomerNumber,',');

            if(CustomerName != "" && CustomerID != "" && CustomerAddress != "" && CustomerNumber != "")
            {
            cout 
            << "\nCustomer Name: "      << CustomerName 
            << "\nCustomer ID: "        << CustomerID 
            << "\nCustomer Address: "   << CustomerAddress 
            << "\nCustomer Number: "    << CustomerNumber
            << "\n\n" << endl;
            }
        }
    }

    void CustomerLogin()
    {   
        int loop = 0;
            while (loop == 0)
            {
                while ((getchar()) != '\n');
                cout<<"Enter Username: "<<endl;
                getline(cin, CustomerName);

                cout<<"Enter Password: "<<endl;
                getline(cin, CustomerPassword);

                bool check=islogged(CustomerName,CustomerPassword); // CHECK USER AND PASS COMBINATION
                    if(check)
                    {
                        cout<<"\n Welcome to your account, "<<CustomerName<<endl;
                        CustomerFunction(); // CONTINUE TO CUSTOMER FUNCTIONALITIES
                    }
                    else
                    {
                        cout<<"! Wrong Login username and password"<<endl;
                        return;
                    }
            }


    }
    
    void SearchCustomer()
    {
        ifstream MyFile("info.txt");
        string search, line;
        int offset;

        cout << "Input Customer ID: ";
        cin >> search;

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                        stringstream ss(line);
                        getline(ss,CustomerName, ',');
                        getline(ss,CustomerID,',');
                        getline(ss,CustomerAddress,',');
                        getline(ss,CustomerNumber,',');

                        cout 
                        << "\nCustomer Name: "      << CustomerName 
                        << "\nCustomer ID: "        << CustomerID 
                        << "\nCustomer Address: "   << CustomerAddress 
                        << "\nCustomer Number: "    << CustomerNumber
                        << "\n\n" << endl;
                }
            }
        }
        MyFile.close();
    }

    void EditCustomer()
    {
        fstream filetemp;
        ifstream MyFile("info.txt");

        string search,line;
        int offset;
        char flag='n';

        filetemp.open("temp.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Customer ID: ";
        cin >> search;
        // CheckWord("info.txt",search);

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                        stringstream ss(line);
                        getline(ss,CustomerName, ',');
                        getline(ss,CustomerID,',');
                        getline(ss,CustomerAddress,',');
                        getline(ss,CustomerNumber,'\n');

                        cout 
                        << "\nCustomer Name: "      << CustomerName 
                        << "\nCustomer ID: "        << CustomerID 
                        << "\nCustomer Address: "   << CustomerAddress 
                        << "\nCustomer Number: "    << CustomerNumber 
                        << "\n\n" << endl;
                        flag='y';
                        line="";
                }
                filetemp<<line<<endl;
            }
        }

        if (flag=='n')
        {
            filetemp<<line<<endl;
        }
        if (flag=='y')
        {
            while ((getchar()) != '\n');

            cout<<"Customer Address: ";
            getline(cin,CustomerAddress);

            cout<<"Customer Number: ";
            getline(cin,CustomerNumber);

            filetemp<<CustomerName<<","<<CustomerID<<","<<CustomerAddress<<","<<CustomerNumber<<endl;
            flag='n';
            cout << "Record editted succesfully!" <<endl;
        }
    MyFile.close();
    filetemp.close();
    remove("info.txt");
    rename("temp.txt","info.txt");
    }

    void DeleteCustomer()
    {
        fstream filetemp, filetemptwo;
        ifstream MyFile("info.txt");
        ifstream OtherFile("login.txt");

        string search,line,linetwo;
        int offset;
        char flag='n';

        filetemp.open("Temp.txt",ios :: in|ios::out|ios::trunc);
        filetemptwo.open("Temptwo.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Customer ID: ";
        cin >> search;

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                        stringstream ss(line);
                        getline(ss,CustomerName, ',');
                        getline(ss,CustomerID,',');
                        getline(ss,CustomerAddress,',');
                        getline(ss,CustomerNumber,',');

                        cout 
                        << "\nCustomer Name: "      << CustomerName 
                        << "\nCustomer ID: "        << CustomerID 
                        << "\nCustomer Address: "   << CustomerAddress
                        << "\nCustomer Number: "    << CustomerNumber
                        << "\n\n" << endl;
                        line="";
                }
                filetemp<<line<<endl;
            }
        }

            if(OtherFile.is_open())
            {
                while (!OtherFile.eof())
                {
                    getline(OtherFile,linetwo);
                    if((offset = linetwo.find(CustomerName,0) != string::npos))
                    {
                            stringstream ss(linetwo);
                            getline(ss,CustomerName, ',');
                            getline(ss,CustomerPassword,',');
                            linetwo="";
                    }
                    filetemptwo<<linetwo<<endl;
                }
            }
        


    MyFile.close();
    OtherFile.close();
    filetemp.close();
    filetemptwo.close();

    remove("login.txt");
    rename("Temptwo.txt","login.txt");

    remove("info.txt");
    rename("Temp.txt","info.txt");

    }

    void CustomerFunction();
    
private:
    string CustomerName;
    string CustomerID;
    string CustomerAddress;
    string CustomerNumber;
    string CustomerPassword;
    friend class Admin;
    friend class Order;
};

class Product {

public:

    void AddProduct() {
        ofstream input;
        input.open("products.txt",ios::app);

        while ((getchar()) != '\n');

        cout << "Enter Product Name: ";
        getline(cin, ProductName);
        CheckWord("products.txt", ProductName);

        cout << "Enter Product ID: ";
        getline(cin, ProductID);
        CheckWord("products.txt", ProductID);


        do 
        {
        cout << "Enter Product Type, 1. Fragile 2. Non-Fragile\n";
        cout << "Choice: ";
        getline(cin, ProductType);
        }while (ProductType != "1" && ProductType != "2"); // Validation

  
        cout << "Enter Product Price: ";
        cin >> ProductPrice;
       
    
        if (ProductType == "1") 
        {
            ProductType  = "Fragile";
        }
        else if (ProductType == "2") 
        {
            ProductType  = "Non-Fragile";
        }

        while ((getchar()) != '\n');
        cout << "Enter Product Description: ";
        getline(cin, ProductDescription);

            input<<ProductName; 
            input<<','; 
         
            input<<ProductID;
            input<<','; 

            input<<ProductPrice;
            input<<','; 

            input<<ProductType;
            input<<',';

            input<<ProductDescription;
            input<<'\n';

            input.close(); 

        cout << "Product Recorded!" << endl << endl;
       // ShowMenu();
        
    }
     
    void ViewProduct() 
    {
        string line;
        string tempString = "";
        fstream myFileStream("products.txt");
        while(getline(myFileStream, line))
        {
            stringstream ss(line);
            getline(ss,ProductName, ',');
            getline(ss,ProductID,',');
            getline(ss,tempString,','); 
            ProductPrice = atoi(tempString.c_str());
            getline(ss,ProductType,',');
            getline(ss,ProductDescription,',');

            if(ProductName != "" && ProductID != "" && ProductType != "" && ProductDescription != "")
            {
                    cout
                    << "\nProduct Name: "           << ProductName 
                    << "\nProduct ID: "             << ProductID 
                    << "\nProduct Price: "          << ProductPrice 
                    << "\nProduct Type: "           << ProductType 
                    << "\nProduct Description: "    << ProductDescription << "\n\n" << endl;
            }
        }
        myFileStream.close();
    }

    void SearchProduct()
    {
        ifstream MyFile("products.txt");
        string search, line;
        int offset;

        cout << "Input Product ID: ";
        cin >> search;
        

        string tempString = "";

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,ProductName, ',');
                    getline(ss,ProductID,',');
                    getline(ss,tempString,','); // EDIT THIS
                    ProductPrice = atoi(tempString.c_str());
                    getline(ss,ProductType,',');
                    getline(ss,ProductDescription,',');

            if(ProductName != "" && ProductID != "" && ProductType != "" && ProductDescription != "")
            {
                    cout 
                    << "\nProduct Name: "           << ProductName 
                    << "\nProduct ID: "             << ProductID 
                    << "\nProduct Price: "          << ProductPrice 
                    << "\nProduct Type: "           << ProductType 
                    << "\nProduct Description: "    << ProductDescription << "\n\n" << endl;
            }

                }
            }
        }
        MyFile.close();
    }

    void EditProduct()
    {
        fstream filetemp;
        ifstream MyFile("products.txt");

        string search,line,tempString;
        int offset;
        char flag='n';

        filetemp.open("Temp.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Product ID: ";
        cin >> search;
        CheckWord("product.txt",search);

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                        stringstream ss(line);
                        getline(ss,ProductName, ',');
                        getline(ss,ProductID,',');
                        getline(ss,tempString,','); 
                        ProductPrice = atoi(tempString.c_str());
                        getline(ss,ProductType,',');
                        getline(ss,ProductDescription,',');

                        cout 
                        << "\nProduct Name: "           << ProductName 
                        << "\nProduct ID: "             << ProductID 
                        << "\nProduct Price: "          << ProductPrice
                        << "\nProduct Type: "           << ProductType 
                        << "\nProduct Description: "    << ProductDescription 
                        << "\n\n" << endl;
                        flag='y';
                        line="";
                }
                filetemp<<line<<endl;
            }
        }
        if (flag=='n')
        {
            filetemp<<line<<endl;
        }
        else if (flag=='y')
        {
            while ((getchar()) != '\n');
            cout<<"Product Name: ";
            getline(cin,ProductName);

            do 
            {
            cout << "Enter Product Type, 1. Fragile 2. Non-Fragile\n";
            cout << "Choice: ";
            cin>>ProductType;
            }while (ProductType != "1" && ProductType != "2"); // Validation

            if (ProductType == "1") 
            {
                ProductType  = "Fragile";
            }
            else if (ProductType == "2") 
            {
                ProductType  = "Non-Fragile";
            }


            while ((getchar()) != '\n');
            cout<<"Product ID: ";
            getline(cin,ProductID);
            CheckWord("products.txt",ProductID);

            cout<<"Description: ";
            getline(cin,ProductDescription);


            cout<<"Price: ";
            cin>>ProductPrice;

            filetemp<<ProductName<<","<<ProductID<<","<<ProductPrice<<","<<ProductType<<","<<ProductDescription<<"\n"<<endl;
             cout << "Product Editted!" << endl << endl;
            flag='n';
        }
    MyFile.close();
    filetemp.close();
    remove("products.txt");
    rename("Temp.txt","products.txt");
    }

    void DeleteProduct()
    {
        fstream filetemp;
        ifstream MyFile("products.txt");

        string search,line,tempString;
        int offset;
        char flag='n';

        filetemp.open("Temp.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Product ID: ";
        cin >> search;

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                        stringstream ss(line);
                        getline(ss,ProductName, ',');
                        getline(ss,ProductID,',');
                        getline(ss,tempString,','); 
                        ProductPrice = atoi(tempString.c_str());
                        getline(ss,ProductType,',');
                        getline(ss,ProductDescription,',');

                        cout 
                        << "\nProduct Name: "           << ProductName 
                        << "\nProduct ID: "             << ProductID 
                        << "\nProduct Price: "          << ProductPrice
                        << "\nProduct Type: "           << ProductType 
                        << "\nProduct Description: "    << ProductDescription 
                        << "\n\n" << endl;
                        line="";
                }
                filetemp<<line<<endl;
            }
        }

    MyFile.close();
    filetemp.close();
    remove("products.txt");
    rename("Temp.txt","products.txt");
    }

private:
    string ProductID;
    string ProductName;
    string ProductType;
    string ProductDescription;
    int ProductPrice;
    friend class Admin;
    friend class Order;
};

class Order : public Customer
{
    public:

    virtual void AddOrder()
    {
        ifstream MyFile("products.txt");
        fstream Order("orders.txt");
        string search, line;
        int offset;
        int qty;
        int total = 0;

        class Customer c1;
        class Product p1;

        ifstream CFile("info.txt");
        string searchone, linetemp;
        int offsetone;

        cout << "Input Customer ID: ";
        cin >> searchone;

        if(CFile.is_open())
        {
            while (!CFile.eof())
            {
                getline(CFile,linetemp);
                if((offsetone = linetemp.find(searchone,0) != string::npos))
                {
                        stringstream as(linetemp);
                        getline(as,CustomerName, ',');
                        getline(as,CustomerID,',');
                        getline(as,CustomerAddress,',');
                        getline(as,CustomerNumber,',');


                        cout 
                        << "\nCustomer Name: " << CustomerName 
                        << "\nCustomer ID: " << CustomerID 
                        << "\nCustomer Address: " << CustomerAddress 
                        << "\nCustomer Number: " << CustomerNumber
                        << "\n\n" << endl;
                        break;
                }
                else
                {
                    cout << "No such ID, try again later." << endl;
                    exit(1);
                }
            }
        }
        

        cout << "Welcome, " <<  CustomerName << endl;

        p1.ViewProduct();

        cout << "Write the ID of the product you wish to purchase: ";
        cin >> search;

        string tempString = "";

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,p1.ProductName, ',');
                    getline(ss,p1.ProductID,',');
                    getline(ss,tempString,',');
                    p1.ProductPrice = atoi(tempString.c_str());
                    getline(ss,p1.ProductType,',');
                    getline(ss,p1.ProductDescription,',');

                    if(p1.ProductName != "" && p1.ProductID != "" && p1.ProductType != "" && p1.ProductDescription != "")
                    {
                        cout 
                        << "\nProduct Name: " << p1.ProductName 
                        << "\nProduct ID: " << p1.ProductID
                        << "\nProduct Price: " << p1.ProductPrice 
                        << "\nProduct Type: " << p1.ProductType 
                        << "\nProduct Description: " << p1.ProductDescription << "\n\n" << endl;
                    }

                }
                
            }
        }
        cout << "You have chosen: " << p1.ProductName << endl;
        cout << "The price per item is: " << p1.ProductPrice << endl;

        ofstream input;
        input.open("orders.txt",ios::app);

        cout << "How much would you like to order?"<<endl;
        cout << "Quantity: ";
        cin >> qty;

        p1.ProductPrice = p1.ProductPrice * qty;

        if(p1.ProductType == "Fragile")
        {
            p1.ProductPrice = p1.ProductPrice + 4;
            cout << "$4 has been added for Fragile packaging." << endl;
        }
        else if(p1.ProductType == "Non-Fragile")
        {
            p1.ProductPrice = p1.ProductPrice + 2;
            cout << "$2 has been added for Non-Fragile packaging." << endl;
        }
        else
        {
            cout << "Invalid Product!" << endl;
            exit(1);
        }


        cout << "\nYour total is: " << p1.ProductPrice << endl;

            input<<p1.ProductName; 
            input<<','; 
         
            input<<p1.ProductID;
            input<<','; 

            input<<p1.ProductPrice; 
            input<<','; 

            input<<qty; // Product Quantity
            input<<',';

            input<<p1.ProductType;
            input<<',';

            input<<CustomerID; // Order ID
            input<<'\n';
            input.close(); 


        cout << "Your Order ID is: " << CustomerID << endl;
        cout << "Order Recorded!" << endl;
       
        MyFile.close();
        CFile.close();
        
    }

    void ViewOrder()
    {

        ifstream MyFile("orders.txt");
       
        string searchone, line;
        int offset;
        int qty;
        int total = 0;
        
        class Product p1;

        string tempString = "";
        string tempStringOne = "";
       

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(searchone,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,p1.ProductName, ',');
                    getline(ss,p1.ProductID,',');
                    getline(ss,tempString,',');
                    p1.ProductPrice = atoi(tempString.c_str());
                    getline(ss,tempStringOne,',');
                    qty = atoi(tempStringOne.c_str());
                    getline(ss,p1.ProductType,',');
                    getline(ss,CustomerID,',');

                    if(p1.ProductName != "" && p1.ProductID != "" && p1.ProductType != "")
                    {
                        cout
                        << "\n___ORDER DETAILS___"
                        << "\nProduct Name: "       << p1.ProductName 
                        << "\nProduct ID: "         << p1.ProductID
                        << "\nTotal Price: "      << p1.ProductPrice 
                        << "\nOrder Quantity: "     << qty
                        << "\nProduct Type: "       << p1.ProductType
                        <<"\nOrder ID: "            << CustomerID // Order ID
                        << "\n\n" << endl;
                    }
                }
            }
        }
        MyFile.close();

    }

    void SearchOrder()
    {
        ifstream MyFile("orders.txt");
       
        string search, line;
        int offset;
        int qty;
        int total = 0;
        
        class Product p1;

        ifstream CFile("info.txt");
        string searchone, linetemp;
        int offsetone;

        cout << "Input Customer ID: "; // To Display Respective Orders for that customer
        cin >> searchone;

        if(CFile.is_open())
        {
            while (!CFile.eof())
            {
                getline(CFile,linetemp);
                if((offsetone = linetemp.find(searchone,0) != string::npos))
                {
                        stringstream as(linetemp);
                        getline(as,CustomerName, ',');
                        getline(as,CustomerID,',');
                        getline(as,CustomerAddress,',');
                        getline(as,CustomerNumber,',');

                        cout 
                        << "\nCustomer Name: "      << CustomerName 
                        << "\nCustomer ID: "        << CustomerID 
                        << "\nCustomer Address: "   << CustomerAddress 
                        << "\nCustomer Number: "    << CustomerNumber
                        << "\n\n" << endl;
                }
            }
        }
        
        cout << "Welcome! " <<  CustomerName << endl;


        string tempString = "";
        string tempStringOne = "";
       

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(searchone,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,p1.ProductName, ',');
                    getline(ss,p1.ProductID,',');
                    getline(ss,tempString,',');
                    p1.ProductPrice = atoi(tempString.c_str());
                    getline(ss,tempStringOne,',');
                    qty = atoi(tempStringOne.c_str());
                    getline(ss,p1.ProductType,',');
                    getline(ss,CustomerID,',');

                    if(p1.ProductName != "" && p1.ProductID != "" && p1.ProductType != "")
                    {
                        cout
                        << "\n___ORDER DETAILS___"
                        << "\nProduct Name: "       << p1.ProductName 
                        << "\nProduct ID: "         << p1.ProductID
                        << "\nTotal Price: "      << p1.ProductPrice 
                        << "\nOrder Quantity: "     << qty
                        << "\nProduct Type: "       << p1.ProductType
                        <<"\nOrder ID: "            << CustomerID // Order ID
                        << "\n\n" << endl;
                    }
                }
            }
        }
        MyFile.close();
        CFile.close(); 
    }

    void EditOrder()
    {
        class Product p1;
        fstream filetemp;
        ifstream MyFile("orders.txt");

        string search,line,tempString;
        int offset,qty;
        char flag='n';

        filetemp.open("Temp.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Order ID: ";
        cin >> search;
        

        string tempStringOne = "";

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,p1.ProductName, ',');
                    getline(ss,p1.ProductID,',');
                    getline(ss,tempString,',');
                    p1.ProductPrice = atoi(tempString.c_str());
                    getline(ss,tempStringOne,',');
                    qty = atoi(tempStringOne.c_str());
                    getline(ss,p1.ProductType,',');
                    getline(ss,CustomerID,',');

                    cout << "You are now editing the following order." << endl;

                        cout
                        << "\n___ORDER DETAILS___"
                        << "\nProduct Name: "       << p1.ProductName 
                        << "\nProduct ID: "         << p1.ProductID
                        << "\nOrder Price: "         << p1.ProductPrice 
                        << "\nOrder Quantity: "     << qty
                        << "\nProduct Type: "       << p1.ProductType
                        <<  "\nOrder ID: "          << CustomerID // Order ID
                        << "\n\n" << endl;
                        flag='y';
                        line="";
                }
                filetemp<<line<<endl;
            }
        }
        if (flag=='n')
        {
            filetemp<<line<<endl;
        }
        if (flag=='y')
        {
            cout<<"Order ID: ";
            cin>>CustomerID;

            cout<<"Order Price: ";
            cin>>p1.ProductPrice ;

            cout<<"Quantity: ";
            cin>>qty;

            filetemp<<p1.ProductName<<","<<p1.ProductID<<","<<p1.ProductPrice<<","<<qty<<","<<p1.ProductType<<","
            <<CustomerID<<endl;
            flag='n';
            cout << "Order record updated!" <<endl;
        }
    MyFile.close();
    filetemp.close();
    remove("orders.txt");
    rename("Temp.txt","orders.txt");

    }

    void DeleteOrder()
    {
        class Product p1;

        fstream filetemp;
        ifstream MyFile("orders.txt");

        string search,line,tempString, tempStringOne;
        int offset,qty;
        char flag='n';

        filetemp.open("Temp.txt",ios :: in|ios::out|ios::trunc);

        cout << "Input Order ID: ";
        cin >> search;

     

        if(MyFile.is_open())
        {
            while (!MyFile.eof())
            {
                getline(MyFile,line);
                if((offset = line.find(search,0) != string::npos))
                {
                    stringstream ss(line);
                    getline(ss,p1.ProductName, ',');
                    getline(ss,p1.ProductID,',');
                    getline(ss,tempString,',');
                    p1.ProductPrice = atoi(tempString.c_str());
                    getline(ss,tempStringOne,',');
                    qty = atoi(tempStringOne.c_str());
                    getline(ss,p1.ProductType,',');
                    getline(ss,CustomerID,',');

                    cout << "The following will be deleted" <<endl;

                        cout
                        << "\n___ORDER DETAILS___"
                        << "\nProduct Name: "       << p1.ProductName 
                        << "\nProduct ID: "         << p1.ProductID
                        << "\nOrder Price: "         << p1.ProductPrice 
                        << "\nOrder Quantity: "     << qty
                        << "\nProduct Type: "       << p1.ProductType
                        <<  "\nOrder ID: "          << CustomerID // Order ID
                        << "\n\n" << endl;
                        line="";
                }
                filetemp<<line<<endl;
            }
        }

    MyFile.close();
    filetemp.close();
    remove("orders.txt");
    rename("Temp.txt","orders.txt");

    }

    private:
    string OrderID;
    friend class Customer;
};

class Admin
{
    public:
    void AdminMenu()
    {
        class Customer c1;
        class Product p1;
        class Order o1;

        int option = 0;

        while(option != 16) 
        {
            cout << "\n_________ADD_________" << endl;
            cout << "1: Add Customers" << endl;
            cout << "2: Add Products" << endl;
            cout << "3: Add Orders\n" << endl;

            cout << "_________DELETE_________" << endl;
            cout << "4: Delete Customers" << endl;
            cout << "5: Delete Products" << endl;
            cout << "6: Delete Orders\n" << endl;

            cout << "_________EDIT_________" << endl;
            cout << "7: Edit Customers" << endl;
            cout << "8: Edit Products" << endl;
            cout << "9: Edit Orders\n" << endl;

            cout << "_________VIEW_________" << endl;
            cout << "10: View Customers" << endl;
            cout << "11: View Products" << endl;
            cout << "12: View Orders\n" << endl;

            cout << "_________SEARCH_________" << endl;
            cout << "13: Search Customers" << endl;
            cout << "14: Search Products" << endl;
            cout << "15: Search Orders\n" << endl;

            cout << "16: Exit\n" << endl;

            cout << "Enter 1 - 16 to select an option: ";
            cin >> option;


            // ADD // 

            if(option == 1) {c1.AddCustomer();}

            else if(option == 2) {p1.AddProduct();}

            else if(option == 3) {o1.AddOrder();}

            // DELETE // 

            else if(option == 4) {c1.DeleteCustomer();}

            else if(option == 5) {p1.DeleteProduct();}

            else if(option == 6) {o1.DeleteOrder();}

            // EDIT // 

            else if(option == 7) {c1.EditCustomer();}

            else if(option == 8) {p1.EditProduct();}

            else if(option == 9) {o1.EditOrder();}

            // VIEW // 

            else if(option == 10) {c1.ViewCustomer();}

            else if(option == 11) {p1.ViewProduct();}

            else if(option == 12) {o1.ViewOrder();}

            // SEARCH // 

            else if(option == 13) {c1.SearchCustomer();}

            else if(option == 14) {p1.SearchProduct();}

            else if(option == 15) {o1.SearchOrder();}
        }
    
    }

    void AdminLogin()
    {
        
        while ((getchar()) != '\n');
        int loop = 0;
                while (loop == 0)
                {      
                    cout<<"Enter Username: "<<endl;
                    cin >> AdminUsername;
                
                    cout<<"Enter Password: "<<endl;
                    cin >> AdminPassword;
                    
                    if (AdminUsername=="admin" && AdminPassword=="1234")
                    {
                        cout<<"Login Successful!\n"<<"Welcome, Admin!" <<endl;
                        break;     
                    }
                    cout<<"Incorrect Credentials!\n"; 
                }
    this->AdminMenu();
      //AdminMenu();
    }
    
    private:
    string AdminUsername;
    string AdminPassword;
};

void Customer :: CustomerFunction()
{
    Order b;

            int choice;
            cout << "_____FUNCTIONALITIES_____" <<endl;
            cout << "1. Add Order" << endl;
            cout << "2. Delete Order" << endl;
            cout << "3. Edit Order" << endl;
            cout << "4. View Order" << endl;
            cout << "5. Search Order" << endl;
            cout << "Enter Choice: ";
            

        cin>>choice;
        cout<<endl;

        switch(choice)
        {
                case 1:
                    b.AddOrder();
                    break;
                case 2:
                    b.DeleteOrder();
                    break;
                case 3:
                    b.EditOrder();
                    break;

                case 4:
                    b.ViewOrder();
                    break;
                
                case 5:
                    b.SearchOrder();
                    break;

                default:
                    cout<<"Invalid input, try again!\n"<<endl; 
        }
}

int main()
{
    Customer c1;
    Product p1;
    Admin a1;
    int choice;

    cout<<"1.Admin"<<endl;
    cout<<"2.Customer"<<endl;
    cout<<"3.Exit"<<endl;

    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    
    switch(choice)
        {
                case 1:
                        a1.AdminLogin();
                        break;
                case 2:
                        c1.CustomerMenu();
                        break;
                case 3:
                        exit(1);
                        break;
                default:
                        system("cls");
                        cout<<"Invalid input, try again!\n"<<endl; 
                        main();
        }

}

