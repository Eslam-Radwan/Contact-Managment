#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

using namespace std;

struct Contact
{
	string First_Name, Last_Name, Phone_Number, Email_Address;
	bool category[3] = { 0 };
	//category[0]--> family    category[1]--> friend    category[0]--> work ;
};

// pre program functions 
int log_in();
void delchar(string username);
void menu();

string to_stringg(int num);
string reverss(string s);


// program main functions
void edit(), display_contact(bool display_choice), add(), delet();
int valid_input(int l, int r);


//search
void search();
void Header(bool search);
int search_footer();
void display_one_contact(int i);

//file stream functions
void import();
void display_import_contacts(string Import_From);
string Export_or_Backup();
void add_erase_chosen_numbers(int choice);
void erase_array();
void Export();
void back_up();


//category
void category_menu();
void category(int type);
void add_to_category(int type);
void delett_category(int type);
void display_category(int type);

//global variables 
int const size_of_array = 1000;
Contact Contacts[size_of_array];
int chosen_contacts[size_of_array];
int import_counter = 0;
int number_of_contacts = 0;
//for display
const int name_length = 10, number_length = 15, email_length = 30, category_length = 8; const char separator = ' ';
bool  return_category = 0;

string password;
int incorrect = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////program start////////


int main()
{
	while (log_in() == 0) { password.clear(); incorrect = 1; }
	menu();
	back_up();
	return 0;
}


int log_in()
{
	cout << "...................................Log In...................................\n\n";
	string username;
	//char   password = 'a';
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	while (true)
	{
		char p;
		p = _getch();
		if (p == '\r')break;
		else if (p == '\b')
		{
			if (!password.empty())
			{
				password.pop_back();
				delchar(username);
			}
		}
		else
		{
			password.push_back(p);
			cout << '*';
		}
	}
	if (password == "1234" && username == "admin")
	{
		system("cls");
		cout << "Login Successsfully\n";
		return 1;
	}
	else
	{
		system("cls");
		cout << "Username or password is incorrect please try again\n";
		return 0;
	}
}
void delchar(string username)
{
	system("cls");
	if (incorrect)cout << "Username or password is incorrect please try again\n";
	cout << "...................................Log In...................................\n\n";
	cout << "Username: " << username << "\n";
	cout << "Password: ";
	for (int i = 0; i < password.size(); i++)
		cout << '*';


}
void menu()
{

	int  choice = 1;
	while (true) {
		cout << "...................................Main Menu..................................." << endl;
		cout << " [1] Display Contatct                       [2] Add A New Contact              " << endl;
		cout << " [3] Delete Contacts                        [4] Categorize Contacts            " << endl;
		cout << " [5] Search Contacts                        [6] Edit Contacts                  " << endl;
		cout << " [7] Export Contacts                        [8] Import Contacts                " << endl;
		cout << " [9] Back Up                                [0] Exit                           " << endl;

		cout << "\nGo To:";
		choice = valid_input(0, 9);
		if (choice == 1) {
			system("cls");  display_contact(1);
		}
		else if (choice == 2) add();
		else if (choice == 3) delet();
		else if (choice == 4) category_menu();
		else if (choice == 5) { system("cls");   search(); }
		else if (choice == 6)edit();
		else if (choice == 7)Export();
		else if (choice == 8)import();
		else if (choice == 9)back_up();
		else if (choice == 0)
		{
			back_up();
			return;
		}
	}
}
string reverss(string s)
{
	string ss;
	for (int i = s.size() - 1; i >= 0; i--)
		ss += s[i];
	return ss;
}
string to_stringg(int num)
{
	string s;
	for (; num; num /= 10)
		s += (num % 10 + 48);

	return reverss(s);
}
void display_contact(bool display_choice) {

	int choice;
	Header(0);
	for (int i = 0; i < number_of_contacts; i++) {
		string numm = "[" + to_stringg(i + 1) + "]";
		cout << left << setw(6) << setfill(separator) << numm;
		cout << left << setw(name_length) << setfill(separator) << Contacts[i].First_Name << "|";
		cout << left << setw(name_length) << setfill(separator) << Contacts[i].Last_Name << "|";
		cout << left << setw(number_length) << setfill(separator) << Contacts[i].Phone_Number << "|";
		cout << left << setw(email_length) << setfill(separator) << Contacts[i].Email_Address << "|";
		if (Contacts[i].category[0] == 1)
			cout << left << setw(category_length) << setfill(separator) << "family" << "|";
		if (Contacts[i].category[1] == 1)
			cout << left << setw(category_length) << setfill(separator) << "friend" << "|";
		if (Contacts[i].category[2] == 1)
			cout << left << setw(category_length) << setfill(separator) << "work" << "|";



		cout << "\n";
	}
	if (display_choice == 1) {
		cout << "[1]Back to menu\n";
		cout << "Go To: ";
		cin >> choice;
		system("cls");

	}
}

