
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <numeric>
#include <climits>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cstdlib>
using namespace std;

// hàm kiểm tra, ràng buộc, chuẩn hóa
bool checkUsername(string username);
bool checkPassword(string password);
bool kiTuDacBiet(char c) {
	if (int(c) >= 32 && int(c) <= 47 || int(c) >= 58 && int(c) <= 64 || int(c) >= 91 && int(c) <= 96 || int(c) >= 123) {
			return true;
	}
	return false;
}
bool checkEmail(string email);
bool checkPhoneNumber(string phoneNumber);
void chuanHoaTen(string& ten);
bool checkContactID(string contactID);

//Set dùng để check trùng lập và check xem đã tồn tại username, phone number,... của User và Contact chưa.
set<string> usernameCheck;
set<string> phoneNumberCheck;
set<string> emailCheck;
set<string> userIDCheck;


//Cấu trúc dữ liệu map để quản lí tài khoản User (không phải tài khoản contact);
map<string, string> userAccountData;



class User {	
private:
	string userID, username, email, password;
public:
	User() {};
	User(string username, string email, string password) {
		this->username = username;
		this->email = email;
		this->password = password;
	}
	friend istream& operator >> (istream& in, User& x) {

		//Tạo userID ngẫu nhiên từ 10000 đến 99999 và kiểm tra trùng lặp
		srand(time(NULL));
		int soID = rand() % 90000 + 10000; 
		string ssoID = to_string(soID);
		while (userIDCheck.count(ssoID)) {
			soID = rand() % 90000 + 10000;
		}
		x.userID = soID;

		//Nhập và kiểm tra username
		cout << "Ten dang nhap: ";
		getline(in, x.username);
		while (!checkUsername(x.username) || usernameCheck.count(x.username)) {
			cout << "Ten dang nhap khong hop le. Vui long nhap lai: ";
			getline(in, x.username);
		}
		usernameCheck.insert(x.username);

		//Nhập và kiểm tra password
		
		cout << "Mat khau : ";
		getline(in, x.password);
		while (!checkPassword(x.password)) {
			cout << "Mat khau khong hop le. Vui long nhap lai: ";
			getline(in, x.password);
		}

		//Nhập và kiểm tra email
		cout << "Email : ";
		getline(in, x.email);
		while (!checkEmail(x.email)) {
			cout << "Email khong hop le. Vui long nhap lai: ";
			getline(in, x.email);
		}

		//Thêm email vào set để kiểm tra trùng lặp
		emailCheck.insert(x.email);
		userAccountData.insert({ x.username,x.password });
		return in;
	}
	void showProfile() {
		cout << "UserID : " << userID << endl;
		cout << "Username : " << username << endl;
		cout << "Email : " << email << endl;
		cout << "Password : ";
		string tmpPassword = password;
		for (int i = 0; i < tmpPassword.size(); i++) {
			tmpPassword[i] = '*';
			cout << tmpPassword[i];
		}
		cout << endl;
		cout << "Nhan 1 de hien Password : ";
		string ch; getline(cin, ch);
		while (ch != "1") {
			cout << "Vui long nhap lai : ";
			getline(cin, ch);
		}
		if (ch == "1") {
			cout << "Password : " << password << endl;
		}
		cout << endl;
	}
	string getUserID() {
		return userID;
	}
	string getUsername() {
		return username;
	}
	string getEmail() {
		return email;
	}
	string getPassword() {
		return password;
	}
	void setUserID(string userID) {
		this->userID = userID;
	}
	void setUsername(string username) {
		this->username = username;
	}
	void setEmail(string email) {
		this->email = email;
	}
	void setPassword(string password) {
		this->password = password;
	}
	void login(string username, string password) {
		if (userAccountData.find(username) != userAccountData.end() && userAccountData[username] == password) {
			cout << "Dang nhap thanh cong !" << endl;
		}
		else cout << "Dang nhap that bai !" << endl;
	}
	void logout() {
		cout << "Dang xuat thanh cong!" << endl;
	}
};


