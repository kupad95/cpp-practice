// A simple program to practice defining classes and methods that takes in the hour, minute and second in 24-hour time, and calls on a method to display the output in 12-hour and 24-hour time

#include<iostream>
using namespace std;

class Time // Changed class name to start with an uppercase letter (convention)
{
    int m, s, h;

public:
    void get(int p, int q, int r)
    {
        h = p;
        m = q;
        s = r;
    }

    void display()
    {
        // Corrected the condition for 12-hour format
        if (h < 12)
        {
            if (h == 0) // Handle midnight (0:00:00)
            {
                cout << "12-hour time is 12:" << m << ":" << s << "am" << endl;
                cout << "24-hour time is 00:" << m << ":" << s;
            }
            else
            {
                cout << "12-hour time is " << h << ":" << m << ":" << s << "am" << endl;
                cout << "24-hour time is " << h << ":" << m << ":" << s;
            }
        }
        else
        {
            if (h == 12) // Handle noon (12:00:00)
            {
                cout << "12-hour time is 12:" << m << ":" << s << "pm" << endl;
                cout << "24-hour time is 12:" << m << ":" << s;
            }
            else
            {
                cout << "12-hour time is " << (h - 12) << ":" << m << ":" << s << "pm" << endl;
                cout << "24-hour time is " << h << ":" << m << ":" << s;
            }
        }
        cout << endl;
    }
};

int main()
{
    int p, q, r;
    Time t; // Changed class name here as well

    cout << "Enter hour (24-hour time): ";

    while (!(cin >> p) || p >= 24 || p < 0) // Corrected the condition for valid hours
    {
        cout << "You input an invalid value. Try again: ";
        cin.clear();
        cin.ignore(123, '\n');
    };

    cout << "Enter minute: ";
    while (!(cin >> q) || q >= 60 || q < 0)
    {
        cout << "You input an invalid value. Try again: ";
        cin.clear();
        cin.ignore(123, '\n');
    };

    cout << "Enter seconds: ";
    while (!(cin >> r) || r >= 60 || r < 0)
    {
        cout << "You input an invalid value. Try again: ";
        cin.clear();
        cin.ignore(123, '\n');
    };

    t.get(p, q, r);
    t.display();

    return 0;
}
