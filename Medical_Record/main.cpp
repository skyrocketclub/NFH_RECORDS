/*
 **    --------------------------------Always use in full screen for the best experience----------------------------------------------------------
            THE MEDICAL RECORDS OF NFH
    1 - SEARCH FOR A PATIENT --- (The Doctor Enters his name here so that any modification done in this session has his name attached to it)

    IF THE PATIENT IS NOT THERE
        --- ADD A NEW PATIENT
        --- GO BACK
    ELSE
            THEN THE ID OF THE PATIENT IS SOUGHT FOR ,(The first name can also be sought for and the list of all the people with that name pop)AND IF IT POPS UP
                THE DETAILS LIKE
                    NAME:
                    SEX:
                    GENOTYPE:
                    BLOOD GROUP:
                    ALLERGIES:

                    POP UP...
                THEN... RECORD OF PREVIOUS TREATMENTS POP UP IN A TABLE

                --S/N --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS --- MEMBER OF HOSPITAL STAFF

                        1. FOLLOW UP CASE?
                                SELECT THE NUMBER OF THE CASE TO FOLLOW UP...(THEN CHOOSE WHAT YOU WOULD LIKE TO EDIT/ADD INFO... EITHER
                                    SYMPTOMS
                                    DIAGNOSIS
                                    TREATMENT

                        2. NEW CASE...
                            SIMPLE ENTER THE
                --S/N --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS -------->

                        3. GO BACK
    2 - ADD A NEW PATIENT
            WHEN YOU WANT TO ADD A NEW PATIENT, JUST ASK FOR THE DETAILS ABOVE AND INPUT THEM INTO THE APPROPRIATE FILES

    3 - VIEW ALL PATIENTS.............VIEW ALL THE PATIENTS IN A WELL FORMATTED FORMAT WITH ALL THE BASIC INFORMATION ABOUT THEM

    4 - QUIT
****************************************************************************************************************************************************
*                                                   APROACH TO THE PROGRAMMING // PSEUDO CODE
*   1. Work on the display menu, which is like the engine house of the program
*   2. Then Implement the adding of a new patient first
*           1 .txt file will have the reg number and the basic details of all the patients (masterlist)
*                   NAME:
                    SEX:
                    GENOTYPE:
                    BLOOD GROUP:
                    ALLERGIES:
            Then there is a Patients folder---
                Here in this folder, once a patient is added to the hospital record, a file is opened automatically for him
                The name of the .txt file will be the reg number of the patient...
                This is where all the relevant information about the cases are stored...

                Implement --> List all patients...
    3. Then Implement "SEARCH FOR A PATIENT"
            --- Follow up case..(The Case availble )
                    Then Select the Case...The Case Appears on the screen
                        The Select if you want to
                            a. Edit the sympthon, diagnosis or treatment (If it is edited, the name of the two doctors will be present in the table)
                            b. Add... (Same as the above)
            --- New Case
                    Then add all the info required...
            --- Or Go Back
           There is always feedback like: Entry successful... ETC.....................


 **/


#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <direct.h>
#include <vector>
#include <iomanip>
#include <conio.h>


//Function Prototypes
void home();
int data_validation(int, int);
void quit();
void add_patient();
void search();
bool search_name(std::string,std::string);
bool search_id(std::string);
std::string capitalise(std::string);
std::string assign_num();
void view_all();
void p_operation(std::string);
void p_operation_editnew(std::string);
bool file_update(std::string, std::vector<std::string>); //where the doctor  after he/she has signed in actually edit patient's data.
void admin();
void add_doctors();
int case_num(std::string);
std::vector<int> get_date();

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

/*
 *          THINGS TO IMPLEMENT
 *
 *          Subject to further implementation in the second version
 *1. Implement having database for the doctors so that they are identified via their tags

 *
 *      -Then Implement that Only authorised doctors can access patients portal in order to edit
 *            ---Before The doctor can edit the details of a patient, the doctor will enter the serial number
 *               and the last name as validation
 *            ---Then if the doctor cannot login
 *                   go to home
 *                   Try again
 *
 *2. Then Implement the NEw TReatment Function
 *             --- Implement the doctor's name to be written alongside treatments made
 *3. Then Implement the edit treatment Function or Add...
 *
 * */