vector<User> lockAccount;
vector<User> unlockAccount;
class Admin : public User {
public: 
	Admin() {};
	Admin(string userID, string username, string email, string password) : User(username, email, password) {};
	void UnlockAccount() {
		if (lockAccount.size() == 0) {
			cout << "Khong co tai khoan bi khoa!" << endl;
			return;
		}
		cout << "Nhap ma ID tai khoan can mo khoa : ";
		string id;
		getline(cin, id);
		while (!userIDCheck.count(id)) {
			cout << "Khong tim thay ID, vui long nhap lai : ";
			getline(cin, id);
		}
		for (int i = 0; i < lockAccount.size(); i++) {
			if (lockAccount[i].getUserID() == id) {
				unlockAccount.push_back(lockAccount[i]);
				lockAccount.erase(lockAccount.begin() + i);
				cout << "Mo khoa tai khoan thanh cong!" << endl;
				return;
			}
		}
	}
	void LockAccount() {
		if(unlockAccount.size() == 0) {
			cout << "Khong co tai khoan de khoa!" << endl;
			return;
		}
		cout << "Nhap ma ID tai khoan can khoa : ";
		string id;
		getline(cin, id);
		while (!userIDCheck.count(id)) {
			cout << "Khong tim thay ID, vui long nhap lai : ";
			getline(cin, id);
		}
		for (int i = 0; i < unlockAccount.size(); i++) {
			if (unlockAccount[i].getUserID() == id) {
				lockAccount.push_back(unlockAccount[i]);
				unlockAccount.erase(unlockAccount.begin() + i);
				cout << "Khoa tai khoan thanh cong!" << endl;
				return;
			}
		}
	}
};


class Contact {
private:
	string contactID, fullName, phoneNumber, email, address, company, relatives;
public :
	Contact() {};
	Contact(string contactID, string fullName, string phoneNumber, string email, string address, string company,string relatives) {
		this->contactID = contactID;
		this->fullName = fullName;
		this->phoneNumber = phoneNumber;
		this->email = email;
		this->address = address;
		this->company = company;
		this->relatives = relatives;
	}
	void updateInfo(string contactID, string fullName, string phoneNumber, string email, string address, string company, string relatives) {
		this->contactID = contactID;
		this->fullName = fullName;
		this->phoneNumber = phoneNumber;
		this->email = email;
		this->address = address;
		this->company = company;
		this->relatives = relatives;
	}
	friend istream& operator >> (istream& in, Contact& x) {
		//Nhập và kiểm tra contactID
		cout << "Contact ID: ";
		getline(in, x.contactID);
		while (!checkContactID(x.contactID)) {
			cout << "ContactID khong hop le. Vui long nhap lai: ";
			getline(in, x.contactID);
		}
		userIDCheck.insert(x.contactID);

		//Full Name
		//Nhập và kiểm tra fullName
		cout << "Ten day du : ";
		getline(in, x.fullName);
		while (!checkUsername(x.fullName)) {
			cout << "Ten khong hop le. Vui long nhap lai: ";
			getline(in, x.fullName);
		}
		chuanHoaTen(x.fullName);

		//Nhập và kiểm tra phoneNumber
		cout << "Phone Number : ";
		getline(in, x.phoneNumber);
		while (!checkPhoneNumber(x.phoneNumber) || phoneNumberCheck.count(x.phoneNumber)) {
			cout << "So dien thoai khong hop le : ";
			getline(in, x.phoneNumber);
		}
		phoneNumberCheck.insert(x.phoneNumber);

		//Nhập và kiểm tra email
		cout << "Email : ";
		getline(in, x.email);
		while (!checkEmail(x.email)) {
			cout << "Email khong hop le. Vui long nhap lai: ";
			getline(in, x.email);
		}
		emailCheck.insert(x.email);

		cout << "Address : ";
		getline(in, x.address);
		cout << "Company : ";
		getline(in, x.company);

		//Nhập quan hệ
		cout << "Relative : ";
		getline(in, x.relatives);

		return in;
	}
	void displayContact() {
		cout << "ContactID : " << contactID << endl;
		cout << "Name : " << fullName << endl;
		cout << "Phone Number : " << phoneNumber << endl;
		cout << "Email : " << email << endl;
		cout << "Address : " << address << endl;
		cout << "Company : " << company << endl;
	}
	string getFullName() {
		return fullName;
	}
	string getPhoneNumber() {
		return phoneNumber;
	}
	string getEmail() {
		return email;
	}
	string getContactID() {
		return contactID;
	}
	char getContactFirstLetter() {
		string username = getFullName();
		stringstream ss(username);
		string tmp;
		vector<string> ten;
		while (ss >> tmp) {
			ten.push_back(tmp);
		}
		return ten[ten.size() - 1][0];
	}
	string getContactFirstName() {
		string username = getFullName();
		stringstream ss(username);
		string tmp;
		vector<string> ten;
		while (ss >> tmp) {
			ten.push_back(tmp);
		}
		return ten[ten.size() - 1];
	}
	void setFullName(string fullName) {
		this->fullName = fullName;
	}
	void setPhoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}
	void setEmail(string email) {
		this->email = email;
	}
	void setAddress(string address) {
		this->address = address;
	}
	void setCompany(string company) {
		this->company = company;
	}
	void setRelatives(string relatives) {
		this->relatives = relatives;
	}
};