int valid_input(int l, int r)
{
	int x;
	while (true) {


		cin >> x;
		bool ok = cin.fail();
		if (x >= l && x <= r && !ok)break;
		else
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "\nInvalid Choice\n";

		}
		cout << "please enter your choice: ";
	}
	return x;

}

void add()
{
	system("cls");

	while (true)
	{
		cout << "Enter First Name : ";
		cin >> Contacts[number_of_contacts].First_Name;
		cout << "\nEnter Last Name : ";
		cin >> Contacts[number_of_contacts].Last_Name;
		cout << "\nEnter Phone Number : ";
		cin >> Contacts[number_of_contacts].Phone_Number;
		cout << "\nEnter Email Address : ";
		cin >> Contacts[number_of_contacts].Email_Address;
		number_of_contacts++;
		//continue

		cout << "\n[1] Add another contact\t[2] Back to menu ";
		cout << "\nGo to: ";


		if (valid_input(1, 2) == 2) {
			system("cls");
			return;
		}
	}
}
void delet()
{
	while (true) {
		system("cls");


		int delete_var;

		display_contact(0);
		cout << "number of contact to delete\n";
		delete_var = valid_input(1, number_of_contacts);


		for (int i = 0; i < 3; i++) {
			Contacts[delete_var - 1].category[i] = 0;
		}


		for (int i = delete_var - 1; i < number_of_contacts; i++) {

			Contacts[i] = Contacts[i + 1];

		}number_of_contacts--;

		system("cls");
		display_contact(0);

		cout << "\n[1] Delete another contact\t[2] Back to menu \n";
		if (valid_input(1, 2) == 2) {
			system("cls");
			return;
		}

	}


}
void edit() {
	while (true) {
		system("cls");
		display_contact(0);
		int choice, edit_contact, op2;
		string neww;
		cout << "Enter contact number to edit: ";
		edit_contact = valid_input(1, number_of_contacts);
		cout << "[1] " << Contacts[edit_contact - 1].First_Name << '\n';
		cout << "[2] " << Contacts[edit_contact - 1].Last_Name << '\n';
		cout << "[3] " << Contacts[edit_contact - 1].Phone_Number << '\n';
		cout << "[4] " << Contacts[edit_contact - 1].Email_Address << '\n';
		cout << "enter what you want to edit: ";
		op2 = valid_input(1, 4);
		if (op2 == 1) {
			cout << "enter new first name: ";
			cin >> neww;
			Contacts[edit_contact - 1].First_Name = neww;
		}
		else if (op2 == 2) {
			cout << "enter new last name: ";
			cin >> neww;
			Contacts[edit_contact - 1].Last_Name = neww;

		}
		else if (op2 == 3) {
			cout << "enter new number: ";
			cin >> neww;
			Contacts[edit_contact - 1].Phone_Number = neww;
		}
		else if (op2 == 4) {
			cout << "enter new email adress: ";
			cin >> neww;
			Contacts[edit_contact - 1].Email_Address = neww;
		}
		cout << "\n[1] edit contact\t[2] Back to menu ";
		cout << "\nGo to: ";
		choice = valid_input(1, 2);
		if (choice == 2) {
			system("cls");
			return;
		}
	}

}

