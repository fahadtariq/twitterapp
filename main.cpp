// ============================================================================
// Name: Fahad Tariq
// File: main.cpp
// Project Description: Twitter Application by using HashMap
// ============================================================================
#include <iostream>
#include <string>
#include "HashMap.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <vector> 

using namespace std;

struct TwitterDB
{
	string Tuser_id;
	string Tuser_name;
	string Tuser_txt;
	string Tuser_loc;
	int Tuser_frndC;
	int Tuser_statusC;
	int Tuser_followC;

	// struct comparison operators used for 'remove' function
	bool operator == (const TwitterDB& rhs)const
	{
		return Tuser_id == rhs.Tuser_id &&
			Tuser_name == rhs.Tuser_name &&
			Tuser_txt == rhs.Tuser_txt &&
			Tuser_loc == rhs.Tuser_loc &&
			Tuser_frndC == rhs.Tuser_frndC &&
			Tuser_statusC == rhs.Tuser_statusC &&
			Tuser_followC == rhs.Tuser_followC;
	}
	// used for 'sort' function
	bool operator > (const TwitterDB& rhs)const
	{
		return Tuser_statusC > rhs.Tuser_statusC;
	}
};// end of TwitterDB

// iterator declaration
typedef HashMap<string, TwitterDB>::Iterator iterDec;

// Class for uploading data to Hashmap
class Twitter {
public:

	vector<int> status_array; // array for counting

	TwitterDB access;
	HashMap<string, TwitterDB> hashMap;
	// Function for getting data file
	string getfile() {


		string filename;
		cout << "Please Enter FileName With Ext. (eg: data.json)=> ";
		cin >> filename;
		return filename;

	}

	// Function for uploading data to hashmap 
	int uploadDB(string fileOpen) {


		// Initialization Data in Loop
		ifstream file(fileOpen.c_str()); // Twitter File
		if (!file.is_open()){

			cerr << "Failed to open file. Please try again\n\n" << endl;
			File_valid();

			return (EXIT_FAILURE);
			
		}

		for (string line; (getline(file, line));)
		{
			// User Text From Twitter
			const size_t start_pos_txt = line.find("\"text\":");
			string temp1 = line.substr(start_pos_txt + 8);
			// User Location From Twitter
			const size_t start_pos_loc = line.find("\"location\":");
			string temp2 = line.substr(start_pos_loc + 12);
			// User Number of Status From Twitter
			const size_t start_pos_SC = line.find("\"statuses_count\":");
			string temp3 = line.substr(start_pos_SC + 17);
			// User ID From Twitter 
			const size_t start_pos_Id = line.find("\"user\":{");
			string temp4 = line.substr(start_pos_Id + 8);
			const size_t stop_pos4 = temp4.find("}");
			string t_id = temp4.substr(0, stop_pos4);
			istringstream in(t_id);
			string user_line;
			string t_user_id;
			int t_userID;
			while (getline(in, user_line))
			{
				const size_t find_id = user_line.find("\"id\":");
				string pos_id = user_line.substr(find_id + 5);
				const size_t stop_pos_id2 = pos_id.find(",\"");
				t_user_id = pos_id.substr(0, stop_pos_id2);
				//t_userID = atoi(t_user_id.c_str());
			}

			// Finding Data
			const size_t start_pos_nm = line.find("\"name\":");
			string temp5 = line.substr(start_pos_nm + 8);
			const size_t start_pos_fc = line.find("\"followers_count\":");
			string temp6 = line.substr(start_pos_fc + 18);
			const size_t start_pos_fri_c = line.find("\"friends_count\":");
			string temp7 = line.substr(start_pos_fri_c + 16);

			// Stop Positions
			const size_t stop_pos1 = temp1.find("\"");
			const size_t stop_pos2 = temp2.find("\"");
			const size_t stop_pos3 = temp3.find(",\"");
			const size_t stop_pos5 = temp5.find("\"");
			const size_t stop_pos6 = temp6.find("\"");
			const size_t stop_pos7 = temp7.find("\"");
			string t_text = temp1.substr(0, stop_pos1);
			string t_loc = temp2.substr(0, stop_pos2);
			string t_status_c = temp3.substr(0, stop_pos3);
			int t_status = atoi(t_status_c.c_str());
			string t_name = temp5.substr(0, stop_pos5);
			string t_follow_c = temp6.substr(0, stop_pos6);
			int t_follow = atoi(t_follow_c.c_str());
			string t_frnd_c = temp7.substr(0, stop_pos7);
			int t_frnd = atoi(t_frnd_c.c_str());


			// Inserting Data in hashtable
			access.Tuser_id = t_user_id;
			access.Tuser_name = t_name;
			access.Tuser_txt = t_text;
			access.Tuser_loc = t_loc;
			access.Tuser_frndC = t_frnd;			
			access.Tuser_statusC = t_status;
		

			access.Tuser_followC = t_follow;
			hashMap.Insert(t_user_id, access);
					}

		file.close();
		User_Input();
	}

	// File Validation
	void File_valid() {
		string file_name = getfile();
		uploadDB(file_name);
	}

