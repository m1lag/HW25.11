#include <iostream>
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
	TelephoneBook(const string& name, const string& homePhone, const string& workPhone, const string& mobilePhone, const string& additionalInformation)
		: m_name(name)
		, m_homePhone(homePhone)
		, m_workPhone(workPhone)
		, m_mobilePhone(mobilePhone)
		, m_additionalInformation(additionalInformation)
	{
    
    }

    const string& getName() const
    {
        return m_name;
    }

    const string& getHomePhone() const
    {
        return m_homePhone;
    }

    const string& getWorkPhone() const
    {
        return m_workPhone;
    }

    const string& getMobilePhone() const
    {
        return m_mobilePhone;
    }

    const string& getAdditionalInformation() const
    {
        return m_additionalInformation;
    }

    void setName(const string& name)
    {
        m_name = name;
    }

    void setHomePhone(const string& homePhone)
    {
        m_homePhone = homePhone;
    }

    void setWorkPhone(const string& workPhone)
    {
        m_workPhone = workPhone;
    }

    void setMobilePhone(const string& mobilePhone)
    {
        m_mobilePhone = mobilePhone;
    }

    void setAdditionalInformation(const string& additionalInformation)
    {
        m_additionalInformation = additionalInformation;
    }

    void dataEntry() const
    {
        cout << "Name: " << m_name << endl;
        cout << "Home Phone: " << m_homePhone << endl;
        cout << "Work Phone: " << m_workPhone << endl;
        cout << "Mobile Phone: " << m_mobilePhone << endl;
        cout << "Additional Information: " << m_additionalInformation << endl;
    }
};

int main()
{
	TelephoneBook markWahlberg("Mark Wahlberg", "44444444444", "4", "*", "Actor, producer");

	cout << "Mark Wahlberg's Info:" << endl;
	markWahlberg.dataEntry();

	markWahlberg.setHomePhone("807879");
	markWahlberg.setWorkPhone("32435345");
	markWahlberg.setMobilePhone("1");

	cout << "\nUpdated Mark Wahlberg's Info:" << endl;
	markWahlberg.dataEntry();

}