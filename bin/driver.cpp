/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Fall 2022
 * @author Mitchell Shapiro <mshapiro6805@sdsu.edu>
 * @date Oct 2022
 */

 /* Single Programmer Affidavit
I the undersigned promise that the submitted assignment is my own work. While I was 
free to discuss ideas with others, the work contained is my own. I recognize that 
should this not be the case; I will be subject to penalties as outlined in the course 
syllabus. 
Name: Cameron Cobb
Red ID: 826504686
*/

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void assert(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
		// If you do comment this out, ignore the
		// "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2   3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);

    Employee *emptyList = new Employee();

    Employee *head2 = new Employee(10, vector<int>{11, 12, 55, 36});
    Employee *new_e10 = head2->getDirectReports().at(0);
    Employee *new_e12 = head2->getDirectReports().at(1);
    Employee *new_e55 = head2->getDirectReports().at(2);


    new_e10->addDirectReports(vector<int>{4, 24});
    new_e12->addDirectReports(vector<int>{8, 16, 46});
    new_e55->addDirectReport(1);
 
    // Begin Testing
    // A few sample testing code are provided below
    
    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature. 
    
    // IMPORTANT: You should also construct at least one different chart 
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 1);
    assert(employeePresent, "ID 1 Present in first tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 10);
    assert(employeePresent, "ID 10 present in first tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -5);
    assert(employeePresent == false, "ID -5 Not present in first tree");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, 7);
    assert(employeePresent, "ID 7 present in first tree");

    bool employeePresent2 = Orgtree::isEmployeePresentInOrg(emptyList, -10);
    assert(employeePresent2 == false, "ID -10 Not present in empty tree");

    bool employeePresent3 = Orgtree::isEmployeePresentInOrg(head2, 10);
    assert(employeePresent3, "ID 10 Present in second tree");
    employeePresent3 = Orgtree::isEmployeePresentInOrg(head2, 12);
    assert(employeePresent3, "ID 30 present in second tree");
    employeePresent3 = Orgtree::isEmployeePresentInOrg(head2, 36);
    assert(employeePresent3, "ID 36 present in second tree");
    employeePresent3 = Orgtree::isEmployeePresentInOrg(head2, 55);
    assert(employeePresent3, "ID 1 present in second tree");
    employeePresent3 = Orgtree::isEmployeePresentInOrg(head2, -15);
    assert(employeePresent3 == false, "ID -15 Not present in second tree"); 



    //TODO...

    // Test findEmployeeLevel function
    int employeeLevel = Orgtree::findEmployeeLevel(head, 4, 0);
    assert(employeeLevel == 1, "Level of ID 4 in first tree returns " + to_string(employeeLevel) + ", expected 1");
    employeeLevel = Orgtree::findEmployeeLevel(head, 1, 0);
    assert(employeeLevel == 0, "Level of ID 1 in first tree returns " + to_string(employeeLevel) + ", expected 0");
    employeeLevel = Orgtree::findEmployeeLevel(head, 10, 0);
    assert(employeeLevel == 3, "Level of ID 10 in first tree returns " + to_string(employeeLevel) + ", expected 3");
    employeeLevel = Orgtree::findEmployeeLevel(head, 100, 0);
    assert(employeeLevel == -1, "Level of ID 100 in first tree returns " + to_string(employeeLevel) + ", expected -1");

    employeeLevel = Orgtree::findEmployeeLevel(emptyList, 1, 0);
    assert(employeeLevel == -1, "Level of ID 10 in empty tree returns " + to_string(employeeLevel) + ", expected -1");

    int employeeLevel2 = Orgtree::findEmployeeLevel(head2, 10, 0);
    assert(employeeLevel2 == 0, "Level of ID 10 in second tree returns " + to_string(employeeLevel2) + ", expected 0");
    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 40, 0);
    assert(employeeLevel2 == -1, "Level of ID 40 in second tree returns " + to_string(employeeLevel2) + ", expected -1");
    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 36, 0);
    assert(employeeLevel2 == 1, "Level of ID 10 in second tree returns " + to_string(employeeLevel2) + ", expected 1");
    employeeLevel2 = Orgtree::findEmployeeLevel(head2, 16, 0);
    assert(employeeLevel2 == 2, "Level of ID 16 in second tree returns " + to_string(employeeLevel2) + ", expected 2");

    

    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID
    Employee *employeeSharedManager = Orgtree::findClosestSharedManager(head, 10, 12);
    assert(employeeSharedManager->getEmployeeID() == 1, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 1");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 2, 12);
    assert(employeeSharedManager->getEmployeeID() == 1, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 1");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 5, 11);
    assert(employeeSharedManager->getEmployeeID() == 2, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 2");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 7, 8);
    assert(employeeSharedManager->getEmployeeID() == 3, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 3");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 4, 12);
    assert(employeeSharedManager->getEmployeeID() == 4, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 4");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 10, 5);
    assert(employeeSharedManager->getEmployeeID() == 5, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 5");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 2, 20);
    assert(employeeSharedManager->getEmployeeID() == 2, "Closest shared manager for first tree returns " + to_string(employeeSharedManager->getEmployeeID()) + ", expected 2");
    employeeSharedManager = Orgtree::findClosestSharedManager(head, 50, 20);
    assert(employeeSharedManager == nullptr, "Closest shared manager for first tree returns nullptr");

    employeeSharedManager = Orgtree::findClosestSharedManager(emptyList, 1, 2);
    assert(employeeSharedManager == nullptr, "Closest shared manager for empty tree returns nullptr");

    Employee *employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 10, 11);
    assert(employeeSharedManager2->getEmployeeID() == 10, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 10");
    employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 16, 46);
    assert(employeeSharedManager2->getEmployeeID() == 12, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 12");
    employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 10, 24);
    assert(employeeSharedManager2->getEmployeeID() == 10, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 10");
    employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 4, 57);
    assert(employeeSharedManager2->getEmployeeID() == 4, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 4");
    employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 11, 1);
    assert(employeeSharedManager2->getEmployeeID() == 10, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 10");
    employeeSharedManager2 = Orgtree::findClosestSharedManager(head2, 24, 1);
    assert(employeeSharedManager2->getEmployeeID() == 10, "Closest shared manager for second tree returns " + to_string(employeeSharedManager2->getEmployeeID()) + ", expected 10");
    employeeSharedManager = Orgtree::findClosestSharedManager(head2, 22, 30);
    assert(employeeSharedManager == nullptr, "Closest shared manager for second tree returns nullptr");
    


    //TODO...

    // Test findNumOfManagersBetween function
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    assert(numManagers == 3, "Managers between 10 and 11 for first tree returns " + to_string(numManagers) + ", expected 3");
    numManagers = Orgtree::findNumOfManagersBetween(head, 7, 8);
    assert(numManagers == 1, "Managers between 7 and 8 for first tree returns " + to_string(numManagers) + ", expected 1");
    numManagers = Orgtree::findNumOfManagersBetween(head, 8, 9);
    assert(numManagers == 3, "Managers between 8 and 9 for first tree returns " + to_string(numManagers) + ", expected 3");
    numManagers = Orgtree::findNumOfManagersBetween(head, 10, 12);
    assert(numManagers == 5, "Managers between 10 and 12 for first tree returns " + to_string(numManagers) + ", expected 5");
    numManagers = Orgtree::findNumOfManagersBetween(head, 100, 12);
    assert(numManagers == -1, "Managers between 100 and 12 for first tree returns " + to_string(numManagers) + ", expected -1");
    numManagers = Orgtree::findNumOfManagersBetween(head, 1, 12);
    assert(numManagers == 2, "Managers between 1 and 12 for first tree returns " + to_string(numManagers) + ", expected 2");

    numManagers = Orgtree::findNumOfManagersBetween(emptyList, 4, 23);
    assert(numManagers == -1, "Managers between 4 and 23 for empty list returns " + to_string(numManagers) + ", expected -1");

    int numManagers2 = Orgtree::findNumOfManagersBetween(head2, 24, 16);
    assert(numManagers2 == 3, "Managers between 10 and 11 for second tree returns " + to_string(numManagers2) + ", expected 3");
    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 36, 11);
    assert(numManagers2 == 1, "Managers between 36 and 11 for second tree returns " + to_string(numManagers2) + ", expected 1");
    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 30, 40);
    assert(numManagers2 == -1, "Managers between 30 and 40 for second tree returns " + to_string(numManagers2) + ", expected -1");
    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 10, 46);
    assert(numManagers2 == 1, "Managers between 10 and 46 for second tree returns " + to_string(numManagers2) + ", expected 1");
    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 120, 250);
    assert(numManagers2 == -1, "Managers between 120 and 250 for second tree returns " + to_string(numManagers2) + ", expected -1");
    numManagers2 = Orgtree::findNumOfManagersBetween(head2, 4, 36);
    assert(numManagers2 == 2, "Managers between 4 and 36 for second tree returns " + to_string(numManagers2) + ", expected 2");



    // TODO numManagers = ...

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree. 

    Orgtree::deleteOrgtree(head);
    Orgtree::deleteOrgtree(emptyList);
    Orgtree::deleteOrgtree(head2);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}