//search functions
void search()
{
	//intialize
	int choice = 0;
	while (true)
	{
		//search menu
		cout << "...................................Search Contacts...................................\n" << endl;
		cout << "[1]Search by name\t[2]Search by number\t[3]Search by email address\t[4]Back to the menu" << endl;
		cout << "\nGo to: ";
		choice = valid_input(1, 4);
		system("cls");


		// search by name
		if (choice == 1)
		{
			bool found = 0;
			string name;
			cout << "...................................Search Contacts...................................\n" << endl;
			cout << "Search->Search by name\n";
			cout << "Search for: ";
			cin.ignore();
			getline(cin, name);
			cout << "\n";
			for (int i = 0; i < number_of_contacts; i++)
			{
				string s;
				s = Contacts[i].First_Name + " " + Contacts[i].Last_Name;
				if (s.find(name) >= 0 && s.find(name) < s.size())
				{
					if (found == 0)
					{
						Header(1);
						found = 1;
					}
					display_one_contact(i);
				}
			}
			if (found == 0)cout << "There is no name found" << endl;
			if (search_footer() == 1)continue;
			else return;
		}


		//search by number
		else if (choice == 2)
		{
			bool found = 0;
			string number;
			cout << "...................................Search Contacts...................................\n" << endl;
			cout << "Search->Search by number\n";
			cout << "Search for: ";
			cin >> number;
			cout << "\n";
			for (int i = 0; i < number_of_contacts; i++)
			{
				if (Contacts[i].Phone_Number.find(number) >= 0 && Contacts[i].Phone_Number.find(number) < Contacts[i].Phone_Number.size())
				{
					if (found == 0)
					{
						Header(1);
						found = 1;
					}
					display_one_contact(i);
				}
			}
			if (found == 0)cout << "\nThere is no number found" << endl;
			if (search_footer() == '1')continue;
			else return;
		}


		//search by email
		else if (choice == 3)
		{
			bool found = 0;
			string email;
			cout << "...................................Search Contacts...................................\n" << endl;
			cout << "Search->Search by email address\n";
			cout << "search for: ";
			cin >> email;
			cout << "\n";
			for (int i = 0; i < number_of_contacts; i++)
			{
				if (Contacts[i].Email_Address.find(email) >= 0 && Contacts[i].Email_Address.find(email) < Contacts[i].Email_Address.size())
				{
					if (found == 0)
					{
						Header(1);
						found = 1;
					}
					display_one_contact(i);
				}
			}
			if (found == 0)cout << "\nThere is no email found" << endl;
			if (search_footer() == 1)continue;
			else return;
		}

		//back to the main menu
		else if (choice == 4)return;
	}
}
void Header(bool search)
{
	Contact Head;
	if (search)
		Head.First_Name = "First Name";
	else
		Head.First_Name = "      First Name";
	Head.Last_Name = "Last Name";
	Head.Phone_Number = "Phone Number";
	Head.Email_Address = "Email Address";
	cout << left << setw(name_length) << setfill(' ') << Head.First_Name << "|";
	cout << left << setw(name_length) << setfill(' ') << Head.Last_Name << "|";
	cout << left << setw(number_length) << setfill(' ') << Head.Phone_Number << "|";
	cout << left << setw(email_length) << setfill(' ') << Head.Email_Address << "|" << "         ";
	cout << left << setw(8) << setfill(' ') << "Category" << endl;

}
int search_footer()
{
	char choice;
	cout << "\n[1]Do another search\t[2]Back to the menu" << endl;
	cout << "\nGo to: ";
	choice = valid_input(1, 2);
	system("cls");
	return choice;
}
void display_one_contact(int i)
{
	cout << left << setw(name_length) << setfill(' ') << Contacts[i].First_Name << "|";
	cout << left << setw(name_length) << setfill(' ') << Contacts[i].Last_Name << "|";
	cout << left << setw(number_length) << setfill(' ') << Contacts[i].Phone_Number << "|";
	cout << left << setw(email_length) << setfill(' ') << Contacts[i].Email_Address << "|";
	if (Contacts[i].category[0] == 1)
		cout << left << setw(category_length) << setfill(separator) << "Family" << "|";
	if (Contacts[i].category[1] == 1)
		cout << left << setw(category_length) << setfill(separator) << "Friend" << "|";
	if (Contacts[i].category[2] == 1)
		cout << left << setw(category_length) << setfill(separator) << "Work";
	cout << endl;

}

