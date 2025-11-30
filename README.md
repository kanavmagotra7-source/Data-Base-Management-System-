# Database Management System in C

A lightweight DBMS built in C featuring file-based storage, CRUD operations, simple indexing, and a command-line query interface. Designed as a learning project to demonstrate how database internals work.

---

## 📌 Features

* File-based data storage
* Create, Read, Update, Delete (CRUD) operations
* Support for multiple tables
* Basic indexing for faster lookups
* Simple query parser
* Error handling and input validation
* Modular and well-documented C code

---

## 🛠 Tech Stack

* **Language:** C
* **Compiler:** GCC / Clang
* **Storage:** Flat Files
* **Platform:** Windows / Linux

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/dbms-in-c.git
cd dbms-in-c
```

### 2. Compile the Program

```bash
gcc main.c db.c utils.c -o dbms
```

### 3. Run the DBMS

```bash
./dbms
```

---

## 📂 Project Structure

```
├── main.c          # Entry point and CLI handler
├── db.c            # Core database functions
├── db.h            # DB function declarations
├── utils.c         # Helper functions
├── utils.h         # Utility declarations
├── data/           # Stored table files
└── README.md
```

---

## 📘 How It Works

* Tables are stored as structured flat files
* Each table contains records with fixed formats
* Indexing improves lookup speed for selected fields
* User commands are parsed into operations executed on the data files

---

## 🤝 Contributing

Pull requests are welcome! Feel free to improve performance, add features, or fix bugs.

---

## 📄 License

This project is licensed under the MIT License.
