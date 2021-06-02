// by: Kian Majlessi - Restaurant Management System

#include <iostream>
#include <string.h>
using namespace std;

struct userdb
{
    bool isAdmin = false;
    char username[100];
    char password[100];
} us, ustemp;

struct fooddb
{
    int code;
    double price;
    unsigned int deals;
    char name[1000];
} fd;

void mainmenu();
void menu();
void admindash();
bool signup();
bool login(bool again = false);
bool addfood();
void submitorder(unsigned int kind);
bool foodsearch(int foodcode);
bool usersearch(char username[] = {0}, char password[] = {0});
void userlist();
bool editfood(char mch, int foodcode, bool submit = false, int numd = 0);
bool fooddel(int foodcode);

int main()
{
    mainmenu();
    return 0;
}

void mainmenu()
{
    system("cls");
    cout << "------------- Welcome To The Restaurant Management System ! -------------" << endl;
    cout << "\tMenu:" << endl;
    cout << "\t<L> : Login" << endl
         << "\t<S> : Signup" << endl
         << "\t<E> : Exit" << endl;
    cout << endl
         << "\tEnter Your Choice ---> ";
    char menutemp;
    cin >> menutemp;

    if (menutemp == 'E' || menutemp == 'e')
    {
        cout << "\tThanks For Using Restaurant Management System (by: Kian Majlessi)" << endl
             << "\tPress Enter To Exit" << endl;
        cin.ignore();
        cin.ignore();
        exit(0);
    }

    if (menutemp == 'S' || menutemp == 's')
    {
        while (!signup())
        {
            cout << "\tPress Enter To Continue";
            cin.ignore();
        }

        us = ustemp;
        system("cls");
        cout << "------------- Hi " << us.username << ", Thanks for Signing up! -------------" << endl;
        cout << "\t<M> : Menu\n\t<E> : Exit" << endl;
        cout << endl
             << "\tPress <E> / <M> : ";
        cin >> menutemp;
        if (menutemp == 'E' || menutemp == 'e')
        {
            cout << "\tThanks For Using Restaurant Management System (by: Kian Majlessi)" << endl
                 << "\tPress Enter To Exit" << endl;
            cin.ignore();
            cin.ignore();
            exit(0);
        }
        else
        {
            if (us.isAdmin)
                admindash();
            else
                menu();
        }
    }

    else
    {
        if (login())
        {
            if (us.isAdmin)
                admindash();
            else
            {
                menu();
                mainmenu();
            }
        }

        else
        {
            cout << endl
                 << "\tThe Username Or Password Is Incorrect !" << endl
                 << "\tPress Enter To Continue" << endl;
            cin.ignore();
            mainmenu();
        }
    }
}

void menu()
{
    char menutemp;
    unsigned int kind;
    system("cls");
    cout << "!------------ Restaurant Management System | Menu (" << us.username << ") ------------!" << endl;
    cout << endl
         << "Item Code#\tDescription\tPrice" << endl;
    FILE *ffood;
    ffood = fopen("fooddb.dat", "r");
    if (!ffood)
    {
        fprintf(stderr, "\n\tNo Food Founded !\n");
        cerr << "\tPress Enter To Continue";
        cin.ignore();
        if (us.isAdmin)
            cin.ignore();
        return;
    }

    while (fread(&fd, sizeof(fd), 1, ffood))
        if (fd.deals > 0)
        {
            cout << "[" << fd.code << "]\t\t" << fd.name << "\t\t$" << fd.price << endl;
            kind++;
        }

    fclose(ffood);

    cout << endl
         << "Do You Want To Submit An Order ? <Y/N>" << endl;
    cin >> menutemp;

    if (menutemp == 'Y' || menutemp == 'y')
        submitorder(kind);
    else if (!us.isAdmin)
        mainmenu();
}

