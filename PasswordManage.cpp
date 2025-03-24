#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <conio.h>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;

// Function prototypes
void checkPasswordStrength(const string& password);
string generatePassword(int length = 12);
bool verifyMasterPassword();

struct PasswordEntry {
    string website;
    string username;
    string password;
};

string encryptDecrypt(const string &input, char key) {
    string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key;
    }
    return output;
}

void saveToFile(const vector<PasswordEntry> &entries, const string &filename, char key) {
    ofstream file(filename.c_str());
    if (file.is_open()) {
        for (size_t i = 0; i < entries.size(); ++i) {
            file << encryptDecrypt(entries[i].website, key) << "\n";
            file << encryptDecrypt(entries[i].username, key) << "\n";
            file << encryptDecrypt(entries[i].password, key) << "\n";
        }
        file.close();
    }
}

vector<PasswordEntry> loadFromFile(const string &filename, char key) {
    vector<PasswordEntry> entries;
    ifstream file(filename.c_str());
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            PasswordEntry entry;
            entry.website = encryptDecrypt(line, key);
            getline(file, line);
            entry.username = encryptDecrypt(line, key);
            getline(file, line);
            entry.password = encryptDecrypt(line, key);
            entries.push_back(entry);
        }
        file.close();
    }
    return entries;
}

void displayMenu() {
    system("cls");
    cout << "=== Password Manager ===\n";
    cout << "1. Add Password\n";
    cout << "2. View All Passwords\n";
    cout << "3. Search Password\n";
    cout << "4. Delete Password\n";
    cout << "5. Generate Strong Password\n";
    cout << "6. Backup Passwords\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

void checkPasswordStrength(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    
    for (size_t i = 0; i < password.length(); ++i) {
        char c = password[i];
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }
    
    int strength = hasUpper + hasLower + hasDigit + hasSpecial;
    
    cout << "\nPassword Strength: ";
    if (password.length() < 6) cout << "Very Weak (too short)";
    else switch(strength) {
        case 1: cout << "Weak"; break;
        case 2: cout << "Medium"; break;
        case 3: cout << "Strong"; break;
        case 4: cout << "Very Strong"; break;
    }
    cout << endl;
}

string generatePassword(int length) {
    const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz"
                        "0123456789!@#$%^&*";
    string password;
    srand(time(0));
    
    for (int i = 0; i < length; ++i) {
        password += chars[rand() % chars.length()];
    }
    return password;
}

void addPassword(vector<PasswordEntry> &entries) {
    PasswordEntry entry;
    cout << "Enter Website/App: ";
    getline(cin, entry.website);
    cout << "Enter Username: ";
    getline(cin, entry.username);
    
    char choice;
    cout << "Generate password? (y/n): ";
    cin >> choice;
    cin.ignore();
    
    if (tolower(choice) == 'y') {
        entry.password = generatePassword(12);
        cout << "Generated Password: " << entry.password << endl;
    } else {
        cout << "Enter Password: ";
        getline(cin, entry.password);
    }
    
    checkPasswordStrength(entry.password);
    entries.push_back(entry);
    cout << "\nPassword added successfully!\nPress any key to continue...";
    getch();
}

void viewPasswords(const vector<PasswordEntry> &entries) {
    if (entries.empty()) {
        cout << "No passwords stored!\n";
    } else {
        cout << "\n=== Stored Passwords ===\n";
        for (size_t i = 0; i < entries.size(); ++i) {
            cout << i+1 << ". " << entries[i].website 
                 << " | " << entries[i].username 
                 << " | " << entries[i].password << "\n";
        }
    }
    cout << "\nPress any key to continue...";
    getch();
}

void backupPasswords(const vector<PasswordEntry>& entries) {
    ofstream backup("passwords_backup.txt");
    if (backup.is_open()) {
        for (size_t i = 0; i < entries.size(); ++i) {
            backup << entries[i].website << "\t" 
                   << entries[i].username << "\t" 
                   << entries[i].password << "\n";
        }
        backup.close();
        cout << "Backup created successfully!\n";
    } else {
        cout << "Error creating backup!\n";
    }
    cout << "Press any key to continue...";
    getch();
}

bool verifyMasterPassword() {
    const string correctPassword = "password"; // Simple password for demo
    string input;
    
    cout << "Enter Master Password: ";
    char ch;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!input.empty()) {
                input.erase(input.end() - 1);
                cout << "\b \b";
            }
        } else {
            input += ch;
            cout << '*';
        }
    }
    cout << endl;
    
    if (input == correctPassword) {
        return true;
    }
    cout << "Wrong password!\n";
    return false;
}

int main() {
    if (!verifyMasterPassword()) {
        cout << "Access denied!\n";
        getch();
        return 1;
    }
    
    vector<PasswordEntry> entries;
    const string filename = "passwords.dat";
    const char encryptionKey = 'K';
    
    entries = loadFromFile(filename, encryptionKey);
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch(choice) {
            case 1: addPassword(entries); break;
            case 2: viewPasswords(entries); break;
            case 3: {
                string searchTerm;
                cout << "Enter website/app name to search: ";
                getline(cin, searchTerm);
                
                bool found = false;
                for (size_t i = 0; i < entries.size(); ++i) {
                    if (entries[i].website.find(searchTerm) != string::npos) {
                        cout << "\nFound:\n" << entries[i].website 
                             << " | " << entries[i].username 
                             << " | " << entries[i].password << "\n";
                        found = true;
                    }
                }
                if (!found) cout << "No matching passwords found!\n";
                cout << "\nPress any key to continue...";
                getch();
                break;
            }
            case 4: {
                viewPasswords(entries);
                if (!entries.empty()) {
                    int index;
                    cout << "\nEnter number to delete (0 to cancel): ";
                    cin >> index;
                    cin.ignore();
                    
                    if (index > 0 && index <= entries.size()) {
                        entries.erase(entries.begin() + index - 1);
                        cout << "Entry deleted successfully!\n";
                    } else if (index != 0) {
                        cout << "Invalid selection!\n";
                    }
                }
                cout << "Press any key to continue...";
                getch();
                break;
            }
            case 5: {
                string newPass = generatePassword(12);
                cout << "Generated Password: " << newPass << endl;
                cout << "Press any key to continue...";
                getch();
                break;
            }
            case 6: {
                backupPasswords(entries);
                break;
            }
            case 7: 
                cout << "Saving and exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                getch();
        }
    } while (choice != 7);
    
    saveToFile(entries, filename, encryptionKey);
    return 0;
}
