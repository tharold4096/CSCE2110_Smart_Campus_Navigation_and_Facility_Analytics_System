
#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H

#include <string>
#include <vector>

struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;
    std::vector<DepartmentNode*> children;

    DepartmentNode(const std::string& departmentName,
                   DepartmentNode* parentNode = nullptr)
        : name(departmentName), parent(parentNode) {}
};

#endif
