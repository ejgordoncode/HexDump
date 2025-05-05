#include <stdio.h>
#include <string.h>
#include <fstream> 
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <bitset>


using namespace std;

int main(int argcount, char **argv) {

    // EDGE CASE: no filename or flag //
    if ((argcount) < 2) {
        cerr << "ERROR: no filename";
        return 1;
    }

    int bytePace; // the amount of bytes read per iteration
    bytePace = 16; // hex mode is 16 bytes
    enum {hex, bin};
    int format = hex;
    const char *fileToRead = nullptr; 
    size_t currentAddress = 0; 
    int bytesPerGroup = 2;





    // Determine if it's binary or hexadecimal format //
    for (int i = 1; i < argcount; ++i) {
        /* "-b" signifies that the output should be in binary format. 
        * If arg1 is "-b" then the output will be in binary form
        * and output 6 groups of 1 byte each at a time. 
        * Otherwise, the output will be in hexadecimal format 
        * and output 8 groups of 2 bytes each at a time.
        */ 
        if(strcmp (argv[i], "-b") == 0){
            // EDGE CASE: no filename after "-b"
            if (i+1 < argcount) {
                fileToRead = argv[i+1];
            }
            else {
                cerr << "ERROR: no filename";
                return 1;
            }

            bytePace = 6;
            bytesPerGroup = 1;
            format = bin; 

            
        }
        else {
            fileToRead = argv[i];
            
        }

    }

    // Output depending on binary or hexadecimal requirements //
    if (format == bin){
        ifstream file(fileToRead, ios::binary); // reading in binary format
        char buffer[bytePace]; // buffer of size 6
        // Reading 6 bytes at a time or fewer:
        while(file.read(buffer, bytePace) || file.gcount() > 0){
            cout << setw(6) << setfill('0') << std::hex << (currentAddress & 0xFFFFFF) << ": ";

            // Print bin bytes //
            int bytesToRead = file.gcount();
            for (size_t i = 0; i < static_cast<size_t>(bytesToRead); i++) {
                // Hadle space case //
                if (i > 0){
                    cout << " ";
                }
                
                // Print one byte //
                cout << bitset<8> (static_cast<unsigned char>(buffer[i])); // print binary digits, converted from hex
            
            }
            cout << "  "; // padding before ASCII

            // Print ASCII //
            for (size_t i = 0; i < static_cast<size_t>(bytesToRead); i++) {
                // CASE: Is printable char //
                if (isprint(buffer[i])){
                    cout << buffer[i];
                }
                // CASE: Is NOT printable char //
                else{
                    cout << ".";
                }
            }

            cout << endl;

            currentAddress += bytePace; // increase currentAddress by 6 bytes
            
        }
    }
    else{
        ifstream file(fileToRead, ios::binary); // reading in binary format
        char buffer[bytePace]; // buffer of size 16

        // Reading 16 bytes at a time or fewer:
        while(file.read(buffer, bytePace) || file.gcount() > 0){

            // Print Address //
            cout << setw(6) << setfill('0') << std::hex << currentAddress << ": ";

            // Print hex bytes //
            int bytesToRead = file.gcount();
            for (size_t i = 0; i < (bytesToRead); i++) {
                cout << setw(2) << setfill('0') << std::hex << (static_cast<unsigned int>(static_cast<unsigned char>(buffer[i])));
                // Hadle space case //
                if ((i + 1) % 2 == 0) {  // Space every 2 bytes
                    cout << " ";
                }
            }
            cout << "  "; // padding before ASCII

            // Print ASCII //
            for (size_t i = 0; i < static_cast<size_t>(bytesToRead); i++) {
                // CASE: Is printable char //
                if (isprint(buffer[i])){
                    cout << buffer[i];
                }
                // CASE: Is NOT printable char //
                else{
                    cout << ".";
                }
            }

            cout << endl;
            currentAddress += bytePace; // increase currentAddress by 16 bytes
            
        }
    }


    return 0;
}

