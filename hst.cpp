#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;
void login_regiS();
int valid(string);
class Student
{
    public:
    string std_name;
    string roll_no;
    string ph_no;
    string gender;
    string room_no;
    int twr_no;
    int choice,i,exit=0,fee;
    string sname,aname;
    ofstream fileo;
    ifstream filei;
    void getdata()
    {
        cout<<"Enter Your Name:\n";
        cin.ignore();
        getline(cin,std_name);
        cout<<"Enter Your registered admission number(APXXXXXXXXX):\n";
        cin>>roll_no;
        int k=valid(roll_no);
        while(k!=1){
            cout<<"Hostel already booked with this registration number(please login/check the registration number)\n";
            cout<<"Enter the registration number:\n";
            cin>>roll_no;
            k=valid(roll_no);
        }
        cout<<"Enter Your Mobile Number:\n";
        cin>>ph_no;
        sname=roll_no+".txt";
            filei.open(sname.c_str());
            if(filei.is_open() && filei.fail())
            {
                cout<<"\nYou are registered.\n Redirecting ........";
                filei.close(); 
                login_regiS();
            }
        cout<<"Enter Your gender:\n";
        cin>>gender;
        if(gender=="M"||gender=="m"|| gender=="Male"|| gender=="male"){
            twr_no=1;
            string filename1="tower1.txt";
            int avail=roomAllocation(room_no,filename1);
            while(avail!=1){
            cout<<"Select a Room Number:\n";
            cin>>room_no;
            avail=roomAllocation(room_no,filename1);
            }
            cout<<room_no<<" is alloted to "<<roll_no<<"\n";
        }
        else{
            twr_no=2;
            string filename2="tower2.txt";
            roomAllocation(room_no,filename2);
            int avail=roomAllocation(room_no,filename2);
            while(avail!=1){
            cout<<"Select a Room Number:\n";
            cin>>room_no;
            avail=roomAllocation(room_no,filename2);
            }
            cout<<room_no<<" is alloted to "<<roll_no<<"\n";

        }
        fee=160000;         
        cout<<"The amount for two sharing is 160000\n";
        while(fee!=0){
            cout<<"The amount to be paid is :\n"<<fee<<"\n";
            int x;
            cout<<"Enter the amount paid :\n";
            cin>>x;
            fee-=x;
        }
        cout<<"The fee is paid successfully\n";
    }
    int roomAllocation(string room_no,string filename);
    void createprofile();
};
void Student:: createprofile()
{
   sname=roll_no+".txt";
   fstream fileAo("Admin.txt",ios::app);
            //cout<<fname;
            fileo.open(sname.c_str());
            fileo<<roll_no<<endl<<ph_no<<endl<<std_name<<endl<<room_no<<endl<<twr_no<<endl;
            cout<<"\nYou are successfully registered:)\n";
            fileo.close();
            fileAo<<roll_no<<endl<<ph_no<<endl<<std_name<<endl<<room_no<<endl<<twr_no<<endl;
            fileAo.close();
}
int Student::roomAllocation(string room_no,string filename)
{
    string myText,my;
    ifstream MyReadFile(filename);
    ofstream out("newfile.txt");
    int flag=0;
    while(getline(MyReadFile,my)){
        if(my==room_no && flag==0){
            flag=1;
        }
        else{
            out<<my;
            out<<"\n";
        }
    }
    // Close the file
    MyReadFile.close();
    out.close();
    string f;
    f=filename;
    if(filename=="tower1.txt"){
    remove("tower1.txt");
    rename("newfile.txt","tower1.txt");
    }
    else{
    remove("tower2.txt");
    rename("newfile.txt","tower2.txt");
    }
    if(flag==0){
        return flag;
    }
    else{
        return flag;
    }
}
class Admin{
    public:
    void get_bill();
    void show_hst_vacancies();
    void show_bill();
    void show_rec();
};
void Admin::get_bill(){
    string date,bill;
    cout<<"Enter date to enter the mess bill:\n";
    cin>>date;
    cout<<"Enter the amount of the mess bill:\n";
    cin>>bill;
    fstream out("messbill.txt",ios::app);
    out<<date<<" "<<bill<<"\n";
    out.close();
}
void Admin::show_rec(){
    ifstream in("Admin.txt");
    string choice;
    string rool_no,pho_no,name,room,tower,e;
    cout<<"Select a tower to display data:\n1.Tower-1\n2.Tower-2\n";
    cin>>choice;
    if(choice=="1" || choice=="2"){

    while(getline(in,rool_no)){
        getline(in,pho_no);
        getline(in,name);
        getline(in,room);
        getline(in,tower);
        if(tower==choice){
            cout<<"Registered Number: "<<rool_no<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Room No. "<<room<<endl;
            cout<<"Tower No. "<<tower<<endl;
        }
    }
    in.close();
    }
    else{
        cout<<"Invalid option\n";
        return;
    }
}
void Admin::show_hst_vacancies(){
    int choice;
    string room;
    cout<<"Enter the tower vacancies you want to know:\n";
    cout<<"1.Tower-1\n2.Tower-2\n";
    cin>>choice;
    if(choice==1){
        ifstream in("tower1.txt");
        while(getline(in,room)){
            cout<<room<<"\n";
        }
    }
    else if(choice==2){
        ifstream in("tower2.txt");
        while(getline(in,room)){
            cout<<room<<"\n";
        }
    }
    else{
        cout<<"Invalid input\n";
        return;
    }
}
void Admin::show_bill(){
    ifstream in("messbill.txt");
    string line;
    cout<<"Date        bill\n";
    while(getline(in,line)){
        cout<<line<<"\n";
    }
}

