
#include <iostream>
using namespace std;
class SecretVault {
    int* ptr;
public:

    SecretVault() {
        ptr = nullptr;
    }
    void setSecret(int val) {
        delete ptr;//deleting the prevoius memory that it pointed to 
        ptr = new int(val);
    }
    void clearVault() {
        if (ptr != nullptr) {
            delete ptr;
            ptr = nullptr;
        }
        else {
            cout << "the vault is already empty \n";
             }
    }
    ~SecretVault() {
        delete ptr;
        ptr = nullptr;
    }

    void show() {
        if (ptr!=nullptr) {
            cout << "the vale of the secret is " << *ptr<<endl;
        }
        else {
            cout<<"The vault is empty\n";
        }
    }
    SecretVault(const SecretVault& vault) {
        if (vault.ptr != nullptr) {
            int x = *(vault.ptr);
            ptr = new int(x);
        }
        else {
            ptr = nullptr;
        }
    }
    

};
int main() {
    SecretVault myVault;

    myVault.show();            // Should say "Vault is empty"
    myVault.setSecret(1234);
    myVault.show();            // Should show 1234

    myVault.setSecret(9999);   // Should delete 1234 and allocate 9999
    myVault.show();

    myVault.clearVault();
    myVault.show();            // Should say "Vault is empty"

    return 0;
}



