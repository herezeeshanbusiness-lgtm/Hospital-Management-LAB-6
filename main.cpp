#include <iostream>
#include <string>
#include <limits>
#include "CircularLinkedList.h"
using namespace std;

bool ReadInteger(const string& prompt, int& value) {
    cout << prompt;
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\\n');
        cout << "Invalid input. Please enter a number.\\n";
        return false;
    }
    return true;
}
bool ReadPatient(int& id, string& name, int& age, string& disease, int& priority) {
    if (!ReadInteger("Enter Patient ID: ", id)) return false;
    cout << "Enter Patient Name: "; getline(cin >> ws, name);
    if (!ReadInteger("Enter Patient Age: ", age)) return false;
    if (age < 0 || age > 130) { cout << "Enter a valid age (0-130).\\n"; return false; }
    cout << "Enter Disease or Complaint: "; getline(cin >> ws, disease);
    if (!ReadInteger("Enter Priority (1=Urgent, 2=Regular, 3=Low): ", priority)) return false;
    if (priority < 1 || priority > 3) { cout << "Priority must be 1, 2, or 3.\\n"; return false; }
    return true;
}
int main() {
    CircularLinkedList hospital;
    int choice = 0;
    do {
        cout << "\\n===== HOSPITAL MANAGEMENT: CIRCULAR LINKED LIST =====\\n"
             << "1. Display All Patients\\n"
             << "2. Insert Patient at Head\\n"
             << "3. Process/Remove Patient from Head\\n"
             << "4. Insert Patient at Index\\n"
             << "5. Remove Patient at Index\\n"
             << "6. Swap Patients\\n"
             << "7. Sort Patients by Priority\\n"
             << "8. Reverse Patient Circle\\n"
             << "9. Move to Next Patient (Circular Traversal)\\n"
             << "10. Check Circular List Status\\n"
             << "11. Exit\\n";
        if (!ReadInteger("Enter your choice: ", choice)) continue;
        switch (choice) {
        case 1: hospital.Print(); break;
        case 2: {
            int id, age, priority; string name, disease;
            if (ReadPatient(id, name, age, disease, priority))
                hospital.Insert(id, name, age, disease, priority);
            break;
        }
        case 3: {
            PatientNode* p = hospital.Remove();
            if (p) { cout << "Processed patient: " << p->patientName << " (ID: " << p->patientID << ")\\n"; delete p; }
            break;
        }
        case 4: {
            int index, id, age, priority; string name, disease;
            if (!ReadInteger("Enter insertion index: ", index)) break;
            if (ReadPatient(id, name, age, disease, priority))
                hospital.InsertAt(index, id, name, age, disease, priority);
            break;
        }
        case 5: {
            int index; if (!ReadInteger("Enter index to remove: ", index)) break;
            PatientNode* p = hospital.RemoveAt(index);
            if (p) { cout << "Removed patient: " << p->patientName << " (ID: " << p->patientID << ")\\n"; delete p; }
            break;
        }
        case 6: {
            int a, b; if (!ReadInteger("Enter first index: ", a)) break;
            if (!ReadInteger("Enter second index: ", b)) break;
            hospital.Swap(a, b); break;
        }
        case 7: hospital.Sort(); break;
        case 8: hospital.Reverse(); break;
        case 9: hospital.MoveToNext(); break;
        case 10: hospital.QueueStatus(); break;
        case 11: cout << "Exiting Hospital Management System.\\n"; break;
        default: cout << "Invalid choice. Please try again.\\n";
        }
    } while (choice != 11);
    return 0;
}