void admindash()
{
    unsigned short int menutemp;

    system("cls");
    cout << "!------------ Restaurant Management System | Admin Dashboard (" << us.username << ") ------------!" << endl;
    cout << "\tMenu:" << endl;
    cout << "\t<1> : Insert Records (Food)" << endl
         << "\t<2> : Insert Records (User)" << endl
         << "\t<3> : Display All Records (Food)" << endl
         << "\t<4> : Display All Records (User)" << endl
         << "\t<5> : Search For A Record (Food)" << endl
         << "\t<6> : Search For A Record (User)" << endl
         << "\t<7> : Modify A Record (Food)" << endl
         << "\t<8> : Delete A Record (Food)" << endl
         << "\t<0> : Logout" << endl;

    cout << endl
         << "\tEnter Your Choice ---> ";
    cin >> menutemp;

    switch (menutemp)
    {
        int itemcode;
    case 0:
        mainmenu();
        break;
    case 1: //<1> : Insert Records (Food)
        while (!addfood())
        {
            cout << "\tError!" << endl
                 << "\tPress Enter To Continue";
            cin.ignore();
        }
        cout << endl
             << "\tFood Successfully Added!" << endl
             << "\tPress Enter To Continue";
        cin.ignore();
        cin.ignore();
        admindash();
        break;
    case 2: //<2> : Insert Records (User)
        while (!signup())
        {
            cout << "\tError!" << endl
                 << "\tPress Enter To Continue";
            cin.ignore();
        }
        cout << endl
             << "\tUser Successfully Created!" << endl
             << "\tPress Enter To Continue";
        cin.ignore();
        admindash();
        break;
    case 3: //<3> : Display All Records (Food)
        menu();
        admindash();
        break;
    case 4: //<4> : Display All Records (User)
        userlist();
        cin.ignore();
        admindash();
        break;
    case 5: //<5> : Search For A Record (Food)
        cout << endl
             << "\tEnter Item Code : ";
        cin >> itemcode;
        if (foodsearch(itemcode))
        {
            cout << endl
                 << "\t---> Description: " << fd.name << endl
                 << "\t     Price: $" << fd.price << endl
                 << "\t     In Stock: " << fd.deals << endl
                 << "\t     Press Enter To Continue";
        }
        else
            cout << endl
                 << "\tNot Found!" << endl
                 << "\tPress Enter To Continue";
        cin.ignore();
        cin.ignore();
        admindash();
        break;
    case 6: //<6> : Search For A Record (User)
        char user[100];
        cout << endl
             << "\tEnter Username : ";
        cin.getline(user, 100);
        cin.getline(user, 100);
        if (usersearch(user))
        {
            cout << endl
                 << "\t---> Username: " << ustemp.username << endl
                 << "\t     Password: " << ustemp.password << endl
                 << "\t     IsAdmin: " << ustemp.isAdmin << endl
                 << "\t     Press Enter To Continue";
        }
        else
            cout << endl
                 << "\tNot Found!" << endl
                 << "\tPress Enter To Continue";
        cin.ignore();
        admindash();
        break;
    case 7: //<7> : Modify A Record (Food)
        char editmenu;
        cout << endl
             << "\tEnter Item Code : ";
        cin >> itemcode;
        if (foodsearch(itemcode))
        {
            cout << endl
                 << "\t---> <D> Description: " << fd.name << endl
                 << "\t     <P> Price: $" << fd.price << endl
                 << "\t     <S> In Stock: " << fd.deals << endl
                 << "\t     Enter Your Choise For Edit: ";
            cin >> editmenu;
            if (editfood(editmenu, itemcode))
                cout << endl
                     << "\tDone!";
        }
        else
        {
            cout << endl
                 << "\tNot Found!" << endl
                 << "\tPress Enter To Continue";
        }

        cin.ignore();
        cin.ignore();
        admindash();
        break;

    case 8: //<8> : Delete A Record (Food)
        cout << endl
             << "\tEnter Item Code : ";
        cin >> itemcode;
        if (foodsearch(itemcode))
        {
            cout << endl
                 << "\t---> Description: " << fd.name << endl
                 << "\t     Price: $" << fd.price << endl
                 << "\t     In Stock: " << fd.deals << endl
                 << "\t     Are You Sure? <Y/N>: ";
            cin >> editmenu;
            if (editmenu == 'y' || editmenu == 'Y')
                if (fooddel(itemcode))
                    cout << endl
                         << "\tDone!";
        }
        else
        {
            cout << endl
                 << "\tNot Found!" << endl
                 << "\tPress Enter To Continue";
        }

        cin.ignore();
        cin.ignore();
        admindash();
        break;

    default:
        admindash();
    }
}

