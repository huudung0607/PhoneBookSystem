#include <fstream>
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
	bool login(string username, string password) {
		if (userAccountData.find(username) != userAccountData.end() && userAccountData[username] == password) {
			return true;
		}
		else return false;
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
		cout << "Nhap username tai khoan can mo khoa : ";
		string name;
		getline(cin, name);
		while (!usernameCheck.count(name)) {
			cout << "Khong tim thay ten, vui long nhap lai : ";
			getline(cin, name);
		}
		for (int i = 0; i < lockAccount.size(); i++) {
			if (lockAccount[i].getUsername() == name) {
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
		cout << "Nhap ma name tai khoan can khoa : ";
		string name;
		getline(cin, name);
		while (!usernameCheck.count(name)) {
			cout << "Khong tim thay name, vui long nhap lai : ";
			getline(cin, name);
		}
		for (int i = 0; i < unlockAccount.size(); i++) {
			if (unlockAccount[i].getUsername() == name) {
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
	void setContactID(string contactID) {
		this->contactID = contactID;
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
		return out;
	}
};
vector<Group> groupList;
set<string> groupIDCheck;
set<string> groupNameCheck;
/////////////////////////////////


class phoneBook {
private:
	string bookID;
	vector<Contact> contactList;
public:
	phoneBook() {};
	phoneBook(string bookID) {
		this->bookID = bookID;
	}
	/////PhoneBook Features
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
		else if (ch == "2") {
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
	void searchContact() {
		cout << "1. Tim theo ten : ";
		cout << "2. Tim theo sdt : ";
		string choice;
		getline(cin, choice);
		while (choice != "1" && choice != "2") {
			cout << "Khong hop le, vui long nhap lai ";
			getline(cin, choice);
		}
		if (choice == "1") {
			cout << "Nhap ten contact : ";
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
		}
		else {
			cout << "Nhap so dien thoai : ";
			string sdt;
			getline(cin, sdt);
			while (!checkPhoneNumber(sdt) || !phoneNumberCheck.count(sdt)) {
				cout << "So dien thoai khong hop le, vui long nhap lai : ";
				getline(cin, sdt);
			}
			for (int i = 0; i < contactList.size(); i++) {
				if (contactList[i].getPhoneNumber() == sdt) {
					contactList[i].displayContact();
				}
			}
		}
	}
	void viewContact() {
		cout << "1. Tim theo ten : ";
		cout << "2. Tim theo sdt : ";
		string choice;
		getline(cin, choice);
		while (choice != "1" && choice != "2") {
			cout << "Khong hop le, vui long nhap lai ";
			getline(cin, choice);
		}
		if (choice == "1") {
			cout << "Nhap ten contact : ";
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
		}
		else {
			cout << "Nhap so dien thoai : ";
			string sdt;
			getline(cin, sdt);
			while (!checkPhoneNumber(sdt) || !phoneNumberCheck.count(sdt)) {
				cout << "So dien thoai khong hop le, vui long nhap lai : ";
				getline(cin, sdt);
			}
			for (int i = 0; i < contactList.size(); i++) {
				if (contactList[i].getPhoneNumber() == sdt) {
					contactList[i].displayContact();
				}
			}
		}
	}
	////Group Features
	void showGroupList() {
		for (int i = 0; i < groupList.size(); i++) {
			cout << "===============================" << endl;
			cout << groupList[i] << endl;
			cout << "===============================" << endl;
		}
	}

	//tao nhom
	void makeGroup() {
		srand(time(NULL));
		Group group;
		int id = rand() % 900 + 100;
		while (groupIDCheck.count(to_string(id))) {
			id = rand() % 900 + 100;
		}
		group.id = "G" + to_string(id);
		groupIDCheck.insert(group.id);
		string name;
		cout << "Nhap ten nhom : ";
		getline(cin, name);
		while (groupNameCheck.count(name)) {
			cout << "Trung ten group, vui long nhap lai : ";
			getline(cin, name);
		}
		groupNameCheck.insert(name);
		group.name = name;
		groupList.push_back(group);
		cout << "Group da tao !" << endl;
		cout << "Group ID : " << group.id << endl;
		cout << "Group Name : " << group.name << endl;
		cout << "Group Member : " << group.member.size() << endl;
	}

	//xoa nhom
	void deleteGroup() {
		cout << "Nhap ten nhom ban muon xoa : ";
		string name;
		getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom !, vui long nhap lai : ";
			getline(cin, name);
		}
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				groupList.erase(groupList.begin() + i);
				cout << "Xoa nhom thanh cong ! " << endl;
			}
		}
		showGroupList();
	}

	//them thanh vien vao nhom
	void addMemberToGroup() {
		// Kiểm tra tên nhóm và số điện thoại có tồn tại hay không
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
		////////thêm 
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				for (int j = 0; j < contactList.size(); j++) {
					if (contactList[j].getPhoneNumber() == sdt) {
						groupList[i].member.push_back(contactList[j]);
						break;
					}
				}
				break;
			}
		}

		///// in ra
		cout << "Thanh vien nhom sau khi add : " << endl;
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				cout << groupList[i] << endl;
				for (int j = 0; j < groupList[i].member.size(); j++) {
					cout << "=================================" << endl;
					groupList[i].member[j].displayContact();
					cout << "=================================" << endl;
				}
			}
		}
	}

	//xoa thanh vien khoi nhom
	void deleteMemberFromGroup() {
		cout << "Nhap ten nhom : ";
		string name; getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom, vui long nhap lai : ";
			getline(cin, name);
		}
		cout << "Nhap so dien thoai Contact ban muon xoa khoi nhom : ";
		string sdt; getline(cin, sdt);
		while (!phoneNumberCheck.count(sdt)) {
			cout << "So dien thoai khong ton tai, vui long nhap lai : ";
			getline(cin, sdt);
		}
		bool found = false;
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				for (int j = 0; j < groupList[i].member.size(); j++) {
					if (groupList[i].member[j].getPhoneNumber() == sdt) {
						groupList[i].member.erase(groupList[i].member.begin() + j);
						found = true;
						cout << endl;
						break;
					}
				}
				break;
			}
		}
		if (!found) cout << "Nhom khong ton tai member co so dien thoai nay ! " << endl;
		cout << endl;
		cout << "Nhom sau khi xoa : " << endl;
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				for (int j = 0; j < groupList[i].member.size(); j++) {
					cout << "=================================" << endl;
					groupList[i].member[j].displayContact();
					cout << "=================================" << endl;
				}
			}
		}
	}

	//tim nhom
	void searchGroup() {
		cout << "Nhap ten nhom : ";
		string name; getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom, vui long nhap lai : ";
			getline(cin, name);
		}
		cout << endl;
		for (int i = 0; i < groupList.size(); i++) {
			if (groupList[i].name == name) {
				cout << groupList[i] << endl;
			}
		}
	}

	// tim thanh vien trong nhom
	void searchMemberInGroup() {
		cout << "Nhap ten nhom : ";
		string name; getline(cin, name);
		while (!groupNameCheck.count(name)) {
			cout << "Khong ton tai ten nhom, vui long nhap lai : ";
			getline(cin, name);
		}
		cout << endl;
		cout << "Nhap so dien thoai : ";
		string sdt; getline(cin, sdt);
		while (!checkPhoneNumber(sdt) || !phoneNumberCheck.count(sdt)) {
			cout << "So dien thoai khong ton tai : ";
			getline(cin, sdt);
		}
		bool found = false;
		for (int i = 0; i < groupList.size(); i++) {
			for (int j = 0; j < groupList[i].member.size(); j++) {
				if (groupList[i].member[j].getPhoneNumber() == sdt) {
					groupList[i].member[j].displayContact();
				}
			}
		}
		if (!found) cout << "Khong tim ra member trong nhom" << endl;
	}

	vector<Contact> getContactList() {
		return contactList;
	}

	void docContactList() {
		fstream input("ContactList.txt", ios::in);
		if (!input.is_open()) {
			cout << "Khong the mo file: " << endl;
			return;
		}
		vector<string> docFile;
		string line;
		while (getline(input, line)) {
			if (!line.empty()) {
				docFile.push_back(line);
			}
		}
		for (int i = 0; i < docFile.size() - 6; i += 7) {
			Contact contact;
			contact.setContactID(docFile[i].substr(13));
			if (userIDCheck.count(contact.getContactID()) || !checkContactID(contact.getContactID())) {
				if (userIDCheck.count(contact.getContactID())) {
					cout << "ContactID da ton tai, vui long nhap lai " << endl;
				}
				else cout << "ContactID : " << contact.getContactID() << " khong hop le" << endl;
			}	
			else {
				userIDCheck.insert(contact.getContactID());
				contact.setFullName(docFile[i + 1].substr(12));
				contact.setPhoneNumber(docFile[i + 2].substr(15));
				if (!checkPhoneNumber(contact.getPhoneNumber()) || phoneNumberCheck.count(contact.getPhoneNumber())) {
					continue;
				}
				contact.setEmail(docFile[i + 3].substr(8));
				if (!checkEmail(contact.getEmail()) || emailCheck.count(contact.getEmail())) {
					continue;
				}
				contact.setAddress(docFile[i + 4].substr(10));
				contact.setCompany(docFile[i + 5].substr(10));
				contact.setRelatives(docFile[i + 6].substr(12));
				phoneNumberCheck.insert(contact.getPhoneNumber());
				emailCheck.insert(contact.getEmail());
				contactList.push_back(contact);
			}
		}
		input.close();
	}
};