char quitter{ '1' };

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int succesful{}, patients{};
        succesful= _mkdir("NFH");
        patients = _mkdir("NFH/PATIENTS");
        home();
    return a.exec();
}

void home() {
    if (quitter != '0')
    {
        cout << "=======================================================================================================\n";
        cout << "|                                  N. F. H. MEDICAL RECORDS                                           | \n";
        cout << "=======================================================================================================\n";
        cout << "| 1 - SEARCH FOR A PATIENT                                                                            |\n";
        cout << "| 2 - ADD A NEW PATIENT                                                                               |\n";
        cout << "| 3 - VIEW ALL PATIENTS                                                                               |\n";
        cout << "| 4 - ADMIN MODE                                                                                      |\n";
        cout << "| 5 - QUIT                                                                                            |\n";
        cout << "=======================================================================================================\n";
        int entry;
        entry = data_validation(1, 5);
        switch (entry)
        {
            case 1:
            {
                search();
                home();
            }break;

            case 2:
            {
                add_patient();
                home();
            }break;

            case 3:
            {
                view_all();
                home();
            }break;

            case 4:
            {
                admin();
                home();
            }break;
            case 5:
            {
                quit();
                home();
            }break;
            default:
                break;
            }
    }


}

void admin(){
    bool done {false};

    cout<<"\t\tADMIN MODE\n";
    char userChar[100], input, passChar[100];

    while(!done){
        cout<<"PASSWORD: ";

        for(int i{0};;i++) //A loop that is terminated when you press enter begins here
        {
            input = _getch(); //You type in the password here
            if((input!=8)&&(input!=13)){
                passChar[i] = input;
                cout<<"*";
            }

            else if(input == 8){
                i-=2;
            }

            else if(input == 13){
                break;
            }
        }

        if(strcmp(passChar,"0000")==0){
            done = true;
            add_doctors();
        }
        else{
            cout<<"\nPassword Incorrect!\n";
            done = true;
        }
    }
}

void add_doctors(){
    //Insert the doctor's first name and last name
    //A serial number is generated automatically and is shown to the admin (Assuming a tag is to be prepared)
    // Once the doctor is created, let him know his tag number

    string f_name {}, l_name{}, word{};
    int serial_no{1};

    //Opening the document for saving the doctors and getting the number available
    string doc_file = "NFH/Doctorlist.txt";
    std::ofstream out_file;
    out_file.open(doc_file,std::ios::app);
    out_file.close();

//    getting the number available to give next doctor added a serial number
    std::ifstream in_file;
    in_file.open(doc_file);
    while(std::getline(in_file,word)){
        serial_no++;
    }
    in_file.close();


    system("cls");
    std::cin.ignore(1,'\n');
    cout<<"ADDING NEW DOCTOR TO DATABASE\n";
    cout<<"FIRSTNAME: ";
    std::getline(std::cin,f_name);
    f_name = capitalise(f_name);

    cout<<"LASTNAME: ";
    std::getline(std::cin,l_name);
    l_name = capitalise(l_name);


    out_file.open(doc_file,std::ios::app);
    out_file<<serial_no<<"#"<<f_name<<"#"<<l_name<<endl;
    out_file.close();

    cout<<f_name<<" "<<l_name<<" has been added succesfully\nSERIAL NUMBER: "<<serial_no<<endl;
}

