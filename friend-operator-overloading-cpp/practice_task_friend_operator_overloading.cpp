// practice_task_friend_operator_overloading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class TV {
	int channel;
	int volume;
	string source;
	bool power;
	string company;
public:
	TV(int c = 100, int v = 10, string s = "Cable", bool pow = true, string comp = "Sony") : channel(c), volume(v), source(s), power(pow), company(comp)
	{
	}

	TV(const TV& t1) {
		channel = t1.channel;
		volume = t1.volume;
		source = t1.source;
		power = t1.power;
		company = t1.company;
	}

	friend ostream& operator<<(ostream& o, const TV& t1);
	friend istream& operator>>(istream& i, TV& t1); //just did this for practice i knew yiu could make the entire class a frined but wanted to memorize the syantx
	//friend void Remote::v_increase(TV& t1); //just did this for practice
	//friend void Remote::v_decrease(TV& t1); //just did this for practice
	//friend void Remote::c_increase(TV& t1); //just did this for practice
	friend class Remote;

	void v_increase() {
		volume = volume + 1;
	}
	void v_decrease() {
		if (volume >= 1) {
			volume--;
		}
		else {
			volume = 100;
		}
	}
	void c_decrease() {
		if (channel > 1) {
			channel--;
		}
		else {
			channel = 100;
		}
	}
	void c_increase() {
		channel++;
	}
	void power_dec() {
		cout << "Eter 1 if you want to switch on \n";
		cin >> power;
	}

	void source_dec() {
		cout << "Eter 1 if you want to switch on \n";
		cin >> source;
	}
	void channel_jump()
	{
		cout << "Enter the channel you want to go to  = ";
		cin >> channel;
	}
	void volume_jump()
	{
		cout << "Enter the channel you want to go to  = ";
		cin >> volume;
	}
	void channel_jump(int x)
	{
		channel = x;
	}
	void volume_jump(int x)
	{
		volume = x;
	}

};

class Remote {
	string source;
	bool mute;
	bool pow;
	string company;

public:
	Remote(string so = "Cable", bool m = false, bool p = true, string co = "Sony") : mute(m), pow(p), company(co), source(so) {}

	Remote(const Remote& r1) {
		source = r1.source;
		pow = r1.pow;
		mute = r1.mute;
		company = r1.company;
	}

	void v_increase(TV& t1) {
		t1.volume = t1.volume + 1;
	}

	void v_decrease(TV& t1) {
		if (t1.volume > 1) {
			t1.volume--;
		}
		else {
			t1.volume = 100;
		}
	}
	void c_increase(TV& t1) {

		t1.channel++;
	}
	void c_decrease(TV& t1) {
		if (t1.channel >= 1) {
			t1.channel--;
		}
		else {
			t1.channel = 100;
		}
	}

	void mute_vol(TV& t1) {
		bool x;
		cout << "Eter 1 if you want to mute \n";
		cin >> x;
		if (x == true) {
			t1.volume = 0;
		}
	}
	void power_dec(TV& t1) {
		;
		cout << "Eter 1 if you want to switch on \n";
		cin >> pow;
		if (pow == true) {
			t1.power = 1;
		}
	}
	void source_1(TV& t1) {
		cout << "Enter the source =  ";
		cin >> source;
		t1.source = source;
	}
	void channel_jump(TV& t1)
	{
		cout << "Enter the channel you want to go to  = ";
		cin >> t1.channel;
	}
	void volume_jump(TV& t1)
	{
		cout << "Enter the channel you want to go to  = ";
		cin >> t1.volume;
	}
	void volume_jump(TV& t1, int x)
	{
		t1.volume = x;
	}
	void channel_jump(TV& t1, int x)
	{
		t1.channel = x;
	}

	friend ostream& operator<<(ostream& o, const Remote& r1) {
		o << "Pow = " << r1.pow << "\n" << "Source" << r1.source << "\n" << "Company = " << r1.company << "\n";
		return o;
	}
	friend istream& operator>>(istream& i, Remote& r1) {
		i >> r1.pow >> r1.source >> r1.company;
		return i;
	}


};








//void Remote::v_increase(TV& t1) {
//	t1.volume=t1.volume+1;
//}
//
//void Remote::v_decrease(TV& t1) {
//	t1.volume--;
//}
//void Remote:: c_increase(TV& t1) {
//	t1.channel--;
//}


ostream& operator<<(ostream& o, const TV& t1) {
	o << "Company = " << t1.company << "\n" << "Channel = " << t1.channel << "\n" << "Volume = " << t1.volume << "\n" << "Source = " << t1.source << "\n" << "Power = " << t1.power << "\n";
	return o;
}
istream& operator>>(istream& i, TV& t1) {
	cout << "Input the name of the company \n Input the starting channel \n Input the starting volume \n Input type of source \n Enter if 1 or 0 ";
	i >> t1.company >> t1.channel >> t1.volume >> t1.source >> t1.power;
	return i;
}


int main() {
	
	TV t;
	cout << t << endl;

	
	Remote r;
	
	cout << r << endl;

	
	r.channel_jump(t, 25);
	
	cout << t << endl;


	r.v_increase(t);
	cout << t << endl;

	
	r.v_decrease(t);
	cout << t << endl;

	
	cout << t << endl;


	r.source_1(t);
	cout << t << endl;


	TV g = t;
	cout << g << endl;

	
	r.channel_jump(g, 1);
	cout << g << endl;


	r.c_decrease(g);
	cout << g << endl;

	
	r.c_decrease(g);
	
	cout << g << endl;


	cout << g << endl;

	
	Remote s = r;
	cout << s << endl;


	cout << t << endl;


	cout << s << endl;

	return 0;
}

