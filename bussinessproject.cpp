#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
string presskey = "";
int howmany = 0;
int usercount = 0;
int linecount2 = 0;
string passwordtemp = "";
string nametemp = "";
string roletemp = "";
string name = "";
string password = "";
string role = "";
string tempfood = "";
int tempprice = 0;
string foodtoupdate = "";
string foodtodelete = "";
int deleted = 0;
int checklength = 0;
const int users = 15;
int foodcount = 0;
string yesno = "";
string cancelorder = "";
float totalBill = 0;
string howMuchItem;
int namecheck = 0;
string foodtoorder = "";
string adress = "";
string acessadress = "";
string foodItemStore[users];
float arrquantity[users];
string arrname[users];
string arrpassword[users];
string arrrole[users];
int arrsorting[10];
string arrfood[15];
int arrprice[15];
bool passwordValidation();   // to check whether the password length is of 8 digits or not
bool nameValidation();       // to check whether the user name is unique or not
void goBack();               // to go back to previous menu
void printHeader();          // to print header
string selectSigninSignup(); // to select whether you want to sign in or sign up
string signUp();             // to create a new account
void signupArrayToFile();    // to store the users name,password and role to file
void signupFileToArray();    // to bring all the users information to arrays
void signIn();               // to take name and password
bool signInCheck();          // when the account is already created and you have to check whether person is the same user or not
string appRole();            // to take the role and return it so person can see interface according to it
void showAdminMainMenu();    // to show admin main menu
string adminMainMenu();      // to chose which option you want to select
void adminsubmenu1();        // this menu is used to view all the food items
void foodToFile();           // to store all the food items to file and keep the file updated
void foodToArray();          // to bring all the food items back to array
string adminSubMenu2();      // to add a new item to list
string adminSubMenu3();      // to update a item already present in list
string adminSubMenu4();      // to delete a already present item in list
bool adminSubMenu5();        // to logout yourself from the program
void showUsermMainMenu();    // to show user main menu
string usermMainMenu();      // to to chose which option you want to select
void userSubMenu1();         // to view the all food items
void userSubMenu2();         // to place order of the food you want to eat
void orderedFoodToFile();    // to send all the food ordered to file
void orderedFoodToArray();   // to bring all the food ordered to arrays
bool userSubMenu3();         // to see all the total bill of the food ordered
string userSubMenu4();       // to enter the adress where where you want the food to be delivered
void userSubMenu5();         // to see which are the most ordered and popular food of that place
string userSubMenu6();       // to cancel the food order
int convertToInt();
bool checkingprice();