//category
void category_menu()
{
	system("cls");

	int choice = 5;
	while (choice != 4) {
		system("cls");
		cout << "...................................Category...................................\n";

		cout << "[1] family \t [2] friends \t [3] work \t [4]back to menu \n";
		int choice = valid_input(1, 4);

		if (choice == 1) category(0);//family

		else if (choice == 2) category(1);//friend

		else if (choice == 3) category(2);//work
		if (choice == 4)
		{
			system("cls");
			break;
		}
	}
	if (choice == 4 || return_category == 1) {
		return_category = 0;
		return;
	}
	system("cls");
}
void category(int type)
{
	int choice = 5;

	while (choice != 3 && choice != 4) {
		system("cls");

		display_category(type);

		cout << "[1]add \t [2]delete \t [3]back \t [4]main menu\n";

		choice = valid_input(1, 4);

		if (choice == 1) {

			add_to_category(type);
		}
		else if (choice == 2) {
			delett_category(type);
		}
		else if (choice == 3) {
			return;
		}

		else if (choice == 4 || return_category == 1) {
			system("cls");
			//menu();
			return_category = 1;
			return;
		}
	}
	system("cls");
}
void add_to_category(int type)
{
	//x: the number of contact that you want to add to category
	int add_contact = 1;
	system("cls");

	//display all contacts
	if (type == 0) cout << "category->Family\n";
	else if (type == 1)cout << "category->Friend\n";
	else if (type == 2)cout << "category->Work\n";
	display_contact(0);
	cout << "Enter -1 to stop\n";
	while (add_contact != -1) {
		cout << "add to category: ";
		add_contact = valid_input(-1, number_of_contacts);

		if (add_contact == -1) break;

		Contacts[add_contact - 1].category[type] = 1;


	}
	system("cls");
	return;
}
void delett_category(int type) {



	int choice = 1;

	while (choice == 1) {
		system("cls");
		int  index = 0, x;
		display_category(type);

		cout << "number of contact to delete\n";

		cin >> x;
		for (int i = 0; i < number_of_contacts; i++) {
			if (Contacts[i].category[type] == 1) {
				index++;
			}
			if (index == x) {
				Contacts[i].category[type] = 0;
				break;
			}
		}
		cout << "\n[1] Delete another contact\t[2] Back \n";
		choice = valid_input(1, 2);
		if (choice == 2) {
			break;
		}
	}
	if (choice == 2)return;
}
void display_category(int type) {
	int j = 1;
	bool d = 1;
	if (type == 0) cout << "category->Family\n";
	else if (type == 1)cout << "category->Friend\n";
	else if (type == 2)cout << "category->Work\n";

	for (int i = 0; i < number_of_contacts; i++) {
		if (Contacts[i].category[type] == 0) continue;
		if (d) { Header(0), d = 0; }
		string numm = "[" + to_stringg(j++) + "]";
		cout << left << setw(6) << setfill(separator) << numm;
		display_one_contact(i);
	}
}