void search() {
    //Implement the serial number here............

    /*
        The user is asked if he would like to search using the patients ID or the patients name...
         Then chooses his preferred choice. When he searches, the function search_name or search_id is used depending on the choice of the user
         if the user is found
            Then {

            The Doctor Enters his name here so that any modification done in this session has his name attached to it)

    IF THE PATIENT IS NOT THERE
        --- ADD A NEW PATIENT
        --- GO BACK
    ELSE
            THEN THE ID OF THE PATIENT IS SOUGHT FOR ,(The last name can also be sought for and the list of all the people with that name pop)AND IF IT POPS UP
                THE DETAILS LIKE
                    NAME:
                    SEX:
                    GENOTYPE:
                    BLOOD GROUP:
                    ALLERGIES:

                    POP UP...
                THEN... RECORD OF PREVIOUS TREATMENTS POP UP IN A TABLE

                --S/N --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS --- MEMBER OF HOSPITAL STAFF

                        1. FOLLOW UP CASE?
                                SELECT THE NUMBER OF THE CASE TO FOLLOW UP...(THEN CHOOSE WHAT YOU WOULD LIKE TO EDIT/ADD INFO... EITHER
                                    SYMPTOMS
                                    DIAGNOSIS
                                    TREATMENT

                        2. NEW CASE...
                            SIMPLE ENTER THE
                --S/N --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS -------->

                        3. GO BACK

    */
    system("cls");
    qInfo()<<"\t\tSEARCH FOR A PATIENT\n1 - SEARCH WITH ID\n2 - SEARCH WITH NAME\n";
    int choice = data_validation(1,2);
    if(choice == 1){
        //User to search with ID
        bool found{false};

        string id{};
        std::cout<<"Enter the ID: ";
        std::cin>>id;
        found = search_id(id);

        if(found == true){
            p_operation(id);
        }
        else{
            qInfo()<<"\nID not found \n";
            //You can implement here that a new user can be added here or home
        }
    }

    else{
        //user to search with name
        //Then the names that match are outputed with the ID---
        //THen the ID can be used to search and continue the operation...
    }
}

void p_operation_editnew (std::string id){
    /*


     *     2. NEW CASE...
                            SIMPLE ENTER THE
                --DOCTOR --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS -------->

     * */

    string s_num, s_name;
    cout<<"\t\tDETAILS OF THE MEDICAL DOCTOR\n";
    cout<<"SERIAL NUMBER: ";
    cin>>s_num;

    /*
     *Then the serial number is searched for to see if it is available
     *  Then if it is available
     *      The name of the doctor is then output
     *      The doctor should select Yes, or No (if that is not him)
     *  If it is not available
     *      A message shows that that serial number is not currently available
     * */

     string line,sub;
     bool found {false};
     vector<string> doctors,subset;
     string doc_file = "NFH/Doctorlist.txt";
     std::ifstream in_file;
     in_file.open(doc_file);
     if(!in_file){
         std::cerr<<"Error Opening File";
     }
     else{
        while(getline(in_file,line)){
            doctors.push_back((line));
        }
     }
     in_file.close();

     for(auto doc : doctors){
         std::istringstream sstream{doc};
         while(sstream.good()){
             std::getline(sstream,sub,'#');
             subset.push_back(sub);
         }
         if(subset.at(0)==s_num){
            found = true;
            break;
         }
     }

     if(found == true){
         cout<<"DOCTOR: "<<subset.at(0)<<" "<<subset.at(1)<<" "<<subset.at(2)<<"\n";
         cout<<"1 - PROCEED\n2 - GO TO HOME\n";
         int choice = data_validation(1,2);
         if (choice == 1){
                 cout<<"\nWELCOME DR "<<subset.at(1)<<endl;

                 //Call the file_update function here for doctor to add or edit an entry
                bool updated = file_update(id,subset);
                if(updated == true){
                    cout<<"\nUPDATES SAVED SUCCESSFULLY\n";
                }
                else{
                    cout<<"\nFILE UPDATE UNSUCCESSFUL\n";
                }
         }else{
             cout<<"If you are not "<<subset.at(1)<<" "<<subset.at(2)<<", you can register new doctors in admin mode (Note Your Serial Number)\n";
             home();
         }

     }
     else{
         //Doctor not found---
         cout<<"NO DOCTOR FOUND WITH SERIAL NUMBER "<<s_num<<endl;
         home();
     }
}

