#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H
#include <string>
using namespace std;

struct PatientNode {
    int patientID;
    string patientName;
    int age;
    string disease;
    int priority; // 1=Urgent, 2=Regular, 3=Low
    PatientNode* next;
};

class CircularLinkedList {
private:
    PatientNode* pivot;          // Last node; pivot->next is first node
    PatientNode* nextToDisplay;
    int count;
    PatientNode* CreateNode(int, const string&, int, const string&, int);
    PatientNode* GetNodeAt(int) const;
    int NormalizeIndex(int) const;
    void SwapData(PatientNode*, PatientNode*);
public:
    CircularLinkedList();
    ~CircularLinkedList();
    bool IsEmpty() const;
    bool IsNotEmpty() const;
    int Size() const;
    void Insert(int, const string&, int, const string&, int);
    PatientNode* Remove();
    void InsertAt(int, int, const string&, int, const string&, int);
    PatientNode* RemoveAt(int);
    void Swap(int, int);
    void Sort();
    void Reverse();
    void Print() const;
    void MoveToNext();
    void QueueStatus() const;
};
#endif
