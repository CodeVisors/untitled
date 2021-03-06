#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include<conio.h>

const int PROJECT_STATUS_IDLE = 1;
const int PROJECT_STATUS_COMPLETED = 2;
const int PROJECT_STATUS_PROGRESS = 3;
const int PROJECT_BILLED = 1;
const int PROJECT_NOT_BILLED = 0;

const int EMP_DESIG_MANAGER = 1;
const int EMP_DESIG_ADMIN = 2;
const int EMP_DESIG_WORKER = 3;

const int EMP_STATUS_IDLE = 1;
const int EMP_STATUS_HAVE_PROJECT = 2;
const int EMP_STATUS_BUSY = 3;

const int EMP_MAX_PROJECTS = 5;
const int ERROR = -1;

const int MEMBER_PRODUCT_OWNER = 1;
const int MEMBER_TECH_LEAD = 2;
const int MEMBER_BA = 3;
const int MEMBER_DEVELOPER = 4;
const int MEMBER_TESTER = 5;

const char ADDRESS_PROJECT[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\project.txt";
const char ADDRESS_EMPLOYEE[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\employee.txt";
const char ADDRESS_MEMBER[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\member.txt";
const char ADDRESS_CLIENT[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\client.txt";
const char ADDRESS_LOGIN[100] = "C:\\Users\\Lenovo\\CLionProjects\\untitled\\login.txt";

const char FORMAT_PROJECT[100] = "%d|%s|%d|%s|%s|%s|%d|%d|%d|%d|%d|%d|%d";
const char FORMAT_EMPLOYEE[100] = "%d|%s|%s|%d|%s|%s|%d|%d|%s|%d|%d";
const char FORMAT_MEMBER[100] = "%d|%d|%d";
const char FORMAT_CLIENT[100] = "%d|%s|%s|%s|%s|%d";
const char FORMAT_LOGIN[100] = "%s|%s|%d|%d";

const char FORMAT_PRINT_PROJECT[100] = "\n%d %s %d %s %s %s %d %d %d %d %d %d %d";
const char FORMAT_PRINT_EMPLOYEE[100] = "\n%d %s %s %d %s %s %d %d %s %d %d";
const char FORMAT_PRINT_MEMBER[100] = "\n%d %d %d";
const char FORMAT_PRINT_CLIENT[100] = "\n%d %s %s %s %s %d"; // IF LAST IS %s THEN NO NEED OF \n
const char FORMAT_PRINT_LOGIN[100] = "\n%s %s %d %d";

const char INVALID_INPUT[100] = "\nInvalid Input, Enter again: ";

const char DOMAIN_ARRAY[5][100] = {"Finance", "Banking", "Data Science",
                                   "HealthCare", "Education"};

const int SIZE_DOMAIN = 5;
const int SIZE_COLUMNS_EMPLOYEE = 11;
const int SIZE_COLUMNS_MEMBER = 3;
const int SIZE_COLUMNS_CLIENT = 6;
const int SIZE_COLUMNS_LOGIN = 4;

const int SIZE_COLUMNS_PROJECT = 13;

const char DESIG_ARRAY_EMP[3][20] = {"Manager", "Admin", "Worker"};
const int SIZE_DESIG = 3;

const char COLUMNS_PROJECT[13][50] = {"Id", "Name", "Status", "DeadLine", "Description",
                                      "CreatedOn", "Employees", "ManagerId", "Experience",
                                      "NumExper", "Bill", "Domain", "Client"};

const char COLUMNS_EMPLOYEE[11][50] = {"Id", "Name", "JoiningDate", "Designation", "Email",
                                       "Mobile", "ManagerId", "numOfProjects", "Dob",
                                       "Experience", "DomainExpert"};

const char COLUMNS_MEMBER[3][50] = {"ProjectId", "EmpId", "EmpRole"};
const char COLUMNS_CLIENT[6][50] = {"Id", "Name", "Company",
                                    "Mobile", "Email", "ProjectId"};

const char COLUMNS_LOGIN[4][50] = {"UserName", "Password", "Role", "EmpId"};

const bool isTesting = false;

struct Project {
    int id;
    char name[100];
    int status;
    char deadLine[9];
    char description[200];
    char createdOn[9];
    int numOfEmpNeeded;
    int managerId;
    int minExperience;
    int minExpEmpNum;
    int isBilled;
    int domainExpertId;
    int clientId;
};

struct Employee {
    int id;
    char name[100];
    char joiningDate[9];
    int designation;
    char email[100];
    char mobile[11];
    int managerId;
    int engagedProjects;
    char dob[9];
    int prevExperience;
    int domainExpert;
    int roleInProject; // extra, not in text file
};

struct Member {
    int projectId;
    int empId;
    int empRole;
};

struct Login {
    char userName[100];
    char password[30];
    int role;
    int empId;
};

struct Client {
    int clientId;
    char personName[100];
    char companyName[100];
    char contactMob[11];
    char contactEmail[100];
    int projectId;
};

struct Employee ALL_EMP_ARRAY[100];
int ALL_EMP_ARRAY_SIZE = 0;

struct Project ALL_PROJECT_ARRAY[100];
int ALL_PROJECT_ARRAY_SIZE = 0;

struct Member ALL_MEMBER_ARRAY[100 * 5];
int ALL_MEMBER_ARRAY_SIZE = 0;

struct Login ALL_LOGIN_ARRAY[100];
int ALL_LOGIN_ARRAY_SIZE = 0;

struct Client ALL_CLIENT_ARRAY[100];
int ALL_CLIENT_ARRAY_SIZE = 0;

// SINGLE LINE PRINTING

void printSingleLineProject(struct Project project) {
    printf(FORMAT_PRINT_PROJECT,
           project.id, project.name, project.status, project.deadLine, project.description,
           project.createdOn, project.numOfEmpNeeded, project.managerId,
           project.minExperience, project.minExpEmpNum, project.isBilled,
           project.domainExpertId, project.clientId);
}

void printSingleLineEmployee(struct Employee employee) {
    printf(FORMAT_PRINT_EMPLOYEE,
           employee.id, employee.name, employee.joiningDate,
           employee.designation,
           employee.email,
           employee.mobile, employee.managerId, employee.engagedProjects,
           employee.dob, employee.prevExperience, employee.domainExpert);
}

void printSingleLineMember(struct Member member) {

    printf(FORMAT_PRINT_MEMBER,
           member.projectId, member.empId, member.empRole);
}

void printSingleLineLogin(struct Login login) {

    printf(FORMAT_PRINT_LOGIN,
           login.userName, login.password, login.role, login.empId);

}

void printSingleLineClient(struct Client client) {

    printf(FORMAT_PRINT_CLIENT,
           client.clientId, client.personName, client.companyName,
           client.contactMob, client.contactEmail, client.projectId);

}

// -------> COLUMNS PRINTING

void printColumnsProject() {
    printf("\n\n");
    for (int i = 0; i < SIZE_COLUMNS_PROJECT; ++i) {
        printf("%s ", COLUMNS_PROJECT[i]);
    }
    printf("\n");
}

void printColumnsEmployee() {
    printf("\n\n");
    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i) {
        printf("%s ", COLUMNS_EMPLOYEE[i]);
    }
    printf("\n");
}

void printColumnsClient() {
    printf("\n\n");
    for (int i = 0; i < SIZE_COLUMNS_CLIENT; ++i) {
        printf("%s ", COLUMNS_CLIENT[i]);
    }
    printf("\n");
}

void printColumnsLogin() {
    printf("\n\n");
    for (int i = 0; i < SIZE_COLUMNS_LOGIN; ++i) {
        printf("%s ", COLUMNS_LOGIN[i]);
    }
    printf("\n");
}

void printColumnsMember() {
    printf("\n\n");
    for (int i = 0; i < SIZE_COLUMNS_MEMBER; ++i) {
        printf("%s ", COLUMNS_MEMBER[i]);
    }
    printf("\n");
}

// INITIALIZATION

void updateProjectFile() {

    FILE *projectFile = fopen(ADDRESS_PROJECT, "w");

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {

        if (i != 0) fprintf(projectFile, "%s", "\n");

        struct Project tempP = ALL_PROJECT_ARRAY[i];
        fprintf(projectFile, FORMAT_PROJECT,
                tempP.id, tempP.name, tempP.status,
                tempP.deadLine, tempP.description,
                tempP.createdOn, tempP.numOfEmpNeeded,
                tempP.managerId, tempP.minExperience,
                tempP.minExpEmpNum, tempP.isBilled,
                tempP.domainExpertId, tempP.clientId);

        ALL_PROJECT_ARRAY[i] = tempP;
    }

    fclose(projectFile);

}

void updateEmployeeFile() {

    FILE *employeeFile = fopen(ADDRESS_EMPLOYEE, "w");

    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {
        if (i != 0) fprintf(employeeFile, "%s", "\n");
        fprintf(employeeFile, FORMAT_EMPLOYEE,
                ALL_EMP_ARRAY[i].id, ALL_EMP_ARRAY[i].name, ALL_EMP_ARRAY[i].joiningDate, ALL_EMP_ARRAY[i].designation,
                ALL_EMP_ARRAY[i].email,
                ALL_EMP_ARRAY[i].mobile, ALL_EMP_ARRAY[i].managerId, ALL_EMP_ARRAY[i].engagedProjects,
                ALL_EMP_ARRAY[i].dob, ALL_EMP_ARRAY[i].prevExperience, ALL_EMP_ARRAY[i].domainExpert);
    }

    fclose(employeeFile);
}

void updateMemberFile() {

    FILE *memberFile = fopen(ADDRESS_MEMBER, "w");

    for (int i = 0; i < ALL_MEMBER_ARRAY_SIZE; ++i) {
        if (i != 0) fprintf(memberFile, "%s", "\n");
        fprintf(memberFile, FORMAT_MEMBER,
                ALL_MEMBER_ARRAY[i].projectId, ALL_MEMBER_ARRAY[i].empId, ALL_MEMBER_ARRAY[i].empRole);
    }

    fclose(memberFile);
}

void updateLoginFile() {

    FILE *loginFile = fopen(ADDRESS_LOGIN, "w");
    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {
        if (i != 0) fprintf(loginFile, "%s", "\n");
        fprintf(loginFile, FORMAT_LOGIN,
                ALL_LOGIN_ARRAY[i].userName, ALL_LOGIN_ARRAY[i].password,
                ALL_LOGIN_ARRAY[i].role, ALL_LOGIN_ARRAY[i].empId);
    }

    fclose(loginFile);
}

void updateClientFile() {

    FILE *clientFile = fopen(ADDRESS_CLIENT, "w");
    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        if (i != 0) fprintf(clientFile, "%s", "\n");
        fprintf(clientFile, FORMAT_CLIENT,
                ALL_CLIENT_ARRAY[i].clientId, ALL_CLIENT_ARRAY[i].personName,
                ALL_CLIENT_ARRAY[i].companyName, ALL_CLIENT_ARRAY[i].contactMob,
                ALL_CLIENT_ARRAY[i].contactEmail, ALL_CLIENT_ARRAY[i].projectId);
    }

    fclose(clientFile);
}

void convertRowToProject(char row[], struct Project *project) {

    char *p = strtok(row, "|");
    char *array[SIZE_COLUMNS_PROJECT];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    /*for (int i = 0; i < 13; ++i){
        printf(array[i]);
        printf(" ");
    }*/

    int c = 0;
    project->id = atoi(array[c++]);
    strcpy(project->name, array[c++]);
    project->status = atoi(array[c++]);
    strncpy(project->deadLine, array[c++], 9);
    strcpy(project->description, array[c++]);
    strncpy(project->createdOn, array[c++], 9);
    project->numOfEmpNeeded = atoi(array[c++]);
    project->managerId = atoi(array[c++]);
    project->minExperience = atoi(array[c++]);
    project->minExpEmpNum = atoi(array[c++]);
    project->isBilled = atoi(array[c++]);
    project->domainExpertId = atoi(array[c++]);
    project->clientId = atoi(array[c++]);
}

void convertRowToEmployee(char row[], struct Employee *employee) {

    char *p = strtok(row, "|");
    char *array[SIZE_COLUMNS_EMPLOYEE];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    int c = 0;
    employee->id = atoi(array[c++]);
    strcpy(employee->name, array[c++]);
    strncpy(employee->joiningDate, array[c++], 9);
    employee->designation = atoi(array[c++]);
    strcpy(employee->email, array[c++]);
    strcpy(employee->mobile, array[c++]);
    employee->managerId = atoi(array[c++]);
    employee->engagedProjects = atoi(array[c++]);
    strncpy(employee->dob, array[c++], 9);
    employee->prevExperience = atoi(array[c++]);
    employee->domainExpert = atoi(array[c++]);
    employee->roleInProject = atoi(array[c++]); // this is useful to add to member table
}

void convertRowToMember(char row[], struct Member *member) {

    char *p = strtok(row, "|");
    char *array[SIZE_COLUMNS_MEMBER];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    int c = 0;
    member->projectId = atoi(array[c++]);
    member->empId = atoi(array[c++]);
    member->empRole = atoi(array[c++]);
}

void convertRowToLogin(char row[], struct Login *login) {
    char *p = strtok(row, "|");
    char *array[SIZE_COLUMNS_LOGIN];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    /*for (int i = 0; i < 4; ++i){
        printf(array[i]);
        printf(" ");
    }*/

    int c = 0;
    strcpy(login->userName, array[c++]);
    strcpy(login->password, array[c++]);
    login->role = atoi(array[c++]);
    login->empId = atoi(array[c++]);
}

void convertRowToClient(char row[], struct Client *client) {

    char *p = strtok(row, "|");
    char *array[SIZE_COLUMNS_CLIENT];

    int i = 0;
    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, "|");
    }

    int c = 0;
    client->clientId = atoi(array[c++]);
    strcpy(client->personName, array[c++]);
    strcpy(client->companyName, array[c++]);
    strcpy(client->contactMob, array[c++]);
    strcpy(client->contactEmail, array[c++]);
    client->projectId = atoi(array[c++]);
}

