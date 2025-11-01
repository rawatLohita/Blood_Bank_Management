#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string> 
using namespace std; 
class BloodBank { 
public: 
string name; 
string bloodType; 
int age; 
string contact; 
int units; 
// Function to initialize default blood stock 
void initializeStock() { 
ofstream file("blood_stock.txt"); 
file << "A+ 10\nA- 5\nB+ 8\nB- 4\nO+ 12\nO- 6\nAB+ 3\nAB- 2\n"; 
file.close(); 
} 
// Function to display available blood stock 
void viewBloodStock() { 
ifstream file("blood_stock.txt"); 
if (!file) { 
cout << "\n⚠ No Blood Data Available! Initializing stock...\n"; 
initializeStock(); 
file.open("blood_stock.txt"); 
} 
cout << "\n Available Blood Stock:\n"; 
cout << "-------------\n"; 
cout << left << setw(8) << "Type" << setw(6) << "Units" << endl; 
cout << "--------------\n"; 
string type; 
int stock; 
while (file >> type >> stock) { 
cout << left << setw(8) << type << setw(6) << stock << endl; 
} 
file.close(); 
} 
// Function to register a new donor and add blood units 
void registerDonor() { 
cout << "\nEnter Donor Name: "; 
cin.ignore(); 
getline(cin, name); 
cout << "Enter Blood Type (A+/A-/B+/B-/O+/O-/AB+/AB-): "; 
cin >> bloodType; 
cout << "Enter Age: "; 
cin >> age; 
cout << "Enter Contact Number: "; 
cin >> contact; 
cout << "Enter Blood Units Donated: "; 
cin >> units; 
// Save donor data 
ofstream donorFile("donors.txt", ios::app); 
donorFile << name << " " << bloodType << " " << age << " " << contact << " " 
<<units << endl; 
donorFile.close(); 
// Update blood stock 
ifstream file("blood_stock.txt"); 
ofstream temp("temp_stock.txt"); 
string type; 
int stock; 
while (file >> type >> stock) { 
if (type == bloodType) { 
stock += units; 
} 
temp << type << " " << stock << endl; 
} 
file.close(); 
temp.close(); 
remove("blood_stock.txt"); 
rename("temp_stock.txt", "blood_stock.txt"); 
cout << "\nDonor Registered & Stock Updated Successfully!\n"; 
} 
// Function to request blood 
void requestBlood() { 
string reqType; 
int reqUnits; 
cout << "\nEnter Required Blood Type: "; 
cin >> reqType; 
cout << "Enter Units Needed: "; 
cin >> reqUnits; 
ifstream file("blood_stock.txt"); 
ofstream temp("temp_stock.txt"); 
string type; 
int stock; 
bool found = false; 
while (file >> type >> stock) { 
if (type == reqType && stock >= reqUnits) { 
stock -= reqUnits; 
found = true; 
} 
temp << type << " " << stock << endl; 
} 
file.close(); 
temp.close(); 
remove("blood_stock.txt"); 
rename("temp_stock.txt", "blood_stock.txt"); 
if (found) 
cout << "\n Blood Request Approved! " << reqUnits << " units of " << reqType << "provided.\n"; 
else 
cout << "\n Requested Blood Type Not Available or Insufficient Units!\n"; 
} 
// Function to manually update stock (admin feature) 
void updateStock() { 
string updateType; 
int addUnits; 
cout << "\nEnter Blood Type to Update: "; 
cin >> updateType; 
cout << "Enter Units to Add: "; 
cin >> addUnits; 
ifstream file("blood_stock.txt"); 
ofstream temp("temp_stock.txt"); 
string type; 
int stock; 
bool updated = false; 
while (file >> type >> stock) { 
if (type == updateType) { 
stock += addUnits; 
updated = true; 
} 
temp << type << " " << stock << endl; 
} 
file.close(); 
temp.close(); 
remove("blood_stock.txt"); 
rename("temp_stock.txt", "blood_stock.txt"); 
if (updated) 
cout << "\n Stock Updated Successfully!\n"; 
else 
cout << "\nInvalid Blood Type Entered!\n"; 
} 
}; 
int main() { 
BloodBank bb; 
int choice; 
// Initialize stock if not present 
ifstream checkFile("blood_stock.txt"); 
if (!checkFile) { 
bb.initializeStock(); 
} 
checkFile.close(); 
while (true) { 
cout << "\n==BLOOD BANK MANAGEMENT SYSTEM ====\n"; 
cout << "1. Register Donor\n"; 
cout << "2. View Blood Stock\n"; 
cout << "3. Request Blood\n"; 
cout << "4. Update Stock (Admin)\n"; 
cout << "5. Exit\n"; 
cout << "Enter your choice: "; 
cin >> choice; 
switch (choice) { 
case 1: 
bb.registerDonor(); 
 
 
                break; 
            case 2: 
                bb.viewBloodStock(); 
                break; 
            case 3: 
                bb.requestBlood(); 
                break; 
            case 4: 
                bb.updateStock(); 
                break; 
            case 5: 
                cout << "\nExiting... Thank you!\n"; 
                return 0; 
            default: 
                cout << "\n⚠ Invalid Choice! Try Again.\n"; 
        } 
    } 
    return 0; 
} 
 