//WORK TO DO HERE...1
void p_operation(std::string id){
    /*


                        2. NEW CASE...
                            SIMPLE ENTER THE
                --S/N --- SYMPTOMS --- DIAGNOSIS --- TREATMENTS -------->

                        3. GO BACK
     * */
    system("CLS");
    qInfo()<<"\t\t\t\t PATIENT'S HISTORY";
    std::ifstream in_file;
    string file_num = "NFH/PATIENTS/" + id + ".txt";
    in_file.open(file_num);

    if(!in_file){
        cout<<"Error Opening "<<file_num<<" file\n";
    }

    string s_num{}, f_name{},mid_name{}, l_name{}, gender{}, genotype{}, bloodgroup{}, allergies{};
    int sex{}, geno{}, blood_gp{};
    string file_line{};
    vector<string> p_data{};


    //Read all the contents of the opened document into a vector
    //The first line of the document will typically be the general information of the patient
    //Then subsequent data will be previous cases...

    while(std::getline(in_file,file_line)){
        p_data.push_back(file_line);
    }
    in_file.close(); //The entire content of the file has been read into a vector...p_data

    //Writing out the initial details of the patient so that all doctors have an overview/ background
    vector<string>p1_data{};
    string substr{};
    std::istringstream s_stream {p_data.at(0)};
    while(s_stream.good()){
        std::getline(s_stream, substr, '#');
        p1_data.push_back(substr);
    }

    //Outputing the Patients Personal Details
    cout << "\n\n=============================================================================================================\n";
    cout <<" "<<std::setw(4)<<std::left<<"S/N" << std::setw(7) << std::left << "ID" << std::setw(15) << std::left << "FIRST NAME"
        << std::setw(15) << std::left << "MIDDLE NAME"<< std::setw(15) << std::left << "LAST NAME" << std::setw(8) << std::left << "SEX"
        << std::setw(10) << std::left << "GENOTYPE" << std::setw(13) << std::left << "BLOOD GRP" <<
        std::setw(40) <<std::right<< "ALLERGIES                       " << "\n";
    cout << "=============================================================================================================\n";
    cout << " " <<std::setw(4)<<std::left<<p1_data.at(0) << std::setw(7) << std::left << p1_data.at(1) << std::setw(15) << std::left << p1_data.at(2)
        << std::setw(15) << std::left << p1_data.at(3) << std::setw(15) << std::left << p1_data.at(4)
        << std::setw(10) << std::left << p1_data.at(5) << std::setw(11) << std::left << p1_data.at(6) <<
        std::setw(17)<< std::left << p1_data.at(7)<<std::setw(50)<<std::left<<p1_data.at(8) << "\n";
    cout << "=============================================================================================================\n\n\n";

    if(p_data.size() == 1){
        cout<<"\nNO PREVIOUS RECORDS OF TREATMENT EXISTS\n";
        cout<<"ADD A NEW TREATMENT\n1 - YES\n2 - NO\n";
        int new_treatment = data_validation(1,2);

        if (new_treatment==1){
             p_operation_editnew(id);
        }
       else{
           home();
        }
    }

    else{
        //when there are already records of the patient inputed prior by a medical doctor
        //display the history of treatments
        //Implement how to display the history first, before doctor starts treetment
        //In displaying, give room for whether treatment status is primary or follow up
        /*
         * 1 - case number
         * 2 - day
         * 3 - Month
         * 4 - Year
         * 5 - Ailment
         * 6 - Diagnosis
         * 7 - Prescription
         * 8 - Dr First Name
         * 9 - Dr Last Name
         * 10 - Pri or F.UP
         * */
        cout<<std::setw(4)<<std::left<<"S/N"<<std::setw(13)
           <<std::left<<"DATE"<<std::setw(50)<<std::left<<"AILMENT"
           <<std::setw(30)<<std::left<<"DIAGNOSIS"<<std::setw(40)<<std::left
          <<"PRESCRIPTION"<<std::setw(20)<<std::left<<"DOCTOR"<<std::setw(5)<<std::left<<"STATUS\n";
        cout<<"______________________________________________________________________________________________________________________________________________________________________\n";
        //All the case numbers of the patient are currently stored in a vector called p_data

        for(size_t i{1}; i<p_data.size(); i++){

                //each case is a string, data is obtaine using # as the delimiter...
                vector<string>pn_data{};
                string substrs{};
                std::istringstream s_stream {p_data.at(i)};
                while(s_stream.good()){
                    std::getline(s_stream, substrs, '#');
                    pn_data.push_back(substrs);
                }

                //Now displaying the particular case that was input into the vector...
                cout<<std::setw(4)<<std::left<<pn_data.at(0)<<std::setw(2)<<std::left<<pn_data.at(1)<<"/"
                   <<std::setw(2)<<std::left<<pn_data.at(2)<<"/"<<std::setw(7)<<std::left<<pn_data.at(3)
                  <<std::setw(50)<<std::left<<pn_data.at(4)<<std::setw(30)<<std::left<<pn_data.at(5)
                 <<std::setw(40)<<std::left<<pn_data.at(6)<<std::setw(10)<<std::left<<pn_data.at(7)
                <<std::setw(10)<<std::left<<pn_data.at(8)<<std::setw(5)<<std::left<<pn_data.at(9)<<std::endl<<std::endl;
        }
        p_operation_editnew(id);
        home();
    }
}

