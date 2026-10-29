#include "CircularLinkedList.h"
#include <iostream>
#include <utility>
using namespace std;

CircularLinkedList::CircularLinkedList() : pivot(nullptr), nextToDisplay(nullptr), count(0) {}

PatientNode* CircularLinkedList::CreateNode(int id, const string& name, int age,
                                            const string& disease, int priority) {
    return new PatientNode{id, name, age, disease, priority, nullptr};
}
CircularLinkedList::~CircularLinkedList() {
    while (IsNotEmpty()) delete Remove();
}
bool CircularLinkedList::IsEmpty() const { return count == 0; }
bool CircularLinkedList::IsNotEmpty() const { return count > 0; }
int CircularLinkedList::Size() const { return count; }

int CircularLinkedList::NormalizeIndex(int index) const {
    if (count == 0) return 0;
    return ((index % count) + count) % count;
}
PatientNode* CircularLinkedList::GetNodeAt(int index) const {
    if (IsEmpty()) return nullptr;
    PatientNode* cur = pivot->next;
    index = NormalizeIndex(index);
    for (int i = 0; i < index; ++i) cur = cur->next;
    return cur;
}
void CircularLinkedList::SwapData(PatientNode* a, PatientNode* b) {
    swap(a->patientID, b->patientID);
    swap(a->patientName, b->patientName);
    swap(a->age, b->age);
    swap(a->disease, b->disease);
    swap(a->priority, b->priority);
}

// Insert at pivot->next (the first node), as required by Lab 06.
void CircularLinkedList::Insert(int id, const string& name, int age,
                                const string& disease, int priority) {
    PatientNode* p = CreateNode(id, name, age, disease, priority);
    if (!pivot) { pivot = p; p->next = p; }
    else { p->next = pivot->next; pivot->next = p; }
    if (!nextToDisplay) nextToDisplay = p;
    ++count;
    cout << "Patient inserted at the head of the circular list.\\n";
}
PatientNode* CircularLinkedList::Remove() {
    if (IsEmpty()) { cout << "No patients in the circular list.\\n"; return nullptr; }
    PatientNode* first = pivot->next;
    if (first == pivot) { pivot = nullptr; nextToDisplay = nullptr; }
    else {
        pivot->next = first->next;
        if (nextToDisplay == first) nextToDisplay = first->next;
    }
    first->next = nullptr;
    --count;
    if (count == 0) nextToDisplay = nullptr;
    else if (!nextToDisplay) nextToDisplay = pivot->next;
    return first;
}

void CircularLinkedList::InsertAt(int index, int id, const string& name, int age,
                                  const string& disease, int priority) {
    if (count == 0) { Insert(id, name, age, disease, priority); return; }
    // Circular index handling: negative and oversized indexes wrap around.
    if (index < 0) index = NormalizeIndex(index);
    if (index > count) index %= count;
    if (index == 0) { Insert(id, name, age, disease, priority); return; }

    PatientNode* p = CreateNode(id, name, age, disease, priority);
    if (index == count) {
        p->next = pivot->next; pivot->next = p; pivot = p; ++count;
    } else {
        PatientNode* prev = GetNodeAt(index - 1);
        p->next = prev->next; prev->next = p; ++count;
    }
    if (!nextToDisplay) nextToDisplay = pivot->next;
    cout << "Patient inserted at index " << index << ".\\n";
}
PatientNode* CircularLinkedList::RemoveAt(int index) {
    if (IsEmpty()) { cout << "Circular list is empty.\\n"; return nullptr; }
    index = NormalizeIndex(index);
    if (index == 0) return Remove();
    PatientNode* prev = GetNodeAt(index - 1);
    PatientNode* target = prev->next;
    prev->next = target->next;
    if (target == pivot) pivot = prev;
    if (nextToDisplay == target) nextToDisplay = target->next;
    target->next = nullptr;
    --count;
    if (count == 0) { pivot = nullptr; nextToDisplay = nullptr; }
    else if (!nextToDisplay) nextToDisplay = pivot->next;
    return target;
}
void CircularLinkedList::Swap(int i, int j) {
    if (IsEmpty()) { cout << "Circular list is empty.\\n"; return; }
    i = NormalizeIndex(i); j = NormalizeIndex(j);
    if (i == j) { cout << "Same index; no swap needed.\\n"; return; }
    SwapData(GetNodeAt(i), GetNodeAt(j));
    cout << "Patients swapped.\\n";
}
void CircularLinkedList::Sort() {
    if (count < 2) { cout << "Not enough patients to sort.\\n"; return; }
    PatientNode* cur = pivot->next;
    for (int i = 0; i < count - 1; ++i) {
        PatientNode* next = cur->next;
        for (int j = i + 1; j < count; ++j) {
            if (cur->priority > next->priority) SwapData(cur, next);
            next = next->next;
        }
        cur = cur->next;
    }
    cout << "Patients sorted by priority (urgent first).\\n";
}
void CircularLinkedList::Reverse() {
    if (count < 2) { cout << "Not enough patients to reverse.\\n"; return; }
    PatientNode* oldPivot = pivot;
    PatientNode* oldFirst = pivot->next;
    PatientNode* prev = oldPivot;
    PatientNode* cur = oldFirst;
    while (cur != oldPivot) {
        PatientNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    oldPivot->next = prev;
    pivot = oldFirst;
    cout << "Circular patient list reversed.\\n";
}
void CircularLinkedList::Print() const {
    if (IsEmpty()) { cout << "No patients waiting.\\n"; return; }
    cout << "\\nIndex\\tID\\tName\\tAge\\tDisease/Complaint\\tPriority\\n";
    cout << "----------------------------------------------------------------\\n";
    PatientNode* cur = pivot->next;
    for (int i = 0; i < count; ++i) {
        cout << i << '\\t' << cur->patientID << '\\t' << cur->patientName << '\\t'
             << cur->age << '\\t' << cur->disease << '\\t' << cur->priority << " ("
             << (cur->priority == 1 ? "Urgent" : cur->priority == 2 ? "Regular" : "Low")
             << ")\\n";
        cur = cur->next;
    }
    cout << "Total patients: " << count << '\\n';
    cout << "Circular link: the last node points back to the first node.\\n";
}
void CircularLinkedList::MoveToNext() {
    if (IsEmpty()) { cout << "No patients in the circular list.\\n"; return; }
    if (!nextToDisplay) nextToDisplay = pivot->next;
    cout << "\\n===== Current Patient in Circular Rotation =====\\n"
         << "Patient ID: " << nextToDisplay->patientID << '\\n'
         << "Patient Name: " << nextToDisplay->patientName << '\\n'
         << "Age: " << nextToDisplay->age << '\\n'
         << "Disease/Complaint: " << nextToDisplay->disease << '\\n'
         << "Priority: " << nextToDisplay->priority << '\\n';
    nextToDisplay = nextToDisplay->next;
}
void CircularLinkedList::QueueStatus() const {
    cout << "Circular List Status: " << (IsEmpty() ? "Empty" : "Not Empty") << '\\n';
    cout << "Patients in List: " << count << '\\n';
}
