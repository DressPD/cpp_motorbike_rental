#include <iostream>
#include <cstdlib>
#include <list>     // for reservations
#include <vector>   // for customers
#include <string>
#include <iterator> 
#include <fstream>

using namespace std;

class Moto {    // class of the motorbike
    private:
    string model;
    bool reserved;

    public:
    Moto() {}
    Moto(string m) {
        model = m;
        reserved = false;
    }

    // setters
    void setModel(string m) {
        model = m;
    }
    void setReserved(bool r) {      // to track reservations
        reserved = r;
    }

    // getters
    string getModel() {
        return model;
    }
    bool getReserved() {
        return reserved;
    }

};

class Customer {    // class customer
    private:    // attributes
    string name, surname, address, telephone;
    int YoB;
    bool license, reserving=false;  // no reservation by default
    Moto moto = Moto("NULL");   // default dummy moto if without reservation

    public:     // methods
    Customer() {}
    Customer(string n, string s, string a, string t, int y, bool l, bool r, string m) { // constructor with parameters
        name = n;
        surname = s;
        address = a;    // I could have decomposed the address in street, postal code, city, but I think it will not affect the program
        telephone = t;
        YoB = y;
        license = l;
        reserving = r;
        moto = Moto(m);
    }
    
    // setters:
    void setName(string n) {
        name = n;
    }
    void setSurname(string s) {
        surname = s;
    }
    void setAddress(string a) {
        address = a;
    }
    void setTelephone(string t) {
        telephone = t;
    }
    void setYoB(int y) {
        YoB = y;
    }
    void setLicense(bool l) {
        license = l;
    }
    void setReserving(bool r) {
        reserving = r;
    }
    void setMoto(Moto m) {
        moto = m;
    }

    // getters:
    string getName() {
        return name;
    }
    string getSurname() {
        return surname;
    }
    string getAddress() {
        return address;
    }
    string getTelephone() {
        return telephone;
    }
    int getYoB() {
        return YoB;
    }
    bool getLicense() {
        return license;
    }
    bool getReserving() {
        return reserving;
    }
    Moto getMoto() {
        return moto;
    }

    // stream operator overloading:
    friend ostream &operator<<(ostream &os, Customer &c);
    friend istream &operator>>(istream &is, Customer &c);

};

list<Customer> CL;   // global list to track reservations;
vector<Customer> CV;    // global vector to track customers

ostream &operator<<(ostream &os, Customer &c) {     // ostream output + operator << overloading
    os << c.getName() << "\t"  << c.getSurname() << "\t"  << c.getYoB() <<
        "\t"  << c.getAddress() << "\t"  << c.getTelephone() << "\t"  << c.getLicense() <<
        "\t"  << c.getReserving() << "\t" << c.getMoto().getModel() << endl;
    return os;
}

istream &operator>>(istream &is, Customer &c) {     //istream input + operator >> overloading
    string s;
    int y;
    bool v;
    cout << "name: ";
    cin >> s;
    c.setName(s);
    cout << "surname: ";
    cin >> s;
    c.setSurname(s);
    cout << "address (one word): ";
    cin >> s;
    c.setAddress(s);
    cout << "telephone: ";
    cin >> s;
    c.setTelephone(s);
    cout << "year of birth (yyyy): ";
    cin >> y;
    c.setYoB(y);
    cout << "license (1=true/0=false): ";
    cin >> v;
    c.setLicense(v);
    return is;
}

void showList(list<Customer>& C) {   // Declaration of the showList function
    list<Customer>::iterator i;
    cout << "name" << "\t"  << "surname" << "\t"  << "year" <<     // headers
        "\t"  << "address" << "\t"  << "telephone" << "\t" << "license A" <<
        "\t"  << "reservation" << "\t" << "model" << endl;
    for (i=C.begin(); i != C.end(); ++i) {
        cout << *i;
        cout << endl;
    }
    cout << endl;
}

void showVector(vector<Customer>& C) {   // Declaration of the showVector function
    vector<Customer>::iterator i;
    cout << "name" << "\t"  << "surname" << "\t"  << "year" <<     // headers
        "\t"  << "address" << "\t"  << "telephone" << "\t" << "license A" <<
        "\t"  << "reservation" << "\t" << "model" << endl;
    for (i=C.begin(); i != C.end(); ++i) {
        cout << *i;
        cout << endl;
    }
    cout << endl;
}

