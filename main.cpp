// creating social media platform
/*
creating profile
adding friend
messaging in between
using graph

*/

#include <iostream>
#define MAX 50
#include <stdlib.h>
#include <fstream>
#include <string.h>

using namespace std;
class profilenode
{
public:
    string name;
    int age;
    string userId;
    string password;
    static int i;
    char sent_message[50];
    char receive_message[50];
    string followrequest;
    string friendname;
    profilenode *friends[50], *next;
    profilenode()
    {
        for (int j = 0; j < 50; j++)
        {
            friends[j] = NULL;
            sent_message[j]='\0';
            receive_message[j]='\0';
        }
    }
};
int profilenode::i = 0;
class socialmedia
{
    profilenode *head;

public:
    socialmedia()
    {
        head = new profilenode;
        head = NULL;
    }
    void creating_profile();
    void adding_friend(profilenode *);
    void messaging(profilenode *);
    void save_info(profilenode *);
    profilenode *search_user(string, string);
    profilenode *search_node(string);
    profilenode *search_friend(string, profilenode *);
    void sign_in();
    void various_activities(profilenode *);
    void Display_friendlist(profilenode *);
    void display_linkedlist();
    void check_received_messages(profilenode *);
    void follow_requests(profilenode *);
};
void socialmedia::follow_requests(profilenode *User){
    cout<<"You have followed by " <<User->followrequest<<endl;
    profilenode *temp=new profilenode;
    temp=search_node(User->followrequest);
    cout<<"Do you want to followback:(y/n)"<<endl;
    char ch;
    cin>>ch;
    if(ch=='y'||ch=='Y'){
        User->friends[User->i]=temp;
        return;
    }
}
void socialmedia::check_received_messages(profilenode *temp)
{
    cout<<"You have received message from \n"<<temp->friendname<<" : "<<endl;
    cout << temp->receive_message << endl;
    return;
}
void socialmedia::display_linkedlist()
{
    profilenode *temp = head;
    if (temp == NULL)
    {
        cout << "Linkedlist is empty!!!" << endl;
    }
    else
    {
        while (temp != NULL)
        {
            cout << temp->name << endl;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            return;
        }
    }
}
void socialmedia::Display_friendlist(profilenode *User)
{
    if (User->friends[0] == NULL)
    {
        cout << "\nFriendlist is Empty" << endl;
    }
    else
    {
        for (int i = 0; i <= User->i; i++)
        {
            cout << User->friends[i]->name << endl;
        }
    }
    return;
}
void socialmedia::messaging(profilenode *User)
{
    string name;
    char message[50];
    profilenode *temp = new profilenode;
    cout << "Do you want to Check Inbox:(y/n)" << endl;
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        check_received_messages(User);
        return;
    }
    else
    {
        cout << "enter your friend name which you want to chat:" << endl;
        cin >> name;
        temp = search_friend(name, User);
        if (temp != NULL)
        {
            cout << "\nNow you able to chat" << endl;
            cout << "\nEnter message:" << endl;
            cin>>message;
            strcpy(User->sent_message,message);
            strcpy(temp->receive_message,message);
            temp->friendname=User->name;
        }
        else
        {
            cout << "No such friend in your Friendlist" << endl;
        }
    }
    return;
}
profilenode *socialmedia::search_friend(string name, profilenode *User)
{
    int i;
    for (i = 0; i <= User->i; i++)
    {
        if (User->friends[i]->name.compare(name) == 0)
        {
            cout << name << " Found in your friend list" << endl;
            return User->friends[i];
            break;
        }
    }
}
void socialmedia::adding_friend(profilenode *User)
{
    string name;
    int i = User->i;
    cout << "enter your friend Name which you want to add:" << endl;
    cin >> name;
    profilenode *temp;
    temp = search_node(name);
    if (temp != NULL)
    {
        User->friends[i] = new profilenode;
        User->friends[i] = temp;
        User->i = User->i + 1;
        cout << "\n"
             << name << " is added in your friendlist Successfully" << endl;
        temp->followrequest=User->name;
        return;
    }
    else
    {
        cout << "No Such User is available" << endl;
    }
}
void socialmedia::various_activities(profilenode *User)
{
    int ch;
    do
    {
        cout << "\n1.display friendlist\n2.add friend\n3.Messanging"
        <<"\n4.Check Follow request" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            Display_friendlist(User);
            return;
            break;
        case 2:
            adding_friend(User);
            break;
        case 3:
            messaging(User);
            break;
        case 4:
            follow_requests(User);
            break;
        case 0:
            return;
        default:
            cout << "Enter valid Choice!!!" << endl;
            break;
        }
    } while (ch != 0);
}
void socialmedia::sign_in()
{
    string User_Id, Password;
    cout << "Enter your User Id:" << endl;
    cin >> User_Id;
    cout << "Enter your Password:" << endl;
    cin >> Password;
    profilenode *temp = new profilenode;
    temp = search_user(User_Id, Password);
    if (temp != NULL)
    {
        various_activities(temp);
    }
    else
    {
        cout << "No such User Available Now on this platform" << endl;
        return;
    }
}
void socialmedia::save_info(profilenode *New)
{
    profilenode *temp = new profilenode;
    temp = head;
    if (head == NULL)
    {
        head = New;
        return;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            temp->next = New;
            return;
        }
    }
}
profilenode *socialmedia::search_user(string name, string password)
{
    profilenode *temp = new profilenode;
    temp = head;
    while (temp != NULL)
    {
        if (temp->userId.compare(name) == 0)
        {
            if (temp->password.compare(password) == 0)
            {
                cout << "\nwelcome to Our Platform" << endl;
                return temp;
            }
            else
            {
                cout << "\nPassword is wrong...." << endl;
                temp = NULL;
                return temp;
            }
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    if (temp == NULL)
    {
        return NULL;
    }
}
profilenode *socialmedia::search_node(string name)
{
    profilenode *temp = head;
    while (temp != NULL)
    {
        if (name.compare(temp->name) == 0)
        {
            cout << name << "is found in the list" << endl;
            return temp;
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        return temp;
    }
}

void socialmedia::creating_profile()
{
    profilenode *New = new profilenode;
    char ch;
    cout << "enter your name:" << endl;
    cin >> New->name;
    cout << "enter your age:" << endl;
    cin >> New->age;
    cout << "Enter User Id:" << endl;
    cin >> New->userId;
    cout << "Enter Password:" << endl;
    cin >> New->password;
    New->next = NULL;
    save_info(New);
    cout << "Do you want to continue(y/n):" << endl;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        various_activities(New);
    }
    else
    {
        return;
    }
}
int main()
{
    system("cls");
    socialmedia sm;
    cout << "\t\tWelcome to My project!!!" << endl;
    cout << "\t\tProject created by Avinash Jadhav" << endl;
    int ch;
    do
    {
        cout << "\n1.Sign in\n2.Create Account\n3.Display All Users "
             << "\nIf you are New User then Enter Create Account Option and"
             << "if you are Existing user then select Sign in Option"
             << "\nFor Exit Press '0'" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            sm.sign_in();
            break;
        case 2:
            sm.creating_profile();
            break;
        case 3:
            sm.display_linkedlist();
            break;
        default:
            cout << "Enter valid choice" << endl;
            break;
        }

    } while (ch != 0);
    return 0;
}