//////////Quan li Group//////////
struct Group {
	string id;
	string name;
	vector<Contact> member;
	friend ostream& operator << (ostream& out, Group x) {
		out << "Group ID : " << x.id << endl;
		out << "Group Name : " << x.name << endl;
		out << "Group Member : " << x.member.size();
	}
};
vector<Group> groupList;
set<string> groupIDCheck;
set<string> groupNameCheck;
/////////////////////////////////


class phoneBook{
private:
	string bookID;
	vector<Contact> contactList;
public:
	phoneBook(string bookID) {
		this->bookID = bookID;
	}
	/////PhoneBook Features
	void viewContactList() {
		for (int i = 0; i < contactList.size(); i++) {
			cout << "========================================" << endl;
			contactList[i].displayContact();
			cout << "========================================" << endl;
			cout << endl;
		}
	}
	void getContactInformation() {
		cout << "Chon phuong thuc tra : ";
		cout << "1. So dien thoai : ";
		cout << "2. Email : ";
		string ch;
		getline(cin, ch);
		while (ch != "1" && ch != "2") {
			cout << "Khong hop le, vui long nhap lai : ";
			getline(cin, ch);
		}
		if (ch == "1") {
			cout << "Nhap so dien thoai nguoi lien he : ";
			string soDienThoai;
			getline(cin, soDienThoai);
			while (!checkPhoneNumber(soDienThoai) || !phoneNumberCheck.count(soDienThoai)) {
				cout << "So dien thoai khong hop le, vui long nhap lai : ";
				getline(cin, soDienThoai);
			}
			for (int i = 0; i < contactList.size(); i++) {
				if (contactList[i].getPhoneNumber() == soDienThoai) {
					cout << "========================================" << endl;
					contactList[i].displayContact();
					cout << "========================================" << endl;
					cout << endl;
				}
			}
		}
		else if(ch == "2") {
			cout << "Nhap email nguoi lien he : ";
			string emailNLH;
			getline(cin, emailNLH);
			while (!checkEmail(emailNLH) || !emailCheck.count(emailNLH)) {
				cout << "Email khong hop le, vui long nhap lai : ";
				getline(cin, emailNLH);
			}
			for (int i = 0; i < contactList.size(); i++) {
				if (contactList[i].getEmail() == emailNLH) {
					cout << "========================================" << endl;
					contactList[i].displayContact();
					cout << "========================================" << endl;
					cout << endl;
				}
			}
		}
	}
	static bool cmp(Contact a, Contact b) {
		if (a.getContactFirstLetter() == b.getContactFirstLetter()) {
			return a.getFullName().length() < b.getFullName().length();
		}
		return a.getContactFirstLetter() < b.getContactFirstLetter();
	}
	static bool checkName(string fullName, string tenNhap) {
		vector<string> fullname;
		vector<string> tennhap;
		stringstream ss1(fullName);
		stringstream ss2(tenNhap);
		string tmp1, tmp2;
		while (ss1 >> tmp1) {
			fullname.push_back(tmp1);
		}
		while (ss2 >> tmp2) {
			tennhap.push_back(tmp2);
		}
		for (string x : tennhap) {
			if (find(fullname.begin(), fullname.end(), x) == fullname.end()) {
				return false;
			}
		}
		return true;
	}
	void sortContactByName() {
		sort(contactList.begin(), contactList.end(), cmp);
		viewContactList();
	}
	void addContact() {
		Contact x;
		cin >> x;
		contactList.push_back(x);
	}
	void editContact() {
		cout << "Nhap ten contact ban muon chinh sua : ";
		string ten;
		getline(cin, ten);
		while (!checkUsername(ten)) {
			cout << "Ten khong hop le, vui long nhap lai :";
			getline(cin, ten);
		}
		chuanHoaTen(ten);
		cout << "Danh sach nguoi co ten " << ten << endl;
		for (int i = 0; i < contactList.size(); i++) {
			if (checkName(contactList[i].getFullName(), ten)) {
				contactList[i].displayContact();
			}
		}
		cout << "Nhap id nguoi ban muon chinh sua : ";
		string id;
		getline(cin, id);
		while (!checkContactID(id) && userIDCheck.find(id) == userIDCheck.end()) {
			cout << "ID khong hop le, vui long nhap lai :";
			getline(cin, id);
		}
		for (int i = 0; i < contactList.size(); i++) {
			if (contactList[i].getContactID() == id) {
				contactList[i].displayContact();
				while (true) {
					cout << "Chon thong tin ban muon chinh sua : " << endl;
					cout << "1. Full Name" << endl;
					cout << "2. So Dien Thoai" << endl;
					cout << "3. Email" << endl;
					cout << "4. Address" << endl;
					cout << "5. Company" << endl;
					cout << "6. Relative" << endl;
					cout << "0. Thoat chinh chua" << endl;
					string ch;
					getline(cin, ch);
					while (ch != "1" && ch != "2" && ch != "3" && ch != "4" && ch != "5" && ch != "6" && ch != "0") {
						cout << "Lua chon khong hop le, vui long nhap lai : ";
						getline(cin, ch);
					}
					if (ch == "1") {
						cout << "Nhap ten thay doi : ";
						string ten;
						getline(cin, ten);
						while (!checkUsername(ten)) {
							cout << "Ten khong hop le, vui long nhap lai : ";
							getline(cin, ten);
						}
						contactList[i].setFullName(ten);
						cout << endl;
					}
					else if (ch == "2") {
						cout << "Nhap so dien thoai thay doi : ";
						string sdt;
						getline(cin, sdt);
						while (!checkPhoneNumber(sdt)) {
							cout << "So dien thoai khong hop le, vui long nhap lai : ";
							getline(cin, sdt);
						}
						contactList[i].setPhoneNumber(sdt);
						cout << endl;
					}
					else if (ch == "3") {
						cout << "Nhap email thay doi : ";
						string email;
						getline(cin, email);
						while (!checkEmail(email)) {
							cout << "Email khong hop le, vui long nhap lai : ";
							getline(cin, email);
						}
						contactList[i].setEmail(email);
						cout << endl;
					}
					else if (ch == "4") {
						cout << "Nhap dia chi thay doi : ";
						string address;
						getline(cin, address);
						contactList[i].setAddress(address);
						cout << endl;
					}
					else if (ch == "5") {
						cout << "Nhap cong ty thay doi : ";
						string company;
						getline(cin, company);
						contactList[i].setCompany(company);
						cout << endl;
					}
					else if (ch == "6") {
						cout << "Nhap quan he thay doi : ";
						string relatives;
						getline(cin, relatives);
						contactList[i].setRelatives(relatives);
						cout << endl;
					}
					else if (ch == "0") {
						cout << "Thoat chinh sua!" << endl;
						cout << endl;
						break;
					}
				}
				cout << "Thong tin sau khi chinh sua : " << endl;
				contactList[i].displayContact();
			}
		}
	}
	void deleteContact() {
		cout << "Nhap so dien thoai nguoi lien he ban muon xoa : ";
		string sdt;
		getline(cin, sdt);
		while (!checkPhoneNumber(sdt) || !phoneNumberCheck.count(sdt)) {
			cout << "So dien thoai khong hop le, vui long nhap lai : ";
			getline(cin, sdt);
		}
		for (int i = 0; i < contactList.size(); i++) {
			if (contactList[i].getPhoneNumber() == sdt) {
				contactList.erase(contactList.begin() + i);
				cout << "Xoa tai khoan thanh cong ! ";
			}
		}
		cout << endl;
		cout << "Danh sach nguoi lien he sau khi chinh sua : " << endl;
		viewContactList();
	}
	void addRelationship() {
		cout << "Nhap so dien thoai nguoi lien he ban muon them contact : ";
		string sdt;
		getline(cin, sdt);
		while (!checkPhoneNumber(sdt) || !phoneNumberCheck.count(sdt)) {
			cout << "So dien thoai khong hop le, vui long nhap lai : ";
			getline(cin, sdt);
		}
		cout << "Nhap moi lien he : ";
		string rela;
		getline(cin, rela);
		while (!checkUsername(rela)) {
			cout << "Moi lien he khong hop le, vui long nhap lai : ";
			getline(cin, rela);
		}
		for (int i = 0; i < contactList.size(); i++) {
			if (contactList[i].getPhoneNumber() == sdt) {
				contactList[i].setRelatives(rela);
			}
		}
		cout << "Danh sach nguoi lien he sau khi chinh sua : ";
		viewContactList();
	}

