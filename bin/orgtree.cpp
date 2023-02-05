#include "orgtree.h"
#include <iostream>
/* Single Programmer Affidavit
I the undersigned promise that the submitted assignment is my own work. While I was 
free to discuss ideas with others, the work contained is my own. I recognize that 
should this not be the case; I will be subject to penalties as outlined in the course 
syllabus. 
Name: Cameron Cobb
Red ID: 826504686
*/
/**
 * Check if an employee is present in an organization chart. 
 * 
 * This recursive function finds whether an employee, indicated by its unique ID, exists in a tree. If the employee is not the root node, then each of its children are recursviely called in order.
 * The first child is considered the first subtree after the first recursvie call. The function is repeated for its children if the employee is not the first child.

 * @param  head the head / root Employee of the organization chart
 * @param  e_id the employee id being searched
 * @return      true or false
 * @see         
 */
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // This statement checks to see if the tree is empty. An empty tree with a root equal to nullptr is considered empty. This will execute the first time this method is called on an empty tree.
  if (head == nullptr) {
    // Employee is not present in an empty tree.
    return false;
  }
  // If the current recursive call, that is if the current node, which could be a child of another node or the root itself, is equal to the employee id, then the employee is located in the tree.
  // head->getEmployeeID() returns the id associated with the current node (head of the subtree) in the tree.
  if (head->getEmployeeID() == e_id) {
    return true;
  }
  // This statement constructs a vector of the children, or the direct reports data member, within the current head of the recursive method.
  vector<Employee*> children = head->getDirectReports();
  // This for-each loop iterates through each child of head, calling the isEmployeePresentInOrg() function with each child passed as an aguemnt to search every possible subtree within the head node. Each child
  // in the head is treated as a separate subtree since the function recursively calls each child. Each function call with a child will treat it as the head in the recursive execution.
  for(Employee* child: children) {
    // This statement implies that that the employee is located somewhere between the current head and a leaf node's children since false cannot be returned. Every possible subtree is searched from
    // the current head node since the for-each loop iterates through every head's children.
    if (isEmployeePresentInOrg(child, e_id)) {
      // The employee was found in the subtree.
      return true;
    }
  }
  // if not found, return false
  return false;
}

/**
 * Find the level of an employee in an organization chart / tree. 
 * 
 * <p>
 * The head / root of the org chart has a level of 0, children of the head have
 * a level of head plus 1, and so on and so forth... 
 * 
 * This function recursviely calls both isEmployeePresentInOrg and itself to determine the head level of an emloyee within a tree givewn the root node and its headLevel, which is assumed to be 0.
 * The root node is checked and if the employee ID number is not equal to the root node ID, then the function is recursively called for each child using a for-each loop. The isEmployeePresentInOrg
 * function is called on each subtree, and if the child is located within the subtree, then the findEmployeeLevel is recursviely called on that child, icnreasing the head level by one in the process 
 * to indicate that the function is traversing through a subtree child. 
 * <p>
 * Assumption: e_id is unique among all employee IDs
 *
 * @param  head      the head / root Employee of the organization chart
 * @param  e_id      the employee id being searched
 * @param  headLevel the level of the head employee of the organization 
 * @return    level of the employee in the org chart
 *      returns Employee::NOT_FOUND if e_id is not present
 * @see         
 */
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
  // Write your recursive implementation here. 

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.
  
  // The first base case is that the curent tree/ or subtree is empty. This is indicated by an empty head node, meaning that
  // the tree cannot be traversed down any more. -1 is returned if this base case is executed.
  if (head == nullptr) {
    return Employee::NOT_FOUND;
  }

  // The second base case here is that the head node's employee ID matches the employee ID parameter passed as either the first call to the function
  // or a recursvie call passed from one of the children or its children or etc. The headLevel is returned once the matching node has been found.
  if (head->getEmployeeID() == e_id) {
    return headLevel;
  }

  // search employee from each child of the head
  // This statement creates a vector of head's children by accessing its direct reports data member, which is a vector itself. This is necessary
  // to traverse the list from each head node's children, creating subtrees after each recursvie call with each child passed as the head node.
  vector<Employee*> children = head->getDirectReports();
  // Traverse through each child of head and check to see if the e1_id is present in any one of these subtrees. The recursive isEmployeePresentInOrd
  // is used to determine whether it is so. If the employee has been found in any one of the children, then traverse from that children by recursviely
  // calling the findEmployeeLevel function with the current child passed as the head and the headLevel incremented by one each time the recursive function
  // is called.
  for(Employee* child: children) {
    if(isEmployeePresentInOrg(child, e_id)) {
      // Return the head level at which the head node's id is equal to e1_id. Every recursive call will increment headLevel by 1.
      return findEmployeeLevel(child, e_id, headLevel + 1);
    }
  }
  
  // if not found
  // All of the children of the root node have been traversed and the employee is not present in any of these subtrees. So return -1.
  return Employee::NOT_FOUND;
}

