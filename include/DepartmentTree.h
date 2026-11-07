
#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include "DepartmentNode.h"
#include <string>

class DepartmentTree {
private:
    DepartmentNode* root;

    DepartmentNode* findNode(DepartmentNode* node,
                             const std::string& name) const;

    void displayNode(DepartmentNode* node, int depth) const;
    void preorderNode(DepartmentNode* node) const;
    void deleteNode(DepartmentNode* node);

public:
    DepartmentTree();
    ~DepartmentTree();

    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    void loadFromFile(const std::string& filename);

    bool addDepartment(const std::string& name,
                       const std::string& parentName);

    void searchDepartment(const std::string& name) const;
    void displayHierarchy() const;
    void preorderTraversal() const;
};

#endif
