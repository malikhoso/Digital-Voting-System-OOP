# Digital Voting System (C++ OOP)

A secure, console-based Electronic Voting System (EVS) tailored for the Pakistani electoral context. This project demonstrates advanced **Object-Oriented Programming (OOP)** concepts and robust data management through file persistence.

## 🏛️ Core Features

* **Dual-User Portal:** Separate interfaces and permissions for **Admins** and **Voters**.
* **Voter Management:** Secure voter registration with CNIC validation and duplicate entry prevention.
* **Candidate & Party System:** Supports both Independent and Party-affiliated candidates with manifesto tracking.
* **Election Timer:** Automated controls to ensure voting is only permitted within specific start and end times.
* **Live Analytics:** Real-time voter turnout calculation and sorted election reports (winner announcement/tie-handling).
* **Data Security:** Passwords are hidden during entry (`*` characters), and account data is persisted via specialized file handlers.

## 💻 OOP Concepts Implemented

This project serves as a comprehensive demonstration of C++ Object-Oriented principles:

* **Abstraction:** Used Abstract Base Classes (`User`) with pure virtual functions to define a standard interface for all system users.
* **Inheritance:** Implemented specialized classes (`Voter`, `Admin`) that inherit from the base `User` class.
* **Polymorphism:** Utilized `virtual` functions and dynamic casting to handle different user types through a single base-class pointer.
* **Encapsulation:** Private data members are protected and accessed only through controlled public Getter and Setter methods.
* **Templates (Generic Programming):** Developed a generic `DataManager<T>` and `FileHandler<T>` class to handle various data types (Parties, Candidates, Voters) using the same logic.
* **Composition & Aggregation:** Modeled complex relationships where a `VotingSystem` *has-a* `DataManager`, and a `Candidate` *belongs-to* a `Party`.

## 📂 Project Structure

* `DigitalVoting.cpp` - The primary source file containing the class definitions and system logic.
* `candidates.txt` / `voters.txt` / `parties.txt` - Flat-file databases for persistent storage.
* `election_timing.txt` - Stores the synchronized timing for the election window.
* `election_report.txt` - Auto-generated final results summary.

## 🚀 How to Run

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/malikhoso/Digital-Voting-System-OOP.git](https://github.com/malikhoso/Digital-Voting-System-OOP.git)
    ```
2.  **Compile:**
    ```bash
    g++ DigitalVoting.cpp -o VotingSystem
    ```
3.  **Execute:**
    ```bash
    ./VotingSystem
    ```

---
**Default Admin Credentials:** **Username:** `admin` | **Password:** `admin123`