	// Menu Options
	int User_Input();
	// Constinue Menu
	void Continue();
	// Display All Data	
	void display_all();
	// Status Count	
	void status_aray();
	// Display Data From single User ID
	void display_SUser(string T_key);
	// Display Data From specific Slot (Index)
	void display_SIndex(int getindex);
	// Display Total Tweets
	void display_CountTweets();
	// Remove User From hashmap
	void remove_user(string U_key);
	// Top 5 Active Users
	void top5_user();


}; // class end

void Twitter::status_aray() {
	for (int z = 0; z < hashMap.TableSize(); ++z)
	{
		iterDec iter = hashMap.begin(z);
		if (!hashMap.IsEmpty(z))
		{
			// initialize an iterator

			// display all the values 			
			for (; iter != hashMap.end(z); ++iter)
			{
			status_array.push_back(iter->value.Tuser_statusC);
						
			}
		}
	}
	
}


void Twitter::display_all() {
	// display all items in the hash map again 
	cout << "\nALL USERS AND THEIR DATA : \n\n";
	for (int x = 0; x < hashMap.TableSize(); ++x)
	{
		iterDec iter = hashMap.begin(x);
		if (!hashMap.IsEmpty(x))
		{
			// initialize an iterator
			// display USERNAME
			cout << "INDEX '" << hashMap.Hash(iter->value.Tuser_id) << "' DATA:\n";
			cout << "===================================================\n";

			// display all the values 			
			for (; iter != hashMap.end(x); ++iter)
			{
			
					
				
				cout << "\tName: " << iter->value.Tuser_name
				     << "\n\tUser ID: " << iter->value.Tuser_id
					//	<< "\n\tText: " << iter->value.Tuser_txt
					<< "\n\tLocation: " << iter->value.Tuser_loc
					<< "\n\tNumber of Friends: " << iter->value.Tuser_frndC
					<< "\n\tNumber of Status: " << iter->value.Tuser_statusC
					<< "\n\tNumber of Followers: " << iter->value.Tuser_followC << endl << endl;


			}
		}
	}
	Continue();
} // end function


void Twitter::display_SUser(string T_key) {
	// display items related to single person in the hash map 
	cout << "\nITEMS RELATED TO SINGLE PERSON IN DATABASE: \n";
	for (int x = 0; x < hashMap.TableSize(); ++x)
	{
		iterDec iter = hashMap.begin(x);
		if (!hashMap.IsEmpty(x) && iter->key == T_key)
		{
			// initialize an iterator
			// display USERNAME
			cout << "\nUSERNAME '" << iter->value.Tuser_name << "' DATA:\n";
			cout << "===================================================\n";
			// display all the values 
			for (; iter != hashMap.end(x); ++iter)
			{
				if (iter->value.Tuser_id == T_key) {
					cout << "\tName: " << iter->value.Tuser_name
						<< "\n\tUser ID: " << iter->value.Tuser_id
						<< "\n\tText: " << iter->value.Tuser_txt
						<< "\n\tLocation: " << iter->value.Tuser_loc
						<< "\n\tNumber of Friends: " << iter->value.Tuser_frndC
						<< "\n\tNumber of Status: " << iter->value.Tuser_statusC
						<< "\n\tIndex: " << hashMap.Hash(iter->value.Tuser_id)
						<< "\n\tNumber of Followers: " << iter->value.Tuser_followC << endl << endl;
				}
							}
		}
	}

	Continue();

} // end function


// display items from specific slot by using index 
void Twitter::display_SIndex(int getindex) {
	cout << "\nItems From Index No: " << getindex << endl;
	for (int x = getindex; x < getindex + 1; x++)
	{
		if (!hashMap.IsEmpty(x))
		{
			// initialize an iterator
			iterDec iter = hashMap.begin(x);
			// display USERNAME
			cout << "USERNAME '" << iter->value.Tuser_name << "' DATA:\n";
			cout << "===================================================\n";
			// display all the values 
			for (; iter != hashMap.end(x); iter++)
			{
				cout << "\tName: " << iter->value.Tuser_name
					<< "\n\tUser ID: " << iter->value.Tuser_id
					<< "\n\tText: " << iter->value.Tuser_txt
					<< "\n\tLocation: " << iter->value.Tuser_loc
					<< "\n\tNumber of Friends: " << iter->value.Tuser_frndC
					<< "\n\tNumber of Status: " << iter->value.Tuser_statusC
					<< "\n\tIndex: " << hashMap.Hash(iter->value.Tuser_id)
					<< "\n\tNumber of Followers: " << iter->value.Tuser_followC << endl << endl;
			}
		}
		else {
			cout << "Index is Empty!" << endl;
			Continue();
		}
	}
	Continue();
} // end function


void Twitter::display_CountTweets() {
	cout << "\n\nTOTAL NUMBER OF TWEETS IN DATABASE IS: " <<
		hashMap.TotalElems() << endl;
		
		Continue();
}// end function