main()
{

    system("cls");
    printHeader();
    // all the information stored in file is restored to arrays
    signupFileToArray();
    foodToArray();
    orderedFoodToArray();
    string choice;
    while (true)
    {
        choice = selectSigninSignup();
        // if our choice is 1 then we are going to sign up and creating an account
        if (choice == "1")
        {
            system("cls");
            printHeader();
            string pass = signUp();
            bool ncheck = nameValidation();
            // if user name we entered already exists then account cant be created
            if (ncheck == true)
            {
                cout << "User name already exists" << endl;
                getch();
                system("cls");
                printHeader();
            }
            // if user name we entered is unique then account is going to created
            else
            {
                cout << "Valid name" << endl;
                bool check = passwordValidation();
                // if password is of 8 digits then it is valid
                if (check == true)
                {
                    // if every thing is valid then all information will be saved in arrays
                    arrname[usercount] = nametemp;
                    arrpassword[usercount] = pass;
                    arrrole[usercount] = roletemp;
                    cout << "Valid password" << endl;
                    cout << "Successfully created an account" << endl;
                    usercount++;
                    signupArrayToFile();
                }
                else
                {
                    cout << "invalid password"<<endl;
                }
            }
            goBack();
            system("cls");
            printHeader();
        }
        // if we enter 2 it means that account is already created and we have to check whether he is the same person
        else if (choice == "2")
        {
            system("cls");
            printHeader();
            signIn();
            bool result = signInCheck();
            // if there is no already such user then you have to create a account
            if (result == false)
            {
                cout << "No such user" << endl;
                getch();
                system("cls");
                printHeader();
            }
            // if there is already present user than role will be returned and you will see the interface according to it
            else
            {
                cout << "Valid user" << endl;
                cout << "Press any where to continue:";
                getch();
                system("cls");
                printHeader();
                string choice2;
                choice2 = roletemp;
                // if we chose admin than we have all the admin main menu
                while (choice2 == "admn")
                {
                    if (choice2 == "admn")
                    {
                        system("cls");
                        printHeader();
                        showAdminMainMenu();
                        string choi = adminMainMenu();
                        // if admin chose 1 than we can view all the food items
                        while (choi == "1")
                        {
                            if (choi == "1")
                            {
                                system("cls");
                                printHeader();
                                adminsubmenu1();
                                foodToFile();
                                cout << "Press 0 to go back:";
                                cin >> choi;
                                if (choi == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if admin chose 2 admn can add any food item to the list
                        while (choi == "2")
                        {
                            if (choi == "2")
                            {
                                system("cls");
                                printHeader();
                                string cfood = adminSubMenu2();
                                arrfood[foodcount] = cfood;
                                arrprice[foodcount] = tempprice;
                                foodToFile();
                                foodcount++;
                                cout << "Press 0 to go back:";
                                cin >> choi;
                                if (choi == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if admin chose 3 then admin can update any of the product
                        while (choi == "3")
                        {
                            if (choi == "3")
                            {
                                system("cls");
                                printHeader();
                                string update = adminSubMenu3();
                                int foodPresent = 0;
                                for (int j = 0; j < users; j++)
                                {
                                    if (foodtoupdate == arrfood[j])
                                    {
                                        // we can give new or new price to a product
                                        cout << "Enter its new name:";
                                        getline(cin, arrfood[j]);
                                        cout << "Enter its new price:";
                                        cin >> arrprice[j];
                                        foodToFile();
                                        foodPresent++;
                                    }
                                }
                                // if we want to update such a product that doesnot exist
                                if (foodPresent <= 0)
                                {
                                    cout << "There is no such food in our items" << endl;
                                }
                                cout << "Press 0 to go back:";
                                cin >> choi;
                                if (choi == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if admin chose 4 then he can delete any product
                        while (choi == "4")
                        {
                            if (choi == "4")
                            {
                                system("cls");
                                printHeader();
                                adminSubMenu4();
                                int deletingProduct = 0;
                                for (int j = 0; j < users; j++)
                                {
                                    if (foodtodelete == arrfood[j])
                                    {

                                        arrfood[j] = "deleted";
                                        arrprice[j] = 0;
                                        deletingProduct++;
                                    }
                                }
                                // if we enter such a food that doesnot exist
                                if (deletingProduct <= 0)
                                {
                                    cout << "There is no such food in our items" << endl;
                                }
                                foodToFile();
                                cout << "Press 0 to go back:";
                                cin >> choi;
                                if (choi == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if admin chose 5 then he can logout from the system
                        while (choi == "5")
                        {
                            if (choi == "5")
                            {
                                system("cls");
                                printHeader();
                                bool logout = adminSubMenu5();
                                if (logout == true)
                                {
                                    system("cls");
                                    choice2 = "";
                                    choi = "0";
                                    printHeader();
                                }
                                else
                                {
                                    system("cls");
                                    printHeader();
                                    showAdminMainMenu();
                                    adminMainMenu();
                                }
                            }
                        }
                        if (choi == "6")
                        {
                            abort();
                        }
                    }
                }
                // if we chose user then we can see user interface
                while (choice2 == "user")
                {
                    if (choice2 == "user")
                    {
                        system("cls");
                        printHeader();
                        showUsermMainMenu();
                        string choi1 = usermMainMenu();
                        // if user chose 1 then he can view the food items
                        while (choi1 == "1")
                        {
                            if (choi1 == "1")
                            {
                                system("cls");
                                printHeader();
                                userSubMenu1();
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 2 then he can place his order
                        while (choi1 == "2")
                        {
                            if (choi1 == "2")
                            {
                                system("cls");
                                printHeader();
                                userSubMenu2();
                                int foodcheck = 0;
                                int j = 0;
                                // user first tell how many item he wants and the enter food and its quantity
                                while (j < howmany)
                                {
                                    for (int dx = 0; dx < users; dx++)
                                    {
                                        if (foodItemStore[j] == arrfood[dx])
                                        {
                                            totalBill = totalBill + (arrprice[dx] * arrquantity[j]);

                                            foodcheck++;
                                        }
                                    }
                                    j++;
                                }
                                if (foodcheck == howmany)
                                {
                                    totalBill = totalBill;
                                    orderedFoodToFile();
                                }
                                // if user enter such a food that doesnot exist
                                else
                                {
                                    cout << "There is no such food in our item" << endl;
                                    totalBill=0;
                                }
                                // if we have not enter the adress we should go back to enter the adress
                                if (acessadress == "")
                                {
                                    cout << "Go back and enter your adress" << endl;
                                }
                                else
                                {
                                    cout << "Your order will deliver to you soon" << endl;
                                }
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 3 than he can see his total bill
                        while (choi1 == "3")
                        {

                            if (choi1 == "3")
                            {
                                system("cls");
                                printHeader();
                                bool checkHowMany = userSubMenu3();
                                if (checkHowMany == true)
                                {
                                    cout << "Your total Bill is:"
                                         << " "
                                         << "Rs"
                                         << "=" << totalBill << endl;
                                    totalBill = 0;
                                }
                                // if you have not ordered any thing than your bill will be 0
                                else
                                {
                                    cout << "You have not ordered any food" << endl;
                                    totalBill = 0;
                                    cout << "Total bill ="
                                         << " " << totalBill << endl;
                                }
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 4 then he can enter his adress there
                        while (choi1 == "4")
                        {
                            if (choi1 == "4")
                            {
                                system("cls");
                                printHeader();
                                acessadress = userSubMenu4();
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 5 then he can see recommendations the most sold food
                        while (choi1 == "5")
                        {
                            if (choi1 == "5")
                            {
                                system("cls");
                                printHeader();
                                userSubMenu5();
                                cout << "Press any where to continue" << endl;
                                getch();
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 6 then he can cancel his order
                        while (choi1 == "6")
                        {

                            if (choi1 == "6")
                            {
                                float totalBill1 = 0;
                                system("cls");
                                printHeader();
                                string order = userSubMenu6();
                                if (order == "yes")
                                {
                                    totalBill = totalBill1;
                                    cout << "Your total bill is" << totalBill1 << endl;
                                }
                                else
                                {
                                    totalBill1 = 0;
                                }
                                cout << "Press 0 to go back:";
                                cin >> choi1;
                                if (choi1 == "0")
                                {
                                    break;
                                }
                            }
                        }
                        // if user chose 7 then he can logout from the system
                        while (choi1 == "7")
                        {
                            if (choi1 == "7")
                            {
                                system("cls");
                                printHeader();
                                bool logout = adminSubMenu5();
                                if (logout == true)
                                {
                                    system("cls");
                                    choice2 = "";
                                    choi1 = "0";
                                    printHeader();
                                }
                                else
                                {
                                    system("cls");
                                    printHeader();
                                    void showUsermMainMenu();
                                    string usermMainMenu();
                                }
                            }
                        }
                        if (choi1 == "8")
                        {
                            abort();
                        }
                    }
                }
            }
        }
    }
}

void printHeader()
{
    // this will print header

    cout << "*********************************************************************************" << endl;
    cout << "*************************ONLINE FOOD DELIVERY SYSTEM*****************************" << endl;
    cout << "*********************************************************************************" << endl;
}
string selectSigninSignup()
{
    // we will give our choice whether we want to sign in or sign out
    cout << "Press 1 if you want to sign up" << endl;
    cout << "Press 2 if you want to sign in" << endl;
    cout << "Select one option:";
    cin >> presskey;
    return presskey;
}
string signUp()
{
    // we will enter our name , password and role to create account
    cout << "Enter your name:" << endl;
    cin.ignore();
    getline(cin, nametemp);
    cout << "Enter your password:" << endl;
    getline(cin, passwordtemp);
    cout << "Enter your role:" << endl;
    getline(cin, roletemp);
    return passwordtemp;
}
bool passwordValidation()
{
    // if length of password is 8 then return true
    checklength = passwordtemp.length();
    if (checklength == 8)
        return true;
    else
        return false;
}
void signupArrayToFile()
{
    // this will save all peoples record in file
    fstream file;
    file.open("sa.txt", ios::app);
    for (int j = 0; j < usercount; j++)
    {

        file << arrname[j] << endl;
        file << arrpassword[j] << endl;
        file << arrrole[j] << endl;
    }
    file.close();
}
void signupFileToArray()
{
    // this will put all peoples data in arrays again
    string line;
    int linecount = 0;
    fstream file;
    file.open("sa.txt", ios::app); // create file in case it is not already present
    file.close();
    file.open("sa.txt", ios::in);
    int j = 0;
    while (!file.eof())
    {
        getline(file,line);
        arrname[j]=line;
        if(line=="")
        {
            continue;
        }
        getline(file,line);
        arrpassword[j]=line;
        getline(file,line);
        arrrole[j]=line;
        j++;
    }
    usercount = j;
    file.close();
}
void goBack()
{
    cout << "Press 3 to go back:";
    cin >> presskey;
    if (presskey == "3")
    {
        system("cls");
        printHeader();
    }
}
void signIn()
{
    // we will enter name and password
    cout << "Enter your name:" << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Enter your password:" << endl;
    getline(cin, password);
}
bool signInCheck()
{
    // this will check whether user name and password is present in file already or not
    // if present then account already created will be verified
    for (int j = 0; j < users; j++)
    {
        if (name == arrname[j] && password == arrpassword[j])
        {
            roletemp = arrrole[j];
            return true;
        }
    }
    return false;
}
string appRole()
{
    // enter the role
    cout << "Enter your role:";
    getline(cin, role);
    return role;
}
void showAdminMainMenu()
{
    // showing admin main menu and its choices
    cout << "  Select one of the option from 1 to 5" << endl;
    cout << "  1.View products" << endl;
    cout << "  2.Add items" << endl;
    cout << "  3.Update items" << endl;
    cout << "  4.Delete items" << endl;
    cout << "  5.Log out" << endl;
    cout << "  6.Exit" << endl;
}
string adminMainMenu()
{
    // entering which option we want to select
    cin >> presskey;
    return presskey;
}
void adminsubmenu1()
{
    // showing all food items
    for (int j = 0; j < foodcount; j++)
    {
        if (deleted == j)
        {
            continue;
        }
        else
        {
            arrfood[0] = {"pizza"};
            cout << arrfood[j] << " " << arrprice[j] << endl;
        }
    }
}
void foodToFile()
{
    fstream file;
    file.open("r1.txt", ios::out);
    for (int j = 0; j < foodcount; j++)
    {

        file << arrfood[j] << endl;
        file << arrprice[j] << endl;
    }
    file.close();
}
void foodToArray()
{

    string line1;
    int linecount1 = 0;
    fstream file;
    file.open("r1.txt", ios::app);
    file.close();
    file.open("r1.txt", ios::in);
    foodcount = 0;
    while (!file.eof())
    {
        file >> line1;
        arrfood[foodcount]=line1;
        if(line1=="")
        {
            continue;
        }
        file >> line1;
        arrprice[foodcount]=stoi(line1);
        if(line1=="")
        {
            continue;
        }
        foodcount++;
        linecount1++;
    }
    foodcount--;
    file.close();
}
string adminSubMenu2()
{
    // here we can enter or add a new item
    cout << "Enter the food you want to add:";
    cin.ignore();
    cin >> tempfood;
    cout << "Enter the price of that food:";
    cin.ignore();
    cin >> tempprice;
    return tempfood;
}
string adminSubMenu3()
{
    // here admin can enter the product we want to update and can gives its new or price
    cout << "Enter the product you want to update:" << endl;
    cin.ignore();
    getline(cin, foodtoupdate);
    return foodtoupdate;
}
string adminSubMenu4()
{
    // admin can enter the product he want to delete
    cout << "Enter the product you want to delete:" << endl;
    cin.ignore();
    getline(cin, foodtodelete);
    return foodtodelete;
}
bool adminSubMenu5()
{
    // here admin can logout from the program
    cout << "Do you really want to logout yes or no:";
    getline(cin >> ws, yesno);
    if (yesno == "yes")
    {
        return true;
    }
    return false;
}
void showUsermMainMenu()
{
    // here we can see the user interface
    cout << "  Select one of the option from 1 to 6" << endl;
    cout << "  1.View items" << endl;
    cout << "  2.Place your order" << endl;
    cout << "  3.Total bill" << endl;
    cout << "  4.Acessing address" << endl;
    cout << "  5.Recommendations" << endl;
    cout << "  6.Cancel order" << endl;
    cout << "  7.Logout" << endl;
    cout << "  8.Exit" << endl;
}
string usermMainMenu()
{
    // user can enter which option he want to chose
    cin >> presskey;
    return presskey;
}
void userSubMenu1()
{
    // user can view all food items here
    for (int j = 0; j < foodcount; j++)
    {
        cout << arrfood[j] << "=" << arrprice[j] << endl;
    }
}
void userSubMenu2()
{
    // here user will enter how many and which item he want to order
    cout << "How many item you want:";
    cin.ignore();
    cin >> howMuchItem;
    bool ch = checkingprice();
    if (ch == true)
    {
        howmany = stoi(howMuchItem);
        cout << howmany;
    }
    else
    {
        cout << "Invalid input" << endl;
    }

    if (howmany <= 10)
    {
        for (int dx = 0; dx < howmany; dx++)
        {
            cout << "Enter the"
                 << " " << dx << " "
                 << "item you want to eat:" << endl;
            getline(cin >> ws, foodItemStore[dx]);
            cout << "How much quantity you want per person:";
            cin >> arrquantity[dx];
        }
    }
}
void orderedFoodToFile()
{
    // to enter all the ordered food to arrays
    fstream file;
    file.open("ramsha2.txt", ios::app);
    for (int j = 0; j < howmany; j++)
    {
        file << foodItemStore[j] << endl;
    }
    file.close();
}
void orderedFoodToArray()
{
    // to put all ordered food to array
    string line;
    fstream file;
    file.open("ramsha2.txt", ios::app); // create file in case it's not present
    file.close();
    file.open("ramsha2.txt", ios::in);
    int j = 0;
    while (!file.eof())
    {
        file>>line;
        if(line=="")
        {
            break;
        }
        foodItemStore[j]=line;
        j++;
        linecount2++;
    }
    file.close();
}
bool userSubMenu3()
{
    // here if user have ordered something he can see our bill
    if (howmany > 0)
    {
        return true;
    }
    return false;
}
string userSubMenu4()
{
    // here user will enter hia adress
    cout << "Enter your adress:";
    cin.ignore();
    getline(cin, adress);
    return adress;
}
void userSubMenu5()
{
    // here we will keep the count that which item is sold the most
    // so most famous item will be recommended to customers
    int pizza = 0;
    int burger = 0;
    int shawarma = 0;
    int sandwich = 0;
    int fries = 0;
    int cake = 0;
    int macroni = 0;
    int loadedfries = 0;
    int paratharoll = 0;
    int milkshake = 0;
    for (int dx = 0; dx < linecount2; dx++)
    {
        if (foodItemStore[dx] == arrfood[0])
        {

            pizza++;
        }
        else if (foodItemStore[dx] == arrfood[1])
        {
            burger++;
        }
        else if (foodItemStore[dx] == arrfood[2])
        {
            shawarma++;
        }
        else if (foodItemStore[dx] == arrfood[3])
        {

            sandwich++;
        }
        else if (foodItemStore[dx] == arrfood[4])
        {

            fries++;
        }
        else if (foodItemStore[dx] == arrfood[5])
        {
            cake++;
        }
        else if (foodItemStore[dx] == arrfood[6])
        {
            loadedfries++;
        }
        else if (foodItemStore[dx] == arrfood[7])
        {

            macroni++;
        }
        else if (foodItemStore[dx] == arrfood[8])
        {

            paratharoll++;
        }
        else if (foodItemStore[dx] == arrfood[9])
        {
            milkshake++;
        }
    }
    int arrrecommendation[10] = {pizza, burger, shawarma, sandwich, fries, cake, loadedfries, macroni, paratharoll, milkshake};
    for (int j = 0; j < 10; j++)
    {
        for (int m = j + 1; m < 10; m++)
        {
            if (arrrecommendation[j] < arrrecommendation[m])
            {
                float temp = arrrecommendation[j];
                string temp1 = arrfood[j];
                arrrecommendation[j] = arrrecommendation[m];
                arrfood[j] = arrfood[m];
                arrrecommendation[m] = temp;
                arrfood[m] = temp1;
            }
        }
    }
    for (int n = 0; n < 10; n++)
    {
        cout << "The food given below is ordered"
             << " " << arrrecommendation[n] << " "
             << "times" << endl;
        cout << arrfood[n] << endl;
    }
}
string userSubMenu6()
{
    // here user can cancel his order
    cout << "Do you really want to cancel your order yes or no:";
    cin.ignore();
    getline(cin, cancelorder);
    return cancelorder;
}
bool userSubMenu7()
{
    // here user can logout from the system
    cout << "Do you really want to logout yes or no:";
    cin.ignore();
    getline(cin, yesno);
    if (yesno == "yes")
    {
        return true;
    }
    return false;
}
bool nameValidation()
{
    // here it is checked whether the name is unique or not
    bool foundName = false;
    for (int j = 0; j < 15; j++)
    {
        if (nametemp == arrname[j])
        {
            foundName = true;
        }
    }

    return foundName;
}
int convertToInt()
{
    int wordInInt = 0;
    stringstream wordInString;
    wordInString << howMuchItem;
    wordInString >> wordInInt;
    return wordInInt;
}
bool checkingprice()
{
    bool result = true;
    for (int i = 0; i < howMuchItem.length(); i++)
    {
        if (!(howMuchItem[i] >= '0' && howMuchItem[i] <= '9'))
        {
            result = false;
        }
    }
    return result;
}