	////Group Features
	void showGroupList() {
		for (int i = 0; i < groupList.size(); i++) {
			cout << "===============================" << endl;
			cout << groupList[i] << endl;
			cout << "===============================" << endl;
		}
	}
	void makeGroup() {
		srand(time(NULL));
		Group group;
		int id = rand() % 900 + 100;
		while (groupIDCheck.count(to_string(id))) {
			id = rand() % 900 + 100;
		}
		group.id = "G" + to_string(id);
		string name;
		getline(cin, name);
		while (groupNameCheck.count(name)) {
			cout << "Trung ten group, vui long nhap lai : ";
			getline(cin, name);
		}
		group.name = name;
		cout << "Group da tao !" << endl;
		cout << "Group ID : " << group.id << endl;
		cout << "Group Name : " << group.name << endl;
		cout << "Group Member : " << group.member.size() << endl;
	}
	void deleteGroup() {
		cout << "Nhap ten nhom ban muon xoa : ";
		string name;
		getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom !, vui long nhap lai : ";
			getline(cin, name);
		}
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name){
				groupList.erase(groupList.begin() + i);
				cout << "Xoa nhom thanh cong ! " << endl;
			}
		}
		showGroupList();
	}
	void addMemberToGroup() {
		cout << "Nhap ten nhom : ";
		string name; getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom, vui long nhap lai : ";
			getline(cin, name);
		}
		cout << "Nhap so dien thoai Contact ban muon them vao nhom : ";
		string sdt; getline(cin, sdt);
		while (!phoneNumberCheck.count(sdt)) {
			cout << "So dien thoai khong ton tai, vui long nhap lai : ";
			getline(cin, sdt);
		}
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				for (int i = 0; i < contactList.size(); i++) {
					if (contactList[i].getPhoneNumber() == sdt) {
						groupList[i].member.push_back(contactList[i]);
						break;
					}
				}
			}
		}
		cout << "Nhom sau khi add : " << endl;
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				for (int i = 0; i < groupList[i].member.size(); i++) {
					cout << "=================================" << endl;
					groupList[i].member[i].displayContact();
					cout << "=================================" << endl;
				}
			}
		}
	}
};