void getDataOfProjectTable() {

    FILE *fileProject = fopen(ADDRESS_PROJECT, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, fileProject) != NULL) {
        struct Project pr;
        convertRowToProject(tempRow, &pr);
        ALL_PROJECT_ARRAY[index++] = pr;
    }

    ALL_PROJECT_ARRAY_SIZE = index;
    fclose(fileProject);
}

void getDataOfEmployeeTable() {

    FILE *empFile = fopen(ADDRESS_EMPLOYEE, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, empFile) != NULL) {
        struct Employee tempEmp;
        convertRowToEmployee(tempRow, &tempEmp);
        ALL_EMP_ARRAY[index++] = tempEmp;
    }

    ALL_EMP_ARRAY_SIZE = index;
    fclose(empFile);
}

void getDataOfMemberTable() {

    FILE *memberFile = fopen(ADDRESS_MEMBER, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, memberFile) != NULL) {
        struct Member tempMember;
        convertRowToMember(tempRow, &tempMember);
        ALL_MEMBER_ARRAY[index++] = tempMember;
    }

    ALL_MEMBER_ARRAY_SIZE = index;

    fclose(memberFile);
}

void getDataOfLoginTable() {

    FILE *loginFile = fopen(ADDRESS_LOGIN, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, loginFile) != NULL) {
        struct Login login;
        convertRowToLogin(tempRow, &login);
        ALL_LOGIN_ARRAY[index++] = login;
    }

    ALL_LOGIN_ARRAY_SIZE = index;

    fclose(loginFile);
}