/**
 * Find the closest shared manager of two employees e1 and e2. 
 * 
 * <p>
 * There are two possible organizational relationships between two employees in the org chart:
 * case 1: e1 or e2 is a manager of the other employee; 
 * case 2: e1 or e2 is not a manager of the other employee, they have at least one shared manager
 *
 * This recursvie function uses the root node of a tree and two employee ids, e1_id and e2_id, to determine the closest manager of each employee.
 * Pointers are necessary in this function to keep track of which subtrees of children contain which nodes matching each respective exployee ID
 * parameter. For the first case, e1 or e2 is a manager of the other employee and for the second case they share a common manager that is different
 * from themselves.

 * Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2 in the organization chart 
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   closest shared manager in the org chart between employee e1 and employee e2
   *           if head is nullptr, returns nullptr
   *           if neither e1 or e2 is present, returns empty employee           
   *           if e1 is present and e2 is not, returns e1
   *           if e2 is present and e1 is not, returns e2
   *           if e1 and e2 both are present, returns their shared manager
   *              if e1 is a manager (ancestor) of e2, returns e1
   *              else if e2 is a manager (ancestor) of e1, returns e2
   *              else returns the shared manager of e1 and e2
 * @see         
 */
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {
  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // Assign each node with nullptr to indicate that the default value of each subtreeChild node is nullptr. If an employee is not found in a subtree
  // then this will indicate that the employee has not been found. Using this nullptr value if not found will be especially important in the recursive call.
  Employee* subtreeChild1 = nullptr;
  Employee* subtreeChild2 = nullptr;


  // base case 1: empty organization chart
  // A head node equal to nullptr indicates that the tree has been empty since the start. This will only execute if the root node is a Employee* pointer.
  if (head == nullptr) {
    return nullptr;
  }

  // base case 2: either e1_id or e2_id is the same as the head / root
  // The head node's employee id is accessed through the notation head->getEmployeeID() to compare it with each employee ID passed from each call. If it is equal,
  // then return the current head node. This is especially important to traverse down the tree as well as reutnring the first employee id that is 
  // a manager of another.
  if (e1_id == head->getEmployeeID() || e2_id == head->getEmployeeID()) {
    return head;
  }


  // Recursively traverse through direct reports of the head to find 
  // where e1 and e2 are
  
  /*
     For each recursive call (starting from the root), you need to handle three possible scenarios:
     1) if e1 is found in one subtree, and e2 is found from another subtree; 
        the head at that recursive step would be the closest shared manager of e1 and e2.

        you can use the returned pointer (being NOT NULL) from findClosestSharedManager 
        to see if e1 or e2 is found from a subtree (one of the base cases).

     2) if either e1 or e2 is first found in one subtree (following one subtree), 
        but the other employee is NOT found from any other subtree, then the found 
        employee must either be the manager of the other employee, or the other employee 
        is NOT in the org chart; in either case, the first found employee should be 
        returned as the shared manager.

     3) if neither e1 or e2 is found in the org chart, return nullptr
  */
    // This vector creates a list of head's children by returning the direct reports data member of the head node. This vector is necessary to traverse through each children so that
    // tree can be further broken down into a smaller one. This is the goal of recursion.
    vector<Employee*> children = head->getDirectReports();
    

    // This for each loops iterates through each children of the head. The children vector is the list of direct reports, or the children of the head in the current recursive execution.
    for (Employee* child: children) {
        // This statement is necessary to keep track of the first subtree. If the first employee is present in one of the children, subtreeChild1
        // is initialized with the child pointer at which the recursvie call to isEmployeePresentInOrd(child, e1_id) is true. This is the same for the other employee.
        // If it is present in one of the children (or it is the child itself), then assign subtreeChild2 with that child pointer.
          if(isEmployeePresentInOrg(child, e1_id)) {
            subtreeChild1 = child;
          }
          if (isEmployeePresentInOrg(child, e2_id)) {
            subtreeChild2 = child;
          }
    }
    // If the employees are present in the same child subtree, then that means that the closest manager has not been found yet. So recursively
    // return the manager at findClosestManager(subtreeChild1, e1_id, e2_id), which may result in another recursvie call.
    if (subtreeChild1 == subtreeChild2) {
      // Traverse the subtree at that child where both employees are present, eliminating a large portion of the tree to search.
      return findClosestSharedManager(subtreeChild1, e1_id, e2_id);
    }
    // This means that one of the children cannot be found in the list of children of the head node. This means that the first employee found will be the manager,
    // therefore recursively call findClosestManager at the subtree where one of the employees is present.
    else if (subtreeChild1 == nullptr && subtreeChild2 != nullptr) {
      return findClosestSharedManager(subtreeChild2, e1_id, e2_id);
    }
    // This statement is necessary since if one of the employees are not present, then the closest manager is implied to be the first employee found. 
    // So the function must recursviely call itself with the subtreeChild1, which is where the first employee is found. 
    else if (subtreeChild1 != nullptr && subtreeChild2 == nullptr) {
      return findClosestSharedManager(subtreeChild1, e1_id, e2_id);
    }
    else {
      // If both children are not nullptr and they are not equal to each other, theis means they are in different subtrees now and the head node can 
      // be returned since it is the common manager between the two subtrees.
      return head;
    }
    // This means that both of the employees are not present in any of the children, so return nullptr.
    return nullptr;
  }

