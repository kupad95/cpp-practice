# include<iostream>
using namespace std;

class time
{
	int m,s,h;
	public:
		void get(int p,int q,int r)
		{
			h=p;
			m=q;
			s=r;
		}
		void display()
		{ if(h < 13){
			cout<<"12-hour time is "<<h<<":"<<m<<":"<<s <<"am"<< endl;
			cout<<"24-hour time is "<<h<<":"<<m<<":"<<s;
		} else {
			cout<<"12-hour time is "<<(h - 12)<<":"<<m<<":"<<s <<"pm"<< endl;
			cout<<"24-hour time is "<<h<<":"<<m<<":"<<s;
		}
		}
};

int main()

{
	int p,q,r;
	time t;

	cout<<"Enter hour (24-hour time): ";

	while (!(cin >> p) || p > 24 || p < 1)
	{
		cout<<"You input a stupid value. Try again: ";
		cin.clear();
		cin.ignore(123, '\n');
	};

	cout<<"Enter minute: ";
	while (!(cin >> q) || q > 60 || q < 0)
	{
		cout<<"You input a stupid value. Try again: ";
		cin.clear();
		cin.ignore(123, '\n');
	};

	cout<<"Enter seconds: ";
	while (!(cin >> r) || r > 60 || r < 0)
	{
		cout<<"You input a stupid value. Try again: ";
		cin.clear();
		cin.ignore(123, '\n');
	};

	t.get(p,q,r);
	t.display();

	return 0;
}