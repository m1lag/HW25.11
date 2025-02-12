#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TelephoneBook
{
    string m_name;
    string m_homePhone;
    string m_workPhone;
    string m_mobilePhone;
    string m_additionalInformation;

public:
    TelephoneBook(const string& name = "", const string& homePhone = "", const string& workPhone = "",
        const string& mobilePhone = "", const string& additionalInformation = "")
        : m_name(name), m_homePhone(homePhone), m_workPhone(workPhone), m_mobilePhone(mobilePhone), m_additionalInformation(additionalInformation)
    {
    }

    const string& getName() const { return m_name; }

    const string& getHomePhone() const { return m_homePhone; }
    const string& getWorkPhone() const { return m_workPhone; }
    const string& getMobilePhone() const { return m_mobilePhone; }
    const string& getAdditionalInformation() const { return m_additionalInformation; }

    void setName(const string& name) { m_name = name; }
    void setHomePhone(const string& homePhone) { m_homePhone = homePhone; }
    void setWorkPhone(const string& workPhone) { m_workPhone = workPhone; }
    void setMobilePhone(const string& mobilePhone) { m_mobilePhone = mobilePhone; }
    void setAdditionalInformation(const string& additionalInformation) { m_additionalInformation = additionalInformation; }

    void dataEntry() const
    {
        cout << "Name: " << m_name << endl;
        cout << "Home Phone: " << m_homePhone << endl;
        cout << "Work Phone: " << m_workPhone << endl;
        cout << "Mobile Phone: " << m_mobilePhone << endl;
        cout << "Additional Information: " << m_additionalInformation << endl;
    }

    void serialize(ofstream& ofs) const
    {
        ofs << m_name << '\n' << m_homePhone << '\n' << m_workPhone << '\n' << m_mobilePhone << '\n' << m_additionalInformation << '\n';
    }

    void deserialize(ifstream& ifs)
    {
        getline(ifs, m_name);
        getline(ifs, m_homePhone);
        getline(ifs, m_workPhone);
        getline(ifs, m_mobilePhone);
        getline(ifs, m_additionalInformation);
    }
};

class PhoneBookManager
{
    TelephoneBook* m_contacts[100];
    int m_contactCount;

public:
    PhoneBookManager() : m_contactCount(0) { for (int i = 0; i < 100; ++i) m_contacts[i] = nullptr; }

    ~PhoneBookManager()
    {
        for (int i = 0; i < m_contactCount; ++i)
        {
            delete m_contacts[i];
        }
    }

    void addContact(const TelephoneBook& contact)
    {
        if (m_contactCount < 100)
        {
            m_contacts[m_contactCount] = new TelephoneBook(contact);
            m_contactCount++;
        }
        else
        {
            cout << "Full!" << endl;
        }
    }

    void removeContact(const string& name)
    {
        for (int i = 0; i < m_contactCount; ++i)
        {
            if (m_contacts[i] && m_contacts[i]->getName() == name)
            {
                delete m_contacts[i];
                for (int j = i; j < m_contactCount - 1; ++j)
                {
                    m_contacts[j] = m_contacts[j + 1];
                }
                m_contacts[m_contactCount - 1] = nullptr;
                m_contactCount--;
                cout << "Contact " << name << " removed" << endl;
                return;
            }
        }
        cout << "Contact " << name << " not found" << endl;
    }

    void searchContact(const string& name) const
    {
        for (int i = 0; i < m_contactCount; ++i)
        {
            if (m_contacts[i] && m_contacts[i]->getName() == name)
            {
                m_contacts[i]->dataEntry();
                return;
            }
        }
        cout << "Contact " << name << " not found" << endl;
    }

    void showAllContacts() const
    {
        if (m_contactCount == 0)
        {
            cout << "No contacts available" << endl;
            return;
        }
        for (int i = 0; i < m_contactCount; ++i)
        {
            if (m_contacts[i])
            {
                m_contacts[i]->dataEntry();
                cout << "-------------------" << endl;
            }
        }
    }

    void saveToFile(const string& filename) const
    {
        ofstream ofs(filename);
        if (!ofs)
        {
            cout << "Error opening file for writing." << endl;
            return;
        }
        ofs << m_contactCount << '\n';
        for (int i = 0; i < m_contactCount; ++i)
        {
            m_contacts[i]->serialize(ofs);
        }
    }

    void loadFromFile(const string& filename)
    {
        ifstream ifs(filename);
        if (!ifs)
        {
            cout << "Error opening file for reading." << endl;
            return;
        }
        int count;
        ifs >> count;
        ifs.ignore();
        for (int i = 0; i < count; ++i)
        {
            TelephoneBook* contact = new TelephoneBook();
            contact->deserialize(ifs);
            addContact(*contact);
            delete contact;
        }
    }
};

int main()
{
    PhoneBookManager phoneBookManager;

    TelephoneBook contact1("Mark Wahlberg", "44444444444", "52", "*", "Actor, producer");
    phoneBookManager.addContact(contact1);

    TelephoneBook contact2("John Smith", "525252525252", "3", "4242424242", "Friend");
    phoneBookManager.addContact(contact2);

    cout << "All Contacts:" << endl;
    phoneBookManager.showAllContacts();

    cout << "\nSearching for Mark Wahlberg:" << endl;
    phoneBookManager.searchContact("Mark Wahlberg");

    cout << "\nRemoving John Smith:" << endl;
    phoneBookManager.removeContact("John Smith");

    cout << "\nAll Contacts after removal:" << endl;
    phoneBookManager.showAllContacts();

    phoneBookManager.saveToFile("contacts.txt");

    PhoneBookManager newPhoneBookManager;
    newPhoneBookManager.loadFromFile("contacts.txt");

    cout << "\nAll Contacts loaded from file:" << endl;
    newPhoneBookManager.showAllContacts();
}