/**
 * Calculate the number of managers between employee e1 and employee e2. 
 * 
 * <p>
 * The number of managers between employee e1 and employee e2 can be calculated by: 
 *  number of edges between employee 1 and closest shared manager + 
 *  number of edges between employee 2 and closest shared manager - 1
 *
 * <p>
 * Assumption: e1_id and e2_id are unique among all employee IDs
 *
 * This function uses recursive calling to find the number of managers between two employees. All of the recursvie methods are utilized in this 
 * function. First each employee is checked to see if it is present in the head/root node. If not, then the number of managers between a nonexistent
 // employee and an employee is -1. Otherwise, the closest manager is returned between the two employees through the findClosestSharedManager function
 // with e1_id and e2_id being passed as arguments, along with the head node. The shared manager that is returned will be stored in a closestManager pointer
 // variable. Next the number of levels from each employee to the shared manager is calcualted using the findEmployeeLevel recursive function,
 // with closestManager and e1_id being the first recursive method call arguments and closestManager and e2_id being the second recursive method call arguments.
 // Finally, return the number of edges between the closest manager and e1 + the number of edges between closestManager and e2_id and subtract 1.
 *
 * @param  head  the head / root Employee of the organization chart
 * @param  e1_id id of employee 1 being searched
 * @param  e2_id id of employee 2 being searched 
 * @return   number of managers between employee e1 and employee e2
 *           returns Employee::NOT_FOUND if either e1 or e2 is not present in the chart
 * @see         
 */
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {
  
  // Write your implementation here. You do NOT need to use recursive approach here.
  // This if condition is necessary to ensure that both employee are present in the tree. If not, then -1 is returned to indicate that the operation
  // cannot be performed.
  if (isEmployeePresentInOrg(head, e1_id) && isEmployeePresentInOrg(head, e2_id)) {
    // Store the closest shared manager between e1_id and e2_id by calling the recursive function findClosestManager(head, e1_id, e2_id).
    Employee* closestManager = findClosestSharedManager(head, e1_id, e2_id);
    // The number of edges between the closestManager and the first employee is the head level of closestManager, treating it as the root of a new tree.
    int edgesEmployee1 = findEmployeeLevel(closestManager, e1_id, 0);
    // The number of edges between the closestManager and the second employee is the head level of closestManager, treating it as the root of a new tree.
    int edgesEmployee2 = findEmployeeLevel(closestManager, e2_id, 0);
    // This returns the correct number of edges between between the two children since they share a common manager and the number of levels/edges
    // between each employee and their respective shared manager can easily be calulated using the previous recursive function.
    return edgesEmployee1 + edgesEmployee2 - 1;
  }
  else {
  
  // Use the above functions wherever you need to implement this function.  

  // Continue only if both employee nodes e1_id and e2_id are in the org chart tree
  // otherwise, return Employee::NOT_FOUND
  return Employee::NOT_FOUND;
  }

  // The number of managers between employee e1 and employee e2 can be calculated by: 
  // number of edges between e1_id and closest shared manager + 
  // number of edges between e2_id and closest shared manager - 1
   
}

