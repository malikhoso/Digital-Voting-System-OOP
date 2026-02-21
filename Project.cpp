#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <limits>
#include <conio.h>

using namespace std;

/*
 * ===================================================================
 * FORWARD DECLARATIONS
 * ===================================================================
 */
class Candidate; // Forward declaration for use in Party class

/*
 * ===================================================================
 * PARTY CLASS - Represents a political party
 * This demonstrates COMPOSITION relationship with candidates
 * ===================================================================
 */
class Party {
private:
    string partyId;
    string partyName;
    string partySymbol;
    string manifesto;
    vector<string> candidateIds; // Stores IDs of candidates belonging to this party
    int totalVotes; // Total votes received by all party candidates

public:
    // Default constructor - needed for file operations
    Party() : totalVotes(0) {}
    
    // Parameterized constructor - OOP CONCEPT: Constructor with parameters
    Party(string id, string name, string symbol, string m) 
        : partyId(id), partyName(name), partySymbol(symbol), manifesto(m), totalVotes(0) {}
    
    // GETTER METHODS - OOP CONCEPT: Encapsulation (Data hiding)
    // These methods provide controlled access to private data members
    string getId() const { return partyId; }
    string getName() const { return partyName; }
    string getSymbol() const { return partySymbol; }
    string getManifesto() const { return manifesto; }
    int getTotalVotes() const { return totalVotes; }
    vector<string> getCandidateIds() const { return candidateIds; }
    
    // SETTER METHODS - OOP CONCEPT: Encapsulation
    void setTotalVotes(int votes) { totalVotes = votes; }
    
    // Method to add a candidate to this party - COMPOSITION relationship
    void addCandidate(const string& candidateId) {
        candidateIds.push_back(candidateId);
    }
    
    // Method to remove a candidate from this party
    bool removeCandidate(const string& candidateId) {
        auto it = find(candidateIds.begin(), candidateIds.end(), candidateId);
        if (it != candidateIds.end()) {
            candidateIds.erase(it);
            return true;
        }
        return false;
    }
    
    // Check if party has any candidates
    bool hasCandidates() const {
        return !candidateIds.empty();
    }
    
    // File I/O methods for data persistence
    string toString() const {
        string candidateList = "";
        for (size_t i = 0; i < candidateIds.size(); i++) {
            candidateList += candidateIds[i];
            if (i < candidateIds.size() - 1) candidateList += ";";
        }
        return partyId + "," + partyName + "," + partySymbol + "," + 
               manifesto + "," + to_string(totalVotes) + "," + candidateList;
    }
    
    void fromString(const string& str) {
        stringstream ss(str);
        string token;
        
        getline(ss, partyId, ',');
        getline(ss, partyName, ',');
        getline(ss, partySymbol, ',');
        getline(ss, manifesto, ',');
        getline(ss, token, ',');
        totalVotes = stoi(token);
        
        // Parse candidate IDs
        candidateIds.clear();
        getline(ss, token, ',');
        if (!token.empty()) {
            stringstream candidateStream(token);
            string candidateId;
            while (getline(candidateStream, candidateId, ';')) {
                candidateIds.push_back(candidateId);
            }
        }
    }
};

/*
 * ===================================================================
 * ABSTRACT BASE CLASS - USER
 * OOP CONCEPTS: Abstraction, Inheritance, Polymorphism
 * ===================================================================
 */
class User {
protected: // OOP CONCEPT: Protected access - accessible to derived classes only
    string username;
    string password;
    string name;
    string id;
    string cnic; // Added CNIC for Pakistani voting system

public:
    // OOP CONCEPT: Constructor with parameters
    User(string un, string pw, string n, string i, string c) 
        : username(un), password(pw), name(n), id(i), cnic(c) {}
    
    // OOP CONCEPT: Virtual destructor - ensures proper cleanup in inheritance
    virtual ~User() {}
    
    // OOP CONCEPT: Pure virtual function - makes this an abstract class
    // This MUST be implemented by derived classes (Polymorphism)
    virtual void displayMenu() = 0;
    
    // OOP CONCEPT: Virtual function - can be overridden in derived classes
    virtual bool authenticate(string un, string pw) {
        return (username == un && password == pw);
    }
    
    // OOP CONCEPT: Getter methods for encapsulation
    string getUsername() const { return username; }
    string getName() const { return name; }
    string getId() const { return id; }
    string getCnic() const { return cnic; }
};

/*
 * ===================================================================
 * TEMPLATE CLASS - DATA MANAGER
 * DATA STRUCTURE CONCEPT: Template (Generic Programming)
 * This allows the same class to work with different data types
 * ===================================================================
 */
template<typename T>
class DataManager {
private:
    vector<T> data; // DATA STRUCTURE: Vector (dynamic array)
    
public:
    // Add an item to the collection
    void addData(const T& item) {
        data.push_back(item); // Vector method to add at end
    }
    
    // Get reference to all data (allows modification)
    vector<T>& getAllData() {
        return data;
    }
    
    // Clear all data
    void clearData() {
        data.clear(); // Vector method to remove all elements
    }
    
    // Get number of items
    int getSize() const {
        return data.size(); // Vector method to get size
    }
    