void admin_update(string old,string new_n){
    ifstream file1("Admin.txt");
    ofstream out("newfile.txt");
    string name,roll_no,phone,room,tower,e,k;
    while(getline(file1,roll_no)){
        getline(file1,phone);
        getline(file1,name);
        getline(file1,room);
        getline(file1,tower);
        if(name==old || phone==old){
            if(phone==old){
            out<<roll_no<<endl<<new_n<<endl<<name<<endl<<room<<endl<<tower<<endl;
            }
            else{
            out<<roll_no<<endl<<phone<<endl<<new_n<<endl<<room<<endl<<tower<<endl;
            }
        }
        else{
            out<<roll_no<<endl<<phone<<endl<<name<<endl<<room<<endl<<tower<<endl;
        }
    }
    file1.close();
    out.close();
    remove("Admin.txt");
    rename("newfile.txt","Admin.txt");
}

int valid(string str)
{
    string dir,user;
    ifstream file;
    dir = str+".txt";
    file.open(dir.c_str());
    if(!file.is_open() && file.fail())
    {
        return 1;
    }
    else{
        return -1;
    }
}
void login_regiA()
{
    int choice,i,exit=0;
    string pss,admin_name;
    cout<<"----------------------------------------------Welcome to admin Portal!------------------------------------------------------\n";
            cout<<"Enter your User Name :\n";
            cin>>admin_name;
            cout<<"Enter your password:\n";
            cin>>pss;
            if(admin_name=="Admin" && pss=="srm@123" )
            {
                cout<<"Successfully Logged In! :)\n";
                do{
                cout<<"\n1.Enter the mess bill\n2.View Hostel Vacancies\n3.View Mess Bill Entries\n4.view Resident Details\n5.Exit\n";
                cout<<"Enter a Choice:\n";
                cin>>choice;
                Admin a;
                switch(choice)
                {
                    case 1: a.get_bill();break;
                    case 2: a.show_hst_vacancies();break;
                    case 3: a.show_bill();break;
                    case 4: a.show_rec();break;
                    case 5: break;
                
                }
                }while(choice>0 && choice<5);
            }
            else{
                cout<<"\nWrong username or password!\nPlease try Again.\n";
            }
            cout<<endl;
        
    }

void login_regiS()
{
    int choice,i,exit=0;
    string ph_no,fname,bio,usern,pw,line,roll_no,room,twr;
    ofstream fileo;
    ifstream filei;
    cout<<"----------------------------------------------Welcome to student Portal!------------------------------------------------------\n";
    while(exit==0)
    {
        cout<<"";
        cout<<"\nChoose one option:\n1. SignIn/LogIn(press 1 if you are a registered student )\n2. SignUp/Register(press 2 if you are a new admission)\n3. Exit\n";
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter your Roll Number (AP2XXXXXXXX):\n";
            cin>>roll_no;
            cout<<"\nEnter your password(Phone number):\n";
            cin>>ph_no;
            fname=roll_no+".txt";
            filei.open(fname.c_str());
            if(!filei.is_open() && filei.fail())
            {
                cout<<"\nYou are not registered, please register before logging in.\n";
                filei.close();
                continue;
            }
            getline(filei,usern);
            getline(filei,pw);
            getline(filei,line);
            if(roll_no==usern && ph_no==pw)
            {
                int ch;
                cout<<"\nYou are successfully logged in:)\n";
            
                cout<<"1.VIEW PROFILE\n2.UPDATE PROFILE\n";
                cin>>ch;
                getline(filei,room);
                getline(filei,twr);
                filei.close();
                
                if(ch==1)
                {
                cout<<"Registered Number"<<usern<<endl;
                cout<<"Name:"<<line<<endl;
                cout<<"Room No."<<room<<endl;
                cout<<"Tower No."<<twr<<endl;
                }
                else if(ch==2)
                {
                    int c;
                    cout<<"1.Name\n2.Number\n";
                    cin>>c;
                    ofstream change("new.txt");
                        if(c==1)
                        {
                            string name;
                            cout<<"Enter the name:\n";
                            cin>>name;
                            change<<usern<<endl<<pw<<endl<<name<<endl<<room<<endl<<twr<<endl;
                            change.close();
                            remove(fname.c_str());
                            rename("new.txt",fname.c_str());
                            admin_update(line,name);
                            cout<<"Succssfully changed";
                        }
                        else if(c==2)
                        {
                            string phone;
                            cout<<"Enter the phone number:\n";
                            cin>>phone;
                            change<<usern<<endl<<phone<<endl<<line<<endl<<room<<endl<<twr<<endl;
                            change.close();
                            remove(fname.c_str());
                            rename("new.txt",fname.c_str());
                            admin_update(pw,phone);
                            cout<<"Succssfully Changed\n";
                        }
                  }
              
            }
            else{
                cout<<"\nWrong username or password!\nPlease try Again.\n";
            }
            cout<<endl;
        }
        else if(choice==2)
        {
            Student student;
            student.getdata();
            student.createprofile();
        }
        else
        {
            exit=1;
        } 
    }
    cout<<"\n----------------------------------------------Thank you for visiting:)----------------------------------------------------\n";
}
void main_menu()
{
    int ch;
    cout<<"===============<<<<Welcome to SRM University Hostel>>>>=============="<<endl;
    cout<<"Are You a- "<<endl;
    cout<<"1.Student"<<endl;
    cout<<"2.Staff"<<endl;
    cout<<"select an option :"<<endl;
    cin>>ch;
    switch(ch)
    {
        case 1: login_regiS();break;
        case 2: login_regiA();break;
    }
}
int main()
{
    main_menu();
   return 0;
}