/** Recursively delete a tree 
 *  The proper implementation of this function is also needed for
 *  passing the valgrind memory leaking test. 
 * 
 * <p>
 * Traversing from the head / root node, recursively deallocate 
 * the memory of the descendants from the leaf node level. 

 * This function is a recursvie function that first traverses through the children of a head node. The recursive function then calls itself
 * with each child passed as a head node. After executing, the child is now the current head node of a subtree and its children are traversed, calling
 * the recursive function with each child as the new head node. This will repeat until a head node of nullptr is returned and all of the head node's children
 * are also nullptr. Then the node will delete and the process will continue for the ancestor's next children. This is accomplished through a post-order
 * traversal by using a for each loop to recursively call the method with the first child of each head node every recursive call.
 *
 * DO NOT worry about removing them from the vector directReports
 * 
 * Use post order traversal:
 * Delete / deallocate the children recursively
 * Delete / deallocate the current node after deleting its children
 *     Before deleting the current node, print its employee ID and a new line
 *     This part will be autograded as well as manually inspected for grading
 * 
 * For example, with the following org chart, the post order traversal
 * order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
 *             1
 *           /    \
 *           2    3
 *          / \  / \
 *          5 6  7 8
 *
 * @param  head  the head / root Employee of the organization chart
 * @return   None 
 * 
 * @see         
 */
void Orgtree::deleteOrgtree(Employee* head) {
  // Write your recursive implementation here

  // Important: Your implementation MUST use the recursive approach 
  // as required in the assignment 3 prompt to avoid penalties.

  // base case: empty tree or organization chart
  // This will execute if the head node is empty, indicating that the list is empty or the current subtree head node is null (this indicates
  // that left most or right most child has already been reached and will return to the next children or the ancestor.
  if (head == nullptr) {
    return;
  }

  // delete children recursively
  // This statement creates a vector of children by returning the head node's direct reports data member.
  vector<Employee*> children = head->getDirectReports();

  // This statement traverses through each child and recursviely calls the deleteOrgTree on each child. Then the function will be called on the 
  // children of the first child. Every recursive call will try and find a head with a nullptr. Then the function will return tos the previous head and iterate
  // over to the next child. Every time a nullptr is accessed, the recursvie function gives priority to the ancestor node. Once a head node has been fully traversed,
  // then the head node will be deleted.
  for(Employee* child: children) {
    //Recursviely call the function with each child being a head node.
    deleteOrgtree(child);
  }
  // print current node's employee ID and a new line
  cout << head->getEmployeeID() << endl;
  

  // delete the current node after deleting its children
  delete head;
}

