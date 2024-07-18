#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

// Structure to store contact information
struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

// Function prototypes
void displayMenu();
void addContact(std::vector<Contact>& contacts);
void viewContacts(const std::vector<Contact>& contacts);
void editContact(std::vector<Contact>& contacts);
void deleteContact(std::vector<Contact>& contacts);
void loadContacts(std::vector<Contact>& contacts);
void saveContacts(const std::vector<Contact>& contacts);

int main() {
    std::vector<Contact> contacts;
    loadContacts(contacts); // Load contacts from file on program start

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Ignore the newline character after the choice input

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    saveContacts(contacts); // Save contacts to file before exiting
    return 0;
}

void displayMenu() {
    std::cout << "\nContact Management System" << std::endl;
    std::cout << "1. Add Contact" << std::endl;
    std::cout << "2. View Contacts" << std::endl;
    std::cout << "3. Edit Contact" << std::endl;
    std::cout << "4. Delete Contact" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void addContact(std::vector<Contact>& contacts) {
    Contact newContact;
    std::cout << "Enter name: ";
    std::getline(std::cin, newContact.name);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, newContact.phone);
    std::cout << "Enter email address: ";
    std::getline(std::cin, newContact.email);

    contacts.push_back(newContact);
    std::cout << "Contact added successfully!" << std::endl;
}

void viewContacts(const std::vector<Contact>& contacts) {
    std::cout << "\nContact List:" << std::endl;
    for (size_t i = 0; i < contacts.size(); ++i) {
        std::cout << i + 1 << ". Name: " << contacts[i].name
                  << ", Phone: " << contacts[i].phone
                  << ", Email: " << contacts[i].email << std::endl;
    }

    if (contacts.empty()) {
        std::cout << "No contacts found." << std::endl;
    }
}

void editContact(std::vector<Contact>& contacts) {
    viewContacts(contacts);

    int index;
    std::cout << "Enter the contact number to edit: ";
    std::cin >> index;
    std::cin.ignore(); // Ignore the newline character after the index input

    if (index > 0 && index <= static_cast<int>(contacts.size())) {
        Contact& contact = contacts[index - 1];

        std::cout << "Editing contact #" << index << std::endl;
        std::cout << "Current name: " << contact.name << std::endl;
        std::cout << "Enter new name (leave blank to keep current): ";
        std::string newName;
        std::getline(std::cin, newName);
        if (!newName.empty()) {
            contact.name = newName;
        }

        std::cout << "Current phone number: " << contact.phone << std::endl;
        std::cout << "Enter new phone number (leave blank to keep current): ";
        std::string newPhone;
        std::getline(std::cin, newPhone);
        if (!newPhone.empty()) {
            contact.phone = newPhone;
        }

        std::cout << "Current email address: " << contact.email << std::endl;
        std::cout << "Enter new email address (leave blank to keep current): ";
        std::string newEmail;
        std::getline(std::cin, newEmail);
        if (!newEmail.empty()) {
            contact.email = newEmail;
        }

        std::cout << "Contact updated successfully!" << std::endl;
    } else {
        std::cout << "Invalid contact number." << std::endl;
    }
}

void deleteContact(std::vector<Contact>& contacts) {
    viewContacts(contacts);

    int index;
    std::cout << "Enter the contact number to delete: ";
    std::cin >> index;
    std::cin.ignore(); // Ignore the newline character after the index input

    if (index > 0 && index <= static_cast<int>(contacts.size())) {
        contacts.erase(contacts.begin() + index - 1);
        std::cout << "Contact deleted successfully!" << std::endl;
    } else {
        std::cout << "Invalid contact number." << std::endl;
    }
}

void loadContacts(std::vector<Contact>& contacts) {
    std::ifstream inFile("contacts.txt");
    if (!inFile) {
        std::cout << "No contacts found. Starting with an empty list." << std::endl;
        return;
    }

    Contact contact;
    while (std::getline(inFile, contact.name)) {
        std::getline(inFile, contact.phone);
        std::getline(inFile, contact.email);
        contacts.push_back(contact);
    }

    inFile.close();
}

void saveContacts(const std::vector<Contact>& contacts) {
    std::ofstream outFile("contacts.txt");
    for (const auto& contact : contacts) {
        outFile << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
    }

    outFile.close();
}