list<Customer>::iterator returnListIterator(list<Customer>& C, string t) {      // return iterator based on name
    list<Customer>::iterator i;
    for (i=C.begin(); i != C.end(); ++i) {
        if (i->getName() == t) {    // getter and equality of string
            cout << "customer " << i->getName() << " found" << endl << endl;
            return i;
        }
    }
    cout << "customer not found..." << endl << endl;
}

vector<Customer>::iterator returnVectorIterator(vector<Customer>& C, string t) {      // return iterator based on name
    vector<Customer>::iterator i;
    for (i=C.begin(); i != C.end(); ++i) {
        if (i->getName() == t) {    // getter and equality of string
            cout << "customer " << i->getName() << " found" << endl << endl;
            return i;
        }
    }
    cout << "customer not found..." << endl << endl;
}

void listInitialize() // read and load the reservations file
{
	string name, surname, address, telephone, model;
    int YoB;
    bool license, reserving;
	Customer *c;

	ifstream fileReader("reservations.txt", ios::out);

	if(fileReader.good())
    {
		while(fileReader >> name >> surname >> address >> telephone >> YoB >> license >> reserving >> model)    // extract attributed
    	{
			c = new Customer(name, surname, address, telephone, YoB, license, reserving, model);
        	CL.push_back(*c);   // last element of list
     	}
    }
    fileReader.close();
}

void vectorInitialize() // read and load the customers file
{
	string name, surname, address, telephone, model;
    int YoB;
    bool license, reserving;
	Customer *c;

	ifstream fileReader("customers.txt", ios::out);

	if(fileReader.good())
    {
		while(fileReader >> name >> surname >> address >> telephone >> YoB >> license >> reserving >> model)    // extract attributes
    	{
			c = new Customer(name, surname, address, telephone, YoB, license, reserving, model);
        	CV.push_back(*c);   // last element of vector
     	}
    }
    fileReader.close();
}