void getDataOfClientTable() {

    FILE *clientFile = fopen(ADDRESS_CLIENT, "r");
    char tempRow[1000];

    int index = 0;
    while (fgets(tempRow, 1000, clientFile) != NULL) {
        struct Client client;
        convertRowToClient(tempRow, &client);
        ALL_CLIENT_ARRAY[index++] = client;
    }

    ALL_CLIENT_ARRAY_SIZE = index;

    fclose(clientFile);
}

void initializeApp() {
    // This calls the important startUp functions
    getDataOfProjectTable();
    getDataOfEmployeeTable();
    getDataOfMemberTable();
    getDataOfClientTable();
    getDataOfLoginTable();
}

// -------> REPORTS WORK

void displayEmployeesByWorkStatus(int STATUS) {

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i) {
        printf(" %s", COLUMNS_EMPLOYEE[i]);
    }

    printf("\n");

    if (STATUS == EMP_MAX_PROJECTS || STATUS == 0) {
        for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
            if (ALL_EMP_ARRAY[i].engagedProjects == STATUS)
                printSingleLineEmployee(ALL_EMP_ARRAY[i]);
        }
    }
}

void displayProjectsByProgressStatus(int STATUS) {

    printColumnsProject();

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project temp = ALL_PROJECT_ARRAY[i];
        if (temp.status == STATUS) {
            printSingleLineProject(temp);
        }
    }
}