bool signup()
{
    system("cls");
    cout << "!------------ Restaurant Management System | Input : ------------!" << endl;
    FILE *fuser;
    fuser = fopen("RestaurantUser.dat", "a+");
    if (!fuser)
    {
        fprintf(stderr, "\nError Opend File\n");
        return false;
    }

    char menutemp, tempin[100];

    cout << "\t<A> : Admin\n\t<U> : User" << endl;
    cout << endl
         << "\tPress <A> / <U> : ";
    cin >> menutemp;
    cout << "\tUsername : ";
    cin.ignore();
    cin.getline(tempin, 100);
    while (fread(&ustemp, sizeof(ustemp), 1, fuser))
    {
        if ((menutemp == 'A' || menutemp == 'a') && (ustemp.isAdmin == true))
        {
            cout << "\tThe Admin already exists." << endl;
            return false;
        }
        if (!strcmp(ustemp.username, tempin))
        {
            cout << "\tThe username already exists. Please enter a different username : ";
            cin.getline(tempin, 100);
            fseek(fuser, 0, SEEK_SET);
        }
    }

    if (feof)
    {
        strcpy(ustemp.username, tempin);
        cout << "\tPassword : ";
        cin.getline(ustemp.password, 100);
        if (menutemp == 'A' || menutemp == 'a')
            ustemp.isAdmin = true;
        else
            ustemp.isAdmin = false;
        fwrite(&ustemp, sizeof(ustemp), 1, fuser);
    }

    fclose(fuser);

    return true;
}

bool login(bool again)
{
    system("cls");
    cout << "!------------ Restaurant Management System | Input : ------------!" << endl;
    char tempuser[100], temppass[100];
    cout << "\tUsername : ";
    if (!again)
        cin.ignore();
    cin.getline(tempuser, 100);
    cout << "\tPassword : ";
    cin.getline(temppass, 100);

    if (usersearch(tempuser, temppass))
    {
        us = ustemp;
        return true;
    }

    return false;
}

bool addfood()
{
    int tempcode;
    system("cls");
    cout << "!------------ Restaurant Management System | Input : ------------!" << endl;
    FILE *ffood;
    ffood = fopen("fooddb.dat", "a+");
    if (!ffood)
    {
        fprintf(stderr, "\nError Opend File\n");
        return false;
    }

    cout << "\tItem Code : ";
    cin >> tempcode;

    while (fread(&fd, sizeof(fd), 1, ffood))
    {
        if (fd.code == tempcode)
        {
            cout << "\tThe Item Code already exists. Please enter a different Code : ";
            cin >> tempcode;
            fseek(ffood, 0, SEEK_SET);
        }
    }

    if (feof(ffood))
    {
        fd.code = tempcode;
        cout << "\tDescription : ";
        cin.ignore();
        cin.getline(fd.name, 1000);
        cout << "\tPrice : ";
        cin >> fd.price;
        cout << "\tIn Stock : ";
        cin >> fd.deals;
        fwrite(&fd, sizeof(fd), 1, ffood);
    }

    fclose(ffood);
    return true;
}

void submitorder(unsigned int kind)
{
    unsigned int num;
    double totalprice = 0;
    int *code, *deals;
    cout << endl
         << "How Many Kinds Of Food Do You Want To Order ? ";
    cin >> num;
    while (num > kind)
    {
        cout << endl
             << "Maximum Kinds Of Food Is : " << kind;
        cout << endl
             << "How Many Kinds Of Food Do You Want To Order ? ";
        cin >> num;
    }
    code = new int[num];
    deals = new int[num];

    for (int i = 0; i < num; i++)
    {
        cout << endl
             << "[" << i + 1 << "] >>> Enter Item Code : ";
        cin >> code[i];
        while (!foodsearch(code[i]))
        {
            cout << endl
                 << "Wrong Code! Try Again!";
            cout << endl
                 << "[" << i + 1 << "] >>> Enter Item Code : ";

            cin >> code[i];
        }
        cout << "Enter Number Of Deals (Code : " << code[i] << ") : ";
        cin >> deals[i];
        while (fd.deals < deals[i])
        {
            cout << endl
                 << "The Number Of Portions You've Ordered Is Out Of The Stock!" << endl
                 << "Please Order Less Than " << fd.deals;
            cout << endl
                 << "Enter Number Of Deals (Code : " << code[i] << ") : ";
            cin >> deals[i];
        }

        if (editfood('s', code[i], true, deals[i]))
        {
            totalprice += fd.price * deals[i];
            cout << endl
                 << "---> Description: " << fd.name << endl
                 << "      Rate: $" << fd.price << endl
                 << "      Qty: " << deals[i] << endl
                 << "      Amount: $" << fd.price * deals[i] << endl;
        }
    }

    delete[] code;
    delete[] deals;
    cout << endl
         << "!------------ TOTAL PRICE: $" << totalprice << " | THANKS FOR COMING " << us.username << " ------------!" << endl;
    cin.ignore();
    cin.ignore();
    mainmenu();
}