//WORK TO DO HERE...2
//Doctor to reference already existing cases.
bool file_update(std::string patient, std::vector<std::string> doctor){
    bool done{false};

    /*
     *The patient passed is the serial number
     *The doctor vector passed here is a vector of the details of the doctor.
     *
     *
     * IF SIZE = 1, THEN THE ONLY THING THERE IS GENERAL INFO, NO RECORDED INPUTS YET
     * CHOOSE MAKE AND INPUT
     * //MEANS THAT ALL CASES HAVE CATEGORIES
     * ---- THEY ARE EITHER FOLLOW UP CASES OR NEW CASES ----
     * --- THEN YOU MAKE THE INPUT...
     * --- IN A NEATLY FORMARTED TABLE
     *
     * C'EST FINI.
     *
     * */

    string d_fname{doctor.at(1)}, d_lname{doctor.at(2)}, patient_doc, line;
    std::vector<string> history;
    int case_number = case_num(patient);


    patient_doc = "NFH/PATIENTS/"+patient + ".txt";
    std::ifstream in_file;
    in_file.open(patient_doc);

    if(!in_file){
        std::cerr<<"ERROR OPENING PATIENT FILE\n";
    }
    else{
        //reading all the patient's history into a vector
        while(std::getline(in_file,line)){
            history.push_back(line);   //You are reading all the history of patients into a vector...
        }
        in_file.close();
    }


    //Writing the details of treatment into the file of the patient..
    std::ofstream out_file(patient_doc,std::ios::app);

    if(case_number == 1){ //Only the patient's basic history is written in the patient's file
   arrive:     string symptoms, diagnosis, treatment;

        /*
         *   2. NEW CASE...
                        SIMPLE ENTER THE
            --S/N ---DATE----SYMPTOMS --- DIAGNOSIS --- TREATMENTS ----DOCTOR---->

                    3. GO BACK
         * */

       cout<<"\t\tDATE: \n";
       std::vector<int> date = get_date();
       cout<<std::endl;

       std::cin.ignore(1,'\n');
       cout<<"\t\tSYMPTOMS:  \n";
       std::getline(std::cin, symptoms);
       cout<<std::endl;

       cout<<"\t\tDIAGNOSIS:   \n";
       std::getline(std::cin,diagnosis);
       cout<<std::endl;

       cout<<"\t\tTREATMENTS\n";
       std::getline(std::cin, treatment);
       cout<<std::endl;

       out_file<<case_number<<"#"<<date.at(0)<<"#"<<date.at(1)<<"#"<<date.at(2)<<"#"<<symptoms<<"#"<<diagnosis<<"#"<<treatment<<"#"<<d_fname<<"#"<<d_lname<<"#"<<"PRI"<<std::endl;
       done = true;
    }
    else{
        //There are already existing entries int the file of the patient...
        /*
         *
         *  IF THE SIZE > 1, THEN CHOOSE,
             * 1 - FOLLOW UP CASE
             * 2 - NEW CASE
             *
             * IF NEW CASE --- THEN SIMPLY ADD...
             * IF FOLLOWUP CASE, THEN TYPE THE NUMBER---
             * THE PROGRAM SHOWS YOU THE CASE ---
             * THEN YOU KIND OF MAKE A COPY OF IT
             * THEN YOU IMPLEMENT YOUR FOLLOW UP STUFF
             *          (PERHAPS HERE, SOME FIELDS WILL BE BLANK AS THE HAVE BEEN FILLED BEFORE)
             * THEN YOU PASTE YOUR NEWLY EDITED ENTRY AFTER THE ORIGINAL WITH A TAG CALLED --- FOLLOW UP
         * */
        cout<<"1 - FOLLOW UP A CASE \n2 - NEW CASE\n";
        int choice = data_validation(1,2);
        if(choice == 1){

            string symptoms,diagnosis, treatment;
            //all the previous treatments are currently in a vector called --history
            int cases = history.size();
            int case_number;

            cout<<"\nCASE NUMBER OF CASE TO BE FOLLOWED UP: \n";
            case_number= data_validation(1,cases-1);
            string primary = history.at(case_number); //Identifying the primary case to be followed up

            out_file.close();
            int case_serial = case_num(patient);
            out_file.open(patient_doc,std::ios::app);

            cout<<"\t\tDATE: \n";
            std::vector<int> date = get_date();
            cout<<std::endl;

            std::cin.ignore(1,'\n');
            cout<<"\t\tSYMPTOMS:  \n";
            std::getline(std::cin, symptoms);
            cout<<std::endl;

            cout<<"\t\tDIAGNOSIS:   \n";
            std::getline(std::cin,diagnosis);
            cout<<std::endl;

            cout<<"\t\tTREATMENTS\n";
            std::getline(std::cin, treatment);
            cout<<std::endl;

            out_file<<case_serial<<"#"<<date.at(0)<<"#"<<date.at(1)<<"#"<<date.at(2)<<"#"<<symptoms<<"#"<<diagnosis<<"#"<<treatment<<"#"<<d_fname<<"#"<<d_lname<<"#"<<"FUP-"<<case_number<<std::endl;
        }
        else if(choice == 2){
           goto arrive;
        }
    }
    out_file.close();

    return done;
}