int main() {
    Moto mo[4] = {Moto("Suzuki"), Moto("Honda"), Moto("BMW"), Moto("Kawasaki")};    //array of motos
    Customer *c = new Customer();
    string name;
    list<Customer>::iterator itl;   // list iterator
    vector<Customer>::iterator itv;     // vector iterator
    int select, m;
    ofstream writer;    // for file output

    listInitialize();     // read files and initialize list and vector
    vectorInitialize();

    do
    {
        cout << "--- MENU ---" << endl;     // print iterative menu based on user needs
        cout << "--- SELECT YOUR TASK ---" << endl;
        cout << "[1] Insert a new costumer" << endl;
        cout << "[2] Show customers" << endl;
        cout << "[3] Reserve a bike" << endl;
        cout << "[4] Terminate a reservation" << endl;
        cout << "[5] Show reservations" << endl;
        cout << "[0] exit the program" << endl;
        cout << endl << "Please select: ";
        cin >> select;
        switch(select)
        {
        case 1:     // insert a new customer
            {
                cout << "insert a new customer: " << endl;
                cin >> *c;
                CV.push_back(*c);
                cout << endl;
                break;
            }
        case 2:     // print vectors of customers (with function)
            {
                if (CV.empty()==true) {
                    cout << "there are no customers..." << endl << endl;
                    break;
                }
                else
                    showVector(CV);     // print vector of customers
                break;
            }
        case 3:     // create a reservation
            {
                int choice;
                cout << "[1] new costumer" << endl;
                cout << "[2] existing customers" << endl;
                cin >> choice;
                if (choice==1)  // new costumer
                {
                    cout << "insert a new customer: " << endl;
                    cin >> *c;
                    CV.push_back(*c);   // insert customer in vector
                    if (c->getLicense()==false)     // check license
                        cout << "the customer does not have a license" << endl;
                    else {      // if license is true
                        cout << "select the motorbike..." << endl;
                        cout << "[1] Suzuki" << endl;
                        cout << "[2] Honda" << endl;
                        cout << "[3] BMW" << endl;
                        cout << "[4] Kawasaki" << endl;  
                        cin >> m;
                        if (mo[m-1].getReserved()==true) {      // check if motorbike is reserved
                            cout << mo[m-1].getModel() << " has already been rented";
                            break;
                        }
                        else if (m<1 || m>4) {      // check if model exists
                            cout << "the model does not exist";
                             break;
                        }
                        else {      // reserve moto
                            c->setMoto(mo[m-1]);
                            c->setReserving(true);
                            mo[m-1].setReserved(true);
                        }
                        CL.push_back(*c);
                        cout.setstate(ios_base::failbit);   // to temporarily silence cout
                        itv=returnVectorIterator(CV, c->getName());
                        cout.clear();   // to restart printing of cout
                        itv->setMoto(c->getMoto());
                        itv->setReserving(true);
                        break;
                    } 
                }
                else if (choice==2)     // existing customer
                {
                    showVector(CV);     // show customers
                    if (CV.empty()==true) {
                        cout << "there are no existing customers..." << endl << endl;
                        break;
                    }
                    else {
                        cout << "insert customer name of the reservation to book: ";
                        cin >> name;
                        itv = returnVectorIterator(CV, name);
                        if (itv->getReserving()==true)      // if customer already reserving
                            cout << "the customer has already a reservation" << endl;
                        else {
                            if (itv->getLicense()==false)   // check license
                                cout << "the customer does not have a license" << endl << endl;
                            else {      // insert reservation
                                cout << "select the motorbike..." << endl;
                                cout << "[1] Suzuki" << endl;
                                cout << "[2] Honda" << endl;
                                cout << "[3] BMW" << endl;
                                cout << "[4] Kawasaki" << endl;
                                cin >> m;
                                if (mo[m-1].getReserved()==true) {      // check if motorbike reserved
                                    cout << mo[m-1].getModel() << " has already been rented" << endl;
                                    break;
                                }
                                else if (m<1 || m>4) {      // check if model exists
                                    cout << "the model does not exist" << endl;
                                    break;
                                }
                                else {      // inser reservation
                                    itv->setMoto(mo[m-1]);      // set moto in vector and customer precedently created
                                    itv->setReserving(true);
                                    mo[m-1].setReserved(true);
                                }
                                CL.push_back(*itv);
                                break;
                            }
                        }
                    break;
                    }
                }
                else    // wrong selection
                {
                    cout << "sorry my friend, you did not select the correct number... Try again!" << endl;
                }
                break;
            }
        case 4:     // delete a reservation
            {
                showList(CL);    // print present reservations
                cout << "insert customer name of the reservation to conclude: ";
                cin >> name;
                itl = returnListIterator(CL, name);     // return iterator of the name
                cout.setstate(ios_base::failbit);
                itv = returnVectorIterator(CV, name);   // return vector iterator
                cout.clear();
                CL.erase(itl);      // delete reservation
                itv->setReserving(false); // keep customer, but delete reservation
                itv->setMoto(Moto("NULL"));
                itv->getMoto().setReserved(false);
                break;
            }
        case 5:     // show reservations (with function)
            {
                if (CL.empty()==true) {
                    cout << "there are no reservations..." << endl << endl;
                    break;
                }
                else
                    showList(CL);   // print list of reservations
                break;
            }
        case 0:     // terminate the program and save customers and reservations
            {
                writer.open("customers.txt");   // print customers vector to external file
	                if(writer.good())
	                {
					    for (itv=CV.begin(); itv!=CV.end(); ++itv)  // iterate vector
					    {
					    	writer << *itv;     // write customers
					    }
					    if(CV.begin()!=CV.end())
					    	cout << "Customers vector saved to file customers.txt!" << endl;
				    	}
				    else
				    	cout << "customers.txt cannot be opened. Old list remains." << endl;
                writer.close();
            
                writer.open("reservations.txt");    // print reservations list to external file
	                if(writer.good())
	                {
					    for (itl=CL.begin(); itl!=CL.end(); ++itl)  // iterate list
					    {
					    	writer << *itl;     // write reservations
					    }
					    if(CL.begin()!=CL.end())
					    	cout << "Reservations list saved to file reservations.txt!" << endl;
					    }
				    else
				    	cout << "reservations.txt cannot be opened. Old list remains." << endl;
                writer.close();

	            cout << "Goodbye!" << endl;
	            break;
            }
        default:    // check what you digit
            {
                cout << endl << "Incorrect input!" << endl << endl;
            }
        }
    }
    while(select!=0);

    return 0;   // terminate main function

}