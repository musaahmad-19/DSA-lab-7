#include <iostream>
#include <string>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;

    Student(int id, string n, float g) {
        studentID = id;
        name = n;
        GPA = g;
        left = right = NULL;
    }
};

Student* insert(Student* root, int id, string name, float gpa) {
    if (root == NULL)
        return new Student(id, name, gpa);

    if (id < root->studentID)
        root->left = insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = insert(root->right, id, name, gpa);
    else
        cout << "Student ID already exists.\n";

    return root;
}

Student* search(Student* root, int id) {
    if (root == NULL || root->studentID == id)
        return root;

    if (id < root->studentID)
        return search(root->left, id);

    return search(root->right, id);
}

Student* findMinimum(Student* root) {
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

Student* deleteStudent(Student* root, int id) {
    if (root == NULL)
        return NULL;

    if (id < root->studentID)
        root->left = deleteStudent(root->left, id);
    else if (id > root->studentID)
        root->right = deleteStudent(root->right, id);
    else {
        if (root->left == NULL) {
            Student* temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == NULL) {
            Student* temp = root->left;
            delete root;
            return temp;
        }

        Student* temp = findMinimum(root->right);

        root->studentID = temp->studentID;
        root->name = temp->name;
        root->GPA = temp->GPA;

        root->right = deleteStudent(root->right, temp->studentID);
    }

    return root;
}

void inorder(Student* root) {
    if (root == NULL)
        return;

    inorder(root->left);

    cout << "ID: " << root->studentID
         << ", Name: " << root->name
         << ", GPA: " << root->GPA << endl;

    inorder(root->right);
}

int countStudents(Student* root) {
    if (root == NULL)
        return 0;

    return 1 + countStudents(root->left)
             + countStudents(root->right);
}

void findHighestLowest(Student* root, Student*& highest,
                       Student*& lowest) {
    if (root == NULL)
        return;

    if (highest == NULL || root->GPA > highest->GPA)
        highest = root;

    if (lowest == NULL || root->GPA < lowest->GPA)
        lowest = root;

    findHighestLowest(root->left, highest, lowest);
    findHighestLowest(root->right, highest, lowest);
}

void displayAboveGPA(Student* root, float threshold) {
    if (root == NULL)
        return;

    displayAboveGPA(root->left, threshold);

    if (root->GPA > threshold) {
        cout << "ID: " << root->studentID
             << ", Name: " << root->name
             << ", GPA: " << root->GPA << endl;
    }

    displayAboveGPA(root->right, threshold);
}

void displayStudent(Student* student) {
    if (student == NULL) {
        cout << "Student not found.\n";
        return;
    }

    cout << "ID: " << student->studentID
         << "\nName: " << student->name
         << "\nGPA: " << student->GPA << endl;
}

void deleteTree(Student* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Student* root = NULL;
    int choice;

    do {
        cout << "\n1. Insert Student\n";
        cout << "2. Search Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Display Students\n";
        cout << "5. Count Students\n";
        cout << "6. Highest and Lowest GPA\n";
        cout << "7. Display Students Above GPA\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            float gpa;

            cout << "Enter Student ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> ws;
            getline(cin, name);

            cout << "Enter GPA: ";
            cin >> gpa;

            root = insert(root, id, name, gpa);
        }
        else if (choice == 2) {
            int id;

            cout << "Enter Student ID: ";
            cin >> id;

            displayStudent(search(root, id));
        }
        else if (choice == 3) {
            int id;

            cout << "Enter Student ID to delete: ";
            cin >> id;

            if (search(root, id) == NULL)
                cout << "Student not found.\n";
            else {
                root = deleteStudent(root, id);
                cout << "Student deleted.\n";
            }
        }
        else if (choice == 4) {
            inorder(root);
        }
        else if (choice == 5) {
            cout << "Total Students: "
                 << countStudents(root) << endl;
        }
        else if (choice == 6) {
            Student* highest = NULL;
            Student* lowest = NULL;

            findHighestLowest(root, highest, lowest);

            if (highest == NULL)
                cout << "No students available.\n";
            else {
                cout << "Highest GPA:\n";
                displayStudent(highest);

                cout << "Lowest GPA:\n";
                displayStudent(lowest);
            }
        }
        else if (choice == 7) {
            float threshold;

            cout << "Enter GPA threshold: ";
            cin >> threshold;

            displayAboveGPA(root, threshold);
        }

    } while (choice != 0);     
    deleteTree(root);
    return 0;
}