std::vector<int> get_date(){
    std::vector<int> date;
    int day, month, year;

    std::cout<<"DAY\n";
    day = data_validation(1,31);
    date.push_back(day);
    std::cout<<"MONTH\n";
    std::map<int,std::string> months {{1,"JANUARY"},{2,"FEBRUARY"},{3,"MARCH"},{4,"APRIL"},{5,"MAY"},{6,"JUNE"},{7,"JULY"},{8,"AUGUST"},{9,"SEPTEMBER"},{10,"OCTOBER"},{11,"NOVEMBER"},{12,"DECEMBER"}};

    for(auto val : months){
      cout<<val.first<<" - "<<val.second<<"\n";
    }
    month = data_validation(1,12);
    date.push_back(month);

    std::cout<<"YEAR\n";
    year = data_validation(2021,2050);
    date.push_back(year);

    return date;
}

bool search_id(std::string id){
    bool is_present{false};

    std::ofstream out_file("NFH/MASTERLIST.txt", std::ios::app);
    out_file.close();
    std::ifstream in_file;
    in_file.open("NFH/MASTERLIST.txt");
      string line{};
      std::vector<string> lines;

      while(std::getline(in_file,line)){
      lines.push_back(line);
     }
    in_file.close();
    //The Entire content of the .txt file has been read into the vector called lines
    //thus the vector can be manipulated from here to search for the ID, or to check how many registered patients there are...

    if(lines.size() == 0){
        //if the size of the vector is 0, then no need to even check for the ID...
    }
    else{
        for(size_t i{0}; i<lines.size(); i++){
            string current = lines.at(i);
            string sub;
            std::vector<string> lines_sub;
            std::istringstream s_stream{current};

            while(s_stream.good()){
               std::getline(s_stream,sub,'#');
               lines_sub.push_back(sub);
            }
            if(lines_sub.at(0) == id){
                std::cout<<lines_sub.at(0)<<" - "<<lines_sub.at(1)<<" "<<lines_sub.at(2)<<" "<<lines_sub.at(3)<<"\n";
                qInfo()<<"Proceed to Patient's History\n1 - YES\n2 - NO\n";
                int proceed = data_validation(1,2);
                if (proceed == 1){
                    is_present = true;
                }
                else{
                    home();
                }
            }
        }
    }

    return is_present;
}