// Top 5 Active Users
void Twitter::top5_user(){
	status_aray();
	
	// sotring status
sort(status_array.begin(), status_array.end(), std::greater<int>());

	// display all items in the hash map again 
	cout << "\nTHESE ARE TOP5 MOST ACTIVE USERS ON TWITTER PAGE: \n\n";
	
	for(int p=0; p <=10 ; p++ ) {
		cout << status_array[p] << endl;
	}
		for (int f = 0; f <= 4; f++) {
	for (int x = 0; x < hashMap.TableSize(); ++x)
	{
		iterDec iter = hashMap.begin(x);
		
		 
		//	hashMap.Sort(hashMap.Hash("Kenneth"));   
		if (!hashMap.IsEmpty(x))
		{
			// initialize an iterator

									
				if (iter->value.Tuser_statusC == status_array[f]) {
					// display USERNAME
					cout << "\nUSERNAME '" << iter->value.Tuser_name << "' DATA:\n";
					cout << "===================================================\n";
					cout << "    =============== RANK: #" << f + 1 << " ===============    \n";
					cout << "===================================================\n";
					// display all the values 
					for (; iter != hashMap.end(x); ++iter)
					{
						if (iter->value.Tuser_statusC == status_array[f]) {
							cout << "\tName: " << iter->value.Tuser_name
								<< "\n\tUser ID: " << iter->value.Tuser_id
								<< "\n\tLocation: " << iter->value.Tuser_loc
								<< "\n\tNumber of Friends: " << iter->value.Tuser_frndC
								<< "\n\tNumber of Status: " << iter->value.Tuser_statusC
								<< "\n\tNumber of Followers: " << iter->value.Tuser_followC << endl << endl;
						}
					}
				}
			}
		}
	}
	Continue();

}// end function

// Remove User From hashmap
void Twitter::remove_user(string U_key){

	for (iterDec iter = hashMap.begin(hashMap.Hash(U_key));
		iter != hashMap.end(hashMap.Hash(U_key)); ++iter)
	{
		if (iter->value.Tuser_id == U_key)
		{
			cout << "\nUser '" << iter->value.Tuser_name << "' with UserID: '" << iter->value.Tuser_id << " has been removed from Database..\n" << endl;
			hashMap.Remove(U_key, (*iter).value);
			break;
		}

		else {
			cout << "\nNo Such User Found!. Please Try Again." << endl;
			Continue();
		}
	}
	Continue();
}// end function

// Continue Menu
void Twitter::Continue() {
	char chk;
	cout << "\n\nDo you want to continue with more options (Y/N): " << endl;
	cout << "=> ";
	cin >> chk;
	if (chk == 'y' || chk == 'Y') {
		User_Input();
	}
	else if (chk == 'n' || chk == 'N') {
		cout << "\n\nGOOD BYE!\n\n" << endl;
		exit(0);
	}
	else {
		cout << "Wrong Input!" << endl;
		User_Input();
	}
}

int Twitter::User_Input() {
	system("CLS");
	system("Color 1B");
	string user_id;
	int input, Index_no;

	cout << "  ===========================================================================" << endl;
	cout << "  =========================== TWITTER APPLICATION ===========================" << endl;
	cout << "  ================= FIND TOP 5 ACTIVE USERS ON TWITTER PAGE =================" << endl;
	cout << "  ===========================================================================\n\n" << endl;
	cout << "PLEASE SELECT YOUR OPTION: \n" << endl;
	cout << "1: Display All Users & Data: " << endl;
	cout << "2: Display Single User & Data: " << endl;
	cout << "3: Display User Data From Specific Index: " << endl;
	cout << "4: Display Total Number Of Tweets in DataBase: " << endl;
	cout << "5: Remove User From DataBase: " << endl;
	cout << "6: Top5 Active Users On Twitter Page: " << endl;
	cout << "0: Exit" << endl;
	cout << "=> ";
	cin >> input;
	switch (input) {
	case 1: // Note the colon, not a semicolon
		display_all();
		break;
	case 2: // Note the colon, not a semicolon
		cout << "\nPlease Enter User Id :" << endl;
		cout << "=> ";
		cin >> user_id;
		display_SUser(user_id);
		break;
	case 3: // Note the colon, not a semicolon
		cout << "Please Enter Index Number :" << endl;
		cout << "=> ";
		cin >> Index_no;
		cin.ignore(numeric_limits<int>::max(), '\n');
		if (cin.good()) {
			display_SIndex(Index_no);
		}
		else {
			cin.clear();
			//and empty it
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input; please re-enter.\n" << endl;
			Continue();
		}
		break;
	case 4:
		display_CountTweets();
		break;
	case 5:
		cout << "Please enter user id :" << endl;
		cout << "=> ";
		cin >> user_id;
		remove_user(user_id);
		break;
	case 6:
		top5_user();
		//	  check_array();

		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "Error, bad input, try again\n" << endl;
		Continue();
		break;
	}
} // end function

int main()
{

	cout << "  ===========================================================================" << endl;
	cout << "  =========================== TWITTER APPLICATION ===========================" << endl;
	cout << "  ================= FIND TOP 5 ACTIVE USERS ON TWITTER PAGE =================" << endl;
	cout << "  ===========================================================================\n\n" << endl;

	// File Input	
	Twitter T_DB;
	T_DB.File_valid();
	return 0;
}