void displayAllProjects() {

    printColumnsProject();

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project temp = ALL_PROJECT_ARRAY[i];
        printSingleLineProject(temp);
    }
}

void displayAllEmployees() {

    printf("Employee Report");

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i) {
        printf(" %s", COLUMNS_EMPLOYEE[i]);
    }

    printf("\n");

    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        printSingleLineEmployee(ALL_EMP_ARRAY[i]);
    }

}

void displayEmployeesForProject(int projectId) {

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i)
        printf(" %s", COLUMNS_EMPLOYEE[i]);

    printf("\n");
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        if (ALL_EMP_ARRAY[i].id == projectId)
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
    }
}

void displayClientByProjectId(int projectId) {

    printColumnsClient();

    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        struct Client client = ALL_CLIENT_ARRAY[i];
        if (client.projectId == projectId) {
            printSingleLineClient(client);
        }
    }
}

void displayEmployeesByDesignation(int designation) {
    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i)
        printf(" %s", COLUMNS_EMPLOYEE[i]);

    printf("\n");
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        if (ALL_EMP_ARRAY[i].designation == designation)
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
    }
}

void displayAllClients() {
    printColumnsClient();

    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        struct Client client = ALL_CLIENT_ARRAY[i];
        printSingleLineClient(client);
    }
}