    // Get item at specific index with bounds checking
    T& getItem(int index) {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        // OOP CONCEPT: Exception handling
        throw out_of_range("Index out of range");
    }
    
    // Find item by a predicate function (advanced concept)
    template<typename Predicate>
    T* findItem(Predicate pred) {
        for (auto& item : data) {
            if (pred(item)) {
                return &item;
            }
        }
        return nullptr;
    }
};

/*
 * ===================================================================
 * CANDIDATE CLASS
 * OOP CONCEPT: This class will have AGGREGATION relationship with Party
 * ===================================================================
 */
class Candidate {
private:
    string candidateId;
    string name;
    string cnic; // Added CNIC for Pakistani system
    string partyId; // Reference to party (AGGREGATION - candidate belongs to party)
    string manifesto;
    int votes;
    bool isIndependent; // Flag to check if candidate is independent

public:
    // Default constructor for file operations
    Candidate() : votes(0), isIndependent(true) {}
    
    // Constructor for independent candidate
    Candidate(string id, string n, string c, string m) 
        : candidateId(id), name(n), cnic(c), partyId(""), manifesto(m), votes(0), isIndependent(true) {}
    
    // Constructor for party candidate - AGGREGATION relationship
    Candidate(string id, string n, string c, string pId, string m) 
        : candidateId(id), name(n), cnic(c), partyId(pId), manifesto(m), 
          votes(0), isIndependent(false) {}
    
    // GETTER METHODS - OOP CONCEPT: Encapsulation
    string getId() const { return candidateId; }
    string getName() const { return name; }
    string getCnic() const { return cnic; }
    string getPartyId() const { return partyId; }
    string getManifesto() const { return manifesto; }
    int getVotes() const { return votes; }
    bool getIsIndependent() const { return isIndependent; }
    
    // SETTER METHODS
    void setPartyId(const string& pId) { 
        partyId = pId; 
        isIndependent = pId.empty();
    }
    
    // Increment votes
    void addVote() { votes++; }
    void setVotes(int v) { votes = v; }
    
    // Check if candidate belongs to a specific party
    bool belongsToParty(const string& pId) const {
        return !isIndependent && partyId == pId;
    }
    
    // File I/O methods for data persistence
    string toString() const {
        return candidateId + "," + name + "," + cnic + "," + partyId + "," + 
               manifesto + "," + to_string(votes) + "," + (isIndependent ? "1" : "0");
    }
    
    void fromString(const string& str) {
        stringstream ss(str);
        string token;
        
        getline(ss, candidateId, ',');
        getline(ss, name, ',');
        getline(ss, cnic, ',');
        getline(ss, partyId, ',');
        getline(ss, manifesto, ',');
        getline(ss, token, ',');
        votes = stoi(token);
        getline(ss, token, ',');
        isIndependent = (token == "1");
    }
};

/*
 * ===================================================================
 * VOTER CLASS - INHERITS FROM USER
 * OOP CONCEPT: Inheritance - Voter IS-A User
 * ===================================================================
 */
class Voter : public User { // OOP CONCEPT: Public inheritance
private:
    bool hasVoted;
    string votedFor;

public:
    // Default constructor for file operations
    Voter() : User("", "", "", "", ""), hasVoted(false), votedFor("") {}
    
    // Parameterized constructor - calls base class constructor
    Voter(string un, string pw, string n, string i, string c) 
        : User(un, pw, n, i, c), hasVoted(false), votedFor("") {}
    
    // OOP CONCEPT: Method overriding - implementing pure virtual function
    void displayMenu() override {
        cout << "\n=== VOTER MENU ===" << endl;
        cout << "Welcome, " << name << " (CNIC: " << cnic << ")" << endl;
        cout << "1. View Candidates" << endl;
        cout << "2. View Parties" << endl;
        cout << "3. Cast Vote" << endl;
        cout << "4. Check Voting Status" << endl;
        cout << "5. Logout" << endl;
        cout << "=================" << endl;
    }
    
    // GETTER METHODS
    bool getHasVoted() const { return hasVoted; }
    string getVotedFor() const { return votedFor; }
    
    // Cast vote method
    void castVote(string candidateId) {
        hasVoted = true;
        votedFor = candidateId;
    }
    
    // File I/O methods
    string toString() const {
        return username + "," + password + "," + name + "," + id + "," + cnic + "," +
               (hasVoted ? "1" : "0") + "," + votedFor;
    }
    
    void fromString(const string& str) {
        stringstream ss(str);
        string token;
        
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, id, ',');
        getline(ss, cnic, ',');
        getline(ss, token, ',');
        hasVoted = (token == "1");
        getline(ss, votedFor, ',');
    }
};

/*
 * ===================================================================
 * ADMIN CLASS - INHERITS FROM USER
 * OOP CONCEPT: Inheritance - Admin IS-A User
 * ===================================================================
 */
class Admin : public User { // OOP CONCEPT: Public inheritance
public:
    // Constructor - calls base class constructor
    Admin(string un, string pw, string n, string i, string c) : User(un, pw, n, i, c) {}
    
