
#include "DepartmentTree.h"
#include "FileUtils.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

DepartmentTree::DepartmentTree() : root(nullptr) {}

DepartmentTree::~DepartmentTree() {
    deleteNode(root);
}

void DepartmentTree::deleteNode(DepartmentNode* node) {
    if (node == nullptr) return;

    for (DepartmentNode* child : node->children) {
        deleteNode(child);
    }

    delete node;
}

DepartmentNode* DepartmentTree::findNode(
    DepartmentNode* node, const string& name) const {

    if (node == nullptr) return nullptr;

    if (equals_ignore_case(trim(node->name), trim(name)))
        return node;

    for (DepartmentNode* child : node->children) {
        DepartmentNode* found = findNode(child, name);
        if (found != nullptr) return found;
    }

    return nullptr;
}

bool DepartmentTree::addDepartment(
    const string& name, const string& parentName) {

    string department = trim(name);
    string parent = trim(parentName);

    if (department.empty()) return false;
    if (findNode(root, department) != nullptr) return false;

    if (root == nullptr) {
        if (!parent.empty() && !equals_ignore_case(parent, "NONE"))
            return false;

        root = new DepartmentNode(department);
        return true;
    }

    DepartmentNode* parentNode = findNode(root, parent);
    if (parentNode == nullptr) return false;

    DepartmentNode* newNode =
        new DepartmentNode(department, parentNode);

    parentNode->children.push_back(newNode);
    return true;
}

bool DepartmentTree::hasDepartment(const string& name) const {
    return findNode(root, name) != nullptr;
}

void DepartmentTree::loadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        return;
    }

    string line;
    int lineNumber = 0;
    int accepted = 0;
    int rejected = 0;

    while (getline(file, line)) {
        lineNumber++;

        if (is_skippable_line(line)) continue;

        vector<string> fields = split_fields(line);

        if (fields.size() != 2) {
            print_load_warning(filename, lineNumber,
                               "Invalid number of fields");
            rejected++;
            continue;
        }

        string name = fields[0];
        string parent = fields[1];

        if (name.empty() || parent.empty()) {
            print_load_warning(filename, lineNumber,
                               "Empty department or parent");
            rejected++;
            continue;
        }

        if (findNode(root, name) != nullptr) {
            print_load_warning(filename, lineNumber,
                               "Duplicate department");
            rejected++;
            continue;
        }

        if (root == nullptr) {
            if (!equals_ignore_case(parent, "NONE")) {
                print_load_warning(filename, lineNumber,
                                   "Root must have parent NONE");
                rejected++;
                continue;
            }
        } else if (equals_ignore_case(parent, "NONE")) {
            print_load_warning(filename, lineNumber,
                               "Multiple roots not allowed");
            rejected++;
            continue;
        }

        if (addDepartment(name, parent)) {
            accepted++;
        } else {
            print_load_warning(filename, lineNumber,
                               "Parent department not found");
            rejected++;
        }
    }

    print_load_summary(filename, accepted, rejected);
}

void DepartmentTree::searchDepartment(const string& name) const {
    DepartmentNode* node = findNode(root, name);

    if (node == nullptr) {
        cout << "Department not found." << endl;
        return;
    }

    int depth = 0;
    DepartmentNode* current = node;

    while (current->parent != nullptr) {
        depth++;
        current = current->parent;
    }

    cout << "Name: " << node->name << endl;
    cout << "Parent: "
         << (node->parent ? node->parent->name : "None") << endl;
    cout << "Direct children: " << node->children.size() << endl;
    cout << "Depth: " << depth << endl;
}

void DepartmentTree::displayNode(
    DepartmentNode* node, int depth) const {

    if (node == nullptr) return;

    cout << string(depth * 4, ' ') << node->name << endl;

    for (DepartmentNode* child : node->children) {
        displayNode(child, depth + 1);
    }
}

void DepartmentTree::displayHierarchy() const {
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }

    displayNode(root, 0);
}

void DepartmentTree::preorderNode(DepartmentNode* node) const {
    if (node == nullptr) return;

    cout << node->name << endl;

    for (DepartmentNode* child : node->children) {
        preorderNode(child);
    }
}

void DepartmentTree::preorderTraversal() const {
    if (root == nullptr) {
        cout << "Department tree is empty." << endl;
        return;
    }

    preorderNode(root);
}
