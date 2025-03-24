# Password Manager

A simple and secure password manager built in C++ that allows users to store, retrieve, generate, and manage passwords with encryption.

## Features

- **Secure Storage:** Encrypts and stores passwords safely.
- **Password Strength Checker:** Evaluates the security level of passwords.
- **Random Password Generator:** Generates strong passwords.
- **Master Password Authentication:** Protects access to stored credentials.
- **Backup Functionality:** Allows users to create a backup of their passwords.
- **Search & Delete:** Users can search and remove stored credentials.

## Installation & Compilation

### Prerequisites
- Dev-C++ (or any C++ compiler like MinGW/GCC)
- Windows operating system (or modify for Linux/macOS compatibility)

### Steps to Compile & Run

1. Open Dev-C++ and create a new project.
2. Add `PasswordManage.cpp` to the project.
3. Ensure `conio.h` is available for Windows compatibility.
4. Compile the program.
5. Run the executable.

## Usage

1. **Launch the Application**
   - Run the program and enter the master password.
   
2. **Main Menu Options:**
   - `1. Add Password` - Stores credentials securely.
   - `2. View All Passwords` - Displays saved passwords.
   - `3. Search Password` - Finds stored credentials.
   - `4. Delete Password` - Removes an entry from storage.
   - `5. Generate Strong Password` - Creates a secure password.
   - `6. Backup Passwords` - Saves data in a backup file.
   - `7. Exit` - Saves all changes and exits the program.

## Security Considerations

- The program uses XOR-based encryption. Consider replacing it with a stronger encryption library like AES (Crypto++ or OpenSSL) for better security.
- The master password is stored in plaintext (`password`). Modify it for enhanced security.

## Future Improvements

- **GUI Integration:** Use Qt for a graphical interface.
- **Stronger Encryption:** Implement AES-256 encryption.
- **Cloud Sync:** Store encrypted data securely in the cloud.

## License

This project is open-source and available for educational purposes. Modify and improve as needed.


#CODE WITH ARPIT