    // OOP CONCEPT: Method overriding - implementing pure virtual function
    void displayMenu() override {
        cout << "\n=== ADMIN MENU ===" << endl;
        cout << "Welcome, " << name << endl;
        cout << "1. Manage Parties" << endl;
        cout << "2. Add Candidate" << endl;
        cout << "3. View All Candidates" << endl;
        cout << "4. Register Voter" << endl;
        cout << "5. View All Voters" << endl;
        cout << "6. Set Election Timing" << endl;
        cout << "7. View Election Status" << endl;
        cout << "8. Generate Election Report" << endl;
        cout << "9. Logout" << endl;
        cout << "====================" << endl;
    }
};

/*
 * ===================================================================
 * ELECTION TIMER CLASS
 * OOP CONCEPT: Encapsulation - manages election timing internally
 * ===================================================================
 */
class ElectionTimer {
private:
    time_t startTime;
    time_t endTime;
    bool timingSet;

public:
    // Constructor
    ElectionTimer() : startTime(0), endTime(0), timingSet(false) {}
    
    // Set election timing
    void setTiming(time_t start, time_t end) {
        startTime = start;
        endTime = end;
        timingSet = true;
    }
    
    // Check if election is currently active
    bool isElectionActive() const {
        if (!timingSet) return false;
        time_t current = time(0);
        return (current >= startTime && current <= endTime);
    }
    
    // Check if election has started
    bool hasElectionStarted() const {
        if (!timingSet) return false;
        time_t current = time(0);
        return current >= startTime;
    }
    
    // Check if election has ended
    bool hasElectionEnded() const {
        if (!timingSet) return false;
        time_t current = time(0);
        return current > endTime;
    }
    
    // Get current election status
    string getStatus() const {
        if (!timingSet) return "Election timing not set";
        
        time_t current = time(0);
        if (current < startTime) return "Election not started";
        else if (current <= endTime) return "Election is active";
        else return "Election has ended";
    }
    
    // File I/O methods for persistence
    void saveToFile() const {
        ofstream file("election_timing.txt");
        if (file.is_open()) {
            file << startTime << "," << endTime << "," << timingSet << endl;
            file.close();
        }
    }
    
    void loadFromFile() {
        ifstream file("election_timing.txt");
        if (file.is_open()) {
            string line;
            if (getline(file, line)) {
                stringstream ss(line);
                string token;
                
                getline(ss, token, ',');
                startTime = stoll(token);
                getline(ss, token, ',');
                endTime = stoll(token);
                getline(ss, token, ',');
                timingSet = (token == "1");
            }
            file.close();
        }
    }
    
    // GETTER METHODS
    time_t getStartTime() const { return startTime; }
    time_t getEndTime() const { return endTime; }
    bool isTimingSet() const { return timingSet; }
};

/*
 * ===================================================================
 * FILE HANDLER CLASS - TEMPLATE CLASS
 * DATA STRUCTURE CONCEPT: Template for generic file operations
 * ===================================================================
 */
template<typename T>
class FileHandler {
public:
    // Static method - belongs to class, not instance
    static void saveToFile(const vector<T>& data, const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            // Range-based for loop (C++11 feature)
            for (const auto& item : data) {
                file << item.toString() << endl;
            }
            file.close();
        }
    }
    
    // Static method for loading data from file
    static void loadFromFile(vector<T>& data, const string& filename) {
        data.clear();
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (!line.empty()) {
                    T item;
                    item.fromString(line);
                    data.push_back(item);
                }
            }
            file.close();
        }
    }
};

/*
 * ===================================================================
 * MAIN VOTING SYSTEM CLASS
 * OOP CONCEPT: Composition - VotingSystem HAS-A DataManager, Admin, Timer
 * This is the main class that orchestrates the entire system
 * ===================================================================
 */
class VotingSystem {
private:
    // OOP CONCEPT: Composition relationships
    DataManager<Candidate> candidates;  // HAS-A relationship
    DataManager<Voter> voters;         // HAS-A relationship
    DataManager<Party> parties;        // HAS-A relationship
    Admin admin;                       // HAS-A relationship
    ElectionTimer timer;               // HAS-A relationship
    User* currentUser;                 // Pointer for polymorphism
    int nextCandidateId;
    int nextPartyId; 
    int nextVoterId;

    string generateCandidateId() {
        return to_string(nextCandidateId++);
    }
    
    string generatePartyId() {
        return to_string(nextPartyId++);
    }
    
    string generateVoterId() {
        return to_string(nextVoterId++);
    }
    
    void initializeIdCounters() {
        nextCandidateId = 101;
        nextPartyId = 201;
        nextVoterId = 10001;
        
        // Find max existing candidate ID
        for (const auto& candidate : candidates.getAllData()) {
            int id = stoi(candidate.getId());
            if (id >= nextCandidateId) {
                nextCandidateId = id + 1;
            }
        }
        
        // Find max existing party ID
        for (const auto& party : parties.getAllData()) {
            int id = stoi(party.getId());
            if (id >= nextPartyId) {
                nextPartyId = id + 1;
            }
        }
        
        // Find max existing voter ID
        for (const auto& voter : voters.getAllData()) {
            int id = stoi(voter.getId());
            if (id >= nextVoterId) {
                nextVoterId = id + 1;
            }
        }
    }

public:
    // Constructor - initializes the system
    VotingSystem() : admin("admin", "admin123", "System Administrator", "ADM001", "00000-0000000-0"), 
                     currentUser(nullptr) {
        loadData();
        initializeIdCounters();
    }
    