int data_validation(int min, int max) {
    string entry{};
    int number{};
    bool done{false};

    do {
        cout << "ENTRY: ";
        cin >> entry;
        std::istringstream validator{ entry };
        if (validator >> number && (number>=min && number<=max)) {
            done = true;
        }
        else {
            std::cout << "PLEASE ENTER A VALID OPTION\n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    } while (!done);
    return number;
}

void quit() {
    system("CLS");
    cout << "\t\t\t=======================================================================================================\n";
    cout << "\t\t\t|                                 GOOD - BYE FROM N. F. H.                                            | \n";
    cout << "\t\t\t=======================================================================================================\n";
    cout << endl << endl;
    quitter = '0';
}


void add_patient() {
    /*
         THE DETAILS LIKE
                    NAME:
                    SEX:
                    GENOTYPE:
                    BLOOD GROUP:
                    ALLERGIES:
    */
    system("CLS");

    int case_number;
    string s_num{}, f_name{},mid_name{}, l_name{}, gender{}, genotype{}, bloodgroup{}, allergies{};
    int sex{}, geno{}, blood_gp{};
    std::ofstream out_file("NFH/MASTERLIST.txt", std::ios::app);

    cout << "HOW MANY PATIENTS WOULD YOU LIKE TO ADD?: ";
    bool done{ false };
    std::string entry;
    int number;
    do {
        cin >> entry;
        std::istringstream validator{ entry };
        if (validator >> number) {
            done = true;
        }
        else {
            cout << "KINDLY ENTER A VALID INPUT\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!done);
    cin.ignore(1, '\n');

    for (int i{ 0 }; i < number; i++) {

        cout << "\t\t\t==================================================\n";
        cout << "\t\t\t|                  PATIENT " << i +1<< "                     |\n";
        cout << "\t\t\t==================================================\n";


        s_num = assign_num(); //The serial number is automatically generated...
        out_file << s_num << "#";




        cout << "FIRST NAME: ";
        std::getline(cin, f_name);
        f_name = capitalise(f_name);
        out_file << f_name << "#"; //Writing Information to the Master list in the NFH Folder...
        cout << endl;

        cout << "MIDDLE NAME: ";
        std::getline(cin, mid_name);
        mid_name = capitalise(mid_name);
        out_file << mid_name << "#"; //Writing Information to the Master list in the NFH Folder...
        cout << endl;

        cout << "LAST NAME: ";
        std::getline(cin, l_name);
        l_name = capitalise(l_name);
        out_file << l_name << "#";
        cout << endl;

        cout << "SEX \n1 - MALE\n2 - FEMALE\n";
        sex = data_validation(1, 2);
        if (sex == 1) {
            gender = "MALE";
            out_file << "MALE" << "#";
        }
        else {
            gender = "FEMALE";
            out_file << "FEMALE" << "#";
        }
        cout << endl;



        cout << "GENOTYPE: \n1 - AA\n2 - AS \n3 - SS\n";
        geno = data_validation(1, 3);
        if (geno == 1) {
            genotype = "AA";
        }
        else if (geno == 2) {
            genotype = "AS";
        }
        else {
            genotype = "SS";
        }
        cout << endl;
        out_file << genotype << "#";



        cout << "BLOOD GROUP\n1 - A+\n2 - O+\n3 - B+\n4 - AB+\n5 - A-\n6 - O-\n7 - B-\n8 - AB-\n";
        blood_gp = data_validation(1, 8);
        switch (blood_gp)
        {
        case 1:
        {
            bloodgroup = "A+";

        }break;

        case 2:
        {
            bloodgroup = "O+";

        }break;

        case 3:
        {
            bloodgroup = "B+";
        }break;

        case 4:
        {
            bloodgroup = "AB+";
        }break;

        case 5:
        {
            bloodgroup = "A-";
        }break;

        case 6:
        {
            bloodgroup = "O-";
        }
        break;

        case 7:
        {
            bloodgroup = "B-";
        }
        break;

        case 8:
        {
            bloodgroup = "AB-";
        }
        break;
        default:
            break;
        }
        cout << endl;
        out_file << bloodgroup << "#";

        cin.ignore(1, '\n');
        cout << "ENTER ALLERGIES\nPLEASE WRITE THE ALLERGIES SEPARATED BY A COMMA (IF MORE THAN 1)\nALLERGIES: ";
        std::getline(std::cin, allergies);
        allergies = capitalise(allergies);
        out_file << allergies << endl;

        //OPEN A FILE FOR THE PATIENT...
        std::string file_no = "NFH/PATIENTS/"+s_num + ".txt";

        //Writing the case number 0 of the patient.
        std::ofstream out_file2(file_no, std::ios::app);
        case_number = case_num(s_num);
        out_file2.close();

        //Writing the other basic info of the patient
        out_file2.open(file_no, std::ios::app);
        out_file2 <<case_number<<"#"<< s_num << "#" << f_name << "#"<<mid_name<<"#" << l_name << "#" << gender << "#" << genotype << "#" << bloodgroup << "#" << allergies << endl;
        out_file2.close();
        cout<<"FILE NUMBER: "<<s_num<<endl;
    }


    if(number>1){
        cout <<number << " PATIENTS HAVE BEEN SUCCESSFULLY ADDED\n\n";
    }

    else if (number==1){
         cout <<number << " PATIENT HAS BEEN SUCCESSFULLY ADDED\n\n";
    }

    out_file.close();
}

int case_num(std::string id){
    std::ifstream in_file;
    std::string lined = "NFH/PATIENTS/" + id + ".txt";
    in_file.open(lined);

    int count{0};
    string line{}; //to represent the last line at every point in time
    while (getline(in_file, line)) {
        count++;
    }
    return count;
}

std::string assign_num() {
    std::ifstream in_file;
    in_file.open("NFH/MASTERLIST.txt");

    int num{}, count{0};
    string line{}, c_line{}, c_num{}, r_num{}; //to represent the last line at every point in time
    while (getline(in_file, line)) {
        c_line = line;
        count++;
    }

    if (count == 0) { //If the document is empty, It means the person is the first on the list...
        return "0001";
    }

    //c_line upon exit of the while loop will then be the last line... which is what you want...
    std::istringstream sstream{ c_line };
    getline(sstream, c_num, '#');
    num = stoi(c_num);
    num++;

    r_num = std::to_string(num);

    if (num < 10) {
        r_num = "000" + r_num;
    }

    else if (num > 9 && num < 100) {
        r_num = "00" + r_num;
    }

    else if (num>99 && num < 999) {
        r_num = "0" + r_num;
    }

    else {}

    in_file.close();
    return r_num;
}

std::string capitalise(std::string word) {

    std::transform(word.begin(), word.end(), word.begin(), toupper);
    return word;
}

void view_all() {
    /*
                    NAME:
                    SEX:
                    GENOTYPE:
                    BLOOD GROUP:
                    ALLERGIES:

    */
    std::string line{}, f_name{}, l_name{}, sex{}, genotype{}, blood_group{}, allergies{};

    system("cls");
    std::ifstream in_file;
    in_file.open("NFH/MASTERLIST.txt");

    cout << "\n\n=============================================================================================================\n";
    cout <<" "<< std::setw(7) << std::left << "ID" << std::setw(15) << std::left << "FIRST NAME"
        << std::setw(15) << std::left << "MIDDLE NAME"<< std::setw(15) << std::left << "LAST NAME" << std::setw(8) << std::left << "SEX"
        << std::setw(10) << std::left << "GENOTYPE" << std::setw(13) << std::left << "BLOOD GRP" <<
        std::setw(40) <<std::right<< "ALLERGIES                       " << "\n";
    cout << "=============================================================================================================\n";

    while (std::getline(in_file, line)) {
        std::vector<std::string> lists;
        std::string substr;
        std::istringstream s_stream{ line };
        while (s_stream.good()) {
            std::getline(s_stream, substr, '#');
            lists.push_back(substr);
        }

        //Modify the content of the vectors here so that ou can output the list ...
        cout << " " << std::setw(7) << std::left << lists.at(0) << std::setw(15) << std::left << lists.at(1)
            << std::setw(15) << std::left << lists.at(2) << std::setw(15) << std::left << lists.at(3)
            << std::setw(10) << std::left << lists.at(4) << std::setw(11) << std::left << lists.at(5) <<
            std::setw(17)<< std::left << lists.at(6)<<std::setw(50)<<std::left<<lists.at(7) << "\n";
    }
    cout << "=============================================================================================================\n\n";

    in_file.close();
}