class System {
private:
	vector<User> userList;
public:
	void registerAccount() {
		User x;
		cin >> x;
		userList.push_back(x);
	}
	void showMenu() {
		cout << "=======PHONEBOOK MANAGEMENT SYSTEM========" << endl;
		cout << "Moi chon vai tro he thong : " << endl;
		cout << "1.Khach" << endl;
		cout << "2.Nguoi Dung" << endl;
		cout << "3.Admin" << endl;
		cout << "==========================================" << endl;
	}
};

int main()
{

}





bool checkUsername(string username) {
	if (isdigit(username[0])) return false;
	return true;
}
bool checkPassword(string password) {
	if (password.length() < 8) return false;
	for (int i = 0; i < password.size(); i++) {
		if (kiTuDacBiet(password[i])) {
			return true;
		}
	}
	return false;
}
bool checkEmail(string email) {
	for (int i = 0; i < email.length(); i++) {
		if (email[i] == '@') {
			return true;
		}
	}
	return false;
}
bool checkPhoneNumber(string phoneNumber) {
	if (phoneNumber.size() != 10) return false;
	for (int i = 0; i < phoneNumber.size(); i++) {
		if (!isdigit(phoneNumber[i])) {
			return false;
		}
	}
	return true;
}
void chuanHoaTen(string& ten) {
	stringstream ss(ten);
	string tmp;
	string res = "";
	while (ss >> tmp) {
		res += toupper(tmp[0]);
		for (int i = 1; i < tmp.size(); i++) {
			res += tolower(tmp[i]);
		}
		res += " ";
	}
	res.pop_back();
	ten = res;
}
bool checkContactID(string contactID) {
	for (int i = 0; i < contactID.size(); i++) {
		if (!isdigit(contactID[i])) {
			return false;
		}
	}
	return true;
}