int showAllManagersCustom() {

    // It shows all managers
    // return the count of managers

    for (int i = 0; i < SIZE_COLUMNS_EMPLOYEE; ++i)
        printf(" %s", COLUMNS_EMPLOYEE[i]);

    int totalManagers = 0;
    printf("\n");
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {

        printf("");
        if (ALL_EMP_ARRAY[i].designation == EMP_DESIG_MANAGER) {
            struct Employee e = ALL_EMP_ARRAY[i];
            printf("\n%d. %s %s", i + 1, e.name, e.designation);
            printSingleLineEmployee(ALL_EMP_ARRAY[i]);
            totalManagers++;
        }
    }

    return totalManagers;
}

void displayEmployeesByDesignation(int designation);

void displayAllClients();

// ------------> COUNT FUNCTIONS

int getCountProjectByStatus(int status) {

    int projectsCount = 0;

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project temp = ALL_PROJECT_ARRAY[i];
        if (temp.status == status) {
            projectsCount++;
        }
    }
    return projectsCount;
}

int getCountEmployeeByStatus(int empStatus) {

    int count = 0;

    if (empStatus == EMP_MAX_PROJECTS || empStatus == 0) {
        for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
            if (ALL_EMP_ARRAY[i].engagedProjects == empStatus) count++;
        }
    }

    return count;

}