class System {
private:
	vector<User> userList;
public:
	System() {};
	void registerAccount() {
		User x;
		cin >> x;
		userList.push_back(x);
		unlockAccount.push_back(x);
	}
	void showMenu() {
		cout << "=======PHONEBOOK MANAGEMENT SYSTEM========" << endl;
		cout << "Moi chon vai tro he thong : " << endl;
		cout << "1.Khach" << endl;
		cout << "2.Nguoi Dung" << endl;
		cout << "3.Admin" << endl;
		cout << "==========================================" << endl;
	}
	vector<User> getUserList() {
		return userList;
	}
	void docFile() {
		fstream input("UserList.txt", ios::in);
		if (!input.is_open()) {
			cout << "Khong the mo file: " << endl;
			return;
		}
		string line;
		vector<string> tmp;
		while (getline(input, line)) {
			if (!line.empty()) {
				tmp.push_back(line);
			}
		}
		for (int i = 0; i < tmp.size() - 2; i += 3) {
			User x;
			x.setUsername(tmp[i].substr(11));
			x.setPassword(tmp[i + 1].substr(11));
			x.setEmail(tmp[i + 2].substr(8));
			usernameCheck.insert(x.getUsername());
			emailCheck.insert(x.getEmail());
			userList.push_back(x);
			unlockAccount.push_back(x);
			userAccountData.insert({ x.getUsername(),x.getPassword() });
		}
		input.close();
	}
};

