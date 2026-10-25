
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

int main() {
string name;
string choice;
string installed;

cout << "Do you have GitHub CLI installed? (Y/N): ";
cin >> installed;

if (installed == "n" || installed == "N") {

    int result = system("sudo apt install gh");

    if (result != 0) {

        cout << "Installation failed. Please install gh manually.\n";
        return 1;

    }
}

else if (installed != "y" && installed != "Y") {

    cout << "Invalid choice.\n";

    return 1;

}

    cout << "Is your GitHub CLI login complete? (Y/N): ";
    cin >> choice;

    if (choice == "n" || choice == "N") {
        int result = system("gh auth login");

        if (result != 0) {
            cout << "GitHub authentication failed.\n";
            return 1;
        }
    }
    else if (choice != "y" && choice != "Y") {
        cout << "Invalid choice.\n";
        return 1;
    }

    cout << "Enter GitHub username: ";
    cin >> name;

    // Basic GitHub username validation
    if (name.empty() || name.length() > 39) {
        cout << "Invalid GitHub username length.\n";
        return 1;
    }

    for (char c : name) {
        if (!isalnum(static_cast<unsigned char>(c)) && c != '-') {
            cout << "Invalid character in username.\n";
            return 1;
        }
    }

    cout << "\nGitHub username: " << name << "\n\n";

    string command =
        "curl -fsSL -- "
        "https://api.github.com/users/" + name + "/events";

    int result = system(command.c_str());

    if (result != 0) {
        cout << "\nFailed to fetch GitHub events.\n";
        return 1;
    }

    cout << endl;
    return 0;
}