int getCountProjectsByBilling(int billed) {
    int projectsCount = 0;

    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project temp = ALL_PROJECT_ARRAY[i];
        if (temp.isBilled == billed) {
            projectsCount++;
        }
    }
    return projectsCount;
}

int getCountAllProjects() {
    return ALL_PROJECT_ARRAY_SIZE;
}

int getCountAllEmployees() {
    return ALL_EMP_ARRAY_SIZE;
}

// -------> GET STRUCTURES BY ID'S

struct Employee getEmployeeById(int empId) {
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; i++) {
        if (ALL_EMP_ARRAY[i].id == empId)return ALL_EMP_ARRAY[i];
    }
}

struct Project getProjectById(int projectId) {
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; i++) {
        if (ALL_PROJECT_ARRAY[i].id == projectId)
            return ALL_PROJECT_ARRAY[i];
    }
}

// INTERNAL - NO DIRECT CALL ---> Print ALL Data for testing

void testPrintClients() {

    printf("\n\nDATA OF FILE CLIENT:");
    printColumnsClient();

    for (int i = 0; i < ALL_CLIENT_ARRAY_SIZE; ++i) {
        struct Client client = ALL_CLIENT_ARRAY[i];
        printSingleLineClient(client);
    }
}

void testPrintEmployees() {

    printf("\n\nDATA OF FILE EMPLOYEE:");
    printColumnsEmployee();
    for (int i = 0; i < ALL_EMP_ARRAY_SIZE; ++i) {
        struct Employee emp1 = ALL_EMP_ARRAY[i];
        printSingleLineEmployee(emp1);
    }
}

void testPrintMembers() {

    printf("\n\nDATA OF FILE MEMBER:");
    printColumnsMember();
    for (int i = 0; i < ALL_MEMBER_ARRAY_SIZE; ++i) {
        struct Member member = ALL_MEMBER_ARRAY[i];
        printSingleLineMember(member);
    }
}

void testPrintProjects() {

    printf("\n\nDATA OF FILE PROJECT:");
    printColumnsProject();
    for (int i = 0; i < ALL_PROJECT_ARRAY_SIZE; ++i) {
        struct Project p1 = ALL_PROJECT_ARRAY[i];
        printSingleLineProject(p1);
    }
}

void testPrintLogins() {

    printf("\n\nDATA OF FILE LOGIN:");
    printColumnsLogin();
    for (int i = 0; i < ALL_LOGIN_ARRAY_SIZE; ++i) {
        struct Login login = ALL_LOGIN_ARRAY[i];
        printSingleLineLogin(login);
    }
}

void testPrintRowsSize() {

    printf("\n\nNUMBER OF ROWS IN EACH FILE:\n");

    printf("\nProject Rows = %d ", ALL_PROJECT_ARRAY_SIZE);
    printf("\nEmployee Rows = %d ", ALL_EMP_ARRAY_SIZE);
    printf("\nClient Rows = %d ", ALL_CLIENT_ARRAY_SIZE);
    printf("\nMember Rows = %d ", ALL_MEMBER_ARRAY_SIZE);
    printf("\nLogin Rows = %d ", ALL_LOGIN_ARRAY_SIZE);
}

void testUpdatingMethods() {
    updateProjectFile();
    updateMemberFile();
    updateClientFile();
    updateMemberFile();
    updateLoginFile();
}

// --------> Testing Methods

void performDatabaseTesting() {

    testUpdatingMethods();

    testPrintEmployees();
    testPrintMembers();
    testPrintProjects();
    testPrintLogins();
    testPrintClients();

    testPrintRowsSize();

    updateProjectFile();

}

void simpleTest() {
    printf("Checking Simple calling");
}