int main()
{
	System system;
	bool straight = false;
	int cnt = 0;
	system.docFile();
	while (true) {
		if (cnt == 6) cnt = 0;
		cout << "=======PHONEBOOK MANAGEMENT SYSTEM========" << endl;
		cout << "Moi chon vai tro he thong : " << endl;
		cout << "1.Khach" << endl;
		cout << "2.Nguoi Dung" << endl;
		cout << "3.Admin" << endl;
		cout << "0. Exit " << endl;
		cout << "==========================================" << endl;
		cout << "Choice : ";
		string choice;
		getline(cin, choice);
		while (choice != "1" && choice != "2" && choice != "3" && choice != "0") {
			cout << "Lua chon khong hop le, vui long nhap lai : ";
			getline(cin, choice);
		}
		if (choice == "0") {
			cout << "Cam on ban da su dung" << endl;
			return 0;
		}
		if (choice == "1") {
			while (true) {
				cout << "Ban la khach " << endl;
				cout << "1. Dang ky " << endl;
				cout << "2. Dang nhap " << endl;
				cout << "0. Thoat " << endl;
				string ch;
				cout << "Choice : ";
				getline(cin, ch);
				while (ch != "1" && ch != "2" && ch != "0") {
					cout << "Vui long nhap lai :";
					getline(cin, ch);
				}
				if (ch == "0") {
					break;
				}
				if (ch == "1") {
					cout << "Ban la khach!" << endl;
					cout << "Tien hanh dang ky ! " << endl;
					system.registerAccount();
					straight = true;
					cout << endl;	
					cout << endl;
					break;
				}
				if (ch == "2") {
					cout << "Dang nhap" << endl;
					bool flag = false;
					string username, password;
					cout << "Username : ";
					getline(cin, username);
					cout << "Password : ";
					getline(cin, password);
					bool login = false;
					for (int i = 0; i < unlockAccount.size(); i++) {
						if (unlockAccount[i].getUsername() == username) {
							login = true;
						}
					}
					for (int i = 0; i < system.getUserList().size(); i++) {
						if (system.getUserList()[i].login(username, password) && login == true) {
							cout << "Dang nhap thanh cong !" << endl << endl;
							flag = true;
							straight = true;
							break;
						}
					}	
					if (flag == false || login == false) cout << "Dang nhap that bai !" << endl << endl;
					else break;
				}
			}
		}
		while (choice == "2" && cnt <= 5) {
			if(straight == true){
				int id = rand() % 9000 + 1000;
				phoneBook userBook(to_string(id));
				//doc contactList co san
				userBook.docContactList();
				//
				while (true) {
					cout << "\n=================================================" << endl;
					cout << "CHUC NANG QUAN LY DANH BA" << endl;
					cout << "1. Them lien he" << endl;
					cout << "2. Chinh sua lien he" << endl;
					cout << "3. Xoa lien he" << endl;
					cout << "4. Tim kiem lien he" << endl;
					cout << "5. Hien thi danh sach lien he (A-Z)" << endl;
					cout << "6. Xem lien he chi tiet" << endl;
					cout << "7. Them nhom" << endl;
					cout << "8. Them quan he" << endl;
					cout << "9. Quan ly nhom" << endl;
					cout << "10. Thoat" << endl;
					cout << "=================================================" << endl;
					cout << "Choice : ";
					string choice;
					getline(cin, choice);
					while (choice != "1" && choice != "2" && choice != "3" && choice != "4" &&
						choice != "5" && choice != "6" && choice != "7" && choice != "8" && choice != "9" && choice != "10") {
						cout << "Lua chon khong hop le, vui long nhap lai : ";
						getline(cin, choice);
					}
					if (choice == "1") {
						userBook.addContact();
					}
					else if (choice == "2") {
						userBook.editContact();
					}
					else if (choice == "3") {
						userBook.deleteContact();
					}
					else if (choice == "4") {
						userBook.searchContact();
					}
					else if (choice == "5") {
						userBook.sortContactByName();
					}
					else if (choice == "6") {
						userBook.viewContact();
					}
					else if (choice == "7") {
						userBook.makeGroup();
					}
					else if (choice == "8") {
						userBook.addRelationship();
					}
					else if (choice == "9") {
						while (true) {
							cout << "\n=== QUAN LY NHOM ===\n";
							cout << "1. Hien thi danh sach nhom\n";
							cout << "2. Them thanh vien vao nhom\n";
							cout << "3. Xoa thanh vien khoi nhom\n";
							cout << "4. Tim nhom\n";
							cout << "5. Tim thanh vien trong nhom\n";
							cout << "6. Xoa nhom\n";
							cout << "0. Quay lai\n";
							cout << "Choice: ";
							string groupChoice;
							getline(cin, groupChoice);
							while (groupChoice != "1" && groupChoice != "2" && groupChoice != "3" && groupChoice != "4" &&
								groupChoice != "5" && groupChoice != "6" && groupChoice != "0") {
								getline(cin, groupChoice);
							}
							if (groupChoice == "1") {
								userBook.showGroupList();
							}
							else if (groupChoice == "2") {
								userBook.addMemberToGroup();
							}
							else if (groupChoice == "3") {
								userBook.deleteMemberFromGroup();
							}
							else if (groupChoice == "4") {
								userBook.searchGroup();
							}
							else if (groupChoice == "5") {
								userBook.searchMemberInGroup();
							}
							else if (groupChoice == "6") {
								userBook.deleteGroup();
							}
							else if (groupChoice == "0") {
								break;
							}
						}
					}
					else if (choice == "10") break;
				}
			}
			else {
				cout << "Ban la nguoi dung !" << endl;
				cout << "Username : ";
				string username;
				getline(cin, username);
				string password;
				cout << "Password : ";
				getline(cin, password);
				bool flag = false;
				bool login = false;
				for (int i = 0; i < unlockAccount.size(); i++) {
					if (unlockAccount[i].getUsername() == username){
						login = true;
					}
				}
				for (int i = 0; i < system.getUserList().size(); i++) {
					if (system.getUserList()[i].login(username, password) && login == true) {
						cout << "Dang nhap thanh cong !" << endl << endl;
						cout << endl;
						flag = true;
						straight = true;
						break;
					}
				}
				if (flag == false || login == false) {
					cout << "Dang nhap that bai !" << endl << endl;
					straight = false;
					cnt++;
				}
			}
		}
		while (choice == "3") {
			string username, password;
			cout << "Username : ";
			getline(cin, username);
			cout << "Password : ";
			getline(cin,password);
			bool flag = false;
			if (username.find("admin") != string::npos && password.find("admin") != string::npos
				|| username.find("Admin") != string::npos && password.find("Admin") != string::npos ||
				username.find("admin") != string::npos && password.find("Admin") != string::npos ||
				username.find("admin") != string::npos && password.find("Admin") != string::npos) {
				cout << "Dang nhap thanh cong ! " << endl << endl;
				flag = true;
			}
			if (flag == false) {
				cout << "Dang nhap that bai ! " << endl << endl;
				break;
			}
			while (true) {
				Admin admin;
				cout << "1. Mo khoa tai khoan " << endl;
				cout << "2. Khoa tai khoan " << endl;
				cout << "0. Thoat" << endl;
				string ch;
				getline(cin, ch);
				while (ch != "1" && ch != "2" && ch != "0") {
					cout << "Lua chon khong hop le, vui long nhap lai";
					getline(cin, ch);
				}
				if (ch == "1") {
					admin.UnlockAccount();
					cout << "Mo khoa tai khoan thanh cong" << endl;
				}
				else if (ch == "2") {
					cout << "Khoa tai khoan thanh cong" << endl;
				}
				else if (ch == "0") {
					break;
				}
			}
		}
	}
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