    // Destructor - saves data when system shuts down
    ~VotingSystem() {
        saveData();
    }
    
    // Save all data to files
    void saveData() {
        FileHandler<Candidate>::saveToFile(candidates.getAllData(), "candidates.txt");
        FileHandler<Voter>::saveToFile(voters.getAllData(), "voters.txt");
        FileHandler<Party>::saveToFile(parties.getAllData(), "parties.txt");
        timer.saveToFile();
    }
    
    // Load all data from files
    void loadData() {
        FileHandler<Candidate>::loadFromFile(candidates.getAllData(), "candidates.txt");
        FileHandler<Voter>::loadFromFile(voters.getAllData(), "voters.txt");
        FileHandler<Party>::loadFromFile(parties.getAllData(), "parties.txt");
        timer.loadFromFile();
    }
    
    /*
     * ===================================================================
     * INPUT VALIDATION METHODS
     * These ensure data integrity and user-friendly input
     * ===================================================================
     */
    
    // Validate string input with length constraints
    string getValidatedString(const string& prompt, int minLength = 1, int maxLength = 100) {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            
            if (input.length() >= minLength && input.length() <= maxLength) {
                return input;
            }
            cout << "Invalid input. Length should be between " << minLength 
                 << " and " << maxLength << " characters." << endl;
        }
    }
    
    // Validate integer input with range constraints
    int getValidatedInt(const string& prompt, int min, int max) {
        int input;
        while (true) {
            cout << prompt;
            if (cin >> input && input >= min && input <= max) {
                cin.ignore(); // Clear input buffer
                return input;
            }
            cout << "Invalid input. Please enter a number between " << min 
                 << " and " << max << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // Validate CNIC format (Pakistani format: 00000-0000000-0)
    string getValidatedCNIC(const string& prompt) {
        string cnic;
        while (true) {
            cout << prompt << " (Format: 00000-0000000-0): ";
            getline(cin, cnic);
            
            // Basic CNIC validation - 13 digits with 2 hyphens
            if (cnic.length() == 15 && cnic[5] == '-' && cnic[13] == '-') {
                // Check if all other characters are digits
                bool valid = true;
                for (int i = 0; i < 15; i++) {
                    if (i != 5 && i != 13 && !isdigit(cnic[i])) {
                        valid = false;
                        break;
                    }
                }
                if (valid) return cnic;
            }
            cout << "Invalid CNIC format. Please use format: 00000-0000000-0" << endl;
        }
    }

    string getHiddenPassword(const string& prompt) {
    string password;
    char ch;
    
    cout << prompt;
    
    // #ifdef _WIN32
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            } else {
                    password += ch;
                    cout << '*';
            }
        }
    // #endif
        cout << endl;
        return password;
    }
    
    // Check if CNIC already exists in the system
    bool cnicExists(const string& cnic) {
        // Check in voters
        for (const auto& voter : voters.getAllData()) {
            if (voter.getCnic() == cnic) return true;
        }
        // Check in candidates
        for (const auto& candidate : candidates.getAllData()) {
            if (candidate.getCnic() == cnic) return true;
        }
        return false;
    }
    
    // Validate date/time input
    time_t getValidatedDateTime(const string& prompt) {
        struct tm timeinfo = {};
        int year, month, day, hour, minute;
        
        while (true) {
            cout << prompt << " (YYYY MM DD HH MM): ";
            if (cin >> year >> month >> day >> hour >> minute) {
                if (year >= 2024 && month >= 1 && month <= 12 && day >= 1 && day <= 31 &&
                    hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59) {
                    
                    timeinfo.tm_year = year - 1900;
                    timeinfo.tm_mon = month - 1;
                    timeinfo.tm_mday = day;
                    timeinfo.tm_hour = hour;
                    timeinfo.tm_min = minute;
                    timeinfo.tm_sec = 0;
                    
                    cin.ignore();
                    return mktime(&timeinfo);
                }
            }
            cout << "Invalid date/time format. Please use YYYY MM DD HH MM format." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    /*
     * ===================================================================
     * PARTY MANAGEMENT METHODS
     * These handle party-related operations
     * ===================================================================
     */
    
    void manageParties() {
        while (true) {
            cout << "\n=== PARTY MANAGEMENT ===" << endl;
            cout << "1. Add New Party" << endl;
            cout << "2. View All Parties" << endl;
            cout << "3. View Party Details" << endl;
            cout << "4. Back to Main Menu" << endl;
            
            int choice = getValidatedInt("Enter your choice: ", 1, 4);
            
            switch (choice) {
                case 1: addParty(); break;
                case 2: viewAllParties(); break;
                case 3: viewPartyDetails(); break;
                case 4: return;
            }
        }
    }
    
    void addParty() {
        cout << "\n=== ADD NEW PARTY ===" << endl;
        
        string id = generatePartyId();
        
        string name = getValidatedString("Party Name: ", 2, 50);
        string symbol = getValidatedString("Party Symbol: ", 1, 20);
        string manifesto = getValidatedString("Party Manifesto: ", 10, 500);
        
        parties.addData(Party(id, name, symbol, manifesto));
        cout << "Party added successfully!" << endl;
    }
    
    void viewAllParties() {
        cout << "\n=== ALL PARTIES ===" << endl;
        if (parties.getSize() == 0) {
            cout << "No parties registered." << endl;
            return;
        }
        
        cout << left << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Symbol" 
             << setw(12) << "Candidates" << setw(12) << "Total Votes" << endl;
        cout << string(82, '-') << endl;
        
        for (const auto& party : parties.getAllData()) {
            cout << left << setw(10) << party.getId()
                 << setw(30) << party.getName()
                 << setw(15) << party.getSymbol()
                 << setw(12) << party.getCandidateIds().size()
                 << setw(12) << party.getTotalVotes() << endl;
        }
    }
    
    void viewPartyDetails() {
        if (parties.getSize() == 0) {
            cout << "No parties available." << endl;
            return;
        }
        
        viewAllParties();
        string partyId = getValidatedString("Enter Party ID to view details: ");
        
        for (const auto& party : parties.getAllData()) {
            if (party.getId() == partyId) {
                cout << "\n=== PARTY DETAILS ===" << endl;
                cout << "Party ID: " << party.getId() << endl;
                cout << "Party Name: " << party.getName() << endl;
                cout << "Symbol: " << party.getSymbol() << endl;
                cout << "Manifesto: " << party.getManifesto() << endl;
                cout << "Total Votes: " << party.getTotalVotes() << endl;
                cout << "Number of Candidates: " << party.getCandidateIds().size() << endl;
                
                // Show party candidates
                if (!party.getCandidateIds().empty()) {
                    cout << "\nParty Candidates:" << endl;
                    for (const string& candidateId : party.getCandidateIds()) {
                        for (const auto& candidate : candidates.getAllData()) {
                            if (candidate.getId() == candidateId) {
                                cout << "- " << candidate.getName() 
                                     << " (ID: " << candidate.getId() 
                                     << ", Votes: " << candidate.getVotes() << ")" << endl;
                                break;
                            }
                        }
                    }
                }
                return;
            }
        }
        cout << "Party not found!" << endl;
    }
    
    /*
     * ===================================================================
     * USER AUTHENTICATION METHODS
     * OOP CONCEPT: Polymorphism - different types of users
     * ===================================================================
     */
    
    // OOP CONCEPT: Polymorphism - returns pointer to base class User
    User* login() {
        string username, password;
        cout << "\n=== LOGIN ===" << endl;
        username = getValidatedString("Username: ");
        password = getHiddenPassword("Password: ");
        
        // Check admin login first
        if (admin.authenticate(username, password)) {
            cout << "Admin login successful!" << endl;
            return &admin;
        }
        
        // Check voter login
        for (auto& voter : voters.getAllData()) {
            if (voter.authenticate(username, password)) {
                cout << "Voter login successful!" << endl;
                return &voter; // Polymorphism - returning Voter* as User*
            }
        }
        
        cout << "Invalid credentials!" << endl;
        return nullptr;
    }
    
    /*
     * ===================================================================
     * CANDIDATE MANAGEMENT METHODS
     * ===================================================================
     */
    
    void addCandidate() {
        cout << "\n=== ADD CANDIDATE ===" << endl;
        
        string id = generateCandidateId();
        
        string name = getValidatedString("Candidate Name: ", 2, 50);
        string cnic = getValidatedCNIC("Candidate CNIC");
        
        // Check if CNIC already exists
        if (cnicExists(cnic)) {
            cout << "CNIC already registered in the system!" << endl;
            return;
        }
        
        cout << "\nCandidate Type:" << endl;
        cout << "1. Independent Candidate" << endl;
        cout << "2. Party Candidate" << endl;
        int type = getValidatedInt("Select type: ", 1, 2);
        
        if (type == 1) {
            // Independent candidate
            string manifesto = getValidatedString("Personal Manifesto: ", 10, 200);
            candidates.addData(Candidate(id, name, cnic, manifesto));
            cout << "Independent candidate added successfully!" << endl;
        } else {
            // Party candidate
            if (parties.getSize() == 0) {
                cout << "No parties available. Please add a party first." << endl;
                return;
            }
            
            viewAllParties();
            string partyId = getValidatedString("Enter Party ID: ");
            
            // Verify party exists
            bool partyExists = false;
            for (auto& party : parties.getAllData()) {
                if (party.getId() == partyId) {
                    partyExists = true;
                    string manifesto = getValidatedString("Candidate Manifesto: ", 10, 200);
                    candidates.addData(Candidate(id, name, cnic, partyId, manifesto));
                    
                    // Add candidate to party's candidate list
                    party.addCandidate(id);
                    cout << "Party candidate added successfully!" << endl;
                    break;
                }
            }
            
            if (!partyExists) {
                cout << "Invalid Party ID!" << endl;
            }
        }
    }
    
    void viewAllCandidates() {
        cout << "\n=== ALL CANDIDATES ===" << endl;
        if (candidates.getSize() == 0) {
            cout << "No candidates registered." << endl;
            return;
        }
        
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(25) << "CNIC" 
             << setw(12) << "Party/Type" << setw(10) << "Votes" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& candidate : candidates.getAllData()) {
            string partyInfo = candidate.getIsIndependent() ? "Independent" : candidate.getPartyId();
            cout << left << setw(10) << candidate.getId()
                 << setw(20) << candidate.getName()
                 << setw(25) << candidate.getCnic()
                 << setw(12) << partyInfo
                 << setw(10) << candidate.getVotes() << endl;
        }
    }

    void viewAllCandidatesForVoter() {
        cout << "\n=== ALL CANDIDATES ===" << endl;
        if (candidates.getSize() == 0) {
            cout << "No candidates registered." << endl;
            return;
        }
        
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(25) << "CNIC" 
             << setw(12) << "Party/Type" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& candidate : candidates.getAllData()) {
            string partyInfo = candidate.getIsIndependent() ? "Independent" : candidate.getPartyId();
            cout << left << setw(10) << candidate.getId()
                 << setw(20) << candidate.getName()
                 << setw(25) << candidate.getCnic()
                 << setw(12) << partyInfo << endl;
        }
    }
    
    /*
     * ===================================================================
     * VOTER MANAGEMENT METHODS
     * ===================================================================
     */
    
    void registerVoter() {
        cout << "\n=== REGISTER VOTER ===" << endl;
        
        string username = getValidatedString("Username: ", 3, 20);
        
        // Check if username already exists
        for (const auto& voter : voters.getAllData()) {
            if (voter.getUsername() == username) {
                cout << "Username already exists!" << endl;
                return;
            }
        }
        
        string password = getValidatedString("Password: ", 6, 20);
        string name = getValidatedString("Full Name: ", 2, 50);
        string id = generateVoterId();
        
        string cnic = getValidatedCNIC("CNIC");
        
        // Check if CNIC already exists
        if (cnicExists(cnic)) {
            cout << "CNIC already registered in the system!" << endl;
            return;
        }
        
        voters.addData(Voter(username, password, name, id, cnic));
        cout << "Voter registered successfully!" << endl;
    }
    
    void viewAllVoters() {
        cout << "\n=== ALL VOTERS ===" << endl;
        if (voters.getSize() == 0) {
            cout << "No voters registered." << endl;
            return;
        }
        
        cout << left << setw(15) << "Username" << setw(25) << "Name" << setw(25) << "CNIC" 
             << setw(12) << "Voter ID" << setw(10) << "Voted" << endl;
        cout << string(85, '-') << endl;
        
        for (const auto& voter : voters.getAllData()) {
            cout << left << setw(15) << voter.getUsername()
                 << setw(25) << voter.getName()
                 << setw(25) << voter.getCnic()
                 << setw(12) << voter.getId()
                 << setw(10) << (voter.getHasVoted() ? "Yes" : "No") << endl;
        }
    }
    
    /*
     * ===================================================================
     * VOTING METHODS
     * ===================================================================
     */
    
    void castVote(Voter* voter) {
        if (!timer.isElectionActive()) {
            cout << "Election is not currently active!" << endl;
            cout << "Status: " << timer.getStatus() << endl;
            return;
        }
        
        if (voter->getHasVoted()) {
            cout << "You have already voted!" << endl;
            cout << "You voted for candidate: " << voter->getVotedFor() << endl;
            return;
        }
        
        if (candidates.getSize() == 0) {
            cout << "No candidates available for voting." << endl;
            return;
        }
        
        cout << "\n=== CAST VOTE ===" << endl;
        cout << "Available Candidates:" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Party/Type" << endl;
        cout << string(45, '-') << endl;
        
        for (const auto& candidate : candidates.getAllData()) {
            string partyInfo = candidate.getIsIndependent() ? "Independent" : candidate.getPartyId();
            cout << left << setw(10) << candidate.getId()
                 << setw(20) << candidate.getName()
                 << setw(15) << partyInfo << endl;
        }
        
        string candidateId = getValidatedString("Enter Candidate ID to vote for: ");
        
        // Find and validate candidate
        bool candidateFound = false;
        for (auto& candidate : candidates.getAllData()) {
            if (candidate.getId() == candidateId) {
                candidateFound = true;
                
                // Confirm vote
                cout << "You are about to vote for: " << candidate.getName() << endl;
                cout << "Are you sure? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore();
                
                if (confirm == 'y' || confirm == 'Y') {
                    // Cast vote
                    candidate.addVote();
                    voter->castVote(candidateId);
                    
                    // Update party votes if candidate belongs to a party
                    if (!candidate.getIsIndependent()) {
                        for (auto& party : parties.getAllData()) {
                            if (party.getId() == candidate.getPartyId()) {
                                party.setTotalVotes(party.getTotalVotes() + 1);
                                break;
                            }
                        }
                    }
                    
                    cout << "Vote cast successfully!" << endl;
                } else {
                    cout << "Vote cancelled." << endl;
                }
                break;
            }
        }
        
        if (!candidateFound) {
            cout << "Invalid candidate ID!" << endl;
        }
    }
    
    /*
     * ===================================================================
     * ELECTION TIMING METHODS
     * ===================================================================
     */
    
    void setElectionTiming() {
        cout << "\n=== SET ELECTION TIMING ===" << endl;
        
        time_t currentTime = time(0);
        cout << "Current time: " << ctime(&currentTime);
        
        time_t startTime = getValidatedDateTime("Enter election start time");
        time_t endTime = getValidatedDateTime("Enter election end time");
        
        if (endTime <= startTime) {
            cout << "End time must be after start time!" << endl;
            return;
        }
        
        timer.setTiming(startTime, endTime);
        cout << "Election timing set successfully!" << endl;
        
        cout << "Election Start: " << ctime(&startTime);
        cout << "Election End: " << ctime(&endTime);
    }
    
    void viewElectionStatus() {
        cout << "\n=== ELECTION STATUS ===" << endl;
        cout << "Status: " << timer.getStatus() << endl;
        
        if (timer.isTimingSet()) {
            time_t start = timer.getStartTime();
            time_t end = timer.getEndTime();
            cout << "Start Time: " << ctime(&start);
            cout << "End Time: " << ctime(&end);
        }
        
        cout << "Total Registered Voters: " << voters.getSize() << endl;
        cout << "Total Candidates: " << candidates.getSize() << endl;
        cout << "Total Parties: " << parties.getSize() << endl;
        
        // Count votes cast
        int votesCast = 0;
        for (const auto& voter : voters.getAllData()) {
            if (voter.getHasVoted()) votesCast++;
        }
        cout << "Votes Cast: " << votesCast << endl;
        
        if (voters.getSize() > 0) {
            double turnout = (double)votesCast / voters.getSize() * 100;
            cout << "Voter Turnout: " << fixed << setprecision(2) << turnout << "%" << endl;
        }
    }
    
    /*
     * ===================================================================
     * ELECTION REPORT GENERATION
     * ===================================================================
     */
    
    void generateElectionReport() {
        cout << "\n=== ELECTION REPORT ===" << endl;
        
        if (!timer.hasElectionEnded()) {
        cout << "Election is still ongoing. Report will be available after election ends." << endl;
        return;
        }
        
        // Count total votes
        int totalVotes = 0;
        for (const auto& candidate : candidates.getAllData()) {
            totalVotes += candidate.getVotes();
        }
        
        if (totalVotes == 0) {
            cout << "No votes have been cast yet." << endl;
            return;
        }
        
        // Sort candidates by votes (using STL algorithm)
        vector<Candidate> sortedCandidates = candidates.getAllData();
        sort(sortedCandidates.begin(), sortedCandidates.end(),
             [](const Candidate& a, const Candidate& b) {
                 return a.getVotes() > b.getVotes();
             });
        
        cout << "\n=== CANDIDATE RESULTS (Sorted by Votes) ===" << endl;
        cout << left << setw(5) << "Rank" << setw(10) << "ID" << setw(20) << "Name" 
             << setw(15) << "Party/Type" << setw(8) << "Votes" << setw(12) << "Percentage" << endl;
        cout << string(70, '-') << endl;
        
        for (size_t i = 0; i < sortedCandidates.size(); i++) {
            const auto& candidate = sortedCandidates[i];
            string partyInfo = candidate.getIsIndependent() ? "Independent" : candidate.getPartyId();
            double percentage = (double)candidate.getVotes() / totalVotes * 100;
            
            cout << left << setw(5) << (i + 1)
                 << setw(10) << candidate.getId()
                 << setw(20) << candidate.getName()
                 << setw(15) << partyInfo
                 << setw(8) << candidate.getVotes()
                 << setw(12) << fixed << setprecision(1) << percentage << "%" << endl;
        }
        
        // Party-wise results
        if (parties.getSize() > 0) {
            cout << "\n=== PARTY-WISE RESULTS ===" << endl;
            
            // Sort parties by votes
            vector<Party> sortedParties = parties.getAllData();
            sort(sortedParties.begin(), sortedParties.end(),
                 [](const Party& a, const Party& b) {
                     return a.getTotalVotes() > b.getTotalVotes();
                 });
            
            cout << left << setw(5) << "Rank" << setw(10) << "ID" << setw(25) << "Name" 
                 << setw(8) << "Votes" << setw(12) << "Percentage" << endl;
            cout << string(60, '-') << endl;
            
            for (size_t i = 0; i < sortedParties.size(); i++) {
                const auto& party = sortedParties[i];
                double percentage = (double)party.getTotalVotes() / totalVotes * 100;
                
                cout << left << setw(5) << (i + 1)
                     << setw(10) << party.getId()
                     << setw(25) << party.getName()
                     << setw(8) << party.getTotalVotes()
                     << setw(12) << fixed << setprecision(1) << percentage << "%" << endl;
            }
        }
        
        // Winner announcement - handle ties
        if (!sortedCandidates.empty()) {
            const auto& topCandidate = sortedCandidates[0];
            
            // Check for ties
            vector<Candidate> winners;
            for (const auto& candidate : sortedCandidates) {
                if (candidate.getVotes() == topCandidate.getVotes()) {
                    winners.push_back(candidate);
                } else {
                    break; // Since sorted, no more ties
                }
            }
            
            cout << "\n=== ELECTION RESULT ===" << endl;
            if (winners.size() == 1) {
                cout << "Winner: " << winners[0].getName() << " (ID: " << winners[0].getId() << ")" << endl;
                cout << "Votes: " << winners[0].getVotes() << " (" 
                    << fixed << setprecision(1) << (double)winners[0].getVotes() / totalVotes * 100 << "%)" << endl;
                
                if (!winners[0].getIsIndependent()) {
                    cout << "Party: " << winners[0].getPartyId() << endl;
                } else {
                    cout << "Independent Candidate" << endl;
                }
            } else {
                cout << "TIE RESULT - " << winners.size() << " candidates tied with " << topCandidate.getVotes() << " votes each:" << endl;
                for (const auto& winner : winners) {
                    cout << "- " << winner.getName() << " (ID: " << winner.getId() << ")";
                    if (!winner.getIsIndependent()) {
                        cout << " (Party: " << winner.getPartyId() << ")";
                    } else {
                        cout << " (Independent)";
                    }
                    cout << endl;
                }
                cout << "A runoff election may be required." << endl;
            }
        }
        
        // Save report to file
        saveReportToFile(sortedCandidates, totalVotes);
    }
    
    void saveReportToFile(const vector<Candidate>& sortedCandidates, int totalVotes) {
        ofstream reportFile("election_report.txt");
        if (reportFile.is_open()) {
            time_t currentTime = time(0);
            reportFile << "ELECTION REPORT - Generated on: " << ctime(&currentTime) << endl;
            reportFile << string(50, '=') << endl;
            
            reportFile << "Total Votes Cast: " << totalVotes << endl;
            reportFile << "Total Candidates: " << candidates.getSize() << endl;
            reportFile << "Total Parties: " << parties.getSize() << endl;
            
            reportFile << "\nCANDIDATE RESULTS:" << endl;
            for (size_t i = 0; i < sortedCandidates.size(); i++) {
                const auto& candidate = sortedCandidates[i];
                double percentage = (double)candidate.getVotes() / totalVotes * 100;
                reportFile << (i + 1) << ". " << candidate.getName() 
                          << " - " << candidate.getVotes() << " votes (" 
                          << fixed << setprecision(1) << percentage << "%)" << endl;
            }
            
            if (!sortedCandidates.empty()) {
                const auto& winner = sortedCandidates[0];
                reportFile << "\nWINNER: " << winner.getName() << endl;
            }
            
            reportFile.close();
            cout << "\nReport saved to 'election_report.txt'" << endl;
        }
    }
    
    /*
     * ===================================================================
     * MAIN SYSTEM CONTROL METHODS
     * ===================================================================
     */
    
    void runSystem() {
        cout << "\n=== ELECTRONIC VOTING SYSTEM ===" << endl;
        cout << "Welcome to the Digital Democracy Platform" << endl;
    
        while (true) {
        cout << "\n=== DIGITAL VOTING SYSTEM ===" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Voter" << endl;
        cout << "3. Check Election Results (Public)" << endl;
        cout << "4. Exit" << endl;
    
        int choice = getValidatedInt("Enter your choice: ", 1, 4);
    
        switch (choice) {
            case 1:
            case 2:
                currentUser = login();
                if (currentUser != nullptr) {
                    handleUserSession();
                }
                break;
            case 3:
                generateElectionReport();
                break;
            case 4:
                cout << "Thank you for using the Digital Voting System!" << endl;
                return;
        }
    }
}
    
    void handleUserSession() {
        while (currentUser != nullptr) {
            currentUser->displayMenu();
            
            // Check if admin or voter
            Admin* adminPtr = dynamic_cast<Admin*>(currentUser);
            Voter* voterPtr = dynamic_cast<Voter*>(currentUser);
            
            if (adminPtr) {
                handleAdminMenu();
            } else if (voterPtr) {
                handleVoterMenu(voterPtr);
            }
        }
    }
    
    void handleAdminMenu() {
        int choice = getValidatedInt("Enter your choice: ", 1, 9);
        
        switch (choice) {
            case 1: manageParties(); break;
            case 2: addCandidate(); break;
            case 3: viewAllCandidates(); break;
            case 4: registerVoter(); break;
            case 5: viewAllVoters(); break;
            case 6: setElectionTiming(); break;
            case 7: viewElectionStatus(); break;
            case 8: generateElectionReport(); break;
            case 9: 
                cout << "Logging out..." << endl;
                currentUser = nullptr;
                break;
        }
    }
    
    void handleVoterMenu(Voter* voter) {
        int choice = getValidatedInt("Enter your choice: ", 1, 5);
        
        switch (choice) {
            case 1: viewAllCandidatesForVoter(); break;
            case 2: viewAllParties(); break;
            case 3: castVote(voter); break;
            case 4: 
                cout << "\n=== VOTING STATUS ===" << endl;
                cout << "Has Voted: " << (voter->getHasVoted() ? "Yes" : "No") << endl;
                if (voter->getHasVoted()) {
                    cout << "Voted For: " << voter->getVotedFor() << endl;
                }
                break;
            case 5:
                cout << "Logging out..." << endl;
                currentUser = nullptr;
                break;
        }
    }
};

/*
 * ===================================================================
 * MAIN FUNCTION - ENTRY POINT OF THE PROGRAM
 * ===================================================================
 */
int main() {
    // try {
        VotingSystem system;
        system.runSystem();
    // } catch (const exception& e) {
    //     cout << "System Error: " << e.what() << endl;
    //     return 1;
    // }
    
    return 0;
}