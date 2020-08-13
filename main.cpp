/* -------------------- HEADERS -------------------- */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <string.h>
#include <windows.h>
#include <iomanip>

using namespace std;

const char USER_NAME[10] = "admin", PASSCODE[10] = "admin", admission_nos[15] = "admissions.txt";
char subjects[5][5][14] = {
                         {"English", "Hindi", "EVS", "GK", "M. Science"},
                         {"English", "Hindi", "Mathematics", "Science", "Social Std."},
                         {"English", "Physics", "Chemistry", "Mathematics", "Biology"},
                         {"English", "Accounts", "Business Std.", "Mathematics", "Economics"},
                         {"History", "Pol. Science", "Sociology", "Geography", "Psychology"}
                        };
char months[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


/* -------------------- STRUCTURES -------------------- */

// DATE STRUCTURE
struct date{
    int d, m, y;
};

// NOTIFICATION STRUCTURE
struct notification {
    int timestamp;
    char text[100];
    bool seen;
};

/* ----------------------------------------------------- */



/* -------------------- FUNCTION DECLARATION -------------------- */

void printElement(const char*, int);               // Table Printing <<
void intro();                                // Splash Screen  <<
void format_date(date);                      // Format Date To Words <<
int valid(int, int, int);                    // Validate Var For A Range
void printHead(char*);
void space(int);
void sign_out();                             // Signing Out Confirmation <<
int authorize();                             // Check Credentials <<
//Student find_stdnt(int, int);              // Find & Return Student By Adm & Class <<

void main_screen();                          // Main Menu Screen <<
void new_adm_screen();                       // Registration Form Screen <<
void submit_fee_screen();                    // Fee Submission Screen <<
void fetch_screen();                         // Fetch Records Screen <<   "UI not tested"
void academic_screen();                      // Add Academic Records Screen
void modify_record_screen();                 // Modify Records Screen
void delete_record_screen();                 // Delete Records Screen
void notification_screen();                  // Notifications Screen


void new_notif(int, char*);                 // For Adding New Notification To Notification Screen


/* ----------------------------------------------------- */


/* ------------------- STUDENT CLASS ------------------- */

class Student {
private:
    // Personal Information
    char s_name[20]{}, f_name[20]{}, m_name[20]{}, adrs[50]{};
    char gender;
    int cls{}, mobile, adm_no, stream;
    date dob{};
    // Fee Record
    float fee;
    // Academic Record
    int marks[4][5]{};
    int fee_structure;

public:

    Student();
    void fill(char*, char*, char*, char*, char, int, int, date, int, int);
    void display(char, bool);

    char* get_name() {
        return this->s_name;
    }

    int get_cl() {
        return this->cls;
    }

    void get_marks(int arr[][5]) {
        for(int i=0; i<4; i++) {
            for(int j=0; j<5; j++) {
                arr[i][j] = this->marks[i][j];
            }
        }
    }

    int get_adm() {
        return this->adm_no;
    }

    int submit_fee(float f) {
        float total_fee;
        total_fee = fee_structure*11;
        if(this->fee >= total_fee) {return 0;}
        this->fee += f;
        return 1;

    }


    // Setters
    void set_sname(char* name) { strcpy(this->s_name, name); }
    void set_fname(char* name) { strcpy(this->f_name, name); }
    void set_mname(char* name) { strcpy(this->m_name, name); }
    void set_adrs(char* ad) { strcpy(this->adrs, ad); }
    void set_gender(char g) { this->gender = g; }
    void set_cls(int c) { this->cls = c; }
    void set_mob(int m) { this->mobile = m; }
    void set_stream(int s) { this->stream = s; }
    void set_dob(date d) { this->dob = d; }
    void set_marks(int r, int c, int m) { this->marks[r][c] = m;}
    void add_marks(int exam_no) {
        int m[5];
        for(int i=0; i<=4; i++){
            cin >> m[i];
        }
        for(int i=0; i<=4; i++){
            this->marks[exam_no][i] = m[i];
        }
    }

};

/* ----------------------------------------------------- */


/* ------------------- MISC FUNCTIONS ------------------ */

int valid(int input, int start, int end) {
    if(input >= start && input <= end)
        return 1;
    return 0;
}

void center(char str[]) {
    int len = strlen(str);
    int pos = (90-len)/2;
    if(pos%2==0) pos--;
    for(int i=0; i<pos; i++) cout << " ";
    cout << str;
}

void printElement(const char* text, int width) {
    cout << "| ";
    cout << left << setw(width) << setfill(' ') << text;
}

void format_date(date d){
    char post_fix[2];
    if(d.d == 1 || d.d == 21 || d.d == 31)
        strcpy(post_fix, "st");
    else if(d.d == 2 || d.d == 22)
        strcpy(post_fix, "nd");
    else if(d.d == 3 || d.d == 23)
        strcpy(post_fix, "rd");
    else
        strcpy(post_fix, "th");

    cout << d.d << post_fix <<" ";
    int i = d.m - 1;
    cout << months[i] << " ";
    cout << d.y;
}

void space(int n) {
    for(int i=0; i<n; i++) {
        cout << " ";
    }
}

void printHead(char str[]) {
    cout << "\n\n\n";
    int length = strlen(str) + 54;
    int pos = ((90 - length)/2);
    for(int i=1; i<pos; i++) cout << " ";
    cout << "|" << setw(length-1) << setfill('-') << "|" <<"\n";
    for(int i=1; i<pos; i++) cout << " ";
    cout << "|------------------------- "<<str<<" -------------------------|\n";;
    for(int i=1; i<pos; i++) cout << " ";
    cout << "|" << setw(length-1) << setfill('-') << "|" <<"\n";
}

/* ----------------------------------------------------- */









Student::Student() {
    strcpy(this->f_name, "Unknown");
    strcpy(this->s_name, "Unknown");
    strcpy(this->m_name, "Unknown");
    strcpy(this->adrs, "Unknown");
    this->dob = {0, 0, 0};
    this->gender = 'U';
    this->mobile = 0;
    this->adm_no = 0;
    this->stream = 0;
    this->fee = 0;
    this->fee_structure = 0;
    for(int i=0; i<4; i++) {
        for(int j=0; j<5; j++)
            this->marks[i][j] = 0;
    }
}
void Student::fill(char* name, char* fname, char* mname, char* adr, char gen, int clas, int ph, date dbirth, int adm, int strm=0) {
    strcpy(this->s_name, name);
    strcpy(this->f_name, fname);
    strcpy(this->m_name, mname);
    strcpy(this->adrs, adr);
    this->gender = gen;
    this->cls = clas;
    this->adm_no = adm;
    this->mobile = ph;
    this->dob = dbirth;
    this->stream = strm;
    switch (this->cls) {
        case 1: fee_structure = 1300;
            break;
        case 2: fee_structure = 1350;
            break;
        case 3: fee_structure = 1450;
            break;
        case 4: fee_structure = 1600;
            break;
        case 5: fee_structure = 1700;
            break;
        case 7: fee_structure = 1750;
            break;
        case 8: fee_structure = 2000;
            break;
        case 9: fee_structure = 2200;
            break;
        case 10: fee_structure = 2250;
            break;
        case 11: fee_structure = 2500;
            break;
        case 12: fee_structure = 2700;
            break;
    }
    for(int i=0; i<4; i++) {
        for(int j=0; j<5; j++)
            this->marks[i][j] = 0;
    }
    this->fee = 0;
}
void Student::display(char c, bool head) {


    if(head) {
        if(c=='a')
            cout << "|---------------------------------------------------------------------|\n"
                    "|-------------------------- Personal Record --------------------------|\n"
                    "|---------------------------------------------------------------------|\n";

        else if(c=='b')
            cout << "|-------------------------------------------------------------------------------|\n"
                    "|------------------------------- Academic Record -------------------------------|\n"
                    "|-------------------------------------------------------------------------------|\n\n";

        else if(c=='c')
            cout << "|----------------------------------------------------------------------|\n"
                    "|----------------------------- Fee Record -----------------------------|\n"
                    "|----------------------------------------------------------------------|\n\n";

    }

    if(c=='a') {

        cout << "|  Name            |  " << this->s_name << endl;
        cout << "|  Class           |  " << this->cls << endl;
        if(this->cls > 10) {
            cout << "|  Stream          |  ";
            switch (this->stream){
                case 1: cout << "Science";
                    break;
                case 2: cout << "Commerce";
                    break;
                case 3: cout << "Arts";
                    break;
            }
            cout << endl;
        }
        cout << "|  Admission No    |  " << this->adm_no << endl;
        cout << "|  DOB             |  " ;
        format_date(this->dob);
        cout << endl;
        cout << "|  Gender          |  ";
        if(this->gender == 'm'|| this->gender == 'M')
            cout << "Male" << endl;
        else
            cout << "Female" << endl;

        cout << "|  Father's Name   |  " << this->f_name << endl;
        cout << "|  Mother's Name   |  " << this->m_name << endl;
        cout << "|  Mobile          |  " << this->mobile << endl;
        cout << "|  Address         |  " << this->adrs << endl;
        cout << "---------------------------------------------------------------------\n";
    }

    else if (c == 'b') {

        int index = 0;
        if(this->cls >= 1 & this->cls <= 3) index = 0;
        else if(this->cls >= 4 & this->cls <= 10) index = 1;
        else if(this->cls >= 11 & this->cls <= 12) index = stream + 2;

        cout << "\n---------------";
        cout << left << setw(20) << setfill('-') << this->s_name;
        cout << "----------Class: ";
        cout << left << setw(2) << setfill('-') << this->cls;
        cout << "---------------------------\n";
        cout << "---------------------------------------------------------------------------------\n";
        cout <<   "|   Sub./Exam   |  Quarterly 1  | Half Yearly 1 |  Quarterly 2  | Half Yearly 2 |";
        cout << "\n---------------------------------------------------------------------------------\n";


        for(int k=0; k<5; k++) {
            printElement(subjects[index][k], 14);
            for(int i=0; i<4; i++) printElement(to_string(this->marks[k][i]).c_str(), 14);
            cout << "|";
            cout << "\n---------------------------------------------------------------------------------\n";
        }


    }

    else if(c == 'c') {

        cout << "| Name : " << this->s_name << "  | Class : " << this->cls << "  | Admission No. : " << this->adm_no << endl;
        cout << "\n|-----------------------------|\n";
        cout <<   "|    Month    | Fee Submitted |";
        cout << "\n|-----------------------------|\n";

        float remain_fee = this->fee;
        for(int i=3; i<12; i++) {
            printElement(months[i], 12);
            if(remain_fee > 0) {
                if(remain_fee > this->fee_structure) {
                    printElement(to_string(this->fee_structure).c_str(), 14);
                    remain_fee -= this->fee_structure;
                }
                else {
                    printElement(to_string(remain_fee).c_str(), 14);
                    remain_fee = 0;
                }
            } else
                printElement(to_string(0).c_str(), 14);
            cout << "|";
            cout << "\n|-----------------------------|\n";

        }
        for(int i=0; i<2; i++) {
            printElement(months[i], 12);
            if(remain_fee > 0) {
                if(remain_fee > this->fee_structure) {
                    printElement(to_string(this->fee_structure).c_str(), 14);
                    remain_fee -= this->fee_structure;
                }
                else {
                    printElement(to_string(remain_fee).c_str(), 14);
                    remain_fee = 0;
                }
            } else
                printElement(to_string(0).c_str(), 14);
            cout << "|";
            cout << "\n|-----------------------------|\n";
        }

    }

}

Student find_stdnt(int cls, int adm) {

    Student s;
    int admno;
    bool exists = false;


    string path = "Cl" + to_string(cls) + ".dat";
    ifstream cl(path, ios::binary);
    ifstream admissions(admission_nos);


    while(admissions) {
        admissions >> admno;
        if(admno == adm) {
            exists = true;
            break;
        }
    }
    if(!exists) {
        admissions.close();
        cl.close();
        cout << "\nNo Record Found With Admission Number: " << to_string(adm);
        Sleep(2000);
        exit(0);
        //main_screen();
    }

    if(!cl) {
        admissions.close();
        cl.close();
        cout << "Class Record Error!";
        Sleep(2000);
        exit(0);
        //main_screen();
    }
    while(cl) {
        cl.read((char*)&s, sizeof(s));
        if(s.get_adm() == adm)
            return s;
    }
    admissions.close();
    cl.close();

}

int authorize() {
    char uname[15], pass[15];
    system("cls");
    char head[] = "AUTHORIZE";
    printHead(head);

    cout << endl << endl;
    space(30); cout << " | USERNAME: ";
    cin.getline(uname, 10);
    space(30); cout << " | PASSWORD: ";
    cin.getline(pass, 10);

    if(strcmp(uname, USER_NAME) == 0 && strcmp(pass, PASSCODE) == 0 ) {
        return 1;
    }
    return 0;
}




void new_notif(int adm, char* txt){
    notification n = {};
    time_t now = time(0);
    tm *ltm =   localtime(&now);
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;

    strcpy(n.text, txt);
    n.seen = false;
    n.timestamp = ((month*100) + day)*10000 + adm;

    ofstream notifs("notifications.dat", ios::binary | ios::app);
    if(!notifs){
        cout<<"Error! 1";
        return;
    }
    notifs.write((char*) &n, sizeof(n));

    notifs.close();
}

int main() {


    // Get the console handle
    HWND console = GetConsoleWindow();

    //MoveWindow(window_handle, x, y, width, height, redraw_window);
     MoveWindow(console, 200, 60, 740, 600, TRUE);





    intro();

    int attempt = 0;
    while(attempt < 3) {
        if(authorize()==1) {
            main_screen();
        }

        else {
            if(attempt == 2){
                cout << "Too many attempts! Exiting.";
                Sleep(1500);
                exit(0);
            }
            cout << "Uh ho! Wrong Passcode \nTry Again.";
            Sleep(1000);
            system("cls");
        }

        attempt++;

    }
    return 0;
}



/* ------------------- SCREEN FUNCTIONS ------------------- */

void main_screen() {

    // Record Updation

    Student s;
  //  for(int i=1; i<=12; i++) {
  //      string path = "Cl" + to_string();
  //  }

    menu:
    system("cls");
    char head[] = "STUDENT MANAGEMENT";
    printHead(head);
    cout << endl;

    int sp = 33;
    space(sp); cout << "1]  New Admission\n";
    space(sp); cout << "2]  Submit Fee\n";
    space(sp); cout << "3]  Add Academic Record\n";
    space(sp); cout << "4]  Fetch Record\n";
    space(sp); cout << "5]  Modify Record\n";
    space(sp); cout << "6]  Delete Record\n";
    space(sp); cout << "7]  Notifications\n";
    space(sp); cout << "8]  Sign Out\n\n";

    int opt;
    space(sp); cout << ": ";
    cin >> opt;
    if(opt < 1 || opt > 8) {
        cout << "Invalid Choice!";
        Sleep(1500);
        system("cls");
        goto menu;
    }



        switch (opt) {
            case 1: new_adm_screen();
                goto menu;
            case 2: submit_fee_screen();
                goto menu;
            case 3: academic_screen();
                goto menu;
            case 4: fetch_screen();
                goto menu;
            case 5: modify_record_screen();
                goto menu;
            case 6: delete_record_screen();
                goto menu;
            case 7: notification_screen();
                goto menu;
            case 8: sign_out();
                goto menu;

    }


}

void intro() {
    cout << "\n\n\n\n\n"
            "                       _ _|  \\ |  __|__ __|_ _|__ __| |  |__ __| __|\n"
            "                         |  .  |\\__ \\   |    |    |   |  |   |   _| \n"
            "                       ___|_|\\_|____/  _|  ___|  _|  \\__/   _|  ___|\n"
            "                                                                    \n"
            "                                                                    \n"
            "                      \\  |   \\    \\ |   \\   __| __|  \\  | __|  \\ |__ __|\n"
            "                     |\\/ |  _ \\  .  |  _ \\ (_ | _|  |\\/ | _|  .  |   |  \n"
            "                    _|  _|_/  _\\_|\\_|_/  _\\___|___|_|  _|___|_|\\_|  _|  \n"
            "                                                                        \n"
            "                                                                        \n"
            "                                __|\\ \\  / __|__ __| __|  \\  |\n"
            "                              \\__ \\ \\  /\\__ \\   |   _|  |\\/ |\n"
            "                              ____/  _| ____/  _|  ___|_|  _|\n"
            "\n\n\n";
    Sleep(300);
    /* --------- CREDITS ---------------
    cout << setw(62);
    cout << "- Developed by Anshul\n\n\n";
     */
    cout << setw(45);

    for(int j=0; j<1; j++) {
        cout << "LOADING";
        for(int i=0; i<3;i++){
            Sleep(300);
            cout<<".";
            Sleep(300);
        }
    }

}

void new_adm_screen() {

    char s_name[20], f_name[20], m_name[20], adrs[50];
    char gender;
    int cls, mobile, adm, stm = 0;
    date dob = {0, 0, 0};
    Student s;


    system("cls");
    char head[] = "NEW ADMISSION";
    printHead(head);
    cout << "\n\n";
    cout << "| Name           |  ";
    cin.ignore();
    cin.getline(s_name, 20);
    cout << "| Gender (M|F)   |  "; cin >> gender;
    cout << "| DOB            |  "; cin >> dob.d >> dob.m >> dob.y;
    cout << "| Class          |  "; classinput: cin >> cls;



    if(!valid(cls, 1, 12)) {
        cout << "Invalid Class Input!";
        Sleep(1500);
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        goto classinput;
    }

    if(cls>10) {
        cout << "| Major          |";
        cout << "|  |1.Science    |";
        cout << "|  |2.Commerce   |";
        cout << "|  |3.Arts       |  ";
        strminput: cin >> stm;


        if(!valid(stm, 1, 3)) {
            cout << "Invalid Stream Input!";
            Sleep(1500);
            cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
            goto strminput;
        }

    }

    cin.ignore();
    cout << "| Address        |  "; cin.getline(adrs, 50);

    cout << "| Father's Name  |  "; cin.getline(f_name, 20);

    cout << "| Mother's Name  |  "; cin.getline(m_name, 20);
    cout << "| Mobile         |  "; cin >> mobile;



    // Allot Admission Number
    fstream admissions(admission_nos, ios::in | ios::app);
    admissions.seekg(0, ios::end);
    if(admissions.tellg()==0) {
        admissions << "\n" << 1000;
        adm = 1000;
    }
    else {
        admissions.seekg(-4, ios_base::end);
        admissions >> adm;
        adm++;
        admissions.seekg(0, ios::end);
        admissions << "\n" << adm;
    }

    admissions.close();

    cout << " | Admission No: " << adm;
    cout << "\n------------------------------------------------------------";
    cout << "\n\nPress ENTER to Confirm Admission";
    getch();

    s.fill(s_name, f_name, m_name, adrs, gender, cls, mobile, dob, adm, stm);

    string path = "Cl" + to_string(cls) + ".dat";

    ofstream stdnt(path, ios::binary | ios::app);
    stdnt.write((char*)&s, sizeof(s));
    stdnt.close();

















    system("cls");
    s.display('a', true);
    cout << "Record Added Successfully. Press ENTER to go back";
    getch();
}

void submit_fee_screen() {

    system("cls");

    char head[] = "FEE SUBMISSION";
    printHead(head);

    int fee_adm, feecls = 12;

    string path = "Cl" + to_string(feecls) + ".dat";
    cout << " | Class: ";

    //clsinput:
    cin >> feecls;
    /*if(!valid(feecls, 1, 12)) {
        cout << "Invalid Class Input!";
        Sleep(1500);
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        goto clsinput;
    }*/

    cout << " | Admission Number: ";
    cin >> fee_adm;


    Student s = find_stdnt(feecls, fee_adm);

    s.display('c', true);

    cout << " | Fee Amount: ";
    float f;
    cin >> f;

    if(s.submit_fee(f)) {
        cout << "\n Submitted Successfully\n\n";

        s.display('c', true);
        fstream mod(path, ios::binary | ios::in | ios::out);
        cout << "At: " << mod.tellp();
        if(!mod) {
            cout << "Failed to load file";

        }
        else {
            cout << "OPENED";
        }

        /*while(mod) {
            mod.read((char*)&s, sizeof(s));
            if(s.get_adm()==fee_adm) {
                mod.seekg(-sizeof(s), ios::cur);
                mod.write((char*)&s, sizeof(s));
                break;
            }
        }*/
        mod.close();
    }
    else {cout << " Fee Already Submitted";}

    cout << "\n\nPress ENTER to go back";
    getch();
}

void academic_screen() {
    system("cls");

    char head[] = "UPDATE ACADEMIC RECORDS";
    printHead(head);


    int empty_records[4] = {0};
    int m[4][5];
    Student s;
    int cls;
    cout << " | Class: ";
    cin >> cls;
    cout << endl;
    string path = "Cl" + to_string(cls) + ".dat";
    fstream acadmc(path, ios::binary | ios::in | ios::out);


    // Display which records are done for a given class
    while(acadmc) {
        acadmc.read((char*)&s, sizeof(s));

        s.get_marks(m);

        for(int i=0; i<4; i++) {
            bool empty = true;
            for(int j=0; j<5; j++) {
                if(m[i][j] != 0) {
                    empty = false;
                    break;
                }
            }
            if(empty)
                empty_records[i]++;
        }

    }
    cout << "|--------------------------------------------------------------------------------|\n";
    cout << "|      Exam      |  Quarterly 1  | Half Yearly 1 |  Quarterly 2  | Half Yearly 2 |\n";
    cout << "|--------------------------------------------------------------------------------|\n";
    cout << "| Empty Records  ";
    for(int i=0; i<4; i++)
        printElement(to_string(empty_records[i]).c_str(), 14);
    cout << "|";
    cout << "\n|--------------------------------------------------------------------------------|";

    acadmc.seekg(ios::beg);
    int exam_no;
    cout << "\n | Exam: ";
    cin >> exam_no;

    while(acadmc){
        acadmc.read((char*)&s, sizeof(s));
        cout << "\n---------------";
        cout << left << setw(20) << setfill('-') << s.get_name();
        cout << "----------Class: ";
        cout << left << setw(2) << setfill('-') << s.get_cl();
        cout << "---------------------------\n";
        cout << " | Marks: ";
        s.add_marks(exam_no);
    }

    acadmc.close();

    cout << "\nACADEMIC RECORDS UPDATED\n\n";
    Sleep(2000);

    cout << "1. Go Back \n2. Main Screen " ;
    int ch;
    cin >> ch;
    if(ch==1)
        academic_screen();


}

void fetch_screen() {
    system("cls");

    char head[] = "FETCH RECORDS";
    printHead(head);

    cout << " 1. Student Record \n 2. Class Record\n : ";
    int ch;
    cin >> ch;
    if(ch == 1){
        cout << "  A. General Details \n  B. Academic Report \n  C. Fee Record\n : ";
        char c;
        cin >> c;
        int cls, adm;
        cout << "  | Class: ";
        cin >> cls;
        cout << "  | Admission No: ";
        cin >> adm;
        if(c == 'a' || c=='A') {
            find_stdnt(cls, adm).display('a', true);
        }
        else if(c == 'b' || c=='B') {
            find_stdnt(cls, adm).display('b', true);
        }
        else if(c == 'c' || c=='C') {
            find_stdnt(cls, adm).display('c', true);
        }
        else {
            find_stdnt(cls, adm).display('a', true);
        }

    }
    else if(ch == 2) {

        Student s;
        cout << "  A. General Details \n  B. Academic Report";
        char c;
        cin >> c;
        int cls;
        cout << "  | Class: ";
        cin >> cls;
        // if(!valid(cls, 1, 12))
        //     goto clsinput;

        string path = "Cl" + to_string(cls) + ".dat";

        ifstream clas(path, ios::binary);

        bool head = true;

        while(clas) {
            clas.read((char*)&s, sizeof(s));
            if(c=='a' || c=='A')
                s.display('a', head);
            else
                s.display('b', head);
            head = false;
        }
        clas.close();
    }

    cout << "Press ENTER to go back";
    getch();

}

void delete_record_screen() {
    system("cls");
    char head[] = "DELETE RECORD";
    printHead(head);

    int cl, adm;

    cout << " | Class: "; cin >> cl;
    cout << " | Admission No.: "; cin >> adm;
    string path = "Cl" + to_string(cl) + ".dat";

    Student s;
    s = find_stdnt(cl, adm);
    s.display('a', true);

    cout << "\n | Are you sure you want to delete above record? (Y/N): ";

    char ch;
    cin >> ch;

    if(ch=='y' || ch=='Y') {
        ofstream tempadm("tempadm.txt");
        ofstream tempcl("tempcl.dat", ios::binary);
        ifstream cls(path, ios::binary);
        ifstream adms(admission_nos);

        // Copy other Admission Numbers to tempadm
        int admno;
        while (adms) {
            adms >> admno;
            cout << admno << endl;
            if (admno != adm)
                tempadm << admno + "\n";
        }

        // Copy other Students to tempcl
        Student st;
        while (cls) {
            cls.read((char *) &st, sizeof(st));
            if (st.get_adm() != adm)
                tempcl.write((char*) &st, sizeof(st));
        }



        remove(path.c_str());
        remove(admission_nos);
        rename("tempclass.txt", path.c_str());
        rename("tempadm.txt", admission_nos);

        tempadm.close();
        tempcl.close();
        cls.close();
        adms.close();

        cout << " Records Deleted Successfully";

        cout << " | Press ENTER to go back";
        getch();

    }


}

void notification_screen() {

    system("cls");
    char head[] = "NOTIFICATIONS";
    printHead(head);

    notification rn = {};

    fstream rnotifs("notifications.dat", ios::binary | ios::in | ios::out);

    if(!rnotifs){
        cout << "\n\n";
        center("Nothing to show here...");
        cout << "\n\n";
        center("|Press ENTER to go back|");
        getch();
        return;
    }

    while(rnotifs) {
        int pos = (int)(rnotifs.tellg());
        rnotifs.read((char*) &rn, sizeof(rn));
        cout << "> ";
        printElement(to_string(rn.timestamp).c_str(), 10);
        printElement(rn.text, 100);
        if(!rn.seen)
            cout << "←";
        cout << "\n-----------------------------------------------------------------\n";

        rn.seen = true;
        rnotifs.seekg(pos);
        rnotifs.write((char*) &rn, sizeof(rn));
    }
    rnotifs.close();
}

void modify_record_screen() {

    system("cls");

    char head[] = "MODIFY RECORD";
    printHead(head);

    int cls, adm;
    cout << " | Class: ";
    cin >> cls;
    cout << " | Admission Number: ";
    cin >> adm;

    Student s;
    s = find_stdnt(cls, adm);

    s.display('a', true);
    s.display('b', true);


    cout << ": ";
    char ch;
    cin >> ch;




}

void sign_out() {
    system("cls");
    cout << "\n | Sure you want to sign out? (Y|N): ";
    char ch;
    cin >> ch;
    if(ch=='y' || ch=='Y') {
        for(int j=0; j<2; j++) {
            system("cls");
            cout << endl << endl;
            cout << "Signing Out";
            for(int i=0; i<3;i++){
                Sleep(250);
                cout<<".";
                Sleep(250);
            }

        }
        exit(0);
    }
}

/* ----------------------------------------------------- */