bool foodsearch(int foodcode)
{
    FILE *foodf;
    foodf = fopen("fooddb.dat", "r");
    if (!foodf)
    {
        fprintf(stderr, "\n\tNo Food Founded !\n");
        return false;
    }

    while (fread(&fd, sizeof(fd), 1, foodf))
    {
        if (foodcode == fd.code)
            return true;
    }

    fclose(foodf);
    return false;
}

bool usersearch(char username[], char password[])
{
    FILE *fuser;
    fuser = fopen("RestaurantUser.dat", "r");
    if (!fuser)
    {
        fprintf(stderr, "\n\tNo User Founded !\n");
        if (!us.isAdmin)
        {
            cerr << "\tPress Enter To Continue";
            cin.ignore();
            mainmenu();
        }
        return false;
    }

    if (!us.isAdmin)
        while (fread(&ustemp, sizeof(ustemp), 1, fuser))
        {
            if (!strcmp(ustemp.username, username))
                if (!strcmp(ustemp.password, password))
                    return true;
        }

    else
        while (fread(&ustemp, sizeof(ustemp), 1, fuser))
        {
            if (!strcmp(ustemp.username, username))
                return true;
        }

    fclose(fuser);
    return false;
}

void userlist()
{
    system("cls");
    cout << "!------------ Restaurant Management System | Users ------------!" << endl;
    cout << endl
         << "IsAdmin#\tUsername\tPassword" << endl;
    FILE *fuser;
    fuser = fopen("RestaurantUser.dat", "r");
    if (!fuser)
    {
        fprintf(stderr, "\nNo User Founded !\n");
        return;
    }

    while (fread(&ustemp, sizeof(ustemp), 1, fuser))
        cout << "[" << ustemp.isAdmin << "]\t\t" << ustemp.username << "\t\t" << ustemp.password << endl;

    fclose(fuser);
    cout << endl
         << "Press Enter To Continue";
    cin.ignore();
    return;
}

bool editfood(char mch, int foodcode, bool submit, int numd)
{
    if (mch >= 'A' && mch <= 'Z')
        mch += 32;

    FILE *foodf;
    foodf = fopen("fooddb.dat", "r+");
    if (!foodf)
    {
        fprintf(stderr, "\n\tNo Food Founded !\n");
        return false;
    }

    while (fread(&fd, sizeof(fd), 1, foodf))
    {
        if (foodcode == fd.code)
        {
            switch (mch)
            {
            case 'd':
                cout << endl
                     << "\tDescription: ";
                cin.getline(fd.name, 1000);
                cin.getline(fd.name, 1000);
                break;
            case 's':
                if (!submit)
                {
                    cout << endl
                         << "\tIn Stock: ";
                    cin >> fd.deals;
                }
                else
                    fd.deals -= numd;
                break;
            case 'p':
                cout << endl
                     << "\tPrice: ";
                cin >> fd.price;
                break;
            }

            fseek(foodf, -(long int)sizeof(fd), SEEK_CUR);
            fwrite(&fd, sizeof(fd), 1, foodf);
            fclose(foodf);
            return true;
        }
    }

    return false;
}

bool fooddel(int foodcode)
{
    unsigned int count = 0, i = 0;
    fooddb *ffdbtemp;
    FILE *foodf;
    foodf = fopen("fooddb.dat", "r+");
    if (!foodf)
    {
        fprintf(stderr, "\n\tNo Food Founded !\n");
        return false;
    }

    while (fread(&fd, sizeof(fd), 1, foodf))
        count++;

    ffdbtemp = new fooddb[count];

    fseek(foodf, 0, SEEK_SET);
    while (fread(&fd, sizeof(fd), 1, foodf))
    {
        if (fd.code != foodcode)
        {
            ffdbtemp[i] = fd;
            i++;
        }
    }

    fclose(foodf);
    foodf = fopen("fooddb.dat", "w+");
    if (!foodf)
    {
        fprintf(stderr, "\n\tNo Food Founded !\n");
        return false;
    }

    for (int j = 0; j < i; j++)
        fwrite(&ffdbtemp[j], sizeof(fd), 1, foodf);

    fclose(foodf);
    delete[] ffdbtemp;
    return true;
}