//import
void import()
{

	ifstream import_file;
	Contact importc;
	int number_of_lines = 0;
	int choice = 0;
	string Import_From;
	Import_From = Export_or_Backup();


	//numer of lines of the import file

	import_file.open(Import_From);
	if (import_file.is_open())
	{
		string s;
		while (getline(import_file, s))number_of_lines++;
		import_file.close();
	}
	if (number_of_lines == 0)
	{
		system("cls");
		cout << "...................................Import Contacts...................................\n\n" << endl;
		cout << "There Are No Contacts Found\n\n";
		cout << "[1] Back To Menu\n\n";
		cout << "Go To: ";
		choice = valid_input(1, 1);
		system("cls");
		return;
	}

	while (choice != -1)
	{
		//disply the contacts
		display_import_contacts(Import_From);
		cout << "\nEntre -1 to end" << endl;
		choice = valid_input(-1, number_of_lines);

		//add the choosen numbers
		add_erase_chosen_numbers(choice);
	}

	//import the contacts

	display_import_contacts(Import_From);
	cout << "\n[1]Import to my contacts\t[2]Back to the menu\n" << endl;
	cout << "Go to: ";
	choice = valid_input(1, 2);


	//import
	if (choice == 1)
	{
		import_file.open(Import_From);
		if (import_file.is_open())
		{
			for (int i = 1; i <= number_of_lines; i++) {
				import_file >> importc.First_Name >> importc.Last_Name >> importc.Phone_Number >> importc.Email_Address;
				for (int j = 0; j < import_counter; j++)
				{
					if (chosen_contacts[j] == i)
					{
						Contacts[number_of_contacts] = importc;
						number_of_contacts++;
						break;
					}
				}

			}
			erase_array();
			import_file.close();
		}
		system("cls");
		cout << "Contacts have been added\n" << endl;
	}


	//back to the menu
	else
	{
		erase_array();
		system("cls");
	}
}
void display_import_contacts(string Import_From)
{
	ifstream import_file;
	int number_of_lines = 0;
	Contact importc;

	import_file.open(Import_From);
	if (import_file.is_open())
	{
		string s;
		while (getline(import_file, s))number_of_lines++;
		import_file.close();
	}

	system("cls");
	cout << "...................................Import Contacts...................................\n" << endl;
	cout << "choose the contacts you want to import\n" << endl;
	import_file.open(Import_From);
	if (import_file.is_open())
	{
		for (int i = 1; i <= number_of_lines; i++)
		{
			import_file >> importc.First_Name >> importc.Last_Name >> importc.Phone_Number >> importc.Email_Address;
			for (int j = 0; j < import_counter; j++)
			{
				if (chosen_contacts[j] == i)
				{
					cout << '*';
					break;
				}
			}
			string numm = "[" + to_stringg(i) + "]";
			cout << left << setw(6) << setfill(separator) << numm;
			cout << left << setw(name_length) << setfill(' ') << importc.First_Name << "|";
			cout << left << setw(name_length) << setfill(' ') << importc.Last_Name << "|";
			cout << left << setw(number_length) << setfill(' ') << importc.Phone_Number << "|";
			cout << left << setw(email_length) << setfill(' ') << importc.Email_Address << endl;
		}
		import_file.close();
	}

}
string Export_or_Backup()
{
	int choice;

	system("cls");
	cout << "...................................Import Contacts...................................\n\n" << endl;
	cout << " [1]Import From Export File \t [2]Import From Backup File\n\n";
	cout << "Go To: ";
	choice = valid_input(1, 2);
	if (choice == 1)return "export_file.txt";
	else return "backup.txt";


}
void add_erase_chosen_numbers(int choice)
{
	bool found = 0;
	for (int i = 0; i < import_counter; i++)
		if (chosen_contacts[i] == choice)
		{
			chosen_contacts[i] = 0;
			found = 1;
			break;
		}
	if (found == 0)chosen_contacts[import_counter++] = choice;
}
void erase_array()
{
	for (int i = 0; i < import_counter; i++)
		chosen_contacts[i] = 0;
}


void back_up()
{
	ofstream backup;
	backup.open("backup.txt");
	if (backup.is_open())
	{
		for (int i = 0; i < number_of_contacts; i++)
			backup << Contacts[i].First_Name << "\t" << Contacts[i].Last_Name << "\t" << Contacts[i].Phone_Number << " \t" << Contacts[i].Email_Address << "\n";
		backup.close();
	}
	system("cls");
	cout << "Contacts have been backed up\n\n";
}

void Export() {
	system("cls");
	ofstream export_contact;
	export_contact.open("export_file.txt");
	display_contact(0);
	while (1) {
		cout << "enter contact number to export: ";
		int x = valid_input(1, number_of_contacts);
		export_contact << Contacts[x - 1].First_Name << " " << Contacts[x - 1].Last_Name << "\t" << Contacts[x - 1].Phone_Number << "\t" << Contacts[x - 1].Email_Address << '\n';
		cout << "\n[1] export contact\t[2] Back to menu ";
		cout << "\nGo to: ";
		int choice = valid_input(1, 2);
		if (choice == 2) {
			export_contact.close();
			system("cls");
			return;
		}
	}
}